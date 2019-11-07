using System;
using System.Collections.ObjectModel;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Reflection;

namespace ICIDECode.Develop.Sda
{
    /// <summary>
	/// This class can host an instance of SharpDevelop inside another
	/// AppDomain.
	/// </summary>
    public sealed class DevelopHost
    {
        AppDomain appDomain;
        CallHelper helper;
        SDInitStatus initStatus;

        #region Constructors
        /// <summary>
        /// Create a new AppDomain to host SharpDevelop.
        /// </summary>
        public DevelopHost(StartupSettings startup)
        {
            if (startup == null)
            {
                throw new ArgumentNullException("startup");
            }
            this.appDomain = CreateDomain();
            helper = (CallHelper)appDomain.CreateInstanceAndUnwrap(SdaAssembly.FullName, typeof(CallHelper).FullName);
            helper.InitDevelopCore(new CallbackHelper(this), startup);
            initStatus = SDInitStatus.CoreInitialized;
        }

        /// <summary>
        /// Host SharpDevelop in the existing AppDomain.
        /// </summary>
        public DevelopHost(AppDomain appDomain, StartupSettings startup)
        {
            if (appDomain == null)
            {
                throw new ArgumentNullException("appDomain");
            }
            if (startup == null)
            {
                throw new ArgumentNullException("startup");
            }
            this.appDomain = appDomain;
            helper = (CallHelper)appDomain.CreateInstanceAndUnwrap(SdaAssembly.FullName, typeof(CallHelper).FullName);
            helper.InitDevelopCore(new CallbackHelper(this), startup);
            initStatus = SDInitStatus.CoreInitialized;
        }
        #endregion

        #region Static helpers
        internal static Assembly SdaAssembly
        {
            get
            {
                return typeof(DevelopHost).Assembly;
            }
        }
        #endregion
        #region SDInitStatus enum
        enum SDInitStatus
        {
            None,
            CoreInitialized,
            WorkbenchInitialized,
            Busy,
            WorkbenchUnloaded,
            AppDomainUnloaded
        }
        #endregion
        #region CreateDomain
        /// <summary>
        /// Create an AppDomain capable of hosting SharpDevelop.
        /// </summary>
        public static AppDomain CreateDomain()
        {
            return AppDomain.CreateDomain("SharpDevelop.Sda", null, CreateDomainSetup());
        }

        /// <summary>
        /// Creates an AppDomainSetup specifying properties for an AppDomain capable of
        /// hosting SharpDevelop.
        /// </summary>
        public static AppDomainSetup CreateDomainSetup()
        {
            AppDomainSetup s = new AppDomainSetup();
            s.ApplicationBase = Path.GetDirectoryName(SdaAssembly.Location);
            s.ConfigurationFile = SdaAssembly.Location + ".config";
            s.ApplicationName = "SharpDevelop.Sda";
            return s;
        }
        #endregion
        #region Callback Events
        System.ComponentModel.ISynchronizeInvoke invokeTarget;

        /// <summary>
        /// Gets/Sets an object to use to synchronize all events with a thread.
        /// Use null (default) to handle all events on the thread they were
        /// raised on.
        /// </summary>
        public System.ComponentModel.ISynchronizeInvoke InvokeTarget
        {
            get
            {
                return invokeTarget;
            }
            set
            {
                invokeTarget = value;
            }
        }

        /// <summary>
        /// Event before the workbench starts running.
        /// </summary>
        [SuppressMessage("Microsoft.Naming", "CA1713:EventsShouldNotHaveBeforeOrAfterPrefix")]
        public event EventHandler BeforeRunWorkbench;

        /// <summary>
        /// Event after the workbench has been unloaded.
        /// </summary>
        public event EventHandler WorkbenchClosed;

        /// <summary>
        /// Event when SharpDevelop starts to compile a project or solution.
        /// </summary>
        public event EventHandler StartBuild;

        /// <summary>
        /// Event when SharpDevelop finishes to compile a project or solution.
        /// </summary>
        public event EventHandler EndBuild;

        /// <summary>
        /// Event when a solution was loaded inside SharpDevelop.
        /// </summary>
        public event EventHandler SolutionLoaded;

        /// <summary>
        /// Event when the current solution was closed.
        /// </summary>
        public event EventHandler SolutionClosed;

        /// <summary>
        /// Event when a file was loaded inside SharpDevelop.
        /// </summary>
        public event EventHandler<FileEventArgs> FileLoaded;

        /// <summary>
        /// Event when a file was saved inside SharpDevelop.
        /// </summary>
        public event EventHandler<FileEventArgs> FileSaved;

        internal sealed class CallbackHelper : MarshalByRefObject
        {
            private static readonly object[] emptyObjectArray = new object[0];

            readonly DevelopHost host;

            public CallbackHelper(DevelopHost host)
            {
                this.host = host;
            }

            public override object InitializeLifetimeService()
            {
                return null;
            }

            private bool InvokeRequired
            {
                get
                {
                    return host.invokeTarget != null && host.invokeTarget.InvokeRequired;
                }
            }

            private void Invoke(System.Windows.Forms.MethodInvoker method)
            {
                host.invokeTarget.BeginInvoke(method, emptyObjectArray);
            }

            private void Invoke(Action<string> method, string argument)
            {
                host.invokeTarget.BeginInvoke(method, new object[] { argument });
            }

            internal void BeforeRunWorkbench()
            {
                if (InvokeRequired) { Invoke(BeforeRunWorkbench); return; }
                host.initStatus = SDInitStatus.WorkbenchInitialized;
                if (host.BeforeRunWorkbench != null) host.BeforeRunWorkbench(host, EventArgs.Empty);
            }

            internal void WorkbenchClosed()
            {
                if (InvokeRequired) { Invoke(WorkbenchClosed); return; }
                host.initStatus = SDInitStatus.WorkbenchUnloaded;
                if (host.WorkbenchClosed != null) host.WorkbenchClosed(host, EventArgs.Empty);
            }

            internal void StartBuild()
            {
                if (InvokeRequired) { Invoke(StartBuild); return; }
                if (host.StartBuild != null) host.StartBuild(host, EventArgs.Empty);
            }

            internal void EndBuild()
            {
                if (InvokeRequired) { Invoke(EndBuild); return; }
                if (host.EndBuild != null) host.EndBuild(host, EventArgs.Empty);
            }

            internal void SolutionLoaded()
            {
                if (InvokeRequired) { Invoke(SolutionLoaded); return; }
                if (host.SolutionLoaded != null) host.SolutionLoaded(host, EventArgs.Empty);
            }

            internal void SolutionClosed()
            {
                if (InvokeRequired) { Invoke(SolutionClosed); return; }
                if (host.SolutionClosed != null) host.SolutionClosed(host, EventArgs.Empty);
            }

            internal void FileLoaded(string fileName)
            {
                if (InvokeRequired) { Invoke(FileLoaded, fileName); return; }
                if (host.FileLoaded != null) host.FileLoaded(host, new FileEventArgs(fileName));
            }

            internal void FileSaved(string fileName)
            {
                if (InvokeRequired) { Invoke(FileSaved, fileName); return; }
                if (host.FileSaved != null) host.FileSaved(host, new FileEventArgs(fileName));
            }
        }
        #endregion

    }
}