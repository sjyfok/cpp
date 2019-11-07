﻿using System;
using System.Text;
using System.Collections.Concurrent;
using System.Globalization;
using System.Diagnostics;
using System.Reflection;

namespace ICIDECode.Core
{
    public static class StringParser
    {
        readonly static ConcurrentDictionary<string, IStringTagProvider> prefixedStringTagProviders
            = InitializePrefixedStringTagProviders();
        // not really a stack - we only use Add and GetEnumerator
        readonly static ConcurrentStack<IStringTagProvider> stringTagProviders = new ConcurrentStack<IStringTagProvider>();

        static ConcurrentDictionary<string, IStringTagProvider> InitializePrefixedStringTagProviders()
        {
            var dict = new ConcurrentDictionary<string, IStringTagProvider>(StringComparer.OrdinalIgnoreCase);

            // entryAssembly == null might happen in unit test mode
            Assembly entryAssembly = Assembly.GetEntryAssembly();
            if (entryAssembly != null)
            {
                string exeName = entryAssembly.Location;
                dict["exe"] = new PropertyObjectTagProvider(FileVersionInfo.GetVersionInfo(exeName));
            }

            return dict;
        }

        /// <summary>
		/// Expands ${xyz} style property values.
		/// </summary>
		public static string Parse(string input)
        {
            return Parse(input, (StringTagPair[])null);
        }

        //readonly static Regex pattern = new Regex(@"\$\{([^\}]*)\}", RegexOptions.Compiled | RegexOptions.CultureInvariant);

        /// <summary>
        /// Expands ${xyz} style property values.
        /// </summary>
        public static string Parse(string input, params StringTagPair[] customTags)
        {
            if (input == null)
                return null;
            int pos = 0;
            StringBuilder output = null; // don't use StringBuilder if input is a single property
            do
            {
                int oldPos = pos;
                pos = input.IndexOf("${", pos, StringComparison.Ordinal);
                if (pos < 0)
                {
                    if (output == null)
                    {
                        return input;
                    }
                    else
                    {
                        if (oldPos < input.Length)
                        {
                            // normal text after last property
                            output.Append(input, oldPos, input.Length - oldPos);
                        }
                        return output.ToString();
                    }
                }
                if (output == null)
                {
                    if (pos == 0)
                        output = new StringBuilder();
                    else
                        output = new StringBuilder(input, 0, pos, pos + 16);
                }
                else
                {
                    if (pos > oldPos)
                    {
                        // normal text between two properties
                        output.Append(input, oldPos, pos - oldPos);
                    }
                }
                int end = input.IndexOf('}', pos + 1);
                if (end < 0)
                {
                    output.Append("${");
                    pos += 2;
                }
                else
                {
                    string property = input.Substring(pos + 2, end - pos - 2);
                    string val = GetValue(property, customTags);
                    if (val == null)
                    {
                        output.Append("${");
                        output.Append(property);
                        output.Append('}');
                    }
                    else
                    {
                        output.Append(val);
                    }
                    pos = end + 1;
                }
            } while (pos < input.Length);
            return output.ToString();
        }

