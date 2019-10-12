using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StructDemo
{
    class Program
    {
        struct complex
        {
            public double r;
            public double i;
            public complex AddComplex(complex s)
            {
                complex ts;
                ts.r = this.r + s.r;
                ts.i = this.i + s.i;
                return ts;
            }

            public complex SubComplex(complex s)
            {
                complex ts;
                ts.r = this.r - s.r;
                ts.i = this.i - s.i;
                return ts;
            }

            public complex MulComplex(complex s)
            {
                complex ts;
                ts.r = this.r * s.r - this.i * s.i;
                ts.i = this.i * s.r + this.r * s.i;
                return ts;
            }

            public complex DivComplex(complex s)
            {
                complex ts;
                ts.r = (this.r * s.r + this.i * s.i) / (s.r * s.r+s.i*s.i);
                ts.i = (this.i * s.r - this.r * s.i) / (s.r * s.r + s.i * s.i);

                return ts;
            }

            public void Show()
            {
                Console.WriteLine("({0:f2}+{1:f2}i)", this.r, this.i);
            }
        }

       

        
        static void Main(string[] args)
        {
            complex s1, s2;
            string strinput = Console.ReadLine();
            string [] str_c = new string[2];
            str_c = strinput.Split(' ');
            s1.r = double.Parse(str_c[0]);
            s1.i = double.Parse(str_c[1]);
            strinput = Console.ReadLine();
            str_c = strinput.Split(' ');
            s2.r = double.Parse(str_c[0]);
            s2.i = double.Parse(str_c[1]);

            complex s3 = s1.AddComplex(s2);
            s1.Show();
            Console.Write("+");
            s2.Show();
            Console.Write("=");
            s3.Show();
            s3 = s1.SubComplex(s2);
            s1.Show();
            Console.Write('-');
            s2.Show();
            Console.Write('=');
            s3.Show();
            s3 = s1.MulComplex(s2);
            s1.Show();
            Console.Write("*");
            s2.Show();
            Console.Write("=");
            s3.Show();
            s3 = s1.DivComplex(s2);
            s1.Show();
            Console.Write("/");
            s2.Show();
            Console.Write("=");
            s3.Show();
           
        }
    }
}
