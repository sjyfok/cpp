using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vehicles
{
    class Vehicles
    {
        public void StartEngine(string noiseToMakeWhenStarting)
        {
            Console.WriteLine($"Starting engine: { noiseToMakeWhenStarting}");
        }
        public void StopEngine(string noiseToMakeStopping)
        {
            Console.WriteLine($"Stopping engine:{noiseToMakeStopping}");
        }

        public virtual void Drive()
        {
            Console.WriteLine("Default implementation of the Drive method");
        }
    }
}
