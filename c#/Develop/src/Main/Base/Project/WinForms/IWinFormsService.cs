using System;
using System.ComponentModel;
using System.Windows.Forms;
using System.Drawing;

using ICIDECode.Core;

namespace ICIDECode.Develop.WinForms
{
    [SDService("SD.WinForms")]
    public interface IWinFormsService
    {
        IWin32Window MainWin32Window
        {
            get;
        }

        /// <summary>
        /// The LoadFont routines provide a safe way to load fonts.
        /// </summary>
        /// <param name="fontName">The name of the font to load.</param>
        /// <param name="size">The size of the font to load.</param>
        /// <param name="style">The <see cref="System.Drawing.FontStyle"/> of the font</param>
        /// <returns>
        /// The font to load or the menu font, if the requested font couldn't be loaded.
        /// </returns>
        Font LoadFont(string fontName, int size, FontStyle style = FontStyle.Regular);

    }
}