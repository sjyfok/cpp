using System;

namespace ICIDECode.Core
{
    /// <summary>
    /// EventArgs with a file name.
    /// </summary>
    public class FileNameEventArgs : System.EventArgs
    {
        FileName fileName;

        public FileName FileName
        {
            get
            {
                return fileName;
            }
        }

        public FileNameEventArgs(FileName fileName)
        {
            this.fileName = fileName;
        }

        public FileNameEventArgs(string fileName)
        {
            this.fileName = FileName.Create(fileName);
        }
    }
}