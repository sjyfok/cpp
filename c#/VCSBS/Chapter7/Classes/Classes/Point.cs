#region Using directives

using System;
using System.Collections.Generic;
using System.Text;

#endregion

namespace Classes
{
    class Point
    {
        // TODO:
        private int x, y;
        private static int objectCount = 0;
        public static int ObjectCount() => objectCount;
        public Point()
        {
            //  Console.WriteLine("Default constructor called");
            this.x = -1;
            this.y = -1;
            objectCount++;
        }
        public Point(int x, int y)
        {
            //Console.WriteLine($"x:{x}, y:{y}");
            this.x = x;
            this.y = y;
            objectCount++;
        }

        public double DistanceTo(Point other)
        {
            int xDiff = this.x - other.x;
            int yDiff = this.y - other.y;
            double distance = Math.Sqrt((xDiff * xDiff) + (yDiff * yDiff));

            return distance;
        }
    }
}
