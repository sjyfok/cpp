using System;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace ICIDECode.Develop
{
    sealed class FakeMessageLoop:IMessageLoop
    {
        public bool InvokeRequired
        {
            get { return false; }
        }

    }
}