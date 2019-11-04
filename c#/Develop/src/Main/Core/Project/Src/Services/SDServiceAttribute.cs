
using System;
using System.Collections.Generic;

namespace ICIDECode.Core
{
    [AttributeUsage(AttributeTargets.Interface | AttributeTargets.Class, Inherited = false)]
    public class SDServiceAttribute : Attribute
    {
        public SDServiceAttribute()
        {

        }
        public SDServiceAttribute(string staticPropertyPath)
        {
            this.StaticPropertyPath = staticPropertyPath;
        }

        public string StaticPropertyPath { get; set; }

        public Type FallbackImplementation { get; set; }
    }

    sealed class FallbackServiceProvider:IServiceProvider
    {
        Dictionary<Type, object> fallbackServiceDict = new Dictionary<Type, object>();
        public object GetService(Type serviceType)
        {
            object instance;
            lock (fallbackServiceDict)
            {
                if(!fallbackServiceDict.TryGetValue(serviceType, out instance))
                {
                    var attrs = serviceType.GetCustomAttributes(typeof(SDServiceAttribute), false);
                    if(attrs.Length == 1)
                    {
                        var attr = (SDServiceAttribute)attrs[0];
                        if (attr.FallbackImplementation != null)
                            instance = Activator.CreateInstance(attr.FallbackImplementation);
                    }
                    fallbackServiceDict.Add(serviceType, instance);
                }
            }
            return instance;
        }
    }
}