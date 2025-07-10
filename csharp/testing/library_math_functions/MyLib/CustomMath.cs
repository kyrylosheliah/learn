namespace MyLib;
public class CustomMath
{
    public static int sum(int x, int y)
    {
        return x + y; // повертає результат складання двох чисел
    }

    public static int division(int x, int y)
    {
        if (y == 0)
        {// якщо дільник дорівнює нулю
            throw new ArgumentException("divider is 0");
        } // кидається виняток
        return x / y; // повертає результат ділення
    }

    public static int mult(int x, int y)
    {
        return x * y;
    }

    public static double pow(int x, int y)
    {
        //Console.WriteLine($"{x} ^ {y} = {Math.Pow(x, y)}");
        return Math.Pow(x, y);
    }

    public static int sub(int x, int y)
    {
        return x - y;
    }

    public static void IntegratedTest()
    {
        /*
        if (sum(1, 3) == 4)
        {// перевіряємо, що при додаванні 1 і 3
         // нам повертається 4
            Console.WriteLine("Test1 passed.");
        }
        else { Console.WriteLine("Test1 failed."); }

        try
        {
            int z = division(1, 0);
            Console.WriteLine("Test3 failed.");
        }
        catch (ArgumentException)
        {
            // тест вважається успішним, якщо при спробі поділу на 0
            // генерується очікуване виняток
            Console.WriteLine("Test3 passed.");
        }
        //throw new Exception("CustomMath::IntegratedTest()");
        */
    }
}