        public static string GetValue(string propertyName,
            params StringTagPair[] customTags)
        {
            if (propertyName == null)
                throw new ArgumentNullException("propertyName");
            if (propertyName == "$")
                return "$";
            if (customTags != null)
            {
                foreach (StringTagPair pair in customTags)
                {
                    if (propertyName.Equals(pair.Tag, StringComparison.OrdinalIgnoreCase))
                        return pair.Value;
                }
            }
            int k = propertyName.IndexOf(':');
            if (k <= 0)
            {
                if (propertyName.Equals("DATE", StringComparison.OrdinalIgnoreCase))
                    return DateTime.Today.ToShortDateString();
                if (propertyName.Equals("TIME", StringComparison.OrdinalIgnoreCase))
                    return DateTime.Now.ToShortTimeString();
                if (propertyName.Equals("ProductName", StringComparison.OrdinalIgnoreCase))
                    return ServiceSingleton.GetRequiredService<IMessageService>().ProductName;
                if (propertyName.Equals("GUID", StringComparison.OrdinalIgnoreCase))
                    return Guid.NewGuid().ToString().ToUpperInvariant();
                if (propertyName.Equals("USER", StringComparison.OrdinalIgnoreCase))
                    return Environment.UserName;
                if (propertyName.Equals("Version", StringComparison.OrdinalIgnoreCase))
                    return null;// RevisionClass.FullVersion;
                if (propertyName.Equals("CONFIGDIRECTORY", StringComparison.OrdinalIgnoreCase))
                    return ServiceSingleton.GetRequiredService<IPropertyService>().ConfigDirectory;
                foreach (IStringTagProvider provider in stringTagProviders)
                {
                    string result = provider.ProvideString(propertyName, customTags);
                    if (result != null)
                        return result;
                }

                return null;
            }
            else
            {
                // it's a prefixed property


                // res: properties are quite common, so optimize by testing for them first
                // before allocaing the prefix/propertyName strings
                // All other prefixed properties {prefix:Key} shoulg get handled in the switch below.
                if (propertyName.StartsWith("res:", StringComparison.OrdinalIgnoreCase))
                {
                    var resourceService = (IResourceService)ServiceSingleton.ServiceProvider.GetService(typeof(IResourceService));
                    if (resourceService == null)
                        return null;
                    try
                    {
                        return Parse(resourceService.GetString(propertyName.Substring(4)), customTags);
                    }
                    catch (ResourceNotFoundException)
                    {
                        return null;
                    }
                }

                string prefix = propertyName.Substring(0, k);
                propertyName = propertyName.Substring(k + 1);
                switch (prefix.ToUpperInvariant())
                {
                    case "SDKTOOLPATH":
                        return FileUtility.GetSdkPath(propertyName);
                    //case "ADDINPATH":
                    //    foreach (var addIn in ServiceSingleton.GetRequiredService<IAddInTree>().AddIns)
                    //    {
                    //        if (addIn.Manifest.Identities.ContainsKey(propertyName))
                    //        {
                    //            return System.IO.Path.GetDirectoryName(addIn.FileName);
                    //        }
                    //    }
                    //    return null;
                    case "DATE":
                        try
                        {
                            return DateTime.Now.ToString(propertyName, CultureInfo.CurrentCulture);
                        }
                        catch (Exception ex)
                        {
                            return ex.Message;
                        }
                    case "ENV":
                        return Environment.GetEnvironmentVariable(propertyName);
                    case "PROPERTY":
                        return GetProperty(propertyName);
                    default:
                        IStringTagProvider provider;
                        if (prefixedStringTagProviders.TryGetValue(prefix, out provider))
                            return provider.ProvideString(propertyName, customTags);
                        else
                            return null;

                }
            }
        }

        /// <summary>
		/// Allow special syntax to retrieve property values:
		/// ${property:PropertyName}
		/// ${property:PropertyName??DefaultValue}
		/// ${property:ContainerName/PropertyName}
		/// ${property:ContainerName/PropertyName??DefaultValue}
		/// A container is a Properties instance stored in the PropertyService. This is
		/// used by many AddIns to group all their properties into one container.
		/// </summary>
		static string GetProperty(string propertyName)
        {
            string defaultValue = "";
            int pos = propertyName.LastIndexOf("??", StringComparison.Ordinal);
            if (pos >= 0)
            {
                defaultValue = propertyName.Substring(pos + 2);
                propertyName = propertyName.Substring(0, pos);
            }
            Properties properties = ServiceSingleton.GetRequiredService<IPropertyService>().MainPropertiesContainer;
            pos = propertyName.IndexOf('/');
            while (pos >= 0)
            {
                properties = properties.NestedProperties(propertyName.Substring(0, pos));
                propertyName = propertyName.Substring(pos + 1);
                pos = propertyName.IndexOf('/');
            }
            return properties.Get(propertyName, defaultValue);
        }
    }

    public struct StringTagPair
    {
        readonly string tag;
        readonly string value;

        public string Tag
        {
            get { return tag; }
        }

        public string Value
        {
            get { return value; }
        }

        public StringTagPair(string tag, string value)
        {
            if (tag == null)
                throw new ArgumentNullException("tag");
            if (value == null)
                throw new ArgumentNullException("value");
            this.tag = tag;
            this.value = value;
        }
    }   
}