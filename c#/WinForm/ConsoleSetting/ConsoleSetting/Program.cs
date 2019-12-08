using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace ConsoleSetting
{
    class MyClass
    {
        public string Name;
        public int Age;

        public MyClass(string name, int age)
        {
            this.Name = name;
            this.Age = age;
        }
    }

    class Iterator:IEnumerator, IEnumerable
    {
        private MyClass[] ClassArray;
        int Cnt;
        public Iterator()
        {
            ClassArray = new MyClass[4];
            ClassArray[0] = new MyClass("Kith", 23);
            ClassArray[1] = new MyClass("Smith", 30);
            ClassArray[2] = new MyClass("Geo", 19);
            ClassArray[3] = new MyClass("Greg", 14);
            Cnt = -1;
        }
        public void Reset()
        {
            Cnt = -1;
        }

        public bool MoveNext()
        {
            return (++Cnt < ClassArray.Length);
        }

        public object Current
        {
            get { return ClassArray[Cnt]; }
        }

        public IEnumerator GetEnumerator()
        {
            return (IEnumerator)this;
        }

        static void Main(string[] args)
        {
            Iterator It = new Iterator();
            foreach (MyClass MY in It)
            {
                Console.WriteLine("Name : " + MY.Name.ToString());
                Console.WriteLine("Age : " + MY.Age.ToString());
            }
            Console.Read();
        }
    }

    
    //class Program
    //{
    //    static void Main(string[] args)
    //    {

    //    }
    //}
}
