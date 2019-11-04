
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
}