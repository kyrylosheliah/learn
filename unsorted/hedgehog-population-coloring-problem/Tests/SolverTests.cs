using Problem;

namespace Tests;

public class SolverTests
{
  /* // genTestData.js
colors = ["red", "green", "blue"];
for (let i = 0; i < 3; i++) {
  for (let j = 0; j < 3; j++) {
    for (let k = 0; k < 3; k++) {
      for (let c = 0; c < 3; c++) {
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
      // debug case
      ( [8, 1, 9], "red", -1 ),
      ( [8, 0, 9], "red", 9 ),
      // extremes
      ( [3, 3, 21], "red", 9 ),
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
      // ( [0, 1, 1], "red",  ),
      // ( [0, 1, 1], "green",  ),
      // ( [0, 1, 1], "blue",  ),
      // ( [0, 1, 2], "red",  ),
      // ( [0, 1, 2], "green",  ),
      // ( [0, 1, 2], "blue",  ),
      // ( [0, 2, 1], "red",  ),
      // ( [0, 2, 1], "green",  ),
      // ( [0, 2, 1], "blue",  ),
      // ( [0, 2, 2], "red", 2 ),
      // ( [0, 2, 2], "green",  ),
      // ( [0, 2, 2], "blue",  ),
      // ( [1, 0, 1], "red",  ),
      // ( [1, 0, 1], "green",  ),
      // ( [1, 0, 1], "blue",  ),
      // ( [1, 0, 2], "red",  ),
      // ( [1, 0, 2], "green",  ),
      // ( [1, 0, 2], "blue",  ),
      // ( [1, 1, 0], "red",  ),
      // ( [1, 1, 0], "green",  ),
      // ( [1, 1, 0], "blue",  ),
      // ( [1, 1, 1], "red",  ),
      // ( [1, 1, 1], "green",  ),
      // ( [1, 1, 1], "blue",  ),
      // ( [1, 1, 2], "red",  ),
      // ( [1, 1, 2], "green",  ),
      // ( [1, 1, 2], "blue",  ),
      // ( [1, 2, 0], "red",  ),
      // ( [1, 2, 0], "green",  ),
      // ( [1, 2, 0], "blue",  ),
      // ( [1, 2, 1], "red",  ),
      // ( [1, 2, 1], "green",  ),
      // ( [1, 2, 1], "blue",  ),
      // ( [1, 2, 2], "red", 2 ),
      // ( [1, 2, 2], "green",  ),
      // ( [1, 2, 2], "blue",  ),
      // ( [2, 0, 1], "red",  ),
      // ( [2, 0, 1], "green",  ),
      // ( [2, 0, 1], "blue",  ),
      // ( [2, 0, 2], "red",  ),
      // ( [2, 0, 2], "green",  ),
      // ( [2, 0, 2], "blue",  ),
      // ( [2, 1, 0], "red",  ),
      // ( [2, 1, 0], "green",  ),
      // ( [2, 1, 0], "blue",  ),
      // ( [2, 1, 1], "red",  ),
      // ( [2, 1, 1], "green",  ),
      // ( [2, 1, 1], "blue",  ),
      // ( [2, 1, 2], "red",  ),
      // ( [2, 1, 2], "green",  ),
      // ( [2, 1, 2], "blue",  ),
      // ( [2, 2, 0], "red",  ),
      // ( [2, 2, 0], "green",  ),
      // ( [2, 2, 0], "blue",  ),
      // ( [2, 2, 1], "red",  ),
      // ( [2, 2, 1], "green",  ),
      // ( [2, 2, 1], "blue",  ),
      // ( [2, 2, 2], "red",  ),
      // ( [2, 2, 2], "green",  ),
      // ( [2, 2, 2], "blue",  ),
    ];
    foreach (var (population, targetColor, expected) in testCases)
      Assert.Equal(expected, Solver.Solve(population, targetColor));
  }
}
