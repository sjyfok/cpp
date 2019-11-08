using System;
using System.IO;

namespace ICIDECode.Core.Implementation
{
    public class TextWriterMessageService:IMessageService
    {
        readonly TextWriter writer;

        public TextWriterMessageService(TextWriter writer)
        {
            if (writer == null)
                throw new ArgumentNullException("writer");
            this.writer = writer;
            this.DefaultMessageBoxTitle = this.ProductName = "SharpDevelop";
        }

        public void ShowMessage(string message, string caption)
        {
            writer.WriteLine(caption + ": " + message);
        }

        public void ShowMessageFormatted(string formatstring, string caption, params object[] formatitems)
        {
            writer.WriteLine(StringParser.Format(formatstring, formatitems));
        }

        public string DefaultMessageBoxTitle { get; set; }
        public string ProductName { get; set; }
    }
}