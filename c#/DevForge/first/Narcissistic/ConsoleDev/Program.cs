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
            int d1, d2, d3;
            d1 = num / 100;
            d2 = num % 100;
            d3 = d2;
            d2 /= 10;
            d3 %= 10;
            if (d1 * d1*d1 + d2*d2 * d2 + d3*d3 * d3 == num)
                Console.WriteLine("yes");
            else
                Console.WriteLine("no");
        }
    }
}
