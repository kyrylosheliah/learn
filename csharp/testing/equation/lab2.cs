// lab2.cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace lab2
{
    static public class lab2
    {
        /*      Варіант№7
        Void m (const float a, const float b, float x) {
        If (a> 3) || (B == 2)
        X = X / a;
        If (a <= 7) && (x => 1) && (a == 1)
        X = X ++;
        }            */
        static public void toTest(float a, float b, ref float x)
        {
            if ((a > 3) || (b == 2)) // (початково ||)
            {
                x = x / a;
            }
            if ((a <= 7) && (x >= 1) && (a == 1))
            {
                x++; // x = x++;
            }
        }

    }
}