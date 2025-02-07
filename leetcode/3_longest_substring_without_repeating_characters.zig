// 3. Longest Substring Without Repeating Characters
// 
// Given a string s, find the length of the longest
// substring
// without repeating characters.
//
// Example 1:
// 
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.
// 
// Example 2:
// 
// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
// 
// Example 3:
// 
// Input: s = "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
// 
// Constraints:
// 
//     0 <= s.length <= 5 * 10^4
//     s consists of English letters, digits, symbols and spaces.

const std = @import("std");
const print = std.debug.print;
const TestSuite = @import("test_suite").TestSuite;

const TInput = []const u8;

const TOutput = usize;

fn equalInt(x: TOutput, y: TOutput) bool {
    if (x != y) print("{d} != {d}\n", .{ x, y });
    return x == y;
}

fn decrementSlidingWindow_Hashmap(arena: *std.heap.ArenaAllocator, x: TInput) !TOutput {
    const alloc = arena.allocator();
    //print("input: \"{s}\"\n", .{x});
    var map = std.AutoHashMap(u8, usize).init(alloc);
    var start: usize = 0;
    var len = x.len - 1;
    var end = start + len;
    while (len > 0) {
        start = 0;
        end = len;
        while (true) {
            //print("len {d} | start {d} | end {d} | x.len {d}\n", .{len, start, end, x.len});
            //map.clearAndFree();
            map.clearRetainingCapacity();
            const slice = x[start..(end)];
            const pass = blk: {
                for (slice) |ch| {
                    if (map.contains(ch)) {
                        //print("found repeat: \"{s}\" with \'{c}\'\n", .{slice, ch});
                        break :blk false;
                    }
                    try map.put(ch, 0);
                }
                //print("answer: \"{s}\"\n", .{slice});
                //print("len {d} | start {d} | end {d} | x.len {d}\n", .{len, start, end, x.len});
                break :blk true;
            };
            if (pass) return len;
            start += 1;
            end = start + len;
            if (end > x.len) break;
        }
        len -= 1;
    }
    return 0;
}

fn printWindow(prefix: []const u8, x: []const u8, start: usize, end: usize) void {
    print("{s}\"{s}\"\n{s} ", .{ prefix, x, prefix });
    for (0..start) |_| print(" ", .{});
    print("^", .{});
    if (start != end) {
        for(start..end) |_| print("^", .{});
        //print("^", .{});
    }
    print("\n", .{});
    //print("{s}\n", .{ x[start..end+1] });
}

fn repetitionReducesSlidingWindow_Array(arena: *std.heap.ArenaAllocator, x: TInput) !TOutput {
    _ = arena;
    var arr: [256]u8 = .{ 0, } ** 256;
    var start: usize = 0;
    var end: usize = 0;
    var ans: usize = 0;
    //print("\n", .{});
    while (end < x.len) {
        //printWindow("before ", x, start, end);
        arr[x[end]] += 1;
        while (arr[x[end]] > 1) {
            arr[x[start]] -= 1;
            start += 1;
        }
        //printWindow("after ", x, start, end);
        //printWindow("    ", x, start, end);
        const window = end - start + 1;
        ans = if (ans > window) ans else window;
        end += 1;
    }
    return ans;
}

test "3" {
    var test_suite = TestSuite(TInput, TOutput, equalInt, "longest substring without repeating").init();
    defer test_suite.deinit();

    try test_suite.inputs.append("abcabcbb");
    try test_suite.outputs.append(3);

    try test_suite.inputs.append("bbbbb");
    try test_suite.outputs.append(1);

    try test_suite.inputs.append("pwwkew");
    try test_suite.outputs.append(3);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &decrementSlidingWindow_Hashmap },
        .{ .run = &repetitionReducesSlidingWindow_Array },
    });

    try test_suite.run();

    try std.testing.expect(!test_suite.result.failed);
}

