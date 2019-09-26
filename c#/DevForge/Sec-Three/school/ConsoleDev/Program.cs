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
            int year;
            int month;
            int day;
            year = Convert.ToInt32(Console.ReadLine());
            month = Convert.ToInt32(Console.ReadLine());
            day = Convert.ToInt32(Console.ReadLine());
            DateTime d = new DateTime(year, month, day);
            DateTime L1, L2, L3, L4;
            L1 = new DateTime(2013, 8, 31);
            L2 = new DateTime(2012, 8, 31);
            L3 = new DateTime(2011, 8, 31);
            L4 = new DateTime(2010, 8, 31);
            if (d<=L1&& d>L2)
                Console.WriteLine("1");
            if (d <= L2 && d > L3)
                Console.WriteLine("2");
            if (d <= L3 && d > L4)
                Console.WriteLine("3");
            if (d < L4 && d > L1)
                Console.WriteLine("error");      
        }
    }
}
