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
            string orgStr = Console.ReadLine();
            string subStr = Console.ReadLine();
            int pos = orgStr.IndexOf(subStr);

            Console.WriteLine("{0}\n", pos+1);            
        }
    }
}