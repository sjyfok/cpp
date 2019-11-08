using System;
using ICIDECode.NRefactory.TypeSystem;

namespace ICIDECode.NRefactory.Semantics
{
    /// <summary>
    /// The resolved expression refers to a type name.
    /// </summary>
    public class TypeResolveResult : ResolveResult
    {
        public TypeResolveResult(IType type)
            : base(type)
        {
        }

        public override bool IsError
        {
            get { return this.Type.Kind == TypeKind.Unknown; }
        }

        public override DomRegion GetDefinitionRegion()
        {
            ITypeDefinition def = this.Type.GetDefinition();
            if (def != null)
                return def.Region;
            else
                return DomRegion.Empty;
        }
    }
}
