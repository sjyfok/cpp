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
            double cx1 = 2, cy1 = 2;
            double cx2 = -2, cy2 = 2;
            double cx3 = 2, cy3 = -2;
            double cx4 = -2, cy4 = -2;

            double x = Convert.ToDouble(Console.ReadLine());
            double y = Convert.ToDouble(Console.ReadLine());

            double d = Math.Sqrt(Math.Pow((x - cx1), 2) + Math.Pow((y - cy1), 2));
            if (d <= 1)
                Console.WriteLine("10");
            else
            {
                d = Math.Sqrt(Math.Pow((x - cx2), 2) + Math.Pow((y - cy2), 2));
                if (d <= 1)
                    Console.WriteLine("10");
                else
                {
                    d = Math.Sqrt(Math.Pow((x - cx3), 2) + Math.Pow((y - cy3), 2));
                    if (d <= 1)
                        Console.WriteLine("10");
                    else
                    {
                        d = Math.Sqrt(Math.Pow((x - cx4), 2) + Math.Pow((y - cy4), 2));
                        if (d <= 1)
                            Console.WriteLine("10");
                        else
                            Console.WriteLine("0");
                    }
                }
            }     
        }
    }
}
