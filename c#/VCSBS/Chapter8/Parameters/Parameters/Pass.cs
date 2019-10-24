using System;

namespace Parameters
{
    class Pass
    {
        public static void Value(int param)
        {
            param = 56;
        }

        public static void RefValue(ref int param)
        {
            param = 56;
        }

        public static void OutValue(out int param)
        {
            param = 56;
        }


        public static void Reference(WrappedInt param)
        {
            param.Number = 56;
        }
    }
}
