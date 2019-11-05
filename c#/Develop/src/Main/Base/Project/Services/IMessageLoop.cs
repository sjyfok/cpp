using System;

using ICIDECode.Core;

namespace ICIDECode.Develop
{
    [SDService("SD.MainThread", FallbackImplementation = typeof(FakeMessageLoop))]
    public interface IMessageLoop
    {
        bool InvokeRequired { get; }
    }
}