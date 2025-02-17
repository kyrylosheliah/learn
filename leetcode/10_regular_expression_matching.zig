// 10. Regular Expression Matching
// 
// Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
// 
//     '.' Matches any single character.​​​​
//     '*' Matches zero or more of the preceding element.
// 
// The matching should cover the entire input string (not partial).
// 
//  
// 
// Example 1:
// 
// Input: s = "aa", p = "a"
// Output: false
// Explanation: "a" does not match the entire string "aa".
// 
// Example 2:
// 
// Input: s = "aa", p = "a*"
// Output: true
// Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
// 
// Example 3:
// 
// Input: s = "ab", p = ".*"
// Output: true
// Explanation: ".*" means "zero or more (*) of any character (.)".
// 
//  
// 
// Constraints:
// 
//     1 <= s.length <= 20
//     1 <= p.length <= 20
//     s contains only lowercase English letters.
//     p contains only lowercase English letters, '.', and '*'.
//     It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.

const std = @import("std");
const print = std.debug.print;
const TestSuite = @import("test_suite").TestSuite;

const TInput = struct {
    s: []const u8,
    p: []const u8,
};

const TOutput = bool;

fn equalBool(x: bool, y: bool) bool {
    return x == y;
}

//// doesn't work, as it assumes '*' will match to the string end
//fn naive(alloc: *std.mem.Allocator, x: TInput) !TOutput {
//    _ = alloc;
//    var i_p: usize = 0;
//    var i_s: usize = 0;
//    for (x.s) |ch| {
//        const p = x.p[i_p];
//        switch (p) {
//            'a'...'z' => {
//                if (ch != p) return false;
//                i_p += 1;
//            },
//            '.' => {
//                i_p += 1;
//            },
//            '*' => continue,
//            else => unreachable, // p contains only lowercase English letters
//        }
//    }
//    return true;
//}

const FuzzyPattern = enum(u2) {
    // `.clear` pattern validation is the same as for `.end`
    //clear,// _ x _
            //   0 p.len
    // should match from left to right sequentially, without skips
    end,    // _ x * _
            //   0 1
    // should increase string index and reset pattern index on pattern mismatch
    around, // _ * x * _
            //     1 2
    // should determine whether the remaining pattern chunk can be accomodated
    // at the string end and then match every pattern character sequentially
    start,  // _ * x _ 
            //     1 p.len
};

const Fuzzy = struct {
    i_s: usize, // track string index where clear subpattern matching started
    i_p: usize, // track where clear subpattern itself is
    i_next: usize, // next fuzzy border index: 0 at the execution beginning,
    // pattern.len or where '*' resides
    pattern: FuzzyPattern,
};

