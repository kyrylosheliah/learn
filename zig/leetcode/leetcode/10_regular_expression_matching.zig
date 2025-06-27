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

// when an element precedence for '*' pattern is always guaranteed, there are
// only a need to handle the following cases, when iterating the pattern:
// | .   |
// | .*  |
// | .*. |
// | .*a |
// | a*a |
// | a*. |
// | a*  |
// | a   |
// which can be generalized with switch-case logic on 'a'...'z' and '.' to
// | c   |
// | c*  |
// | c*c |
// from the algorithm's nature of jumping 2 indices at once to handle '*'

// this allows for the algorithm to decrement the pattern position, when it
// doesn't match and to build a state decision tree with progressive shaker
// motion

// in this case the end result could have 3 outcomes:
// - an attempt to decrement the pattern index to out of bounds position
//     (string still has chars)                                     | mismatch
// - an attempt to increment the string index to out of bounds position
//     (pattern still has chars)                                    | mismatch
// - an attempt to increment both the string and the pattern to out of bounds
//     position                                                     | match

// to create the decrement-increment pattern pass motion it could be either:
// - parsed to an array of state structs
// - be dynamically discovered when such motion happens
//     (which doesn't work when there's a need to retract twice or more)

//const FuzzyPattern = enum(u2) {
//    end,    // x.* , xa
//    around, // .*x.*
//    start,  // .*x
//};
//
//const Fuzzy = struct {
//    i_s: usize,
//    i_p: usize,
//    i_next: usize,
//    pattern: FuzzyPattern,
//    ch: u8,
//};

// - matching causes both `string` and `pattern` indices to increment
// - both incrementing and decrementing `pattern` causes '*' pattern check to
// overshoot or undershoot it
// - shaker matching alorithm only increments string, but both increment and
// decrement the pattern, which causes the following overflow (>) and
// underflow (<) states:
// ---------------------------------
// string  |   | > |   | > |   | > |
// pattern |   |   | > | > | < | < |
// ---------------------------------
// №       | 1 | 2 | 3 | 4 | 5 | 6 |
// ---------------------------------
// - these cases should be handled according to the list:
// 1) perform main body logic
// 2) return *all remaining `pattern` chars are fuzzy*
// 3) decrement-match the pattern until (5)th case happens or there's a match
// 4) return true
// 5) return false
// 6) return false; but MUST NOT BE POSSIBLE, as the pattern index will either
// constantly decrement on mismatch causing (5)th case or eventually match and
// both `string` and `pattern` will overflow causing (4)th case

const Pattern = struct {
    ch: u8,
    fuzzy: bool,
};

fn shakerMatchingPrepass(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    // edge case
    if (x.p.len == 0) return x.s.len == 0;
    // prepass
    var pattern_container = try std.ArrayList(Pattern).initCapacity(alloc.*, x.p.len);
    for (x.p) |p_ch| {
        if (p_ch == '*') {
            const i_last = pattern_container.items.len - 1;
            pattern_container.items[i_last].fuzzy = true;
        } else {
            try pattern_container.append(.{ .ch = p_ch, .fuzzy = false });
        }
    }
    // ...
    //print("\n", .{}); for (pattern_container.items) |p| print("{}\n", .{p}); print("\n", .{});
    // ...
    var i_p: usize = 0;
    var i_s: usize = 0;
    const pattern = pattern_container.items;
    const string = x.s;
    // edge case
    if (string.len == 0) for (pattern) |p| if (!p.fuzzy) return false;
    // main body
    while (true) {
        //print("  while (true)\n", .{});
        const string_overflow = i_s >= string.len;
        const pattern_overflow = i_p >= pattern.len;
        //print("    string_overflow {} | pattern_overflow {}\n", .{string_overflow, pattern_overflow});
        //print("    i_s {d} | i_p {}\n", .{i_s, i_p});
        if (string_overflow and pattern_overflow) return true; // (4)th
        if (string_overflow) { // (2)nd
            while (i_p < pattern.len) { 
                if (!pattern[i_p].fuzzy) return false;
                i_p += 1;
            }
            return true;
        }
        //print("pattern.len {d} | i_p {d}\n", .{pattern.len, i_p});
        if (pattern_overflow) while (true) { // (3)rd
            // retract continuously
            if (i_p == 0) return false; // pattern underflow; (5)th
            i_p -= 1;
            const ch = string[i_s];
            const p = pattern[i_p];
            if (p.ch == ch or p.ch == '.' or p.fuzzy) {
                break;
            }
        };
        //print("pattern.len {d} | i_p {d}\n", .{pattern.len, i_p});
        // ...
        const ch = string[i_s];
        const p = pattern[i_p];
        if (p.ch == ch or p.ch != '.' or p.fuzzy) { // (1)st
            i_p += 1;
            i_s += 1;
        } else {
            if (i_p == 0) return false; // pattern underflow; (5)th
            i_p -= 1;
        }
    }
    unreachable;
}

// there are additional memory required to match patterns for combinatorics of
// cases "c", "a*c", "b*c" and "a*b*c" in "a*b*c"
// .s = "aa", .p = "a"
// .s = "cab", .p = "a*b*cab"
// .s = "cb", .p = "a*b*cab"
// .s = "ce", .p = "a*b*ce"
// these combinations could be obtained by bitfield counting on each decrement
// recombination

