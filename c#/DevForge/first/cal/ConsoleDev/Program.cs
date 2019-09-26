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
            int pos = strInput.IndexOf('/');
            double A, B;
            if (pos != -1)
            {
                string[] st = strInput.Split('/');
                A = Convert.ToDouble(st[0]);
                B = Convert.ToDouble(st[1]);
                Console.WriteLine("{0:f2}", A / B);
            }
            pos = strInput.IndexOf('+');
            if (pos != -1)
            { 
                string[] st = strInput.Split('+');
                A = Convert.ToDouble(st[0]);
                B = Convert.ToDouble(st[1]);
                Console.WriteLine("{0:f2}", A + B);
            }
            pos = strInput.IndexOf('-');
            if (pos != -1)
            {
                string[] st = strInput.Split('-');
                A = Convert.ToDouble(st[0]);
                B = Convert.ToDouble(st[1]);
                Console.WriteLine("{0:f2}", A - B);
            }
            pos = strInput.IndexOf('*');
            if (pos != -1)
            {
                string[] st = strInput.Split('*');
                A = Convert.ToDouble(st[0]);
                B = Convert.ToDouble(st[1]);
                Console.WriteLine("{0:f2}", A * B);
            }
        }
    }
}
