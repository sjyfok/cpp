using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Windows.Forms;
using System.IO;


using ICIDECode.Core;
using ICIDECode.Develop.Logging;

namespace ICIDECode.Develop.Startup
{
    static class DevelopMain
    {
        static string[] commandLineArgs = null;
        public static string[] CommandLineArgs
        {
            get { return commandLineArgs; }
        }

        static bool UseExceptionBox
        {
            get
            {
                # if DEBUG
                //判断调试器是否加载到内存中
                if (Debugger.IsAttached) return false;
                #endif
                foreach(string arg in commandLineArgs)
                {
                    if (arg.Contains("noExceptionBox"))
                        return false;
                }
                return true;
            }
        }

        static void Main(string[] args)
        {
            commandLineArgs = args;
            if (UseExceptionBox)
            {
                try
                {
                    Run();
                }catch(Exception loadError)
                {
                    MessageBox.Show(loadError.ToString(), "Critical error (Logging service defect?)");
                }
            }
            else
            {
                Run();
            }
        }

        static void HandleMainException(Exception ex)
        {
            LoggingService.Fatal(ex);
            try
            {
                Application.Run(new ExceptionBox(ex, "Unhandled exception terminated SharpDevelop", true));
            }
            catch
            {
                MessageBox.Show(ex.ToString(), "Critical error (cannot use ExceptionBox)");
            }
        }

        static void Run()
        {
            // DO NOT USE LoggingService HERE!
            // LoggingService requires ICSharpCode.Core.dll and log4net.dll
            // When a method containing a call to LoggingService is JITted, the
            // libraries are loaded.
            // We want to show the SplashScreen while those libraries are loading, so
            // don't call LoggingService.

            #if DEBUG
            Control.CheckForIllegalCrossThreadCalls = true;
            #endif
            bool noLogo = false;

            Application.SetCompatibleTextRenderingDefault(false);
            SplashScreenForm.SetCommandLineArgs(commandLineArgs);

            foreach (string parameter in SplashScreenForm.GetParameterList())
            {
                if ("nologo".Equals(parameter, StringComparison.OrdinalIgnoreCase))
                    noLogo = true;
            }

            if (!CheckEnvironment())
                return;

            if (!noLogo)
            {
                SplashScreenForm.ShowSplashScreen();
            }
            try
            {
                RunApplication();
            }
            finally
            {
                if (SplashScreenForm.SplashScreen != null)
                {
                    SplashScreenForm.SplashScreen.Dispose();
                }
            }
        }

        static bool CheckEnvironment()
        {
            // Safety check: our setup already checks that .NET 4 is installed, but we manually check the .NET version in case SharpDevelop is
            // used on another machine than it was installed on (e.g. "SharpDevelop on USB stick")
            //if (!DotnetDetection.IsDotnet45Installed())
            //{
            //    MessageBox.Show("This version of SharpDevelop requires .NET 4.5. You are using: " + Environment.Version, "SharpDevelop");
            //    return false;
            //}
            // Work around a WPF issue when %WINDIR% is set to an incorrect path
            string windir = Environment.GetFolderPath(Environment.SpecialFolder.Windows, Environment.SpecialFolderOption.DoNotVerify);
            if (Environment.GetEnvironmentVariable("WINDIR") != windir)
            {
                Environment.SetEnvironmentVariable("WINDIR", windir);
            }
            return true;
        }

