using System;

namespace ICIDECode.NRefactory.Editor
{
    /// <summary>
    /// An (Offset,Length)-pair.
    /// </summary>
    public interface ISegment
    {
        /// <summary>
        /// Gets the start offset of the segment.
        /// </summary>
        int Offset { get; }

        /// <summary>
        /// Gets the length of the segment.
        /// </summary>
        /// <remarks>For line segments (IDocumentLine), the length does not include the line delimeter.</remarks>
        int Length { get; }

        /// <summary>
        /// Gets the end offset of the segment.
        /// </summary>
        /// <remarks>EndOffset = Offset + Length;</remarks>
        int EndOffset { get; }
    }

    /// <summary>
    /// Extension methods for <see cref="ISegment"/>.
    /// </summary>
    public static class ISegmentExtensions
    {
        /// <summary>
        /// Gets whether <paramref name="segment"/> fully contains the specified segment.
        /// </summary>
        /// <remarks>
        /// Use <c>segment.Contains(offset, 0)</c> to detect whether a segment (end inclusive) contains offset;
        /// use <c>segment.Contains(offset, 1)</c> to detect whether a segment (end exclusive) contains offset.
        /// </remarks>
        public static bool Contains(this ISegment segment, int offset, int length)
        {
            return segment.Offset <= offset && offset + length <= segment.EndOffset;
        }

        /// <summary>
        /// Gets whether <paramref name="thisSegment"/> fully contains the specified segment.
        /// </summary>
        public static bool Contains(this ISegment thisSegment, ISegment segment)
        {
            return segment != null && thisSegment.Offset <= segment.Offset && segment.EndOffset <= thisSegment.EndOffset;
        }
    }
}
