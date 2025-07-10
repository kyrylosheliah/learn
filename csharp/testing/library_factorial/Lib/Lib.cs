using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Lib
{
    static public class Lib
    {
        static public ulong Factorial(ulong n)
        {
            if (n == 0)
            {
                return 1;
            }

            if (n > 20)
            {
                return ulong.MaxValue;
            }

            /* left unchecked until parametric
            requirement of the type ulong is met
            if (n < 0)
            {
                return 0;
            }
            */

            ulong result = 1;
            for(ulong i = 1; i <= n; ++i)
            {
                result *= i;
            }
            return result;
        }
    }
}