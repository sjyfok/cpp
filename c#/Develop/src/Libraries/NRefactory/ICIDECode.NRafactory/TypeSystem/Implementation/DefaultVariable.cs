
using System;

namespace ICIDECode.NRefactory.TypeSystem.Implementation
{
    /// <summary>
    /// Default implementation of <see cref="IVariable"/>.
    /// </summary>
    public sealed class DefaultVariable : IVariable
    {
        readonly string name;
        readonly DomRegion region;
        readonly IType type;
        readonly object constantValue;
        readonly bool isConst;

        public DefaultVariable(IType type, string name)
        {
            if (type == null)
                throw new ArgumentNullException("type");
            if (name == null)
                throw new ArgumentNullException("name");
            this.type = type;
            this.name = name;
        }

        public DefaultVariable(IType type, string name, DomRegion region = default(DomRegion),
                               bool isConst = false, object constantValue = null)
            : this(type, name)
        {
            this.region = region;
            this.isConst = isConst;
            this.constantValue = constantValue;
        }

        public string Name
        {
            get { return name; }
        }

        public DomRegion Region
        {
            get { return region; }
        }

        public IType Type
        {
            get { return type; }
        }

        public bool IsConst
        {
            get { return isConst; }
        }

        public object ConstantValue
        {
            get { return constantValue; }
        }

        public SymbolKind SymbolKind
        {
            get { return SymbolKind.Variable; }
        }

        public ISymbolReference ToReference()
        {
            return new VariableReference(type.ToTypeReference(), name, region, isConst, constantValue);
        }
    }

    public sealed class VariableReference : ISymbolReference
    {
        ITypeReference variableTypeReference;
        string name;
        DomRegion region;
        bool isConst;
        object constantValue;

        public VariableReference(ITypeReference variableTypeReference, string name, DomRegion region, bool isConst, object constantValue)
        {
            if (variableTypeReference == null)
                throw new ArgumentNullException("variableTypeReference");
            if (name == null)
                throw new ArgumentNullException("name");
            this.variableTypeReference = variableTypeReference;
            this.name = name;
            this.region = region;
            this.isConst = isConst;
            this.constantValue = constantValue;
        }

        public ISymbol Resolve(ITypeResolveContext context)
        {
            return new DefaultVariable(variableTypeReference.Resolve(context), name, region, isConst, constantValue);
        }
    }
}
