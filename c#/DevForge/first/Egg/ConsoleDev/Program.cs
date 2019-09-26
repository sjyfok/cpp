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
            double w = Convert.ToDouble(Console.ReadLine());
            double p = 0;
            if (w < 3)
                p = w * 7.60;
            else if (w >= 3)
                p = w * 7.60 * 0.8;

            Console.WriteLine("{0:F2}\n", p);            
        }
    }
}