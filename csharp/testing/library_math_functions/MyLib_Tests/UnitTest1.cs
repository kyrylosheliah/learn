using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MyLib_Tests;

[TestClass]
public class UnitTest1
{
    [TestMethod]
    public void IntegratedTest()
    {
        MyLib.CustomMath.IntegratedTest();
    }

    [TestMethod]
    public void TestSum()
    {
        int result = MyLib.CustomMath.sum(0, 0);
        Assert.AreEqual(result, 0);
    }

    public void TestDivision(int x, int y, int expectedResult)
    {
        try
        {
            int result = MyLib.CustomMath.division(x, y);
            Assert.AreEqual(expectedResult, result);
            if (y == 0)
            {
                throw new DivideByZeroException("Ділення на нуль не створює вийняткової ситуації");
            }
        }
        catch (System.Exception)
        {
            if (y != 0)
            {
                throw new Exception("Вийняткова ситуація з ненульовим знаменником");
            }
        }
    }

    [TestMethod]
    public void TestDivisionByZero_old()
    {
        TestDivision(0, 0, 0);
        TestDivision(0, 1, 0);
    }

    [TestMethod]
    [DataRow(1, 1, 2)]
    [DataRow(-1, 1, 0)]
    [DataRow(10, 15, 25)]
    public void CustomMathTest(int x, int y, int expectedResult)
    {
        Assert.AreEqual(expectedResult, MyLib.CustomMath.sum(x, y));
    }

    [TestMethod]
    [DataRow(0, 0, 0)]
    [DataRow(0, 1, 0)]
    [DataRow(1000, -5, -200)]
    [DataRow(-60, -3, 20)]
    public void TestDivisionByZero(int x, int y, int expectedResult)
    {
        TestDivision(x, y, expectedResult);
    }

    [TestMethod]
    [DataRow(0, 0, 0)]
    [DataRow(0, 1, 0)]
    [DataRow(1000, -5, -5000)]
    [DataRow(-60, -3, 180)]
    public void testMultiplication(int x, int y, int expectedResult)
    {
        Assert.AreEqual(expectedResult, MyLib.CustomMath.mult(x, y));
    }

    [TestMethod]
    [DataRow(0, 0, 1)]
    [DataRow(0, 1, 0)]
    [DataRow(1000, -5, 1e-15)]
    [DataRow(-60, -3, 46296e-10)]
    public void testExponentiation(int x, int y, double expectedResult)
    {
        Assert.AreEqual(expectedResult, MyLib.CustomMath.pow(x, y), 5e-5);
    }

    [TestMethod]
    [DataRow(0, 0, 0)]
    [DataRow(0, 1, -1)]
    [DataRow(1000, -5, 1005)]
    [DataRow(-60, -3, -57)]
    public void testSubstraction(int x, int y, double expectedResult)
    {
        Assert.AreEqual(expectedResult, MyLib.CustomMath.sub(x, y));
    }

}