using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace inout
{
    class Program
    {
        static void Main(string[] args)
        {
            string s = Console.ReadLine();
            string[] ss2 = s.Split(' ');
            
            int max = int.MinValue;
            for(int i = 0; i < ss2.Length; i ++)
            {
                int val;
                val = Convert.ToInt32(ss2[i]);
                if (val > max)
                    max = val;
            }
            Console.WriteLine("{0}", max);

        }
    }
}
