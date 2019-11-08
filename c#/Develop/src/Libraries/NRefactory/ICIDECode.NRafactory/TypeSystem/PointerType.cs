﻿using System;
using System.Collections.Generic;
using ICIDECode.NRefactory.TypeSystem.Implementation;

namespace ICIDECode.NRefactory.TypeSystem
{
    public sealed class PointerType : TypeWithElementType
    {
        public PointerType(IType elementType) : base(elementType)
        {
        }

        public override TypeKind Kind
        {
            get { return TypeKind.Pointer; }
        }

        public override string NameSuffix
        {
            get
            {
                return "*";
            }
        }

        public override bool? IsReferenceType
        {
            get { return null; }
        }

        public override int GetHashCode()
        {
            return elementType.GetHashCode() ^ 91725811;
        }

        public override bool Equals(IType other)
        {
            PointerType a = other as PointerType;
            return a != null && elementType.Equals(a.elementType);
        }

        public override IType AcceptVisitor(TypeVisitor visitor)
        {
            return visitor.VisitPointerType(this);
        }

        public override IType VisitChildren(TypeVisitor visitor)
        {
            IType e = elementType.AcceptVisitor(visitor);
            if (e == elementType)
                return this;
            else
                return new PointerType(e);
        }

        public override ITypeReference ToTypeReference()
        {
            return new PointerTypeReference(elementType.ToTypeReference());
        }
    }

    [Serializable]
    public sealed class PointerTypeReference : ITypeReference, ISupportsInterning
    {
        readonly ITypeReference elementType;

        public PointerTypeReference(ITypeReference elementType)
        {
            if (elementType == null)
                throw new ArgumentNullException("elementType");
            this.elementType = elementType;
        }

        public ITypeReference ElementType
        {
            get { return elementType; }
        }

        public IType Resolve(ITypeResolveContext context)
        {
            return new PointerType(elementType.Resolve(context));
        }

        public override string ToString()
        {
            return elementType.ToString() + "*";
        }

        int ISupportsInterning.GetHashCodeForInterning()
        {
            return elementType.GetHashCode() ^ 91725812;
        }

        bool ISupportsInterning.EqualsForInterning(ISupportsInterning other)
        {
            PointerTypeReference o = other as PointerTypeReference;
            return o != null && this.elementType == o.elementType;
        }
    }
}