fn fuzzyWindowMatching(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    _ = alloc;
    const string = x.s;
    const pattern = x.p;
    var i_p: usize = 0;
    var i_s: usize = 0;
    var fuzzy = Fuzzy{ .i_s = 0, .i_p = 0, .i_next = 0, .pattern = .end };
    //print("\n\n", .{});
    while (true) {
        //print("while (true)\n", .{});
        const pattern_overflow = i_p == pattern.len;
        const string_overflow = i_s == string.len;
        //print("  pattern_overflow {}\n", .{pattern_overflow});
        //print("  string_overflow {}\n", .{string_overflow});
        //print("  string[{d}..] \"{s}\" | pattern[{d}..] \"{s}\"\n", .{i_s, string[i_s..], i_p, pattern[i_p..]});
        //print("  fuzzy.i_p {d} | fuzzy.i_next {d} | fuzzy.pattern {}\n", .{fuzzy.i_p, fuzzy.i_next, fuzzy.pattern});
        if (string_overflow and pattern_overflow) return true;
        //if (string_overflow) return pattern[i_p] == '*'; // somehow, it is handled (didn't bother checking why xd)
        if (pattern_overflow) return false;
        // determine fuzzy pattern by handling `i_p` equal to 0, '*' or pattern.len
        if (i_p == fuzzy.i_next) {
            //print("  if (i_p == fuzzy.i_next)\n", .{});
            // remember where the check in string started
            fuzzy.i_s = i_s;
            // move fuzzy border
            while (true) {
                fuzzy.i_next += 1;
                if (fuzzy.i_next == pattern.len) break;
                if (pattern[fuzzy.i_next] == '*') break;
            }
            if (pattern[i_p] == '*') i_p += 1;
            if (i_p == pattern.len) return pattern[pattern.len - 1] == '*'; // pattern was exhausted, but could match any string ending
            fuzzy.i_p = i_p;
            const start_is_fuzzy = fuzzy.i_p != 0;
            const end_is_fuzzy = fuzzy.i_next != pattern.len;
            if (start_is_fuzzy and end_is_fuzzy) fuzzy.pattern = .around
            else if (start_is_fuzzy) fuzzy.pattern = .start
            // either end_is_fuzzy or !(start_is_fuzzy and end_is_fuzzy)
            else fuzzy.pattern = .end;
            //print("    string[{d}..] \"{s}\" | pattern[{d}..] \"{s}\"\n", .{i_s, string[i_s..], i_p, pattern[i_p..]});
            //print("    fuzzy.i_p {d} | fuzzy.i_next {d} | fuzzy.pattern {}\n", .{fuzzy.i_p, fuzzy.i_next, fuzzy.pattern});
        }
        const ch = string[i_s];
        const p = pattern[i_p];
        //print("  switch ({c})\n", .{p});
        // match the clear pattern block in text
        if (fuzzy.pattern == .start) {
            // match the sequence at the end
            // check if string end accomodates end pattern by length
            const end_pattern_len = pattern.len - fuzzy.i_p;
            const i_string_end = string.len - end_pattern_len;
            if (i_string_end < i_s) return false;
            // ...
            i_s = i_string_end;
            while (i_p < pattern.len) {
                const end_ch = string[i_s];
                const end_p = pattern[i_p];
                if (end_p != '.' and end_ch != end_p) return false;
                i_s += 1;
                i_p += 1;
            }
        } else switch (p) {
            'a'...'z' => {
                if (ch == p) {
                    i_p += 1;
                    i_s += 1;
                } else if (fuzzy.pattern == .around) {
                    // reset the clear block of the pattern
                    i_p = fuzzy.i_p; // full reset of the pattern position
                    fuzzy.i_s += 1;
                    i_s = fuzzy.i_s; // reset the string position to the
                    // incremented fuzzy state (i.e. try next position)
                } else return false;
            },
            '.' => {
                // skip one; any character will do
                i_p += 1;
                i_s += 1;
            },
            else => unreachable, // contains only lowercase English letters
        }
        //print("    string[{d}..] \"{s}\" | pattern[{d}..] \"{s}\"\n", .{i_s, string[i_s..], i_p, pattern[i_p..]});
    }
    unreachable;
}

test "10" {
    var test_suite = TestSuite(TInput, TOutput, equalBool, "regular expression matching").init();
    defer test_suite.deinit();

    // BEGIN original test cases

    try test_suite.inputs.append(.{ .s = "aa", .p = "a", });
    try test_suite.outputs.append(false);

    try test_suite.inputs.append(.{ .s = "aa", .p = "a*", });
    try test_suite.outputs.append(true);

    try test_suite.inputs.append(.{ .s = "ab", .p = ".*", });
    try test_suite.outputs.append(true);

    // END original test cases

    try test_suite.inputs.append(.{ .s = "x", .p = "x", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "x", .p = "x*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "x", .p = "*x", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "x", .p = "*x*", });
    try test_suite.outputs.append(true);

    try test_suite.inputs.append(.{ .s = "yx", .p = "x", });
    try test_suite.outputs.append(false);
    try test_suite.inputs.append(.{ .s = "yx", .p = "x*", });
    try test_suite.outputs.append(false);
    try test_suite.inputs.append(.{ .s = "xy", .p = "*x", });
    try test_suite.outputs.append(false);

    try test_suite.inputs.append(.{ .s = "cab", .p = "c*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "aab", .p = "c*a*b", });
    try test_suite.outputs.append(false);

    try test_suite.inputs.append(.{ .s = "ccaabb", .p = "c*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "ccaabb", .p = "c*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cabb", .p = "c*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "ccabb", .p = "c*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "caba", .p = "c*a*b", });
    try test_suite.outputs.append(false);
    try test_suite.inputs.append(.{ .s = "acab", .p = "c*a*b", });
    try test_suite.outputs.append(false);
    try test_suite.inputs.append(.{ .s = "acaba", .p = "c*a*b", });
    try test_suite.outputs.append(false);

    try test_suite.inputs.append(.{ .s = "cccab", .p = "c.*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cccab", .p = "c*.a*b", }); // 21
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cccab", .p = "c.*.a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cccab", .p = "c*..a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cccab", .p = "c..*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cccab", .p = "..c*a*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cccab", .p = ".c.*a*b", });
    try test_suite.outputs.append(true);

    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b*c.", }); // 27
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*bc*.", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*bc.*.", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*bc*..", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*bc..*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b..c*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b.c.*", });
    try test_suite.outputs.append(true);

    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b.c*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b.*c", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b.*.c", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b..*c", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b*..c", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b*c..", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abccc", .p = "a*b*.c.", });
    try test_suite.outputs.append(true);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &fuzzyWindowMatching },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}
