// 5. Longest Palindromic Substring
// 
// Given a string s, return the longest
// palindromic
// substring
// in s.
// 
// Example 1:
// 
// Input: s = "babad"
// Output: "bab"
// Explanation: "aba" is also a valid answer.
// 
// Example 2:
// 
// Input: s = "cbbd"
// Output: "bb"
// 
// Constraints:
// 
//     1 <= s.length <= 1000
//     s consist of only digits and English letters.

const std = @import("std");
const print = std.debug.print;
const TestSuite = @import("test_suite").TestSuite;

const TInput = []const u8;

const TOutput = [][]const u8;

fn equal_Slice(x: TOutput, y: TOutput) bool {
    for (x) |xi| {
        for (y) |yi| {
            if (xi.len != yi.len) {
                print("\"{s}\" != \"{s}\"\n", .{xi, yi});
                continue;
            }
            if (std.mem.eql(u8, xi, yi)) {
                return true;
            }
        }
    }
    return false;
}

fn reverseSlice(buffer: []u8, string: []const u8) []u8 {
    @memcpy(buffer, string);
    std.mem.reverse(u8, buffer);
    return buffer;
}

fn bruteForce(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    if (x.len == 0) return try alloc.alloc([]const u8, 0);
    var list = std.ArrayList([]const u8).init(alloc.*);
    try list.append(x[0..1]);
    if (x.len == 1) return list.items;
    var max_len: usize = 1;
    for (0..x.len - 1) |i| {
        //print("i {d}\n", .{i});
        var j = x.len;
        while (j > i) : (j -= 1) {
            //print("j {d}\n", .{j});
            const new_len = j - i + 1;
            if (new_len < max_len) continue;
            const left_slice = x[i..j];
            //print("[{d}..{d}] | \"{s}\"\n", .{i, j, left_slice});
            const buffer: []u8 = try alloc.alloc(u8, left_slice.len);
            const reversed = reverseSlice(buffer, left_slice);
            if (!std.mem.eql(u8, left_slice, reversed)) continue;
            if (new_len > max_len) list.clearRetainingCapacity();
            try list.append(left_slice);
            max_len = new_len;
        }
    }
    return list.items; //.{ max_str };
}

// assumes `x[left] == x[right]`
fn expandFromCenter(x: []const u8, left: usize, right: usize) []const u8 {
    var l = left;
    var r = right;
    while (l > 0 and r < x.len - 1) {
        const new_l = l - 1;
        const new_r = r + 1;
        if (x[new_l] == x[new_r]) {
            l = new_l;
            r = new_r;
        } else break;
    }
    return x[l..r + 1];
}

fn expand(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    //_ = alloc;
    if (x.len == 0) return try alloc.alloc([]const u8, 0);
    var list = std.ArrayList([]const u8).init(alloc.*);
    try list.append(x[0..1]);
    if (x.len == 1) return list.items;
    var max_len: usize = 1;
    for (0..x.len-1) |i| {
        const odd = expandFromCenter(x, i, i);
        const even = if (x[i] == x[i + 1])
            expandFromCenter(x, i, i + 1)
            else x[i + 1..i + 2];
        //print("odd \"{s}\" | even \"{s}\"\n", .{odd, even});
        //const new_len = if (odd.len > even.len) odd.len else even.len;
        const new_len = @max(odd.len, even.len);
        if (new_len < max_len) continue;
        if (new_len > max_len) {
            list.clearRetainingCapacity();
            max_len = new_len;
        }
        if (odd.len == even.len) {
            try list.append(odd);
            try list.append(even);
        } else if (odd.len > even.len) {
            try list.append(odd);
        } else {
            try list.append(even);
        }
    }
    return list.items;
}

