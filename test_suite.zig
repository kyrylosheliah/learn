// clear; zig test test_suite.zig

const std = @import("std");

pub fn Solution(
    comptime TInput: type,
    comptime TOutput: type,
) type {
    return struct {
        run: *const fn (x: TInput) TOutput,
    };
}

pub fn TestSuite(
    comptime TInput: type,
    comptime TOutput: type,
) type {
    return struct {
        const Self = @This();
        const TSolution = Solution(TInput, TOutput);
        const TCases = std.ArrayList(TInput);
        const TExpectations = std.ArrayList(TOutput);
        const TSolutions = std.ArrayList(TSolution);
        cases: TCases,
        expectations: TExpectations,
        solutions: TSolutions,
        pub fn init(allocator: std.mem.Allocator) Self {
            return .{
                .cases = TCases.init(allocator),
                .expectations = TExpectations.init(allocator),
                .solutions = TSolutions.init(allocator),
            };
        }
        pub fn deinit(self: *Self) void {
            self.cases.deinit();
            self.expectations.deinit();
            self.solutions.deinit();
        }
        pub fn run(self: Self) void {
            for (self.solutions.items, 1..) |solution, i| {
                for (self.cases.items, self.expectations.items, 1..) |case, expectation, j| {
                    const got = solution.run(case);
                    if (got == expectation) {
                        std.debug.print(" .  pass\n", .{});
                    } else {
                        std.debug.print(
                            "[x] failed: case {}, solution {}\n",
                            .{ i, j },
                        );
                    }
                }
            }
        }
    };
}

fn Sum(x: []const i32) i32 {
    var sum: i32 = 0;
    for (x) |val| {
        sum += val;
    }
    return sum;
}

test "sum" {

    var case_tester = TestSuite([]const i32, i32).init(std.testing.allocator);
    defer case_tester.deinit();

    try case_tester.cases.append(&.{ 1, 2, 3, 4 });
    try case_tester.expectations.append(10);

    try case_tester.cases.append(&.{ 2, 3, 4, 5 });
    try case_tester.expectations.append(14);

    try case_tester.solutions.appendSlice(&.{
        .{ .run = &Sum },
        .{ .run = &Sum },
    });

    case_tester.run();
}

fn Factorial(x: i32) i32 {
    if (x == 0) {
        return 1;
    } else if (x < 0) {
        unreachable;
    }
    var res: i32 = 1;
    var i: i32 = x;
    while (i > 0) {
        res *= i;
        i -= 1;
    }
    return res;
}

test "factorial" {

    var case_tester = TestSuite(i32, i32).init(std.testing.allocator);
    defer case_tester.deinit();

    try case_tester.cases.appendSlice(&.{ 1, 2, 3, 4, 5, 6 });
    try case_tester.expectations.appendSlice(&.{ 1, 2, 6, 24, 120, 720 });

    try case_tester.solutions.appendSlice(&.{
        .{ .run = &Factorial },
        .{ .run = &Factorial },
    });

    case_tester.run();

}
