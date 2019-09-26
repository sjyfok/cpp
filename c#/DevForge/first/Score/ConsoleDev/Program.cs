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
                case "A":
                    Console.WriteLine("90~100");
                    break;
                case "B":
                    Console.WriteLine("80~89");
                    break;
                case "C":
                    Console.WriteLine("70~79");
                    break;
                case "D":
                    Console.WriteLine("60~69");
                    break;
                case "E":
                    Console.WriteLine("0~59");
                    break;
            }
        }
    }
}
