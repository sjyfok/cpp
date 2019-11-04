
using System;

namespace ICIDECode.Core
{
    [SDService("SD.AnalyticsMonitor", FallbackImplementation =typeof(AnalyticsMonitorFallback))]
    public interface IAnalyticsMonitor
    {

    }

    public interface IAnalyticsMonitorTrackedFeature
    {
        void EndTracking();
    }

    sealed class AnalyticsMonitorFallback: IAnalyticsMonitor, IAnalyticsMonitorTrackedFeature
    {
        void IAnalyticsMonitorTrackedFeature.EndTracking()
        { }
    }
}