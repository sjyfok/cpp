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
            int temp = Convert.ToInt32(Console.ReadLine());
            int fan = Convert.ToInt32(Console.ReadLine());
            string sta = Console.ReadLine();

            if (temp >= 28 && fan <= 2 && sta.Equals("good"))
            {
                Console.WriteLine("{0}", "yes");

            }
            else
                Console.WriteLine("{0}", "no");
          



                       
            

        }
    }
}
