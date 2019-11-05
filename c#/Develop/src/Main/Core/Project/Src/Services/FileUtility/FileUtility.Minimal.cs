﻿using System;
using System.IO;
using System.Text;

namespace ICIDECode.Core
{
    /// <summary>
    /// A minimal version of FileUtility. Is used by ICSharpCode.SharpDevelop.Dom (which doesn't reference
    /// ICSharpCode.Core)
    /// </summary>
    static partial class FileUtility
    {
        /// <summary>
		/// Gets the normalized version of fileName.
		/// Slashes are replaced with backslashes, backreferences "." and ".." are 'evaluated'.
		/// </summary>
		public static string NormalizePath(string fileName)
        {
            if (string.IsNullOrEmpty(fileName)) return fileName;

            int i;

            bool isWeb = false;
            for (i = 0; i < fileName.Length; i++)
            {
                if (fileName[i] == '/' || fileName[i] == '\\')
                    break;
                if (fileName[i] == ':')
                {
                    if (i > 1)
                        isWeb = true;
                    break;
                }
            }

            char outputSeparator = isWeb ? '/' : System.IO.Path.DirectorySeparatorChar;
            bool isRelative;

            StringBuilder result = new StringBuilder();
            if (isWeb == false && fileName.StartsWith(@"\\", StringComparison.Ordinal) || fileName.StartsWith("//", StringComparison.Ordinal))
            {
                // UNC path
                i = 2;
                result.Append(outputSeparator);
                isRelative = false;
            }
            else
            {
                i = 0;
                isRelative = !isWeb && (fileName.Length < 2 || fileName[1] != ':');
            }
            int levelsBack = 0;
            int segmentStartPos = i;
            for (; i <= fileName.Length; i++)
            {
                if (i == fileName.Length || fileName[i] == '/' || fileName[i] == '\\')
                {
                    int segmentLength = i - segmentStartPos;
                    switch (segmentLength)
                    {
                        case 0:
                            // ignore empty segment (if not in web mode)
                            if (isWeb)
                            {
                                result.Append(outputSeparator);
                            }
                            break;
                        case 1:
                            // ignore /./ segment, but append other one-letter segments
                            if (fileName[segmentStartPos] != '.')
                            {
                                if (result.Length > 0) result.Append(outputSeparator);
                                result.Append(fileName[segmentStartPos]);
                            }
                            break;
                        case 2:
                            if (fileName[segmentStartPos] == '.' && fileName[segmentStartPos + 1] == '.')
                            {
                                // remove previous segment
                                int j;
                                for (j = result.Length - 1; j >= 0 && result[j] != outputSeparator; j--) ;
                                if (j > 0)
                                {
                                    result.Length = j;
                                }
                                else if (isRelative)
                                {
                                    if (result.Length == 0)
                                        levelsBack++;
                                    else
                                        result.Length = 0;
                                }
                                break;
                            }
                            else
                            {
                                // append normal segment
                                goto default;
                            }
                        default:
                            if (result.Length > 0) result.Append(outputSeparator);
                            result.Append(fileName, segmentStartPos, segmentLength);
                            break;
                    }
                    segmentStartPos = i + 1; // remember start position for next segment
                }
            }
            if (isWeb == false)
            {
                if (isRelative)
                {
                    for (int j = 0; j < levelsBack; j++)
                    {
                        result.Insert(0, ".." + outputSeparator);
                    }
                }
                if (result.Length > 0 && result[result.Length - 1] == outputSeparator)
                {
                    result.Length -= 1;
                }
                if (result.Length == 2 && result[1] == ':')
                {
                    result.Append(outputSeparator);
                }
                if (result.Length == 0)
                    return ".";
            }
            return result.ToString();
        }
    }
}