using System;
using Extensions;

namespace ExtensionMethod
{
    class Program
    {
        static void doWork()
        {
            int x = 591;
            for(int i = 2; i <= 10; i ++)
            {
                //注意两种调用方式
                //Console.WriteLine($"{x} in base{i} is {x.ConvertToBase(i)}");
                Console.WriteLine($"{x} in base{i} is {Util.ConvertToBase(x, i)}");
            }
        }

        static void Main()
        {
            try
            {
                doWork();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception: {0}", ex.Message);
            }
        }
    }
}
