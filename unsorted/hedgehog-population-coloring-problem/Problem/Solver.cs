namespace Problem;

public static class Solver
{
    public static int Solve(int[] population, string targetColor)
    {
        int targetCountIndex = targetColor switch
        {
            "red" => 0,
            "green" => 1,
            "blue" => 2,
            _ => -1
        };

        if (targetCountIndex == -1)
            return -1;

        var total = population[0] + population[1] + population[2];
        //var total = population.Sum();

        // check if the problem is already solved
        if (population[targetCountIndex] == total)
            return 0;

        // check if there's only one color present
        var colorPresenceCount = 0;
        for (int i = 0; i < 3; i++)
            if (population[i] > 0)
                ++colorPresenceCount;
        if (colorPresenceCount == 1)
            return -1;

        // extract two other color indices
        Span<int> others = stackalloc int[2];
        int i_others = 0;
        for (int i = 0; i < 3; ++i)
            if (targetCountIndex != i)
                others[i_others++] = i;
        var lesserCountIndex = others[0];
        var greaterCountIndex = others[1];

        // paired quantities = to be transfered to target color group
        if (population[lesserCountIndex] == population[greaterCountIndex])
            return population[lesserCountIndex];

        if (population[lesserCountIndex] > population[greaterCountIndex])
        { // swap
            lesserCountIndex ^= greaterCountIndex;
            greaterCountIndex ^= lesserCountIndex;
            lesserCountIndex ^= greaterCountIndex;
        }

        // check invariance
        // only other colors count difference of 3 makes the problem solvable
        var lesserCount = population[lesserCountIndex];
        var greaterCount = population[greaterCountIndex];
        if ((greaterCount - lesserCount) % 3 != 0)
            return -1;
        var targetCount = population[targetCountIndex];

        // main shaker transfer cycle
        // example: [ 3 ; 3 ; 21 ]
        // [ 9 ; 0 ; 18 ] // transfer
        // equalization between 0 and 18 with lesser value growing twice
        // as fast as greater one
        // ((9 - (18 / 3)) >= 0) // check if can equalize
        // [ 9 - (18 / 3) ; (18 / 3 * 2) ; 18 - (18 / 3) ] // equalize
        var encountersNeeded = 0;
        while (greaterCount > 0)
        {
            // transfer
            encountersNeeded += lesserCount;
            greaterCount -= lesserCount;
            targetCount += lesserCount * 2;
            lesserCount = 0;
            var third = greaterCount / 3;
            if (targetCount >= third)
            {
                targetCount -= third;
                // can equalize?
                if (targetCount < 0)
                    return -1;
                encountersNeeded += third;
                // equalize
                greaterCount -= third;
                lesserCount = third * 2; // was 0 after transfer
            }
            else // example: [9, 0, 8997]
            { // equalize caps with target counter
                encountersNeeded += targetCount;
                lesserCount += targetCount * 2;
                greaterCount -= targetCount;
                targetCount = 0;
            }
        }
        return encountersNeeded;
        // or just return greaterCount, because the number of steps is capped
        // with it from the bottom, which is exactly the minimal number of
        // steps
    }
}
