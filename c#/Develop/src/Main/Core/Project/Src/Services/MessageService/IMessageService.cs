using System;

using ICIDECode.Core.Implementation;

namespace ICIDECode.Core
{
    [SDService("SD.MessageService", FallbackImplementation = typeof(FallbackMessageService))]
    public interface IMessageService
    {
        string ProductName { get; }
    }

    sealed class FallbackMessageService:TextWriterMessageService
    {
        public FallbackMessageService() : base(Console.Out) { }
    }
}