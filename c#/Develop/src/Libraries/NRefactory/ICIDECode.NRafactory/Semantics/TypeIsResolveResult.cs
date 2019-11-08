﻿
using System;
using ICIDECode.NRefactory.TypeSystem;

namespace ICIDECode.NRefactory.Semantics
{
    /// <summary>
    /// Resolve result for a C# 'is' expression.
    /// "Input is TargetType".
    /// </summary>
    public class TypeIsResolveResult : ResolveResult
    {
        public readonly ResolveResult Input;
        /// <summary>
        /// Type that is being compared with.
        /// </summary>
        public readonly IType TargetType;

        public TypeIsResolveResult(ResolveResult input, IType targetType, IType booleanType)
            : base(booleanType)
        {
            if (input == null)
                throw new ArgumentNullException("input");
            if (targetType == null)
                throw new ArgumentNullException("targetType");
            this.Input = input;
            this.TargetType = targetType;
        }
    }
}