fn dynamicProgramming(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    //_ = alloc;
    if (x.len == 0) return try alloc.alloc([]const u8, 0);
    var list = std.ArrayList([]const u8).init(alloc.*);
    try list.append(x[0..1]);
    if (x.len == 1) return list.items;
    var max_len: usize = 1;
    var left: usize = 0;
    const n = x.len;
    var dp: [][]bool = try alloc.alloc([]bool, n);
    //defer alloc.free(dp);
    for (dp) |*dpi| dpi.* = try alloc.alloc(bool, n);
    //defer for (dp) |dpi| alloc.free(dpi);
    for (0..n) |i| {
        dp[i][i] = true;
        for (0..i) |j| {
            dp[j][i] = (x[j] == x[i]) and ((i - j < 2) or (dp[j + 1][i - 1]));
            if (dp[j][i] and max_len < i - j + 1) {
                left = j;
                max_len = i - j + 1;
            }
        }
    }
    list.clearRetainingCapacity();
    try list.append(x[left..][0..max_len]);
    return list.items;
}

fn manachersAlgorithm(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    //_ = alloc;
    if (x.len == 0) return try alloc.alloc([]const u8, 0);
    var list = std.ArrayList([]const u8).init(alloc.*);
    try list.append(x[0..1]);
    if (x.len == 1) return list.items;
    var T: []u8 = try alloc.alloc(u8, 2 * x.len + 3);
    T[0] = '^'; // + 1
    T[1] = '#'; // + 1
    for (0..x.len) |i| { // * 2
        const t_i = i * 2 + 1;
        T[t_i + 1] = x[i];
        T[t_i + 2] = '#';
    }
    T[T.len - 1] = '$'; // + 1
    const n = T.len;
    var P: []usize = try alloc.alloc(usize, n);
    @memset(P, 0);
    var C: usize = 0;
    var R: usize = 0;
    for (1..n - 1) |i| {
        if (R > i) {
            const i_mirrored = 2 * C - i;
            //P[i] = if (P[i_mirrored] < R - i) P[i_mirrored] else (R - i);
            P[i] = @min(P[i_mirrored], R - i);
        } else P[i] = 0;
        while (T[i + P[i] + 1] == T[i - P[i] - 1]) {
            P[i] += 1;
        }
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
    var max_len: usize = 1;
    for (P) |v| {
        if (v > max_len) {
            max_len = v;
            //i_C = i;
        }
    }
    list.clearRetainingCapacity();
    for (P, 0..P.len) |v, i_C| {
        if (v == max_len) {
            try list.append(x[@divTrunc(i_C - max_len, 2)..@divTrunc(i_C + max_len, 2)]);
        }
    }
    //try list.append(x[@divTrunc(i_C - max_len, 2)..@divTrunc(i_C + max_len, 2)]);
    return list.items;
}

test "5" {
    var test_suite = TestSuite(TInput, TOutput, equal_Slice, "longest palindromic substring").init();
    defer test_suite.deinit();

    var alloc = test_suite.arena.allocator();
    var output: [][]const u8 = undefined;

    try test_suite.inputs.append("babad");
    output = try alloc.alloc([]const u8, 2);
    output[0] = "bab";
    output[1] = "aba";
    try test_suite.outputs.append(output);

    try test_suite.inputs.append("cbbd");
    output = try alloc.alloc([]const u8, 1);
    output[0] = "bb";
    try test_suite.outputs.append(output);

    try test_suite.inputs.append("abcbcba");
    output = try alloc.alloc([]const u8, 1);
    output[0] = "abcbcba";
    try test_suite.outputs.append(output);

    try test_suite.inputs.append("saippuakivikauppias");
    output = try alloc.alloc([]const u8, 1);
    output[0] = "saippuakivikauppias";
    try test_suite.outputs.append(output);

    try test_suite.inputs.append("aaaaaaaaaaaaaasaippuakivikauppias");
    output = try alloc.alloc([]const u8, 1);
    output[0] = "saippuakivikauppias";
    try test_suite.outputs.append(output);

    try test_suite.inputs.append("saippuakivikauppiasaaaaaaaaaaaaaa");
    output = try alloc.alloc([]const u8, 1);
    output[0] = "saippuakivikauppias";
    try test_suite.outputs.append(output);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &bruteForce },
        .{ .run = &expand },
        .{ .run = &dynamicProgramming },
        .{ .run = &manachersAlgorithm },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}