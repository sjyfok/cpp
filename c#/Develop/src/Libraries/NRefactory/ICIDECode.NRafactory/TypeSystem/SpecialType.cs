using System;
using System.Collections.Generic;
using ICIDECode.NRefactory.TypeSystem.Implementation;

namespace ICIDECode.NRefactory.TypeSystem
{
    /// <summary>
    /// Contains static implementations of special types.
    /// </summary>
    [Serializable]
    public sealed class SpecialType : AbstractType, ITypeReference
    {
        /// <summary>
        /// Gets the type representing resolve errors.
        /// </summary>
        public readonly static SpecialType UnknownType = new SpecialType(TypeKind.Unknown, "?", isReferenceType: null);

        /// <summary>
        /// The null type is used as type of the null literal. It is a reference type without any members; and it is a subtype of all reference types.
        /// </summary>
        public readonly static SpecialType NullType = new SpecialType(TypeKind.Null, "null", isReferenceType: true);

        /// <summary>
        /// Type representing the C# 'dynamic' type.
        /// </summary>
        public readonly static SpecialType Dynamic = new SpecialType(TypeKind.Dynamic, "dynamic", isReferenceType: true);

        /// <summary>
        /// A type used for unbound type arguments in partially parameterized types.
        /// </summary>
        /// <see cref="IType.GetNestedTypes(Predicate{ITypeDefinition}, GetMemberOptions)"/>
        public readonly static SpecialType UnboundTypeArgument = new SpecialType(TypeKind.UnboundTypeArgument, "", isReferenceType: null);

        readonly TypeKind kind;
        readonly string name;
        readonly bool? isReferenceType;

        private SpecialType(TypeKind kind, string name, bool? isReferenceType)
        {
            this.kind = kind;
            this.name = name;
            this.isReferenceType = isReferenceType;
        }

        public override ITypeReference ToTypeReference()
        {
            return this;
        }

        public override string Name
        {
            get { return name; }
        }

        public override TypeKind Kind
        {
            get { return kind; }
        }

        public override bool? IsReferenceType
        {
            get { return isReferenceType; }
        }

        IType ITypeReference.Resolve(ITypeResolveContext context)
        {
            if (context == null)
                throw new ArgumentNullException("context");
            return this;
        }

#pragma warning disable 809
        [Obsolete("Please compare special types using the kind property instead.")]
        public override bool Equals(IType other)
        {
            // We consider a special types equal when they have equal types.
            // However, an unknown type with additional information is not considered to be equal to the SpecialType with TypeKind.Unknown.
            return other is SpecialType && other.Kind == kind;
        }

        public override int GetHashCode()
        {
            return 81625621 ^ (int)kind;
        }
    }
}
