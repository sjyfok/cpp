using System;

using ICIDECode.Core.Implementation;

namespace ICIDECode.Core
{
    [SDService("SD.MessageService", FallbackImplementation = typeof(FallbackMessageService))]
    public interface IMessageService
    {
        string ProductName { get; }

        void ShowMessage(string message, string caption = null);
        void ShowMessageFormatted(string formatstring, string caption, params object[] formatitems);
    }

    sealed class FallbackMessageService:TextWriterMessageService
    {
        public FallbackMessageService() : base(Console.Out) { }
    }

    public sealed class ChooseSaveErrorResult
    {
        public bool IsRetry { get; private set; }
        public bool IsIgnore { get; private set; }
        public bool IsSaveAlternative { get { return AlternativeFileName != null; } }
        public FileName AlternativeFileName { get; private set; }

        private ChooseSaveErrorResult() { }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Justification = "ChooseSaveErrorResult is immutable")]
        public readonly static ChooseSaveErrorResult Retry = new ChooseSaveErrorResult { IsRetry = true };
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Justification = "ChooseSaveErrorResult is immutable")]
        public readonly static ChooseSaveErrorResult Ignore = new ChooseSaveErrorResult { IsIgnore = true };

        public static ChooseSaveErrorResult SaveAlternative(FileName alternativeFileName)
        {
            if (alternativeFileName == null)
                throw new ArgumentNullException("alternativeFileName");
            return new ChooseSaveErrorResult { AlternativeFileName = alternativeFileName };
        }
    }
}