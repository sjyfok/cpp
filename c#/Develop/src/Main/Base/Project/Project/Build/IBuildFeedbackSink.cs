using System;
using ICIDECode.AvalonEdit.Highlighting;
using ICIDECode.AvalonEdit.Utils;

namespace ICIDECode.Develop.Project
{
    /// <summary>
    /// Interface for reporting build results in real-time.
    /// </summary>
    /// <remarks>
    /// Implementations of this interface must be thread-safe.
    /// Project-specific build engines use this interface to report results to the main build engine,
    /// and the main build engine uses this interface to report the combined results to the IDE.
    /// </remarks>
    public interface IBuildFeedbackSink
    {
        /// <summary>
        /// Reports an build error/warning/message by adding it to the error list.
        /// This member is thread-safe.
        /// </summary>
        void ReportError(BuildError error);

        /// <summary>
        /// Reports a build message.
        /// This member is thread-safe.
        /// </summary>
        void ReportMessage(RichText message);
    }
}
