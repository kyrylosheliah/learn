// 8. String to Integer (atoi)
// 
// Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.
// 
// The algorithm for myAtoi(string s) is as follows:
// 
//     Whitespace: Ignore any leading whitespace (" ").
//     Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
//     Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
//     Rounding: If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1], then round the integer to remain in the range. Specifically, integers less than -2^31 should be rounded to -2^31, and integers greater than 2^31 - 1 should be rounded to 2^31 - 1.
// 
// Return the integer as the final result.
// 
// 
// 
// Example 1:
// 
// Input: s = "42"
// 
// Output: 42
// 
// Explanation:
// 
// The underlined characters are what is read in and the caret is the current reader position.
// Step 1: "42" (no characters read because there is no leading whitespace)
//          ^
// Step 2: "42" (no characters read because there is neither a '-' nor '+')
//          ^
// Step 3: "42" ("42" is read in)
//            ^
// 
// Example 2:
// 
// Input: s = " -042"
// 
// Output: -42
// 
// Explanation:
// 
// Step 1: "   -042" (leading whitespace is read and ignored)
//             ^
// Step 2: "   -042" ('-' is read, so the result should be negative)
//              ^
// Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)
//                ^
// 
// Example 3:
// 
// Input: s = "1337c0d3"
// 
// Output: 1337
// 
// Explanation:
// 
// Step 1: "1337c0d3" (no characters read because there is no leading whitespace)
//          ^
// Step 2: "1337c0d3" (no characters read because there is neither a '-' nor '+')
//          ^
// Step 3: "1337c0d3" ("1337" is read in; reading stops because the next character is a non-digit)
//              ^
// 
// Example 4:
// 
// Input: s = "0-1"
// 
// Output: 0
// 
// Explanation:
// 
// Step 1: "0-1" (no characters read because there is no leading whitespace)
//          ^
// Step 2: "0-1" (no characters read because there is neither a '-' nor '+')
//          ^
// Step 3: "0-1" ("0" is read in; reading stops because the next character is a non-digit)
//           ^
// 
// Example 5:
// 
// Input: s = "words and 987"
// 
// Output: 0
// 
// Explanation:
// 
// Reading stops at the first non-digit character 'w'.
// 
//  
// 
// Constraints:
// 
//     0 <= s.length <= 200
//     s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.

const std = @import("std");
const print = std.debug.print;
const TestSuite = @import("test_suite").TestSuite;

const TInput = []const u8;

const TOutput = i32;

fn equalInteger(x: TOutput, y: TOutput) bool {
    print("{d} ?? {d}\n", .{x, y});
    return x == y;
}

fn orderAssumption(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    _ = alloc;
    var start: usize = 0;
    // skip whitespaces
    while (start < x.len)  {
        const ch = x[start];
        if (ch == ' ') start += 1
        else break;
    }
    // determine the sign
    // '+' 43
    // '-' 45
    var is_negative = false;
    if (start < x.len) {
        const ch = x[start];
        if (ch == '+') {
            is_negative = false;
            start += 1;
        } else if (ch == '-') {
            is_negative = true;
            start += 1;
        }
    }
    // skip zeroes
    // '0' 48
    while (start < x.len) {
        const ch = x[start];
        if (ch == '0') start += 1
        else break;
    }
    // determine the end by incrementing on valid characters
    // ['0'; '9'] are [48; 57]
    // ['1'; '9'] are [49; 57]
    var end = start;
    while (end < x.len) {
        const ch = x[end];
        if (ch < 48 or ch > 57) break;
        end += 1;
    }
    if (end == start) return 0; // no actual content
    // sum the ranks
    var sum: TOutput = 0;
    var rank: TOutput = @intCast(end - start - 1);
    for (start..end) |i| {
        const ch: TOutput = @intCast(x[i] - 48);
        sum += std.math.pow(TOutput, 10, rank) * ch;
        rank -= 1;
    }
    return if (is_negative) -sum else sum;
}

fn integerStateMachine(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    _ = alloc;
    if (x.len == 0) return 0;
    var sum: usize = 0;
    var state: usize = 0; // ParserState.first;
    var is_negative = false;
    for (0 ..x.len) |i| {
        const ch = x[i];
        switch (state) {
            0 => {
                switch (ch) {
                    ' ' => continue, //' ' => state = 0,
                    '+' => {
                        state = 1;
                        is_negative = false;
                    },
                    '-' => {
                        state = 1;
                        is_negative = true;
                    },
                    '0'...'9' => {
                        state = 2;
                        const digit = ch - 48; // '0' == 48
                        sum = sum * 10 + digit;
                    },
                    else => return 0,
                }
            },
            1 => {
                switch (ch) {
                    '0'...'9' => {
                        state = 2;
                        const digit = ch - 48; // '0' == 48
                        sum = sum * 10 + digit;
                    },
                    else => return 0,
                }
            },
            2 => {
                switch (ch) {
                    '0'...'9' => {
                        state = 2;
                        const digit = ch - 48; // '0' == 48
                        sum = sum * 10 + digit;
                    },
                    else => break,
                }
            },
            else => unreachable,
        }
    }
    //if (is_negative) sum = -sum;
    //sum = @min(sum, std.math.maxInt());
    //sum = @max(sum, std.math.minInt());
    var answer: i32 = @intCast(sum);
    if (is_negative) answer = -answer;
    return answer;
}

const ParserState = enum(u8) {
    first,
    second,
    third,
};

fn enumExhaustiveStateMachine(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    _ = alloc;
    if (x.len == 0) return 0;
    var sum: usize = 0;
    var state = ParserState.first;
    var is_negative = false;
    for (0 ..x.len) |i| {
        const ch = x[i];
        switch (state) {
            .first => {
                switch (ch) {
                    ' ' => continue, //' ' => state = .first,
                    '+' => {
                        state = .second;
                        is_negative = false;
                    },
                    '-' => {
                        state = .second;
                        is_negative = true;
                    },
                    '0'...'9' => {
                        state = .third;
                        const digit = ch - 48; // '0' == 48
                        sum = sum * 10 + digit;
                    },
                    else => return 0,
                }
            },
            .second => {
                switch (ch) {
                    '0'...'9' => {
                        state = .third;
                        const digit = ch - 48; // '0' == 48
                        sum = sum * 10 + digit;
                    },
                    else => return 0,
                }
            },
            .third => {
                switch (ch) {
                    '0'...'9' => {
                        state = .third;
                        const digit = ch - 48; // '0' == 48
                        sum = sum * 10 + digit;
                    },
                    else => break,
                }
            },
        }
    }
    //if (is_negative) sum = -sum;
    //sum = @min(sum, std.math.maxInt());
    //sum = @max(sum, std.math.minInt());
    var answer: i32 = @intCast(sum);
    if (is_negative) answer = -answer;
    return answer;
}

test "8" {
    var test_suite = TestSuite(TInput, TOutput, equalInteger, "string to integer (atoi)").init();
    defer test_suite.deinit();

    try test_suite.inputs.append("2147483647");
    try test_suite.outputs.append(2147483647);

    try test_suite.inputs.append("42");
    try test_suite.outputs.append(42);

    try test_suite.inputs.append("-042");
    try test_suite.outputs.append(-42);

    try test_suite.inputs.append("1337c0d3");
    try test_suite.outputs.append(1337);

    try test_suite.inputs.append("0-1");
    try test_suite.outputs.append(0);

    try test_suite.inputs.append("words and 987");
    try test_suite.outputs.append(0);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &orderAssumption },
        .{ .run = &integerStateMachine },
        .{ .run = &enumExhaustiveStateMachine },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}