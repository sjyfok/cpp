using System;

namespace ICIDECode.Core
{
    public static class ServiceSingleton
    {
        static readonly IServiceProvider fallbackServiceProvider =
            new FallbackServiceProvider();
        volatile static IServiceProvider instance = fallbackServiceProvider;
    }
}