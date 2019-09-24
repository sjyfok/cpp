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
            string[] strCR = strInput.Split(' ');
            int m = Convert.ToInt32(strCR[0]);
            int n = Convert.ToInt32(strCR[1]);

            int R = n / 2 - m;
            int C = m - R;



                       
            Console.WriteLine("{0} {1}", C, R);

        }
    }
}
