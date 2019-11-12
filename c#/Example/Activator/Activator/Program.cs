using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace ActivatorDemo
{
    public  class SomeType
    {
        public void DoSomething(int x)
        {
            Console.WriteLine("100 / {0} = {1}", x, 100 / x);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // Create an instance of the StringBuilder type using 
            // Activator.CreateInstance.
            Object o = Activator.CreateInstance(typeof(StringBuilder));

            // Append a string into the StringBuilder object and display the 
            // StringBuilder.
            StringBuilder  sb = (StringBuilder ) o;
            sb.Append("Hello, there.");
            Console.WriteLine(sb);

            // Create an instance of the SomeType class that is defined in this 
            // assembly.
            System.Runtime.Remoting.ObjectHandle  oh =
                Activator.CreateInstanceFrom(Assembly.GetEntryAssembly().CodeBase,
                                              typeof(SomeType).FullName);

            // Call an instance method defined by the SomeType type using this object.
            SomeType  st = (SomeType) oh.Unwrap();

            st.DoSomething(5);
        }
    }
}
