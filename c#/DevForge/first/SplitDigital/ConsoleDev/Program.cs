using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleDev
{
    class Program
    {
        static void Main(string[] args)
        {
            int num = Convert.ToInt32(Console.ReadLine());
            int d;
            d = num/100;
            num %= 100;
            Console.Write("{0} ", d);
            d = num / 10;
            num %= 10;
            Console.Write("{0} ", d);
            Console.WriteLine("{0}", num);
        }
    }
}