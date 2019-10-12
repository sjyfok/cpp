using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace FileClass
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = @"c:\temp\MyTest.txt";
            if(!File.Exists(path))
            {
                //创建文件
                using (StreamWriter sw = File.CreateText(path))
                {
                    sw.WriteLine("Hello");
                    sw.WriteLine("And");
                    sw.WriteLine("Welcome");
                }
            }
            using (StreamReader sr = File.OpenText(path))
            {
                string s = "";
                while((s=sr.ReadLine()) != null)
                {
                    Console.WriteLine(s);
                }
            }
            try
            {
                string path2 = path + "temp";
                File.Delete(path2);
                File.Copy(path, path2);
                Console.WriteLine("{0} was copied to {1}", path, path2);
                File.Delete(path2);
                Console.WriteLine("{0} was successfully deleted.", path2);
            }
            catch(Exception e)
            {
                Console.WriteLine("The process failed: {0}", e.ToString());
            }

        }
    }
}
