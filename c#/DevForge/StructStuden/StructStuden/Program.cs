using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StructStuden
{
    class Program
    {
        struct Bithday
        {
            public int year;
            public int month;
            public int date;
        }
        struct Student
        {
            public string name;
            public string male;
            public Bithday bith;
        }

        static void Main(string[] args)
        {
            Student stu = new Student();

            stu.name = Console.ReadLine();
            stu.male = Console.ReadLine();
            string strymd = Console.ReadLine();
            string szTemp = strymd.Substring(0, 4);
            stu.bith.year = int.Parse(szTemp);
            szTemp = strymd.Substring(4, 2);
            stu.bith.month = int.Parse(szTemp);
            szTemp = strymd.Substring(6, 2);
            stu.bith.date = int.Parse(szTemp);

            Console.WriteLine("{0}\n{1}\n{2} " +
                "{3:D2} {4:D2}", stu.name, stu.male, stu.bith.year, stu.bith.month,
                stu.bith.date);
        }
    }
}