        static void RunApplication()
        {
            // The output encoding differs based on whether SharpDevelop is a console app (debug mode)
            // or Windows app (release mode). Because this flag also affects the default encoding
            // when reading from other processes' standard output, we explicitly set the encoding to get
            // consistent behaviour in debug and release builds of SharpDevelop.

            #if DEBUG
            // Console apps use the system's OEM codepage, windows apps the ANSI codepage.
            // We'll always use the Windows (ANSI) codepage.
            try
            {
                Console.OutputEncoding = System.Text.Encoding.Default;
            }
            catch (IOException)
            {
                // can happen if SharpDevelop doesn't have a console
            }
            #endif
            //调用LoggingService构造函数
            //然后调用静态类的静态函数 info
            LoggingService.Info("Starting SharpDevelop...");
            try
            {
                //StartupSettings startup = new StartupSettings();
                #if DEBUG
                //startup.UseSharpDevelopErrorHandler = UseExceptionBox;
                #endif

            //    Assembly exe = typeof(SharpDevelopMain).Assembly;
            //    startup.ApplicationRootPath = Path.Combine(Path.GetDirectoryName(exe.Location), "..");
            //    startup.AllowUserAddIns = true;

            //    string configDirectory = ConfigurationManager.AppSettings["settingsPath"];
            //    if (String.IsNullOrEmpty(configDirectory))
            //    {
            //       startup.ConfigDirectory = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
            //                                              "ICSharpCode/SharpDevelop" + RevisionClass.Major);
            //    }
                //else
                //{
                //    startup.ConfigDirectory = Path.Combine(Path.GetDirectoryName(exe.Location), configDirectory);
                //}

                //startup.DomPersistencePath = ConfigurationManager.AppSettings["domPersistencePath"];
                //if (string.IsNullOrEmpty(startup.DomPersistencePath))
                //{
                //    startup.DomPersistencePath = Path.Combine(Path.GetTempPath(), "SharpDevelop" + RevisionClass.Major + "." + RevisionClass.Minor);
                //    #if DEBUG
                //    startup.DomPersistencePath = Path.Combine(startup.DomPersistencePath, "Debug");
                //    #endif
                //}
                //else if (startup.DomPersistencePath == "none")
                //{
                //    startup.DomPersistencePath = null;
                //}

                //startup.AddAddInsFromDirectory(Path.Combine(startup.ApplicationRootPath, "AddIns"));

                //// allows testing addins without having to install them
                //foreach (string parameter in SplashScreenForm.GetParameterList())
                //{
                //    if (parameter.StartsWith("addindir:", StringComparison.OrdinalIgnoreCase))
                //    {
                //        startup.AddAddInsFromDirectory(parameter.Substring(9));
                //    }
                //}

                //SharpDevelopHost host = new SharpDevelopHost(AppDomain.CurrentDomain, startup);

                //string[] fileList = SplashScreenForm.GetRequestedFileList();
                //if (fileList.Length > 0)
                //{
                //    if (LoadFilesInPreviousInstance(fileList))
                //    {
                //        LoggingService.Info("Aborting startup, arguments will be handled by previous instance");
                //        return;
                //    }
                //}

                //host.BeforeRunWorkbench += delegate {
                //    if (SplashScreenForm.SplashScreen != null)
                //    {
                //        SplashScreenForm.SplashScreen.BeginInvoke(new MethodInvoker(SplashScreenForm.SplashScreen.Dispose));
                //        SplashScreenForm.SplashScreen = null;
                //    }
                //};

                //WorkbenchSettings workbenchSettings = new WorkbenchSettings();
                //workbenchSettings.RunOnNewThread = false;
                //for (int i = 0; i < fileList.Length; i++)
                //{
                //    workbenchSettings.InitialFileList.Add(fileList[i]);
                //}
                //SDTraceListener.Install();
                //host.RunWorkbench(workbenchSettings);
            }
            finally
            {
                //LoggingService.Info("Leaving RunApplication()");
            }
        }

        static bool LoadFilesInPreviousInstance(string[] fileList)
        {
            //try
            //{
            //    foreach (string file in fileList)
            //    {
            //        if (SD.ProjectService.IsSolutionOrProjectFile(FileName.Create(file)))
            //        {
            //            return false;
            //        }
            //    }
            //    return SingleInstanceHelper.OpenFilesInPreviousInstance(fileList);
            //}
            //catch (Exception ex)
            //{
            //    LoggingService.Error(ex);
            //    return false;
            //}

            return true;
        }
    }
}
