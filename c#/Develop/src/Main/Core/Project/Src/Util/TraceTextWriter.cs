using System;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace ICIDECode.Core.Implementation
{
    public class TraceTextWriter: TextWriter
    {
        public override Encoding Encoding
        {
            get { return Encoding.Unicode; }
        }
    }
}