const std = @import("std");
const time = std.time;
const Instant = time.Instant;
const print = std.debug.print;

pub fn Solution(
    comptime TInput: type,
    comptime TOutput: type,
) type {
    return struct {
        run: *const fn (allocator: std.mem.Allocator, x: TInput) anyerror!TOutput,
    };
}

pub fn RunResult(comptime TOutput: type) type {
    return struct {
        failed: bool,
        outputs: std.ArrayList(TOutput),
    };
}

pub fn TestSuite(
    comptime TInput: type,
    comptime TOutput: type,
    Equal: *const fn (x: TOutput, y: TOutput) bool,
) type {
    return struct {
        const Self = @This();
        const TSolution = Solution(TInput, TOutput);
        const TInputs = std.ArrayList(TInput);
        const TOutputs = std.ArrayList(TOutput);
        const TSolutions = std.ArrayList(TSolution);
        const TRunResult = RunResult(TOutput);
        allocator: std.mem.Allocator,
        inputs: TInputs,
        outputs: TOutputs,
        solutions: TSolutions,
        result: TRunResult,
        pub fn init(allocator: std.mem.Allocator) Self {
            return .{
                .allocator = allocator,
                .inputs = TInputs.init(allocator),
                .outputs = TOutputs.init(allocator),
                .solutions = TSolutions.init(allocator),
                .result = .{
                    .failed = false,
                    .outputs = TOutputs.init(allocator)
                },
            };
        }
        pub fn deinit(self: *Self) void {
            self.inputs.deinit();
            self.outputs.deinit();
            self.solutions.deinit();
            self.result.outputs.deinit();
        }
        pub fn run(self: *Self) !void {
            self.result.failed = false;
            self.result.outputs.clearAndFree();
            for (self.solutions.items, 1..) |solution, i| {
                for (self.inputs.items, self.outputs.items, 1..) |input, output, j| {
                    // measure time
                    const start = try Instant.now();
                    // do the thing
                    const got = try solution.run(self.allocator, input);
                    try self.result.outputs.append(got);
                    // measure time
                    const end = try Instant.now();
                    const elapsed: f64 = @floatFromInt(end.since(start));
                    const us_elapsed = elapsed / time.ns_per_us;
                    // compare
                    if (Equal(got, output)) {
                        print("[ ] pass | {d:.1}us\n", .{ us_elapsed });
                    } else {
                        print(
                            "[x] failed: solution {d}, case {d} | {d:.1}us\n",
                            .{ i, j, us_elapsed },
                        );
                        self.result.failed = true;
                    }
                }
            }
        }
    };
}
