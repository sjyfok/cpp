using System;
using ICIDECode.NRefactory.Editor;
using ICIDECode.NRefactory.TypeSystem;

namespace ICIDECode.NRefactory.Documentation
{
    /// <summary>
    /// Represents a documentation comment.
    /// </summary>
    public class DocumentationComment
    {
        ITextSource xml;
        protected readonly ITypeResolveContext context;

        /// <summary>
        /// Gets the XML code for this documentation comment.
        /// </summary>
        public ITextSource Xml
        {
            get { return xml; }
        }

        /// <summary>
        /// Creates a new DocumentationComment.
        /// </summary>
        /// <param name="xml">The XML text.</param>
        /// <param name="context">Context for resolving cref attributes.</param>
        public DocumentationComment(ITextSource xml, ITypeResolveContext context)
        {
            if (xml == null)
                throw new ArgumentNullException("xml");
            if (context == null)
                throw new ArgumentNullException("context");
            this.xml = xml;
            this.context = context;
        }

        /// <summary>
        /// Creates a new DocumentationComment.
        /// </summary>
        /// <param name="xml">The XML text.</param>
        /// <param name="context">Context for resolving cref attributes.</param>
        public DocumentationComment(string xml, ITypeResolveContext context)
        {
            if (xml == null)
                throw new ArgumentNullException("xml");
            if (context == null)
                throw new ArgumentNullException("context");
            this.xml = new StringTextSource(xml);
            this.context = context;
        }

        /// <summary>
        /// Resolves the given cref value to an entity.
        /// Returns null if the entity is not found, or if the cref attribute is syntactically invalid.
        /// </summary>
        public virtual IEntity ResolveCref(string cref)
        {
            try
            {
                return IdStringProvider.FindEntity(cref, context);
            }
            catch (ReflectionNameParseException)
            {
                return null;
            }
        }

        public override string ToString()
        {
            return Xml.Text;
        }

        public static implicit operator string(DocumentationComment documentationComment)
        {
            if (documentationComment != null)
                return documentationComment.ToString();
            return null;
        }
    }
}
