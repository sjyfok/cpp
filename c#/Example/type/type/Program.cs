using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace UsingType
{
    class BaseClass
    {
        public int BaseField = 0;
    }

    class DerivedClass:BaseClass
    {
        public int DerivedField = 0;
    }

    class Program
    {
        static void Main(string[] args)
        {
            //var bc = new BaseClass();
            //var dc = new DerivedClass();

            //BaseClass[] bca = new BaseClass[] { bc, dc };

            //foreach(var v in bca)
            //{
            //    Type t = v.GetType();
            //    Console.WriteLine("Object type: {0}", t.Name);
            //    FieldInfo[] fi = t.GetFields();
            //    foreach(var f in fi)
            //    {
            //        Console.WriteLine("     Field : {0}", f.Name);
            //    }
            //    Console.WriteLine();
            //}

            ///另外的用法
            ///
            Type tbc = typeof(DerivedClass);
            Console.WriteLine("Result is {0}", tbc.Name);

            Console.WriteLine("It has the following fields:");
            FieldInfo[] fi = tbc.GetFields();
            foreach (var f in fi)
                Console.WriteLine("    {0}", f.Name);
        }
    }
}
