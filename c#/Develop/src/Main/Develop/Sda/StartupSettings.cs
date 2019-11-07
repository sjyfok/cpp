using System;
using System.Collections.Generic;

namespace ICIDECode.Develop.Sda
{
    /// <summary>
	/// This class contains properties you can use to control how SharpDevelop is launched.
	/// </summary>
	[Serializable]
    public sealed class StartupSettings
    {
        bool useSharpDevelopErrorHandler = true;
        string applicationRootPath;
        bool allowUserAddIns;
        string configDirectory;
        string domPersistencePath;
        internal List<string> addInDirectories = new List<string>();

        /// <summary>
		/// Gets/Sets whether the SharpDevelop exception box should be used for
		/// unhandled exceptions. The default is true.
		/// </summary>
		public bool UseSharpDevelopErrorHandler
        {
            get { return useSharpDevelopErrorHandler; }
            set { useSharpDevelopErrorHandler = value; }
        }

        /// <summary>
		/// Gets/Sets the application root path to use.
		/// Use null (default) to use the base directory of the SharpDevelop AppDomain.
		/// </summary>
		public string ApplicationRootPath
        {
            get { return applicationRootPath; }
            set { applicationRootPath = value; }
        }

        /// <summary>
		/// Gets/Sets the directory used to store SharpDevelop properties,
		/// settings and user AddIns.
		/// Use null (default) to use "ApplicationData\ApplicationName"
		/// </summary>
		public string ConfigDirectory
        {
            get { return configDirectory; }
            set { configDirectory = value; }
        }

        /// <summary>
		/// Allow user AddIns stored in the "application data" directory.
		/// The default is false.
		/// </summary>
		public bool AllowUserAddIns
        {
            get { return allowUserAddIns; }
            set { allowUserAddIns = value; }
        }

        /// <summary>
		/// Find AddIns by searching all .addin files recursively in <paramref name="addInDir"/>.
		/// </summary>
		public void AddAddInsFromDirectory(string addInDir)
        {
            if (addInDir == null)
                throw new ArgumentNullException("addInDir");
            addInDirectories.Add(addInDir);
        }
        /// <summary>
		/// Sets the directory used to store the code completion cache.
		/// Use null (default) to disable the code completion cache.
		/// </summary>
		public string DomPersistencePath
        {
            get { return domPersistencePath; }
            set { domPersistencePath = value; }
        }

    }
}