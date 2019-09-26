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
            string[] strMNXY = strInput.Split(' ');
            int m = Convert.ToInt32(strMNXY[0]);
            int n = Convert.ToInt32(strMNXY[1]);
            int x = Convert.ToInt32(strMNXY[2]);
            int y = Convert.ToInt32(strMNXY[3]);

            int hour = m * n;
            int day = n - x;
            if (day * y == hour)
                Console.WriteLine("yes");
            else
                Console.WriteLine("no");

        }
    }
}
