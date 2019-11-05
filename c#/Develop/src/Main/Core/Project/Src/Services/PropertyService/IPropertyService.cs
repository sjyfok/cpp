using System;
using System.ComponentModel;

namespace ICIDECode.Core
{
    [SDService("SD.PropertyService")]
    public interface IPropertyService : INotifyPropertyChanged
    {
        /// <summary>
        /// Gets the configuration directory. (usually "%ApplicationData%\%ApplicationName%")
        /// </summary>
        DirectoryName ConfigDirectory { get; }
        /// <summary>
		/// Gets the main properties container for this property service.
		/// </summary>
		Properties MainPropertiesContainer { get; }
    }
}