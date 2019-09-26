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
            string strInput = Console.ReadLine();
            string[] nr = strInput.Split(' ');
            double N = Convert.ToDouble(nr[0]);
            double R = Convert.ToDouble(nr[1]);
            double S = N * R / 2 * R / 2 / Math.Tan(3.14 / N);
            Console.WriteLine("{0:f2}", S);
        }
    }
}
