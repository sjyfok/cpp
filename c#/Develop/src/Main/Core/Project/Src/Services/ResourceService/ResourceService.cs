using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Reflection;
using System.Resources;
using System.Threading;

namespace ICIDECode.Core
{
    /// <summary>
	/// Compatibility class; forwards calls to the IResourceService.
	/// TODO: Remove
	/// </summary>
	public static class ResourceService
    {
        static IResourceService Service
        {
            get { return ServiceSingleton.GetRequiredService<IResourceService>(); }
        }

        public static string GetString(string resourceName)
        {
            return Service.GetString(resourceName);
        }

        public static string Language
        {
            get { return Service.Language; }
        }
    }
}