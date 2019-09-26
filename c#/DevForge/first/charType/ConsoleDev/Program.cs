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
            char A;
            A = (char)Console.Read();
            if (A >= 'A' && A <= 'Z')
                Console.WriteLine("upper");
            else if (A >= 'a' && A <= 'z')
                Console.WriteLine("lower");
            else if (A >= '0' && A <= '9')
                Console.WriteLine("digit");
            else
                Console.WriteLine("other");
        }
    }
}
