using System;
using System.Runtime.Serialization;

namespace ICIDECode.Core
{
    [Serializable()]
    public class ServiceNotFoundException:CoreException
    {

        public ServiceNotFoundException(Type serviceType)
            : base("Required service not found: " +
                 serviceType.FullName)
        { }
    }
}