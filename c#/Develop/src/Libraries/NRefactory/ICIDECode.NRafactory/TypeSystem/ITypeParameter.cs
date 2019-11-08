﻿
using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using ICIDECode.NRefactory.TypeSystem;

namespace ICIDECode.NRefactory.TypeSystem
{
    /// <summary>
    /// Type parameter of a generic class/method.
    /// </summary>
    public interface IUnresolvedTypeParameter : INamedElement
    {
        /// <summary>
        /// Get the type of this type parameter's owner.
        /// </summary>
        /// <returns>SymbolKind.TypeDefinition or SymbolKind.Method</returns>
        SymbolKind OwnerType { get; }

        /// <summary>
        /// Gets the index of the type parameter in the type parameter list of the owning method/class.
        /// </summary>
        int Index { get; }

        /// <summary>
        /// Gets the list of attributes declared on this type parameter.
        /// </summary>
        IList<IUnresolvedAttribute> Attributes { get; }

        /// <summary>
        /// Gets the variance of this type parameter.
        /// </summary>
        VarianceModifier Variance { get; }

        /// <summary>
        /// Gets the region where the type parameter is defined.
        /// </summary>
        DomRegion Region { get; }

        ITypeParameter CreateResolvedTypeParameter(ITypeResolveContext context);
    }

    /// <summary>
    /// Type parameter of a generic class/method.
    /// </summary>
    public interface ITypeParameter : IType, ISymbol
    {
        /// <summary>
        /// Get the type of this type parameter's owner.
        /// </summary>
        /// <returns>SymbolKind.TypeDefinition or SymbolKind.Method</returns>
        SymbolKind OwnerType { get; }

        /// <summary>
        /// Gets the owning method/class.
        /// This property may return null (for example for the dummy type parameters used by <see cref="ParameterListComparer.NormalizeMethodTypeParameters"/>).
        /// </summary>
        /// <remarks>
        /// For "class Outer&lt;T&gt; { class Inner {} }",
        /// inner.TypeParameters[0].Owner will be the outer class, because the same
        /// ITypeParameter instance is used both on Outer`1 and Outer`1+Inner.
        /// </remarks>
        IEntity Owner { get; }

        /// <summary>
        /// Gets the index of the type parameter in the type parameter list of the owning method/class.
        /// </summary>
        int Index { get; }

        /// <summary>
        /// Gets the name of the type parameter.
        /// </summary>
        new string Name { get; }

        /// <summary>
        /// Gets the list of attributes declared on this type parameter.
        /// </summary>
        IList<IAttribute> Attributes { get; }

        /// <summary>
        /// Gets the variance of this type parameter.
        /// </summary>
        VarianceModifier Variance { get; }

        /// <summary>
        /// Gets the region where the type parameter is defined.
        /// </summary>
        DomRegion Region { get; }

        /// <summary>
        /// Gets the effective base class of this type parameter.
        /// </summary>
        IType EffectiveBaseClass { get; }

        /// <summary>
        /// Gets the effective interface set of this type parameter.
        /// </summary>
        ICollection<IType> EffectiveInterfaceSet { get; }

        /// <summary>
        /// Gets if the type parameter has the 'new()' constraint.
        /// </summary>
        bool HasDefaultConstructorConstraint { get; }

        /// <summary>
        /// Gets if the type parameter has the 'class' constraint.
        /// </summary>
        bool HasReferenceTypeConstraint { get; }

        /// <summary>
        /// Gets if the type parameter has the 'struct' constraint.
        /// </summary>
        bool HasValueTypeConstraint { get; }
    }

    /// <summary>
    /// Represents the variance of a type parameter.
    /// </summary>
    public enum VarianceModifier : byte
    {
        /// <summary>
        /// The type parameter is not variant.
        /// </summary>
        Invariant,
        /// <summary>
        /// The type parameter is covariant (used in output position).
        /// </summary>
        Covariant,
        /// <summary>
        /// The type parameter is contravariant (used in input position).
        /// </summary>
        Contravariant
    };
}