//const SomePattern = union(u2) {
//    fuzzy: u8,
//    fuzzyMany: []struct{ch: u8, active:bool},
//    clear: u8
//};

// didn't figure out how to handle ".*a*b*c*" sequence without dynamically
// allocating collections to handle ordered fuzzy pattern stacking, so
//```fn fuzzyWindowMatching(alloc: *std.mem.Allocator, x: TInput) !TOutput {```
// like in solution 10_2 isn't possible right now
// at the time solutions seem to be to perform a more aggressive than in
// solution 10_2 shaker motion in order to sometimes retract 2 or more indices
// to rematch the pattern AND:
// - to store a stack for adjacent `Fuzzy` structs with runtime parsing
// - to prepass the pattern in order to pregen linked list of `Fuzzy` structs
// with an additional field or a union type for .ch field to store multiple
// fuzzy patterns
// - to make the decision to include the symbol >0 times locally twice (first
// time when first encountered, second time when rectracted to) and the
// guarantee of performing Kernighan's algorithm on such adjacent fuzzy '*'
// patterns would be to never retract further when the pattern was already
// retracted to once ... < TODO ?

fn dynamicProgramming(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    const p = x.p;
    const s = x.s;
    if (p.len == 0) return s.len == 0;
    var dp: [][]bool = try alloc.alloc([]bool, s.len + 1);
    for (dp) |*dpi| dpi.* = try alloc.alloc(bool, p.len + 1);
    dp[0][0] = true;
    for (2..p.len + 1) |j| {
        if (p[j - 1] == '*') {
            //const match_0_times = dp[0][j - 2]; // match ".*" in "abc.*" 0 times when "abc" also matches
            //dp[0][j] = match_0_times; // for empty `string` and 2 chars before '*' char in `pattern`
            // (+ and - are the attention to the inputs, ? is the attention to the output)
            //     _ a *            _ a *
            //   -------          -------
            // _ | + 0 ?   =>   _ | 1 0 1
            // a | 0 0 0        a | 0 0 0
            // a | 0 0 0        a | 0 0 0
            dp[0][j] = dp[0][j - 2]; // for empty `string` and 2 chars before '*' char in `pattern`
        }
    }
    for (1..s.len + 1) |i| {
        for (1..p.len + 1) |j| {
            if (p[j - 1] == '*') {
                //const match_0_times = dp[i][j - 2]; // 2 chars before '*' char in `pattern`
                //const exact_match = s[i - 1] == p[j - 2] or p[j - 2] == '.';
                //const match_0_times_in_lesser_string = dp[i - 1][j]; // in string with 1 less char
                //dp[i][j] = match_0_times or (exact_match and match_0_times_in_lesser_string);
                //     _ a *                       _ a *
                //   -------                     -------
                // _ | 1 0 +   , 'a'=='a' =>   _ | 1 0 1
                // a | - 1 ?                   a | 0 1 1
                // a | 0 0 0                   a | 0 0 0
                dp[i][j] = dp[i][j - 2] or ((s[i - 1] == p[j - 2] or p[j - 2] == '.') and dp[i - 1][j]);
            } else {
                //const previous_matched = dp[i - 1][j - 1]; // 1 char less for both `pattern` and `string`
                //const exact_match = s[i - 1] == p[j - 1] or p[j - 1] == '.';
                //dp[i][j] = previous_matched and exact_match;
                //     _ a *                       _ a *
                //   -------                     -------
                // _ | + 0 1   , 'a'=='a' =>   _ | 1 0 1
                // a | 0 ? 0                   a | 0 1 0
                // a | 0 0 0                   a | 0 0 0
                dp[i][j] = dp[i - 1][j - 1] and (s[i - 1] == p[j - 1] or p[j - 1] == '.');
            }
        }
    }
    return dp[s.len][p.len];
}

test "10" {
    var test_suite = TestSuite(TInput, TOutput, equalBool, "regular expression matching").init();
    defer test_suite.deinit();

    try test_suite.inputs.append(.{ .s = "aa", .p = "a", });
    try test_suite.outputs.append(false);

    try test_suite.inputs.append(.{ .s = "aa", .p = "a*", });
    try test_suite.outputs.append(true);

    try test_suite.inputs.append(.{ .s = "ab", .p = ".*", });
    try test_suite.outputs.append(true);

    try test_suite.inputs.append(.{ .s = "abbbbb", .p = ".*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abbbbb", .p = "a.*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abbbbb", .p = "ab.*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abbbbb", .p = ".*b", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abbbbb", .p = ".*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "abbbbb", .p = "a*b*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "aaaaabbbbb", .p = "a*b*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "", .p = "", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "", .p = ".*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "", .p = "a*b*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "b", .p = "a*b*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "a", .p = "a*b*", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "c", .p = "a*b*c", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cab", .p = "a*b*cab", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "cb", .p = "a*b*cab", });
    try test_suite.outputs.append(false);
    try test_suite.inputs.append(.{ .s = "ce", .p = "a*b*ce", });
    try test_suite.outputs.append(true);
    try test_suite.inputs.append(.{ .s = "c", .p = "ca*b*", });
    try test_suite.outputs.append(true);

    try test_suite.solutions.appendSlice(&.{
        //.{ .run = &shakerMatchingPrepass },
        .{ .run = &dynamicProgramming },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}
