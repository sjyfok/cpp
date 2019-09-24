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
            double pi = 3.14;
            double r = Convert.ToDouble(Console.ReadLine());
            double l, s;
            l = 2 * pi * r;
            s = pi * r * r;
            Console.WriteLine("{0:f2} {1:f2}", s, l);
        }
    }
}
