using System;
using ICIDECode.NRefactory.TypeSystem;

namespace ICIDECode.NRefactory.Documentation
{
    [Serializable]
    class IdStringMemberReference : IMemberReference
    {
        readonly ITypeReference declaringTypeReference;
        readonly char memberType;
        readonly string memberIdString;

        public IdStringMemberReference(ITypeReference declaringTypeReference, char memberType, string memberIdString)
        {
            this.declaringTypeReference = declaringTypeReference;
            this.memberType = memberType;
            this.memberIdString = memberIdString;
        }

        bool CanMatch(IUnresolvedMember member)
        {
            switch (member.SymbolKind)
            {
                case SymbolKind.Field:
                    return memberType == 'F';
                case SymbolKind.Property:
                case SymbolKind.Indexer:
                    return memberType == 'P';
                case SymbolKind.Event:
                    return memberType == 'E';
                case SymbolKind.Method:
                case SymbolKind.Operator:
                case SymbolKind.Constructor:
                case SymbolKind.Destructor:
                    return memberType == 'M';
                default:
                    throw new NotSupportedException(member.SymbolKind.ToString());
            }
        }

        public ITypeReference DeclaringTypeReference
        {
            get { return declaringTypeReference; }
        }

        public IMember Resolve(ITypeResolveContext context)
        {
            IType declaringType = declaringTypeReference.Resolve(context);
            foreach (var member in declaringType.GetMembers(CanMatch, GetMemberOptions.IgnoreInheritedMembers))
            {
                if (IdStringProvider.GetIdString(member) == memberIdString)
                    return member;
            }
            return null;
        }

        ISymbol ISymbolReference.Resolve(ITypeResolveContext context)
        {
            return Resolve(context);
        }
    }
}
