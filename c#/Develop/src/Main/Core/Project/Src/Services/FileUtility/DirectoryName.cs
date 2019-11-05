using System;
using System.ComponentModel;
using System.Globalization;
using System.IO;

namespace ICIDECode.Core
{
    [TypeConverter(typeof(DirectoryNameConverter))]
    public sealed class DirectoryName : PathName
    {
        public DirectoryName(string path)
            : base(path)
        {
        }

        /// <summary>
		/// Creates a DirectoryName instance from the string.
		/// It is valid to pass null or an empty string to this method (in that case, a null reference will be returned).
		/// </summary>
		public static DirectoryName Create(string DirectoryName)
        {
            if (string.IsNullOrEmpty(DirectoryName))
                return null;
            else
                return new DirectoryName(DirectoryName);
        }

        /// <summary>
		/// Combines this directory name with a relative path.
		/// </summary>
		public DirectoryName Combine(DirectoryName relativePath)
        {
            if (relativePath == null)
                return null;
            return DirectoryName.Create(Path.Combine(normalizedPath, relativePath));
        }
    }

    public class DirectoryNameConverter : TypeConverter
    {
        public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
        {
            return sourceType == typeof(string) || base.CanConvertFrom(context, sourceType);
        }

        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            return destinationType == typeof(DirectoryName) || base.CanConvertTo(context, destinationType);
        }

        public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)
        {
            if (value is string)
            {
                return DirectoryName.Create((string)value);
            }
            return base.ConvertFrom(context, culture, value);
        }

        public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture,
                                         object value, Type destinationType)
        {
            if (destinationType == typeof(string))
            {
                return value.ToString();
            }
            return base.ConvertTo(context, culture, value, destinationType);
        }
    }
}