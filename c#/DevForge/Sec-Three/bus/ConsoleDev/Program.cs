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
            int H = Convert.ToInt32(Console.ReadLine());
            int M = Convert.ToInt32(Console.ReadLine());

            int school = 0;
            int bus = 0;
            int tmp;
            if (M > 0)
                school = (H+1) * 60 + 50;
            tmp = M / 10;
            if (M%10 > 0)
                tmp++;
            if (tmp >= 6)
                bus = (H + 1) * 60 + 80;
            else
                bus = H * 60 + tmp * 10 + 80;

            if (school <= bus)
                Console.WriteLine("school bus");
            else
                Console.WriteLine("916");         
        }
    }
}
