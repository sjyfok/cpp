using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace ICIDECode.Core
{
    /// <summary>
	/// This service is used to summarize important information
	/// about the state of the application when an exception occurs.
	/// </summary>
	[SDService]
    public class ApplicationStateInfoService
    {
        readonly Dictionary<string, Func<object>> stateGetters = new Dictionary<string, Func<object>>(StringComparer.InvariantCulture);

        /// <summary>
		/// Gets a snapshot of the current application state information from all registered state getters.
		/// </summary>
		/// <returns>A dictionary with the titles and results of all registered state getters.</returns>
		[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1024:UsePropertiesWhereAppropriate")]
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1031:DoNotCatchGeneralExceptionTypes")]
        public IReadOnlyDictionary<string, object> GetCurrentApplicationStateInfo()
        {
            Dictionary<string, object> state = new Dictionary<string, object>(stateGetters.Count, stateGetters.Comparer);
            lock (stateGetters)
            {
                foreach (var entry in stateGetters)
                {
                    try
                    {
                        state.Add(entry.Key, entry.Value());
                    }
                    catch (Exception ex)
                    {
                        state.Add(entry.Key, ex);
                    }
                }
            }
            return state;
        }

        /// <summary>
		/// Appends the current application state information from all registered state getters
		/// to the specified <see cref="StringBuilder"/>.
		/// </summary>
		/// <param name="sb">The <see cref="StringBuilder"/> to append the state information to.</param>
		[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1031:DoNotCatchGeneralExceptionTypes")]
        public void AppendFormatted(StringBuilder sb)
        {
            foreach (KeyValuePair<string, object> entry in GetCurrentApplicationStateInfo())
            {
                sb.Append(entry.Key);
                sb.Append(": ");

                if (entry.Value == null)
                {
                    sb.AppendLine("<null>");
                }
                else
                {
                    IFormattable f = entry.Value as IFormattable;
                    if (f != null)
                    {
                        try
                        {
                            sb.AppendLine(f.ToString(null, CultureInfo.InvariantCulture));
                        }
                        catch (Exception ex)
                        {
                            sb.AppendLine("--> Exception thrown by IFormattable.ToString:");
                            sb.AppendLine(ex.ToString());
                        }
                    }
                    else
                    {
                        try
                        {
                            sb.AppendLine(entry.Value.ToString());
                        }
                        catch (Exception ex)
                        {
                            sb.AppendLine("--> Exception thrown by ToString:");
                            sb.AppendLine(ex.ToString());
                        }
                    }
                }
            }
        }
    }
}