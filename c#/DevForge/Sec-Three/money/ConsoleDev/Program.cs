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
            int M = Convert.ToInt32(Console.ReadLine());
            int D = Convert.ToInt32(Console.ReadLine());           
            string C = Console.ReadLine();
            Double p = Convert.ToDouble(Console.ReadLine());
            if (M == 5 && (D >= 1 && D <= 3))
                p *= 0.75;
            else if (C == "yes" && (D == 1 || D == 11 || D == 21))
                p *= 0.85;
            else if (M == 3 && D == 15)
                p *= 0.7;

            Console.WriteLine("{0:f2}", p);
        }
    }
}
