using System;
using System.ComponentModel.Design;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ICIDECode.Core;
using ICIDECode.Develop.WinForms;

namespace ICIDECode.Develop
{
    public static class SD
    {
        public static IServiceContainer Services
        {
            get { return GetRequiredService<IServiceContainer>(); }
        }

        //
        public static IAnalyticsMonitor  AnalyticsMonitor
        {
            get { return GetRequiredService<IAnalyticsMonitor>(); }
        }

        public static T GetRequiredService<T>() where T:class
        {
            return ServiceSingleton.ServiceProvider.GetRequiredService<T>();
        }

        
        public static IMessageLoop MainThread
        {
            get { return GetRequiredService<IMessageLoop>(); }
        }

        public static IClipboard Clipboard
        {
            get { return GetRequiredService<IClipboard>(); }
        }

        public static IWinFormsService WinForms
        {
            get { return GetRequiredService<IWinFormsService>(); }
        }
    }
}
