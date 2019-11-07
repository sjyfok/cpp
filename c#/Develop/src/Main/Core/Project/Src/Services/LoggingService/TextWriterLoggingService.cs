

using System;
using System.IO;

namespace ICIDECode.Core.Implementation
{
    public class TextWriterLoggingService:ILoggingService
    {
        readonly TextWriter writer;
        
        public TextWriterLoggingService(TextWriter writer)
        {
            if (writer == null)
                throw new ArgumentNullException("writer");

            this.writer = writer;
            this.IsFatalEnabled = true;
            this.IsErrorEnabled = true;
            this.IsWarnEnabled = true;
            this.IsInfoEnabled = true;
            this.IsDebugEnabled = true;
        }

        void Write(object message, Exception exception)
        {
            if(message != null)
            {
                writer.WriteLine(message.ToString());
            }
            else
            {
                writer.WriteLine(exception.ToString());
            }
        }
        public bool IsDebugEnabled { get; set; }
        public bool IsInfoEnabled { get; set; }
        public bool IsWarnEnabled { get; set; }
        public bool IsErrorEnabled { get; set; }
        public bool IsFatalEnabled { get; set; }

        public void Debug(object message)
        { }
        public void DebugFormatted(string format, params object [] args)
        { }

        public void Info(object message)
        {
            if (IsInfoEnabled)
                Write(message, null);
        }
        //public void Info(object message, Exception ex)
        //{ }
        public void InfoFormatted(string format, params object[] args)
        { }

        public void Warn(object message)
        { }
        public void Warn(object message, Exception ex)
        { }
        public void WarnFormatted(string format, params object[] args)
        { }

        public void Error(object message)
        { }
        public void Error(object message, Exception ex)
        { }
        public void ErrorFormatted(string format, params object[] args)
        { }

        public void Fatal(object message)
        { }
        public void Fatal(object message, Exception ex)
        { }
        public void FatalFormatted(string format, params object[] args)
        { }


    }
}