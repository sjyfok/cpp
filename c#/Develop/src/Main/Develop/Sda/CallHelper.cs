using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Threading;
using System.Windows;
using System.Windows.Input;
using System.Windows.Threading;
using ICIDECode.Core;
using ICIDECode.Core.WinForms;
//using ICSharpCode.SharpDevelop.Commands;
using ICIDECode.Develop.Gui;
//using ICSharpCode.SharpDevelop.Workbench;
using ICIDECode.Develop.Logging;
//using ICSharpCode.SharpDevelop.Parser;
using ICIDECode.Develop;
namespace ICIDECode.Develop.Sda
{
    internal sealed class CallHelper : MarshalByRefObject
    {
        DevelopHost.CallbackHelper callback;
        bool useDevelopErrorHandler;

        #region Initialize Core
        public void InitDevelopCore(DevelopHost.CallbackHelper callback, StartupSettings properties)
        {
            // Initialize the most important services:
            var container = new DevelopServiceContainer();
            container.AddFallbackProvider(ServiceSingleton.FallbackServiceProvider);
            container.AddService(typeof(IMessageService), new SDMessageService());
            container.AddService(typeof(ILoggingService), new log4netLoggingService());
            ServiceSingleton.ServiceProvider = container;

            LoggingService.Info("InitSharpDevelop...");
            this.callback = callback;
            CoreStartup startup = new CoreStartup(properties.ApplicationName);
            if (properties.UseSharpDevelopErrorHandler)
            {
                this.useDevelopErrorHandler = true;
                ExceptionBox.RegisterExceptionBoxForUnhandledExceptions();
            }
            string configDirectory = properties.ConfigDirectory;
            string dataDirectory = properties.DataDirectory;
            string propertiesName;
            if (properties.PropertiesName != null)
            {
                propertiesName = properties.PropertiesName;
            }
            else
            {
                propertiesName = properties.ApplicationName + "Properties";
            }

            if (properties.ApplicationRootPath != null)
            {
                FileUtility.ApplicationRootPath = properties.ApplicationRootPath;
            }

            if (configDirectory == null)
                configDirectory = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                                               properties.ApplicationName);
            var propertyService = new PropertyService(
                DirectoryName.Create(configDirectory),
                DirectoryName.Create(dataDirectory ?? Path.Combine(FileUtility.ApplicationRootPath, "data")),
                propertiesName);

            startup.StartCoreServices(propertyService);
            Assembly exe = Assembly.Load(properties.ResourceAssemblyName);
            SD.ResourceService.RegisterNeutralStrings(new ResourceManager("ICSharpCode.SharpDevelop.Resources.StringResources", exe));
            SD.ResourceService.RegisterNeutralImages(new ResourceManager("ICSharpCode.SharpDevelop.Resources.BitmapResources", exe));

            CommandWrapper.LinkCommandCreator = (link => new LinkCommand(link));
            CommandWrapper.WellKnownCommandCreator = Core.Presentation.MenuService.GetKnownCommand;
            CommandWrapper.RegisterConditionRequerySuggestedHandler = (eh => CommandManager.RequerySuggested += eh);
            CommandWrapper.UnregisterConditionRequerySuggestedHandler = (eh => CommandManager.RequerySuggested -= eh);
            StringParser.RegisterStringTagProvider(new SharpDevelopStringTagProvider());

            LoggingService.Info("Looking for AddIns...");
            foreach (string file in properties.addInFiles)
            {
                startup.AddAddInFile(file);
            }
            foreach (string dir in properties.addInDirectories)
            {
                startup.AddAddInsFromDirectory(dir);
            }

            if (properties.AllowAddInConfigurationAndExternalAddIns)
            {
                startup.ConfigureExternalAddIns(Path.Combine(configDirectory, "AddIns.xml"));
            }
            if (properties.AllowUserAddIns)
            {
                startup.ConfigureUserAddIns(Path.Combine(configDirectory, "AddInInstallTemp"),
                    Path.Combine(configDirectory, "AddIns"));
            }

            LoggingService.Info("Loading AddInTree...");
            startup.RunInitialization();

            ((AssemblyParserService)SD.AssemblyParserService).DomPersistencePath = properties.DomPersistencePath;

            // Register events to marshal back
            Project.ProjectService.BuildStarted += delegate { this.callback.StartBuild(); };
            Project.ProjectService.BuildFinished += delegate { this.callback.EndBuild(); };
            Project.ProjectService.SolutionLoaded += delegate { this.callback.SolutionLoaded(); };
            Project.ProjectService.SolutionClosed += delegate { this.callback.SolutionClosed(); };
            FileUtility.FileLoaded += delegate (object sender, FileNameEventArgs e) { this.callback.FileLoaded(e.FileName); };
            FileUtility.FileSaved += delegate (object sender, FileNameEventArgs e) { this.callback.FileSaved(e.FileName); };

            LoggingService.Info("InitSharpDevelop finished");
        }
        #endregion
    }
}