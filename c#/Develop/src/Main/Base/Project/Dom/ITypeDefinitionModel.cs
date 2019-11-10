﻿using System;
using System.Collections.Generic;
using ICIDECode.NRefactory.TypeSystem;
using ICIDECode.Develop.Parser;

namespace ICIDECode.Develop.Dom
{
    /// <summary>
    /// Observable model for a type definition.
    /// </summary>
    public interface ITypeDefinitionModel : IEntityModel
    {
        event EventHandler Updated;

        FullTypeName FullTypeName { get; }
        string Namespace { get; }
        TypeKind TypeKind { get; }
        IModelCollection<ITypeDefinitionModel> NestedTypes { get; }
        IModelCollection<IMemberModel> Members { get; }

        IEnumerable<DomRegion> GetPartRegions();

        /// <summary>
        /// Resolves the type definition in the current compilation.
        /// Returns null if the type definition could not be resolved.
        /// </summary>
        new ITypeDefinition Resolve();

        /// <summary>
        /// Resolves the type definition in the specified compilation.
        /// Returns null if the type definition could not be resolved.
        /// </summary>
        new ITypeDefinition Resolve(ICompilation compilation);

        /// <summary>
        /// Retrieves the nested type with the specified name and additional type parameter count
        /// </summary>
        ITypeDefinitionModel GetNestedType(string name, int additionalTypeParameterCount);

        bool IsPartial { get; }
    }
}
