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
            double x = Convert.ToDouble(Console.ReadLine());
            double y;
            if (x < 0)
            {
                y = (x + 1) * (x + 1) + 2 * x + 1 / x;

               
            }
            else
            {
                y = Math.Sqrt(x);
               
            }
            Console.WriteLine("{0:f2}", y);

        }
    }
}
