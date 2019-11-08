using System;
using System.Collections.Generic;
using ICIDECode.NRefactory.Documentation;

namespace ICIDECode.NRefactory.TypeSystem.Implementation
{
    /// <summary>
    /// Implementation of <see cref="IEntity"/> that resolves an unresolved entity.
    /// </summary>
    public abstract class AbstractResolvedEntity : IEntity
    {
        protected readonly IUnresolvedEntity unresolved;
        protected readonly ITypeResolveContext parentContext;

        protected AbstractResolvedEntity(IUnresolvedEntity unresolved, ITypeResolveContext parentContext)
        {
            if (unresolved == null)
                throw new ArgumentNullException("unresolved");
            if (parentContext == null)
                throw new ArgumentNullException("parentContext");
            this.unresolved = unresolved;
            this.parentContext = parentContext;
            this.Attributes = unresolved.Attributes.CreateResolvedAttributes(parentContext);
        }

        public SymbolKind SymbolKind
        {
            get { return unresolved.SymbolKind; }
        }

        

        public DomRegion Region
        {
            get { return unresolved.Region; }
        }

        public DomRegion BodyRegion
        {
            get { return unresolved.BodyRegion; }
        }

        public ITypeDefinition DeclaringTypeDefinition
        {
            get { return parentContext.CurrentTypeDefinition; }
        }

        public virtual IType DeclaringType
        {
            get { return parentContext.CurrentTypeDefinition ?? (IType)SpecialType.UnknownType; }
        }

        public IAssembly ParentAssembly
        {
            get { return parentContext.CurrentAssembly; }
        }

        public IList<IAttribute> Attributes { get; protected set; }

        public virtual DocumentationComment Documentation
        {
            get
            {
                IDocumentationProvider provider = FindDocumentation(parentContext);
                if (provider != null)
                    return provider.GetDocumentation(this);
                else
                    return null;
            }
        }

        [Obsolete("Use the SymbolKind property instead.")]
        public EntityType EntityType
        {
            get { return (EntityType)unresolved.SymbolKind; }
        }

        internal static IDocumentationProvider FindDocumentation(ITypeResolveContext context)
        {
            IAssembly asm = context.CurrentAssembly;
            if (asm != null)
                return asm.UnresolvedAssembly as IDocumentationProvider;
            else
                return null;
        }

        public abstract ISymbolReference ToReference();

        public bool IsStatic { get { return unresolved.IsStatic; } }
        public bool IsAbstract { get { return unresolved.IsAbstract; } }
        public bool IsSealed { get { return unresolved.IsSealed; } }
        public bool IsShadowing { get { return unresolved.IsShadowing; } }
        public bool IsSynthetic { get { return unresolved.IsSynthetic; } }

        public ICompilation Compilation
        {
            get { return parentContext.Compilation; }
        }

        public string FullName { get { return unresolved.FullName; } }
        public string Name { get { return unresolved.Name; } }
        public string ReflectionName { get { return unresolved.ReflectionName; } }
        public string Namespace { get { return unresolved.Namespace; } }

        public Accessibility Accessibility { get { return unresolved.Accessibility; } }
        public bool IsPrivate { get { return unresolved.IsPrivate; } }
        public bool IsPublic { get { return unresolved.IsPublic; } }
        public bool IsProtected { get { return unresolved.IsProtected; } }
        public bool IsInternal { get { return unresolved.IsInternal; } }
        public bool IsProtectedOrInternal { get { return unresolved.IsProtectedOrInternal; } }
        public bool IsProtectedAndInternal { get { return unresolved.IsProtectedAndInternal; } }

        public override string ToString()
        {
            return "[" + this.SymbolKind.ToString() + " " + this.ReflectionName + "]";
        }
    }
}
