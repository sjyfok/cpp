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
            double l = Convert.ToDouble(Console.ReadLine());
            double p = 0;
            //int i_l = Convert.ToInt32(l);
            //if (i_l < l)
            //   i_l++;
            //l = i_l;
            l = Math.Ceiling(l);
            if (l <= 2)
                p = 7;
            else if (l <= 15)
                p = (l-2) * 1.5+7;
            else
                p = (15-2) * 1.5 + (l-15)*2.1+7;

              
            Console.WriteLine("{0:f0}", p);
        }
    }
}
