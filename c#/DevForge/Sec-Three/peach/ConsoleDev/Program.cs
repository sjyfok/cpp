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
            int[] A = new int [4];
            for(int i = 0; i < 4; i ++)
            {
                A[i] = Convert.ToInt32(Console.ReadLine());
            }
            int tmp = A[0];
            int j = 0;
            for(int i = 1; i < 4; i ++)
            {
                if(tmp > A[i])
                {
                    tmp = A[i];
                    j = i;
                }
            }

            int k = 0;
            tmp = A[0];
            for(int i = 1; i < 4; i ++)
            {
                if(tmp >A[i] && i!= j)
                {
                    tmp = A[i];
                    k = i;
                }
            }
            j++;
            k++;
            if (j < k)
                Console.WriteLine("{0} {1}", j, k);
            else
                Console.WriteLine("{0} {1}", k, j);
            
        }
    }
}
