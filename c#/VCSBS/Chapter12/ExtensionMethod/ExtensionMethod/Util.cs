using System;

namespace Extensions
{
    //只能在静态类中定义扩展方法
    static class Util
    {
        //扩展方法:  this 表示扩展方法 扩展的类型是 int
        //在调用时 当用实例.ConvertToBase的形式调用时，只需传递一个阐述 baseToConverTo
        //当用Util.ConvertToBase 及类型名.方法的形式调用时，需要将两个参数都传递
        public static int ConvertToBase(this int i, int baseToConvertTo)
        {
            if (baseToConvertTo < 2 || baseToConvertTo > 10)
                throw new ArgumentException("Value cannot be converted to base"
                    + baseToConvertTo.ToString());

            int result = 0;
            int iterations = 0;
            do
            {
                int nextDigit = i % baseToConvertTo;
                i /= baseToConvertTo;
                result += nextDigit * (int)Math.Pow(10, iterations);
                iterations++;
            } while (i != 0);

            return result;
        }
    }
}