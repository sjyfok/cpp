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
            string number = Console.ReadLine();
            if (number.IndexOf('8') >= 0)
            {
                Console.WriteLine("yes");
            } else
            {
                int num = Convert.ToInt32(number);
                if (num % 8 == 0)
                    Console.WriteLine("yes");
                else
                    Console.WriteLine("no");
            }

        }
    }
}
