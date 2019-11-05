using System;
using System.Runtime.Serialization;

namespace ICIDECode.Core
{
    /// <summary>
	/// Is thrown when the GlobalResource manager can't find a requested
	/// resource.
	/// </summary>
	[Serializable()]
    public class ResourceNotFoundException : CoreException
    {
        string resourceName;
        public string ResourceName { get { return resourceName; } }

        public ResourceNotFoundException(string resourceName) : base("Resource not found : " + resourceName)
        {
            this.resourceName = resourceName;
        }
    }
}