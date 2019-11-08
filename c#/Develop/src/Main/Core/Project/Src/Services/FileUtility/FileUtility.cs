using System;
using System.Collections.Generic;
using Microsoft.Win32;
using System.IO;

namespace ICIDECode.Core
{
    /// <summary>
    /// A utility class related to file utilities.
    /// </summary>
    public static partial class FileUtility
    {
        static string applicationRootPath = AppDomain.CurrentDomain.BaseDirectory;

        public static string ApplicationRootPath
        {
            get
            {
                return applicationRootPath;
            }
            set
            {
                applicationRootPath = value;
            }
        }

        static string GetPathFromRegistryX86(string key, string valueName)
        {
            using (RegistryKey baseKey = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry32))
            {
                using (RegistryKey installRootKey = baseKey.OpenSubKey(key))
                {
                    if (installRootKey != null)
                    {
                        object o = installRootKey.GetValue(valueName);
                        if (o != null)
                        {
                            string r = o.ToString();
                            if (!string.IsNullOrEmpty(r))
                                return r;
                        }
                    }
                }
            }
            return null;
        }
        #region InstallRoot Properties

        static string windowsSdk80InstallRoot = null;
        /// <summary>
        /// Location of the .NET 4.5 SDK (Windows SDK 8.0) install root.
        /// </summary>
        public static string WindowsSdk80NetFxTools
        {
            get
            {
                if (windowsSdk80InstallRoot == null)
                {
                    windowsSdk80InstallRoot = GetPathFromRegistryX86(@"SOFTWARE\Microsoft\Microsoft SDKs\Windows\v8.0A\WinSDK-NetFx40Tools", "InstallationFolder") ?? string.Empty;
                }
                return windowsSdk80InstallRoot;
            }
        }
        #endregion

        /// <summary>
        /// Searches all the .net sdk bin folders and return the path of the
        /// exe from the latest sdk.
        /// </summary>
        /// <param name="exeName">The EXE to search for.</param>
        /// <returns>The path of the executable, or null if the exe is not found.</returns>
        public static string GetSdkPath(string exeName)
        {
            string execPath;
            if (!string.IsNullOrEmpty(WindowsSdk80NetFxTools))
            {
                execPath = Path.Combine(WindowsSdk80NetFxTools, exeName);
                if (File.Exists(execPath)) { return execPath; }
            }
            //if (!string.IsNullOrEmpty(WindowsSdk71InstallRoot))
            //{
            //    execPath = Path.Combine(WindowsSdk71InstallRoot, "bin\\" + exeName);
            //    if (File.Exists(execPath)) { return execPath; }
            //}
            //if (!string.IsNullOrEmpty(WindowsSdk70InstallRoot))
            //{
            //    execPath = Path.Combine(WindowsSdk70InstallRoot, "bin\\" + exeName);
            //    if (File.Exists(execPath)) { return execPath; }
            //}
            //if (!string.IsNullOrEmpty(WindowsSdk61InstallRoot))
            //{
            //    execPath = Path.Combine(WindowsSdk61InstallRoot, "bin\\" + exeName);
            //    if (File.Exists(execPath)) { return execPath; }
            //}
            //if (!string.IsNullOrEmpty(WindowsSdk60aInstallRoot))
            //{
            //    execPath = Path.Combine(WindowsSdk60aInstallRoot, "bin\\" + exeName);
            //    if (File.Exists(execPath)) { return execPath; }
            //}
            //if (!string.IsNullOrEmpty(WindowsSdk60InstallRoot))
            //{
            //    execPath = Path.Combine(WindowsSdk60InstallRoot, "bin\\" + exeName);
            //    if (File.Exists(execPath)) { return execPath; }
            //}
            //if (!string.IsNullOrEmpty(NetSdk20InstallRoot))
            //{
            //    execPath = Path.Combine(NetSdk20InstallRoot, "bin\\" + exeName);
            //    if (File.Exists(execPath)) { return execPath; }
            //}
            return null;
        }

        public static event EventHandler<FileNameEventArgs> FileLoaded;
        public static event EventHandler<FileNameEventArgs> FileSaved;
    }
}