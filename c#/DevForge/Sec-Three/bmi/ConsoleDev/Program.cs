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
            double h = Convert.ToDouble(Console.ReadLine());
            double w = Convert.ToDouble(Console.ReadLine());
            string male = Console.ReadLine();
            double bmi = w / h / h;
            if (male == "female")
            {
                if (bmi < 19)
                    Console.WriteLine("Underweight");
                else if (bmi <= 24)
                    if (bmi == 22)
                        Console.WriteLine("Perfect");
                    else
                        Console.WriteLine("Moderate");
                else if (bmi <= 29)
                    Console.WriteLine("Overweight");
                else if (bmi <= 34)
                    Console.WriteLine("Fat");
                else if (bmi > 34)
                    Console.WriteLine("Very fat");
            }
            else
            {
                if (bmi < 20)
                    Console.WriteLine("Underweight");
                else if (bmi <= 25)
                    if (bmi == 22)
                        Console.WriteLine("Perfect");
                else
                    Console.WriteLine("Moderate");
                else if (bmi <= 30)
                    Console.WriteLine("Overweight");
                else if (bmi <= 35)
                    Console.WriteLine("Fat");
                else if (bmi > 35)
                    Console.WriteLine("Very fat");
            }

        }
    }
}
