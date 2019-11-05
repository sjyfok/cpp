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

        public string DefaultMessageBoxTitle { get; set; }
        public string ProductName { get; set; }
    }
}