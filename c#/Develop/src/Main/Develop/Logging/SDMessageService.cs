using System;
using ICIDECode.Core.WinForms;

namespace ICIDECode.Develop.Logging
{
    sealed class SDMessageService : WinFormsMessageService
    {
        public override void ShowException(Exception ex, string message)
        {
            SD.Log.Error(message, ex);
            SD.Log.Warn("Stack trace of last exception log:\n" + Environment.StackTrace);
            if (ex != null)
                ExceptionBox.ShowErrorBox(ex, message);
            else
                ShowError(message);
        }
    }
}