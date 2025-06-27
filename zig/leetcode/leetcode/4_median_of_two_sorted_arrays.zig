// 4. Median of Two Sorted Arrays
// 
// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
// 
// The overall run time complexity should be O(log (m+n)).
// 
// Example 1:
// 
// Input: nums1 = [1,3], nums2 = [2]
// Output: 2.00000
// Explanation: merged array = [1,2,3] and median is 2.
// 
// Example 2:
// 
// Input: nums1 = [1,2], nums2 = [3,4]
// Output: 2.50000
// Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
// 
// Constraints:
// 
//     nums1.length == m
//     nums2.length == n
//     0 <= m <= 1000
//     0 <= n <= 1000
//     1 <= m + n <= 2000
//     -10^6 <= nums1[i], nums2[i] <= 10^6

const std = @import("std");
const print = std.debug.print;
const minInt = std.math.minInt;
const maxInt = std.math.maxInt;
const TestSuite = @import("test_suite").TestSuite;

const TInput = struct {
    nums1: []const i32,
    nums2: []const i32,
};

const TOutput = f32;

fn equal_I32(x: TOutput, y: TOutput) bool {
    //print("{d:2}, {d:2}\n", .{ x, y });
    return x == y;
}

fn twoIndices(alloc: *std.mem.Allocator, x: TInput) !TOutput{
    _ = alloc;
    const combined_len = x.nums1.len + x.nums2.len;
    if (combined_len == 0) {
        return 0;
    } else if (combined_len == 1) {
        return if (x.nums1.len > x.nums2.len) @as(f32, @floatFromInt(x.nums1[0]))
        else @as(f32, @floatFromInt(x.nums2[0]));
    }
    const stop_idx = @divTrunc(combined_len, 2) + 1;
    var i: usize = 2;
    var idx_1: usize = 0;
    var idx_2: usize = 0;
    while (i < stop_idx) : (i += 1) {
        const stop_1 = idx_1 + 1 == x.nums1.len;
        const stop_2 = idx_2 + 1 == x.nums2.len;
        if (stop_1) {
            if (stop_2) break; // isn't possible when (i < stop_idx)
            idx_2 += 1;
            continue;
        }
        if (stop_2) {
            idx_1 += 1;
            continue;
        }
        if (x.nums1[idx_1] > x.nums2[idx_2]) {
            idx_2 += 1;
        } else {
            idx_1 += 1;
        }
    }
    const num1 = @as(TOutput, @floatFromInt(x.nums1[idx_1]));
    const num2 = @as(TOutput, @floatFromInt(x.nums2[idx_2]));
    if (@rem(combined_len, 2) == 0) {
        return (num1 + num2)  / 2;
    } else {
        return if (num1 > num2) num1 else num2;
    }
}

fn binarySearch(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    _ = alloc;

    const nums1: []const i32 = if (x.nums1.len > x.nums2.len) x.nums1 else x.nums2;
    const nums2: []const i32 = if (x.nums1.len > x.nums2.len) x.nums2 else x.nums1;
    const n1 = nums1.len;
    const n2 = nums2.len;

    const n = n1 + n2;
    const partition = @divTrunc(n + 1, 2);

    // edge cases
    if (n1 == 0) {
        const middle = @divTrunc(n2, 2);
        if (n % 2 == 1) return @as(f32, @floatFromInt(nums2[middle]));
        return (@as(f32, @floatFromInt(nums2[middle] + nums2[middle - 1]))) / 2.0 ;
    }
    if (n2 == 0) {
        const middle = @divTrunc(n1, 2);
        if (n % 2 == 1) return @as(f32, @floatFromInt(nums1[middle]));
        return @as(f32, @floatFromInt(nums1[middle] + nums1[middle - 1])) / 2.0;
    }

    var low: usize = 0;
    var high: usize = n1;
    var partition_l: usize = undefined;
    var partition_r: usize = undefined;
    var max_l: i32 = undefined;
    var max_r: i32 = undefined;
    var min_l: i32 = undefined;
    var min_r: i32 = undefined;

    while (true) {
        partition_l = @divTrunc(low + high, 2);
        partition_r = partition - partition_l;

        max_l = if (partition_l == 0) minInt(i32) else nums1[partition_l - 1];
        max_r = if (partition_r == 0) minInt(i32) else nums2[partition_r - 1];
        min_l = if (partition_l >= n1) maxInt(i32) else nums1[partition_l];
        min_r = if (partition_r >= n2) maxInt(i32) else nums2[partition_r];

        //print("min_l {d} | max_l {d} | min_r {d} | max_r {d}\n", .{min_l, max_l, min_r, max_r});

        if (max_l <= min_r and max_r <= min_l) {
            const max = if (max_l > max_r) max_l else max_r;
            if (@rem(n, 2) == 1) {
                return @as(f32, @floatFromInt(max));
            } else {
                const min = if (min_l < min_r) min_l else min_r;
                return @as(f32, @floatFromInt(max + min)) / 2.0;
            }
        }

        if (max_l > min_r) {
            high = partition_l - 1;
        } else {
            low = partition_l + 1;
        }

        if (low > high) break;
    }

    unreachable;
}

test "4 median of two sorted arrays" {
    var test_suite = TestSuite(TInput, TOutput, equal_I32, "median of two sorted arrays").init();
    defer test_suite.deinit();

    try test_suite.inputs.append(.{ .nums1 = &.{ 1, 3 }, .nums2 = &.{ 2 } });
    try test_suite.outputs.append(2.0);

    try test_suite.inputs.append(.{ .nums1 = &.{ 1, 2 }, .nums2 = &.{ 3, 4 } });
    try test_suite.outputs.append(2.5);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &twoIndices },
        .{ .run = &binarySearch },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}