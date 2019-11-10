using System;
using System.ComponentModel;
using ICIDECode.NRefactory.TypeSystem;
using ICIDECode.Develop.Parser;
using ICIDECode.Develop.Project;

namespace ICIDECode.Develop.Dom
{
    /// <summary>
    /// An NRefactory symbol as a model.
    /// </summary>
    public interface ISymbolModel : INotifyPropertyChanged
    {
        /// <summary>
        /// Gets the name of the entity.
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Gets the symbol kind of the entity.
        /// </summary>
        SymbolKind SymbolKind { get; }

        /// <summary>
        /// Gets the parent project that contains this entity.
        /// May return null if the entity is not part of a project.
        /// </summary>
        IProject ParentProject { get; }

        /// <summary>
        /// Gets the region where this entity is defined.
        /// </summary>
        DomRegion Region { get; }
    }
}
