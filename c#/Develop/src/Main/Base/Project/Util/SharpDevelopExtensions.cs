using System;

using ICIDECode.Core;

namespace ICIDECode.Develop
{
    public static class SharpDevelopExtensions
    {
        #region Service Provider Extensions
        public static T GetRequiredService<T>(this IServiceProvider provider)
                where T : class
        {
            return (T)GetRequiredService(provider, typeof(T));
        }

        public static object GetRequiredService(this IServiceProvider provider,
            Type serviceType)
        {
            object service = provider.GetService(serviceType);
            if (service == null)
                throw new ServiceNotFoundException(serviceType);
            return service;
        }
        #endregion
    }
}