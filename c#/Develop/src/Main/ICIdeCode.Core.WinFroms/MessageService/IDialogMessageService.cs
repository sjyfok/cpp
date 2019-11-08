using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace ICIDECode.Core.WinForms
{
    /// <summary>
    /// Message service that sets an owner for dialog boxes.
    /// </summary>
    public interface IDialogMessageService : IMessageService
    {
        IWin32Window DialogOwner { set; get; }
        ISynchronizeInvoke DialogSynchronizeInvoke { set; get; }
    }
}