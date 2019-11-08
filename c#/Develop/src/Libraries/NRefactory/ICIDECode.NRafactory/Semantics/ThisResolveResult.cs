using System;
using ICIDECode.NRefactory.TypeSystem;

namespace ICIDECode.NRefactory.Semantics
{
    /// <summary>
    /// Represents the 'this' reference.
    /// Also used for the 'base' reference.
    /// </summary>
    public class ThisResolveResult : ResolveResult
    {
        bool causesNonVirtualInvocation;

        public ThisResolveResult(IType type, bool causesNonVirtualInvocation = false) : base(type)
        {
            this.causesNonVirtualInvocation = causesNonVirtualInvocation;
        }

        /// <summary>
        /// Gets whether this resolve result causes member invocations to be non-virtual.
        /// </summary>
        public bool CausesNonVirtualInvocation
        {
            get { return causesNonVirtualInvocation; }
        }
    }
}
