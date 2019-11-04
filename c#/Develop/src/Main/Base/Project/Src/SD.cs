using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ICIDECode.Core;

namespace ICIDECode.Develop
{
    public static class SD
    {
        //
        public static IAnalyticsMonitor  AnalyticsMonitor
        {
            get { return GetRequiredService<IAnalyticsMonitor>(); }
        }

        public static T GetRequiredService<T>() where T:class
        {
            return ServiceSingleton.ServiceProvider.GetRequiredService<T>();
        }
    }
}
