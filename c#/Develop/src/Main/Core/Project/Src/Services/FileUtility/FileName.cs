using System;
using System.ComponentModel;
using System.Globalization;
using System.IO;

namespace ICIDECode.Core
{
    /// <summary>
	/// Represents a path to a file.
	/// The equality operator is overloaded to compare for path equality (case insensitive, normalizing paths with '..\')
	/// </summary>
	[TypeConverter(typeof(FileNameConverter))]
    public sealed class FileName : PathName, IEquatable<FileName>
    {
        public FileName(string path)
            : base(path)
        {
        }

        /// <summary>
		/// Creates a FileName instance from the string.
		/// It is valid to pass null or an empty string to this method (in that case, a null reference will be returned).
		/// </summary>
		public static FileName Create(string fileName)
        {
            if (string.IsNullOrEmpty(fileName))
                return null;
            else
                return new FileName(fileName);
        }

        /// <summary>
		/// Gets the file name (not the full path).
		/// </summary>
		/// <remarks>
		/// Corresponds to <c>System.IO.Path.GetFileName</c>
		/// </remarks>
		public string GetFileName()
        {
            return Path.GetFileName(normalizedPath);
        }

        #region Equals and GetHashCode implementation
        public override bool Equals(object obj)
        {
            return Equals(obj as FileName);
        }

        public bool Equals(FileName other)
        {
            if (other != null)
                return string.Equals(normalizedPath, other.normalizedPath, StringComparison.OrdinalIgnoreCase);
            else
                return false;
        }

        public override int GetHashCode()
        {
            return StringComparer.OrdinalIgnoreCase.GetHashCode(normalizedPath);
        }

        public static bool operator ==(FileName left, FileName right)
        {
            if (ReferenceEquals(left, right))
                return true;
            if (ReferenceEquals(left, null) || ReferenceEquals(right, null))
                return false;
            return left.Equals(right);
        }

        public static bool operator !=(FileName left, FileName right)
        {
            return !(left == right);
        }

        [ObsoleteAttribute("Warning: comparing FileName with string results in case-sensitive comparison")]
        public static bool operator ==(FileName left, string right)
        {
            return (string)left == right;
        }

        [ObsoleteAttribute("Warning: comparing FileName with string results in case-sensitive comparison")]
        public static bool operator !=(FileName left, string right)
        {
            return (string)left != right;
        }

        [ObsoleteAttribute("Warning: comparing FileName with string results in case-sensitive comparison")]
        public static bool operator ==(string left, FileName right)
        {
            return left == (string)right;
        }

        [ObsoleteAttribute("Warning: comparing FileName with string results in case-sensitive comparison")]
        public static bool operator !=(string left, FileName right)
        {
            return left != (string)right;
        }
        #endregion

    }

    public class FileNameConverter : TypeConverter
    {
        public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
        {
            return sourceType == typeof(string) || base.CanConvertFrom(context, sourceType);
        }

        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            return destinationType == typeof(FileName) || base.CanConvertTo(context, destinationType);
        }

        public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)
        {
            if (value is string)
            {
                return FileName.Create((string)value);
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