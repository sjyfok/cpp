using System;

namespace ICIDECode.Core
{
    public interface IStringTagProvider
    {
        string ProvideString(string tag, StringTagPair[] customTags);
    }
}
