﻿
using System;
using System.Diagnostics.Contracts;
using ICIDECode.NRefactory.Semantics;

namespace ICIDECode.NRefactory.TypeSystem
{
    /// <summary>
    /// Represents an unresolved constant value.
    /// </summary>
    public interface IConstantValue
    {
        /// <summary>
        /// Resolves the value of this constant.
        /// </summary>
        /// <param name="context">Context where the constant value will be used.</param>
        /// <returns>Resolve result representing the constant value.
        /// This method never returns null; in case of errors, an ErrorResolveResult will be returned.</returns>
        ResolveResult Resolve(ITypeResolveContext context);
    }
}
