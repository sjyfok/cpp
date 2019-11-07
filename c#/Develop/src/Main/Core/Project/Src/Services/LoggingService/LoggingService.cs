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
            //Service是个属性 调用属性对应的方法
            //然后又牵扯到一个静态类  并调用服务查找函数 如果服务不存在就要建立服务
            //如果服务存在就直接利用此服务，最终返回一个TextWriterLoggingService的实例
            //TextWriterLoggingService的构造函数 显示最终调用了Trace实现输出
            Service.Info(message);
        }
        //public static void Info(object message, Exception ex)
        //{
        //    Service.Info(message, ex);
        //}
        
    }
}
