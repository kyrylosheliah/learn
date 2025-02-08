const std = @import("std");
const time = std.time;
const Instant = time.Instant;
const print = std.debug.print;

pub fn Solution(
    comptime TInput: type,
    comptime TOutput: type,
) type {
    return struct {
        run: *const fn (arena: *std.heap.ArenaAllocator, x: TInput) anyerror!TOutput,
    };
}

pub fn RunResult(comptime TOutput: type) type {
    return struct {
        pass: bool,
        outputs: std.ArrayList(TOutput),
    };
}

pub fn TestSuite(
    comptime TInput: type,
    comptime TOutput: type,
    Equal: *const fn (x: TOutput, y: TOutput) bool,
    test_name: []const u8,
) type {
    return struct {
        const Self = @This();
        const TSolution = Solution(TInput, TOutput);
        const TInputs = std.ArrayList(TInput);
        const TOutputs = std.ArrayList(TOutput);
        const TSolutions = std.ArrayList(TSolution);
        const TRunResult = RunResult(TOutput);
        allocator: std.mem.Allocator,
        arena: *std.heap.ArenaAllocator,
        inputs: TInputs,
        outputs: TOutputs,
        solutions: TSolutions,
        result: TRunResult,
        pub fn init() Self {
            const allocator = std.testing.allocator;
            const arena = allocator.create(std.heap.ArenaAllocator) catch unreachable;
            arena.* = std.heap.ArenaAllocator.init(allocator);
            return .{
                .allocator = allocator,
                .arena = arena,
                .inputs = TInputs.init(allocator),
                .outputs = TOutputs.init(allocator),
                .solutions = TSolutions.init(allocator),
                .result = .{ .pass = false, .outputs = TOutputs.init(allocator) },
            };
        }
        pub fn deinit(self: *Self) void {
            self.inputs.deinit();
            self.outputs.deinit();
            self.solutions.deinit();
            self.result.outputs.deinit();
            // ...
            self.arena.deinit();
            self.allocator.destroy(self.arena);
        }
        pub fn run(self: *Self) !void {
            self.result.pass = true;
            self.result.outputs.clearAndFree();
            print("\n... {s}\n", .{test_name});
            for (self.solutions.items, 1..) |solution, i| {
                for (self.inputs.items, self.outputs.items, 1..) |input, output, j| {
                    // measure time
                    const start = try Instant.now();
                    // do the thing
                    const got = try solution.run(self.arena, input);
                    try self.result.outputs.append(got);
                    // measure time
                    const end = try Instant.now();
                    const elapsed: f64 = @floatFromInt(end.since(start));
                    const us_elapsed = elapsed / time.ns_per_us;
                    // compare `solution(case)`
                    if (Equal(got, output)) {
                        print(
                            "ok {d}:{d} | {d:.1}us\n", 
                            .{ i, j, us_elapsed,
                        });
                    } else {
                        print(
                            "### fail {d}:{d} | {d:.1}us\n",
                            .{ i, j, us_elapsed },
                        );
                        self.result.pass = false;
                    }
                }
            }
        }
    };
}
