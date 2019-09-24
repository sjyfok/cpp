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
            double f = Convert.ToDouble(Console.ReadLine());
            double t = (f - 32) * 5 / 9;          

            Console.WriteLine("{0:F2}\n", t);            
        }
    }
}