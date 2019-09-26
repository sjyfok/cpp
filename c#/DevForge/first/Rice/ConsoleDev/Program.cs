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

            if (w <= 1)
                Console.WriteLine("1");
            else if (w <= 3)
                Console.WriteLine("2");
            else if (w <= 5)
                Console.WriteLine("3");             
        }
    }
}
