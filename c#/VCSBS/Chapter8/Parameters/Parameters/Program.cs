#region using directives

using System;
using System.Collections.Generic;
using System.Text;

#endregion

namespace Parameters
{
    class Program
    {
        static void doWork()
        {
            int i = 0;
            Console.WriteLine(i);
            Pass.Value(i);
            Console.WriteLine(i);

            int j = 0;
            Console.WriteLine(j);
            Pass.RefValue(ref j);
            Console.WriteLine(j);

            int k=0;
            Console.WriteLine(k);
            Pass.OutValue(out k);
            Console.WriteLine(k);

            WrappedInt wi = new WrappedInt();
            Console.WriteLine(wi.Number);
            Pass.Reference(wi);
            Console.WriteLine(wi.Number);
        }

        static void Main(string[] args)
        {
            try
            {
                doWork();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
