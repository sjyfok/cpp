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
            string[] strABC = strInput.Split(' ');
            int A = Convert.ToInt32(strABC[0]);
            int B = Convert.ToInt32(strABC[1]);
            int C = Convert.ToInt32(strABC[2]);

            if ((A + B) > C && (A + C) > B && (B + C) > A)
                Console.WriteLine("yes");
            else
                Console.WriteLine("no");         

        }
    }
}
