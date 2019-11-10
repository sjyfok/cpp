using System;

namespace ICIDECode.Develop.Project
{
    public interface IConfigurable
    {
        /// <summary>
        /// Gets the list of available configuration names.
        /// </summary>
        IConfigurationOrPlatformNameCollection ConfigurationNames { get; }

        /// <summary>
        /// Gets the list of available platform names.
        /// </summary>
        IConfigurationOrPlatformNameCollection PlatformNames { get; }

        /// <summary>
        /// Gets/Sets the active configuration+platform of the solution.
        /// </summary>
        /// <remarks>
        /// After changing this property on the solution, the change will be automatically applied
        /// to the projects (using the solution &lt;-&gt; project configuration mapping).
        /// </remarks>
        ConfigurationAndPlatform ActiveConfiguration { get; set; }

        /// <summary>
        /// Is raised after the ActiveConfiguration property has changed.
        /// </summary>
        event EventHandler ActiveConfigurationChanged;
    }
}
