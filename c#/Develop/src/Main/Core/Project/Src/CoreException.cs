using System;
using System.Runtime.Serialization;

namespace ICIDECode.Core
{
    [Serializable()]
    public class CoreException:Exception
    {
        public CoreException(string message):base(message)
        { }
    }
}