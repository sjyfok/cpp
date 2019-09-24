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
            DateTime d;
            d = Convert.ToDateTime(Console.ReadLine());
            Console.WriteLine("{0}\n", d.DayOfYear);
            //string strDate = Console.ReadLine();
            //string[] subStr = strDate.Split('/');
            //int year = Convert.ToInt32(subStr[0]);
            //int month = Convert.ToInt32(subStr[1]);
            //int day = Convert.ToInt32(subStr[2]);
            //int dayCnt = day;
            //int month2 = 28;
            //if ((year % 100 != 0 && year % 4 == 0) || (year % 400 == 0))
            //    month2 = 29;
            //int i = 1;
            //while(i < month)
            //{
            //    switch(i)
            //    {
            //        case 1:
            //            dayCnt += 31;
            //            break;
            //        case 2:
            //            dayCnt += month2;
            //            break;
            //        case 3:
            //            dayCnt += 31;
            //            break;
            //        case 4:
            //            dayCnt += 30;
            //            break;
            //        case 5:
            //            dayCnt += 31;
            //            break;
            //        case 6:
            //            dayCnt += 30;
            //            break;
            //        case 7:
            //            dayCnt += 31;
            //            break;
            //        case 8:
            //            dayCnt += 31;
            //            break;
            //        case 9:
            //            dayCnt += 30;
            //            break;
            //        case 10:
            //            dayCnt += 31;
            //            break;
            //        case 11:
            //            dayCnt += 30;
            //            break;
            //    }
            //    i++;
            //}


            //Console.WriteLine("{0}\n", dayCnt);
        }
    }
}