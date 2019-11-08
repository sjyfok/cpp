using System;

namespace ICIDECode.NRefactory.TypeSystem
{
    [Obsolete("Use SymbolKind instead")]
    public enum EntityType : byte
    {
        None = SymbolKind.None,
        /// <seealso cref="ITypeDefinition"/>
        TypeDefinition = SymbolKind.TypeDefinition,
        /// <seealso cref="IField"/>
        Field = SymbolKind.Field,
        /// <summary>
        /// The symbol is a property, but not an indexer.
        /// </summary>
        /// <seealso cref="IProperty"/>
        Property = SymbolKind.Property,
        /// <summary>
        /// The symbol is an indexer, not a regular property.
        /// </summary>
        /// <seealso cref="IProperty"/>
        Indexer = SymbolKind.Indexer,
        /// <seealso cref="IEvent"/>
        Event = SymbolKind.Event,
        /// <summary>
        /// The symbol is a method which is not an operator/constructor/destructor or accessor.
        /// </summary>
        /// <seealso cref="IMethod"/>
        Method = SymbolKind.Method,
        /// <summary>
        /// The symbol is a user-defined operator.
        /// </summary>
        /// <seealso cref="IMethod"/>
        Operator = SymbolKind.Operator,
        /// <seealso cref="IMethod"/>
        Constructor = SymbolKind.Constructor,
        /// <seealso cref="IMethod"/>
        Destructor = SymbolKind.Destructor,
        /// <summary>
        /// The accessor method for a property getter/setter or event add/remove.
        /// </summary>
        /// <seealso cref="IMethod"/>
        Accessor = SymbolKind.Accessor,
    }
}
