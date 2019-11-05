using System;
using System.Reflection;
using System.Resources;

namespace ICIDECode.Core
{
    /// <summary>
	/// Provides string and bitmap resources.
	/// </summary>
	[SDService("SD.ResourceService", FallbackImplementation = typeof(FallbackResourceService))]
    public interface IResourceService
    {
        /// <summary>
		/// Gets/Sets the current UI language.
		/// </summary>
		string Language { get; set; }

        /// <summary>
		/// Returns a string from the resource database, it handles localization
		/// transparent for the user.
		/// </summary>
		/// <returns>
		/// The string in the (localized) resource database.
		/// </returns>
		/// <param name="name">
		/// The name of the requested resource.
		/// </param>
		/// <exception cref="ResourceNotFoundException">
		/// Is thrown when the GlobalResource manager can't find a requested resource.
		/// </exception>
		string GetString(string name);

        object GetImageResource(string name);
    }

    sealed class FallbackResourceService : IResourceService
    {
        string IResourceService.Language
        {
            get { return "en"; }
            set
            {
                throw new NotImplementedException();
            }
        }

        string IResourceService.GetString(string name)
        {
            return null;
        }

        object IResourceService.GetImageResource(string name)
        {
            return null;
        }
    }
}