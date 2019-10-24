#region Using directives

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

#endregion

namespace StructsAndEnums
{
    class Program
    {
        static void doWork()
        {

            //Month first = Month.January;
            //Console.WriteLine(first);
            //first++;
            //Console.WriteLine(first);

            //Month first = Month.December;
            //Console.WriteLine(first);
            //first++;  //枚举类型值超出范围 就成数值值
            //Console.WriteLine(first);

            //Date defaultDate = new Date();
            //Console.WriteLine(defaultDate);

            //Date weddingAnniversary = new Date(2015, Month.July, 4);
            //Console.WriteLine(weddingAnniversary);

            Date weddingAnniversary = new Date(2015, Month.July, 4);
            Console.WriteLine(weddingAnniversary);
            Date weddingAnniversaryCopy = weddingAnniversary;
            Console.WriteLine($"Value of copy is {weddingAnniversaryCopy}");
            weddingAnniversary.AdvanceMonth();
            Console.WriteLine($"New value of weddingAnniversary is {weddingAnniversary}");
            Console.WriteLine($"Value of copy is still {weddingAnniversaryCopy}");   //Date是结构或者是类影响此句的输出


        }

        static void Main()
        {
            try
            {
                doWork();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
