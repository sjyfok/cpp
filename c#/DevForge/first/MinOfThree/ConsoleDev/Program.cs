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
            int A, B, C, R;
            A = Convert.ToInt32(Console.ReadLine());
            B = Convert.ToInt32(Console.ReadLine());
            C = Convert.ToInt32(Console.ReadLine());
            if (A < B)
                R = A;
            else
                R = B;
            if (R > C)
                R = C;
            
            Console.WriteLine("{0}", R);
        }
    }
}
