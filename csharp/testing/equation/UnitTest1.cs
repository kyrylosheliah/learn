// UnitTest1.cs
namespace lab2;

[TestClass]
public class UnitTest1
{
    [DataTestMethod]
    [DataRow(4, 2, 2)]
    public void TestMethod1(float a, float b, float x)
    {
        float temp = x / a;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    [DataTestMethod]
    [DataRow(8, 2, 2)]
    public void TestMethod2_1(float a, float b, float x)
    {
        float temp = x / a;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    [DataTestMethod]
    [DataRow(1, 1, 1)]
    public void TestMethod2_2(float a, float b, float x)
    {
        float temp = x + 1;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    /*  a <= 3      a > 3
        b == 2      b != 2
        a <= 7      a > 7
        x >= 1      x < 1
        a == 1      a != 1 */
    [DataTestMethod]
    [DataRow(1, 2, 2)]
    public void TestMethod3_1(float a, float b, float x)
    {
        float temp = (x / a) + 1;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    [DataTestMethod]
    [DataRow(8, 1, -2)]
    public void TestMethod3_2(float a, float b, float x)
    {
        float temp = x / a;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    /*  a <= 3      [x] a > 3
        b != 2      [x] b == 2
        a <= 7      [x] a > 7
        x >= 1      [x] x < 1
        a == 1      [x] a != 1 */
    [DataTestMethod]
    [DataRow(1, 1, 0)]
    //[DataRow(8, 2, 0)]
    public void TestMethod4_1(float a, float b, float x)
    {
        float temp = x;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    /*  a <= 3, b == 2
        a > 3, b == 2
        a <= 3, b != 2
        a > 3, b != 2
        a == 1, a <= 7, x >= 1
        a == 1, a > 7, x >= 1
        a == 1, a <= 7, x < 1
        a == 1, a > 7, x < 1
        a != 1, a <= 7, x >= 1
        a != 1, a > 7, x >= 1
        a != 1, a <= 7, x < 1
        a != 1, a > 7, x < 1

        [DataRow(8, 1, 2 )] a > 7, b != 2, x >= 1
        [DataRow(8, 1, -2)] a > 7, b != 2, x < 1
        [DataRow(8, 2, 2 )] a > 7, b == 2, x >= 1
        [DataRow(8, 2, -2)] a > 7, b == 2, x < 1
        [DataRow(4, 1, 2 )] a > 3, b != 2, a <= 7, x >= 1
        [DataRow(4, 1, -2)] a > 3, b != 2 a <= 7, x < 1
        [DataRow(4, 2, 2 )] a > 3, b == 2, a <= 7, x >= 1
        [DataRow(4, 2, -2)] a > 3, b == 2, a <= 7, x < 1
        [DataRow(1, 1, 2 )] a == 1, b != 2, x >= 1
        [DataRow(1, 1, -2)] a == 1, b != 2, x < 1
        [DataRow(2, 1, 2 )] a <= 3, b != 2, a != 1, x >= 1
        [DataRow(2, 1, -2)] a <= 3, b != 2, a != 1, x < 1
        [DataRow(1, 2, 2 )] a <= 3, b == 2, a == 1, x >= 1
        [DataRow(1, 2, -2)] a <= 3, b == 2, a == 1, x < 1
        [DataRow(2, 2, 2 )] a <= 3, b == 2, a != 1, x >= 1
        [DataRow(2, 2, -2)] a <= 3, b == 2, a != 1, x < 1
        [DataRow(2, 1, 2 )] a <= 3, b != 2, a != 1, a > 7, x >= 1
        [DataRow(2, 1, -2)] a <= 3, b != 2, a != 1, a > 7, x < 1
        [DataRow(2, 2, 2 )] a <= 3, b == 2, a != 1, a > 7, x >= 1
        [DataRow(2, 2, -2)] a <= 3, b == 2, a != 1, a > 7, x < 1
    */
    [DataTestMethod]
    [DataRow(1, 2, 2 )]
    public void TestMethod5_1(float a, float b, float x)
    {
        float temp = (x / a) + 1;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    [DataTestMethod]
    [DataRow(8, 1, 2 )]
    [DataRow(8, 1, -2)]
    [DataRow(8, 2, 2 )]
    [DataRow(8, 2, -2)]
    [DataRow(2, 2, 2 )]
    [DataRow(2, 2, -2)]
    [DataRow(4, 2, 2 )]
    [DataRow(4, 2, -2)]
    [DataRow(4, 1, 2 )]
    [DataRow(4, 1, -2)]
    [DataRow(1, 2, -2)]
    public void TestMethod5_2(float a, float b, float x)
    {
        float temp = x / a;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    [DataTestMethod]
    [DataRow(1, 1, 2 )]
    public void TestMethod5_3(float a, float b, float x)
    {
        float temp = x + 1;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }

    [DataTestMethod]
    [DataRow(2, 1, 2 )]
    [DataRow(2, 1, -2)]
    [DataRow(1, 1, -2)]
    public void TestMethod5_4(float a, float b, float x)
    {
        float temp = x;
        lab2.toTest(a, b, ref x);
        Assert.AreEqual(x, temp);
    }
}