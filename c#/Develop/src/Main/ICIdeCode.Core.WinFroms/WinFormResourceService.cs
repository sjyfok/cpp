using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

using ICIDECode.Core;

namespace ICIDECode.Core.WinForms
{
    /// <summary>
	/// This Class contains two ResourceManagers, which handle string and image resources
	/// for the application. It do handle localization strings on this level.
	/// </summary>
    public static class WinFormsResourceService
    {
        static Dictionary<string, Icon> iconCache = new Dictionary<string, Icon>();
        static Dictionary<string, Bitmap> bitmapCache = new Dictionary<string, Bitmap>();

        static readonly IResourceService resourceService;


        /// <summary>
		/// Returns a bitmap from the resource database, it handles localization
		/// transparent for the user.
		/// The bitmaps are reused, you must not dispose the Bitmap!
		/// </summary>
		/// <returns>
		/// The bitmap in the (localized) resource database.
		/// </returns>
		/// <param name="name">
		/// The name of the requested bitmap.
		/// </param>
		/// <exception cref="ResourceNotFoundException">
		/// Is thrown when the GlobalResource manager can't find a requested resource.
		/// </exception>
		public static Bitmap GetBitmap(string name)
        {
            lock (bitmapCache)
            {
                Bitmap bmp;
                if (bitmapCache.TryGetValue(name, out bmp))
                    return bmp;
                bmp = (Bitmap)resourceService.GetImageResource(name);
                if (bmp == null)
                {
                    throw new ResourceNotFoundException(name);
                }
                bitmapCache[name] = bmp;
                return bmp;
            }
        }
    }
}
