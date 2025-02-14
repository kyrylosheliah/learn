// 6. Zigzag Conversion
// 
// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
// 
// P   A   H   N
// A P L S I I G
// Y   I   R
// 
// And then read line by line: "PAHNAPLSIIGYIR"
// 
// Write the code that will take a string and make this conversion given a number of rows:
// 
// string convert(string s, int numRows);
// 
// Example 1:
// 
// Input: s = "PAYPALISHIRING", numRows = 3
// Output: "PAHNAPLSIIGYIR"
// 
// Example 2:
// 
// Input: s = "PAYPALISHIRING", numRows = 4
// Output: "PINALSIGYAHRPI"
// Explanation:
// P     I    N
// A   L S  I G
// Y A   H R
// P     I
// 
// Example 3:
// 
// Input: s = "A", numRows = 1
// Output: "A"
// 
// Constraints:
// 
//     1 <= s.length <= 1000
//     s consists of English letters (lower-case and upper-case), ',' and '.'.
//     1 <= numRows <= 1000

const std = @import("std");
const print = std.debug.print;
const TestSuite = @import("test_suite").TestSuite;

const TInput = struct {
    s: []const u8,
    numRows: usize,
};

const TOutput = []const u8;

fn equalString(x: []const u8, y: []const u8) bool {
    print("\n\"{s}\"\n\"{s}\"\n", .{x, y});
    return std.mem.eql(u8, x, y);
}

// [?] `gap_size` is `4` if `rows` is `3`
// [?] `gap_size` is `6` if `rows` is `4`
// [?] `gap_size` is `8` if `rows` is `5`
//  'X'         'X'  |  0      >8<        16  |  prepass: 0, >8<, ...
//  'X'      'X''X'  |  1     7 9      15 17  |  1; {7, 9};  {15, 17}; ...
//  'X'   'X'   'X'  |  2   6   10   14   18  |  2; {6, 10}; {14, 18}; ...
//  'X''X'      'X'  |  3 5     11 13     19  |  3; {5, 11}; {13, 19}; ...
//  'X'         'X'  |  4       12        20  |  postpass: 4, 12, ...
// [?] should skip the middle logic if `rows` is `2`
//  'X' 'X' 'X' 'X'  |  0   2   4   6  |  ...
//    'X' 'X' 'X'    |    1   3   5    |  ...
// [?] jump sizes are:
//  ■       +8        ■
//  ■     +6     ■ +2 ■
//  ■   +4   ■   +4   ■
//  ■ +2 ■     +6     ■
//  ■       +8        ■
// [?] or for per "row index" RI and "current vertical pillar index" CVPI case:
//               CVPI is 0*gap    CVPI is 1*gap
//                      v             v
//  prepass  { RI=0  |  ■          +8 ■ }
//             RI=1  |  ■     +6 ■ +8 ■  
//             RI=2  |  ■   +4 ■   +8 ■  
//             RI=3  |  ■ +2 ■     +8 ■  
//  postpass { RI=4  |  ■          +8 ■ }
//                      ^      ^      ^
//                  first    first    second
//                 in row     jump    jump

fn try1(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    const input = x.s;
    const rows = x.numRows;
    if (rows == 1) return input;
    var output: []u8 = try alloc.alloc(u8, input.len);
    const gap_size = rows + rows - 2;
    // prepass
    var output_i: usize = 0;
    var input_i: usize = 0;
    // `row_i` is 0
    for (0..input.len) |i| {
        input_i = i * gap_size;
        if (input_i >= input.len) break;
        //print("input_i {d}\n", .{input_i});
        output[output_i] = input[input_i];
        output_i += 1;
    }
    // middle part
    const stop_row_i = rows - 1;
    var row_i: usize = 0;
    // if `rows` is 2, then it breaks immediately
    var first_jump = gap_size;
    //var second_jump: usize = 0;
    while (true) {
        row_i += 1;
        if (row_i >= stop_row_i) break;
        first_jump -= 2;
        //second_jump += 2;
        const first_in_row_i = row_i;
        if (first_in_row_i >= input.len) break;
        output[output_i] = input[first_in_row_i];
        output_i += 1;
        for (0..input.len) |column_i| {
            const pillar_i = column_i * gap_size;
            const first_i = row_i + pillar_i + first_jump;
            if (first_i >= input.len) break;
            output[output_i] = input[first_i];
            output_i += 1;
            const second_i = row_i + pillar_i + gap_size;
            // or `first_jump + second_jump` instead of `gap_size`
            if (second_i >= input.len) break;
            output[output_i] = input[second_i];
            output_i += 1;
        }
    }
    // postpass
    // `row_i` is `rows - 1` after the previous while loop overshoot
    for (0..input.len) |i| {
        input_i = row_i + (i * gap_size);
        if (input_i >= input.len) break;
        //print("input_i {d}\n", .{input_i});
        output[output_i] = input[input_i];
        output_i += 1;
    }
    return output;
}

test "6" {
    var test_suite = TestSuite(TInput, TOutput, equalString, "zigzag conversion").init();
    defer test_suite.deinit();

    try test_suite.inputs.append(.{ .s = "PAYPALISHIRING", .numRows = 3 });
    try test_suite.outputs.append("PAHNAPLSIIGYIR");

    try test_suite.inputs.append(.{ .s = "PAYPALISHIRING", .numRows = 4 });
    try test_suite.outputs.append("PINALSIGYAHRPI");

    try test_suite.inputs.append(.{ .s = "A", .numRows = 1 });
    try test_suite.outputs.append("A");

    try test_suite.inputs.append(.{ .s = "ABABABABAB", .numRows = 2 });
    try test_suite.outputs.append("AAAAABBBBB");

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &try1 },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}
