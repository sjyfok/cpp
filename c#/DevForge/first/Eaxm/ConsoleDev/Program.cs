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
            switch (strInput)
            {
                case "Monday":
                    Console.WriteLine("Piano");
                    break;
                case "Tuesday":
                    Console.WriteLine("Football");
                    break;
                case "Wednesday":
                    Console.WriteLine("Boxing");
                    break;
                case "Thrusday":
                    Console.WriteLine("Writing");
                    break;
                case "Friday":
                    Console.WriteLine("Etiquette");
                    break;
                default:
                    Console.WriteLine("No arrangements");
                    break;
            }
        }
    }
}
