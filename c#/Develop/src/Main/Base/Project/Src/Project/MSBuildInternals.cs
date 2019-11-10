﻿using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Build.Construction;
using Microsoft.Build.Execution;
using MSBuild = Microsoft.Build;

namespace ICIDECode.Develop.Project
{
    /// <summary>
    /// Messing with MSBuild's internals.
    /// </summary>
    public static class MSBuildInternals
    {
        /// <summary>
        /// SharpDevelop uses one project collection per solution.
        /// Code accessing one of those collections (even if indirectly through MSBuild) should lock on
        /// MSBuildInternals.SolutionProjectCollectionLock.
        /// </summary>
        public readonly static object SolutionProjectCollectionLock = new object();

        // TODO: I think MSBuild actually uses OrdinalIgnoreCase. SharpDevelop 3.x just used string.operator ==, so I'm keeping
        // that setting until all code is ported to use PropertyNameComparer and we've verified what MSBuild is actually using.
        public readonly static StringComparer PropertyNameComparer = StringComparer.Ordinal;
        public readonly static StringComparer ConfigurationNameComparer = ConfigurationAndPlatform.ConfigurationNameComparer;

        internal static void UnloadProject(MSBuild.Evaluation.ProjectCollection projectCollection, MSBuild.Evaluation.Project project)
        {
            lock (SolutionProjectCollectionLock)
            {
                projectCollection.UnloadProject(project);
            }
        }

        internal static MSBuild.Evaluation.Project LoadProject(MSBuild.Evaluation.ProjectCollection projectCollection, ProjectRootElement rootElement, IDictionary<string, string> globalProps)
        {
            lock (SolutionProjectCollectionLock)
            {
                string toolsVersion = rootElement.ToolsVersion;
                if (string.IsNullOrEmpty(toolsVersion))
                    toolsVersion = projectCollection.DefaultToolsVersion;
                return new MSBuild.Evaluation.Project(rootElement, globalProps, toolsVersion, projectCollection);
            }
        }

        internal static ProjectInstance LoadProjectInstance(MSBuild.Evaluation.ProjectCollection projectCollection, ProjectRootElement rootElement, IDictionary<string, string> globalProps)
        {
            lock (SolutionProjectCollectionLock)
            {
                string toolsVersion = rootElement.ToolsVersion;
                if (string.IsNullOrEmpty(toolsVersion))
                    toolsVersion = projectCollection.DefaultToolsVersion;
                return new ProjectInstance(rootElement, globalProps, toolsVersion, projectCollection);
            }
        }

        public static void AddMSBuildSolutionProperties(ISolution solution, IDictionary<string, string> propertyDict)
        {
            propertyDict["SolutionDir"] = solution.Directory.ToStringWithTrailingBackslash();
            propertyDict["SolutionExt"] = ".sln";
            propertyDict["SolutionFileName"] = solution.FileName.GetFileName();
            propertyDict["SolutionName"] = solution.Name ?? string.Empty;
            propertyDict["SolutionPath"] = solution.FileName;
        }

        public const string MSBuildXmlNamespace = "http://schemas.microsoft.com/developer/msbuild/2003";

        #region Escaping
        /// <summary>
        /// Escapes special MSBuild characters ( '%', '*', '?', '@', '$', '(', ')', ';', "'" ).
        /// </summary>
        public static string Escape(string text)
        {
            return MSBuild.Evaluation.ProjectCollection.Escape(text);
        }

        /// <summary>
        /// Unescapes escaped MSBuild characters.
        /// </summary>
        public static string Unescape(string text)
        {
            return MSBuild.Evaluation.ProjectCollection.Unescape(text);
        }
        #endregion

        /// <summary>
        /// This is a special case in MSBuild we need to take care of.
        /// </summary>
        public static string FixPlatformNameForProject(string platformName)
        {
            if (ConfigurationAndPlatform.ConfigurationNameComparer.Equals(platformName, "Any CPU"))
            {
                return "AnyCPU";
            }
            else
            {
                return platformName;
            }
        }

        /// <summary>
        /// This is a special case in MSBuild we need to take care of.
        /// Opposite of FixPlatformNameForProject
        /// </summary>
        public static string FixPlatformNameForSolution(string platformName)
        {
            if (ConfigurationAndPlatform.ConfigurationNameComparer.Equals(platformName, "AnyCPU"))
            {
                return "Any CPU";
            }
            else
            {
                return platformName;
            }
        }

        internal static PropertyStorageLocations GetLocationFromCondition(MSBuild.Construction.ProjectElement element)
        {
            while (element != null)
            {
                if (!string.IsNullOrEmpty(element.Condition))
                    return GetLocationFromCondition(element.Condition);
                element = element.Parent;
            }
            return PropertyStorageLocations.Base;
        }

        internal static PropertyStorageLocations GetLocationFromCondition(string condition)
        {
            if (string.IsNullOrEmpty(condition))
            {
                return PropertyStorageLocations.Base;
            }
            PropertyStorageLocations location = 0; // 0 is unknown
            if (condition.IndexOf("$(Configuration)", StringComparison.OrdinalIgnoreCase) >= 0)
                location |= PropertyStorageLocations.ConfigurationSpecific;
            if (condition.IndexOf("$(Platform)", StringComparison.OrdinalIgnoreCase) >= 0)
                location |= PropertyStorageLocations.PlatformSpecific;
            return location;
        }
    }
}
