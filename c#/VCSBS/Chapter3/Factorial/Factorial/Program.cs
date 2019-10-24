using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Factorial
{
    class Program
    {
        static void Main(string[] args)
        {
            (new Program()).Run();
        }

        void Run()
        {
            Console.Write("Please enter a positive integer: ");
            string inputValue = Console.ReadLine();
            long factorialValue = CalculateFactorial(inputValue);
            Console.WriteLine($"Factorial({inputValue}) is {factorialValue}");
        }

        private long CalculateFactorial(string inputValue)
        {
            //throw new NotImplementedException();
            int input = int.Parse(inputValue);
            long factorial(int dataValue)
            {
                if (dataValue == 1)
                    return 1;
                else
                    return dataValue * factorial(dataValue - 1);
            }

            return factorial(input);
        }
    }
}
