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
            double x;
            double y;
         
            x = Convert.ToDouble(Console.ReadLine());
            y = 3 * Math.Pow(x, 4) - 2 * Math.Pow(x, 3) - Math.Pow(x, 2) + 10;
            Console.WriteLine("{0:f1}", y);
        }
    }
}
