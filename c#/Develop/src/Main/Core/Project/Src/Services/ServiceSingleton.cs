using System;

namespace ICIDECode.Core
{
    public static class ServiceSingleton
    {
        static readonly IServiceProvider fallbackServiceProvider =
            new FallbackServiceProvider();
        volatile static IServiceProvider instance = fallbackServiceProvider;

        public static IServiceProvider ServiceProvider
        {
            get { return instance; }
            set
            {
                if (value == null)
                    throw new ArgumentNullException();
                instance = value;
            }
        }

        public static T GetRequiredService<T>()
        {
            object service = instance.GetService(typeof(T));
            if (service == null)
                throw new ServiceNotFoundException(typeof(T));
            return (T)service;
        }
    }
}