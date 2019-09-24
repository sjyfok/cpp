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
            double num = Convert.ToDouble(Console.ReadLine());
            double rsl = Math.Sqrt(num);

            Console.WriteLine("{0:F3}\n", rsl);            
        }
    }
}