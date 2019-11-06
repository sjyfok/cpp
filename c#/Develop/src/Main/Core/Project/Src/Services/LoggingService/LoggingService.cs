using System;


namespace ICIDECode.Core
{
    public static class LoggingService
    {
        static ILoggingService Service
        {
            get { return ServiceSingleton.GetRequiredService<ILoggingService>(); }
        }
        public static void Fatal(object message)
        { }
        public static void Fatal(object message, Exception ex)
        {
            
        }
        public static void Error(object message)
        { }
        public static void Error(object message, Exception ex)
        { }

        public static void Warn(object message)
        {
        }
        public static void Warn(object message, Exception ex)
        { }

        public static void Info(object message)
        {
            Service.Info(message);
        }
        public static void Info(object message, Exception ex)
        {
            Service.Info(message, ex);
        }
        
    }
}
