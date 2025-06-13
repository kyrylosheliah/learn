using Problem;

namespace Tests;

public class SolverTests
{
  /* // genTestData.js
colors = ["red", "green", "blue"];
for (let i = 0; i <= 3; i += 3) {
  for (let j = 0; j <= 3; j += 3) {
    for (let k = 0; k <= 3; k += 3) {
      for (let c = 0; c < 3; ++c) {
        console.log(`( [${i}, ${j}, ${k}], "${colors[c]}",  ),`);
      }
    }
  }
}
  */
  [Fact]
  public void Solve_Returns_CorrectValue()
  {
    (int[], string, int)[] testCases = [
      ( [3, 3, 21], "red", 21 ),
      // ...
      ( [0, 0, 0], "red", 0 ),
      ( [0, 0, 0], "green", 0 ),
      ( [0, 0, 0], "blue", 0 ),
      // ...
      ( [0, 0, 1], "red", -1 ),
      ( [0, 0, 1], "green", -1 ),
      ( [0, 0, 1], "blue", 0 ),
      ( [0, 1, 0], "red", -1 ),
      ( [0, 1, 0], "green", 0 ),
      ( [0, 1, 0], "blue", -1 ),
      ( [1, 0, 0], "red", 0 ),
      ( [1, 0, 0], "green", -1 ),
      ( [1, 0, 0], "blue", -1 ),
      // ...
      ( [0, 3, 3], "red", 3 ),
      ( [0, 3, 3], "green", 3 ),
      ( [0, 3, 3], "blue", 3 ),
      ( [3, 0, 3], "red", 3 ),
      ( [3, 0, 3], "green", 3 ),
      ( [3, 0, 3], "blue", 3 ),
      ( [3, 3, 0], "red", 3 ),
      ( [3, 3, 0], "green", 3 ),
      ( [3, 3, 0], "blue", 3 ),
      ( [3, 3, 3], "red", 3 ),
      ( [3, 3, 3], "green", 3 ),
      ( [3, 3, 3], "blue", 3 ),
    ];
    foreach (var (population, targetColor, expected) in testCases)
      Assert.Equal(expected, Solver.Solve(population, targetColor));
  }
}
