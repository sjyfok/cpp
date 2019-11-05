
using System;

namespace ICIDECode.Core
{
    [SDService("SD.AnalyticsMonitor", FallbackImplementation =typeof(AnalyticsMonitorFallback))]
    public interface IAnalyticsMonitor
    {
        void TrackException(Exception exception);
    }

    public interface IAnalyticsMonitorTrackedFeature
    {
        void EndTracking();
    }

    sealed class AnalyticsMonitorFallback: IAnalyticsMonitor, IAnalyticsMonitorTrackedFeature
    {
        void IAnalyticsMonitorTrackedFeature.EndTracking()
        { }
        public void TrackException(Exception exception)
        { }
    }
}