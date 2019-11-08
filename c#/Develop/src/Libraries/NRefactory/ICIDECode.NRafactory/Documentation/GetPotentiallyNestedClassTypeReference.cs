using System;
using System.Linq;
using ICIDECode.NRefactory.TypeSystem;
using ICIDECode.NRefactory.TypeSystem.Implementation;

namespace ICIDECode.NRefactory.Documentation
{
    /// <summary>
    /// A type reference of the form 'Some.Namespace.TopLevelType.NestedType`n'.
    /// We do not know the boundary between namespace name and top level type, so we have to try
    /// all possibilities.
    /// The type parameter count only applies to the innermost type, all outer types must be non-generic.
    /// </summary>
    [Serializable]
    class GetPotentiallyNestedClassTypeReference : ITypeReference
    {
        readonly string typeName;
        readonly int typeParameterCount;

        public GetPotentiallyNestedClassTypeReference(string typeName, int typeParameterCount)
        {
            this.typeName = typeName;
            this.typeParameterCount = typeParameterCount;
        }

        public IType Resolve(ITypeResolveContext context)
        {
            string[] parts = typeName.Split('.');
            var assemblies = new[] { context.CurrentAssembly }.Concat(context.Compilation.Assemblies);
            for (int i = parts.Length - 1; i >= 0; i--)
            {
                string ns = string.Join(".", parts, 0, i);
                string name = parts[i];
                int topLevelTPC = (i == parts.Length - 1 ? typeParameterCount : 0);
                foreach (var asm in assemblies)
                {
                    if (asm == null)
                        continue;
                    ITypeDefinition typeDef = asm.GetTypeDefinition(new TopLevelTypeName(ns, name, topLevelTPC));
                    for (int j = i + 1; j < parts.Length && typeDef != null; j++)
                    {
                        int tpc = (j == parts.Length - 1 ? typeParameterCount : 0);
                        typeDef = typeDef.NestedTypes.FirstOrDefault(n => n.Name == parts[j] && n.TypeParameterCount == tpc);
                    }
                    if (typeDef != null)
                        return typeDef;
                }
            }
            int idx = typeName.LastIndexOf('.');
            if (idx < 0)
                return new UnknownType("", typeName, typeParameterCount);
            // give back a guessed namespace/type name
            return new UnknownType(typeName.Substring(0, idx), typeName.Substring(idx + 1), typeParameterCount);
        }
    }
}
