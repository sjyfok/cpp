using System;
using System.Windows;
using ICIDECode.Core;

namespace ICIDECode.Develop
{
    [SDService("SD.Clipboard")]
    public interface IClipboard
    {
        void SetText(string text);
    }
}