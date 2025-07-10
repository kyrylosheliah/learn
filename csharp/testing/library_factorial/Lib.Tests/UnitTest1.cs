using System.Reflection;

namespace Lib.Tests;

[TestClass]
public class UnitTest1
{
    public ulong FactorialMiddleware(int n)
    {
        var type = Assembly
        .LoadFile(@"d:\edu\8 semester\TVPZ\lab3\src\Lib\bin\Debug\net7.0\Lib.dll")
        .GetType("Lib.Lib", false, true);
        if (type == null)
        {
            Console.WriteLine("IS NULL");
        }
        var method = type.GetMethod("Factorial");
        ulong result = (ulong)method.Invoke(type, new object[]{(ulong)n});
        return result;
    }

    [TestMethod]
    public void TestMethod1()
    {
        ulong factorial = FactorialMiddleware(-1);
        ulong expected = 0;
        Assert.AreNotEqual(factorial, expected);
    }

    [DataTestMethod]
    [DataRow((ulong)0)]
    public void TestMethod2(ulong n)
    {
        ulong factorial = Lib.Factorial(n);
        ulong expected = 1;
        Assert.AreEqual(factorial, expected);
    }

    [DataTestMethod]
    [DataRow((ulong)1)]
    public void TestMethod3(ulong n)
    {
        ulong factorial = Lib.Factorial(n);
        ulong expected = 1;
        Assert.AreEqual(factorial, expected);
    }

    [DataTestMethod]
    [DataRow((ulong)2)]
    public void TestMethod4(ulong n)
    {
        ulong factorial = Lib.Factorial(n);
        ulong expected = 2;
        Assert.AreEqual(factorial, expected);
    }

    [DataTestMethod]
    [DataRow((ulong)3)]
    public void TestMethod5(ulong n)
    {
        ulong factorial = Lib.Factorial(n);
        ulong expected = 6;
        Assert.AreEqual(factorial, expected);
    }

    [DataTestMethod]
    [DataRow((ulong)19)]
    public void TestMethod6(ulong n)
    {
        ulong factorial = Lib.Factorial(n);
        ulong expected = 121_645_100_408_832_000;
        Assert.AreEqual(factorial, expected);
    }
    
    [DataTestMethod]
    [DataRow((ulong)20)]
    public void TestMethod7(ulong n)
    {
        ulong factorial = Lib.Factorial(n);
        ulong expected = 2_432_902_008_176_640_000;
        Assert.AreEqual(factorial, expected);
    }
    
    [DataTestMethod]
    [DataRow((ulong)21)]
    public void TestMethod8(ulong n)
    {
        ulong factorial = Lib.Factorial(n);
        ulong expected = ulong.MaxValue;
        Assert.AreEqual(factorial, expected);
    }
}