using System;

namespace ICIDECode.Core
{
    /// <summary>
	/// Class with static methods to show message boxes.
	/// All text displayed using the MessageService is passed to the
	/// <see cref="StringParser"/> to replace ${res} markers.
	/// </summary>
	public static class MessageService
    {
        static IMessageService Service
        {
            get { return ServiceSingleton.GetRequiredService<IMessageService>(); }
        }

        /// <summary>
		/// Gets/Sets the name of the product using ICSharpCode.Core.
		/// Is used by the string parser as replacement for ${ProductName}.
		/// </summary>
		public static string ProductName
        {
            get { return Service.ProductName; }
        }

        public static void ShowMessage(string message, string caption = null)
        {
            Service.ShowMessage(message, caption);
        }
    }
}