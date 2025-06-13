using System.CommandLine;
using Problem;

var redOption = new Option<int>(
    name: "--red",
    description: "Number of red hedgehogs",
    getDefaultValue: () => 0);
redOption.AddAlias("-r");

var greenOption = new Option<int>(
    name: "--green",
    description: "Number of green hedgehogs",
    getDefaultValue: () => 0);
greenOption.AddAlias("-g");

var blueOption = new Option<int>(
    name: "--blue",
    description: "Number of blue hedgehogs",
    getDefaultValue: () => 0);
blueOption.AddAlias("-b");

var targetOption = new Option<string>(
    name: "--target",
    description: "Target color: red, green, or blue");
targetOption.IsRequired = true;
targetOption.AddAlias("-t");

var rootCommand = new RootCommand(@"Hedgehog coloring solver.
Given a target color and an array of red, green and blue hedgehogs color
population counts, output the minimal number of encounters needed for all
hedgehogs to transition into the target color (-1, if unsolvable).
Encounter  transition rules:
color1 + color2 = 2 * color3
color1 != color2 != color3")
{
    redOption,
    greenOption,
    blueOption,
    targetOption
};
rootCommand.SetHandler((red, green, blue, target) =>
{
    int[] population = [red, green, blue];
    int result = Solver.Solve(population, target.ToLower());
    Console.WriteLine(result.ToString());
}, redOption, greenOption, blueOption, targetOption);

return await rootCommand.InvokeAsync(args);
