using System;
using System.ComponentModel;
using ICIDECode.NRefactory.TypeSystem;
using ICIDECode.Develop.Parser;
using ICIDECode.Develop.Project;

namespace ICIDECode.Develop.Dom
{
    /// <summary>
    /// An NRefactory entity as a model.
    /// </summary>
    public interface IEntityModel : ISymbolModel
    {
        /// <summary>
        /// Gets/sets the accessibility of the entity.
        /// </summary>
        Accessibility Accessibility { get; }

        /// <summary>
        /// Gets whether this entity is static.
        /// Returns true if either the 'static' or the 'const' modifier is set.
        /// </summary>
        bool IsStatic { get; }

        /// <summary>
        /// Returns whether this entity is abstract.
        /// </summary>
        /// <remarks>Static classes also count as abstract classes.</remarks>
        bool IsAbstract { get; }

        /// <summary>
        /// Returns whether this entity is sealed.
        /// </summary>
        /// <remarks>Static classes also count as sealed classes.</remarks>
        bool IsSealed { get; }

        /// <summary>
        /// Gets whether this member is declared to be shadowing another member with the same name.
        /// (C# 'new' keyword)
        /// </summary>
        bool IsShadowing { get; }

        /// <summary>
        /// Resolves the entity in the current compilation.
        /// Returns null if the entity could not be resolved.
        /// </summary>
        IEntity Resolve();

        /// <summary>
        /// Resolves the entity in the specified compilation.
        /// Returns null if the entity could not be resolved.
        /// </summary>
        IEntity Resolve(ICompilation compilation);
    }
}
