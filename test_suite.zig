const std = @import("std");
const allocator = std.testing.allocator;
const time = std.time;
const Instant = time.Instant;
const print = std.debug.print;

pub fn Solution(
    comptime TInput: type,
    comptime TOutput: type,
) type {
    return struct {
        run: *const fn (alloc: *std.mem.Allocator, x: TInput) anyerror!TOutput,
    };
}

// thanks to dimdin:
// https://ziggit.dev/t/what-is-the-resolution-of-std-time-timer-and-is-it-good-enough/4678/3
fn x86_64_ticks() u64 {
    return asm volatile(
        \\ rdtsc
        \\ shl $32, %%rdx
        \\ or %%rdx, %%rax
        : [ret] "={rax}" (-> u64)
        :
        : "rdx"
    );
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
        arena: *std.heap.ArenaAllocator,
        inputs: TInputs,
        outputs: TOutputs,
        solutions: TSolutions,
        pass: bool,
        pub fn init() Self {
            var arena = allocator.create(std.heap.ArenaAllocator) catch unreachable;
            arena.* = std.heap.ArenaAllocator.init(allocator);
            const alloc = arena.allocator();
            return .{
                .arena = arena,
                .inputs = TInputs.init(alloc),
                .outputs = TOutputs.init(alloc),
                .solutions = TSolutions.init(alloc),
                .pass = false,
            };
        }
        pub fn deinit(self: *Self) void {
            self.arena.deinit();
            allocator.destroy(self.arena);
        }
        pub fn run(self: *Self) !void {
            self.pass = true;
            print("\n... {s}\n", .{test_name});
            var alloc = self.arena.allocator();
            for (self.solutions.items, 1..) |solution, i| {
                for (self.inputs.items, self.outputs.items, 1..) |input, output, j| {
                    // measure time
                    const start = try Instant.now();
                    const ticks_before = x86_64_ticks();
                    // do the thing
                    const got = try solution.run(&alloc, input);
                    // measure time
                    const ticks_after = x86_64_ticks();
                    const end = try Instant.now();
                    // ...
                    const ticks_elapsed = ticks_after - ticks_before;
                    const elapsed: f64 = @floatFromInt(end.since(start));
                    const us = elapsed / time.ns_per_us;
                    const ms = elapsed / time.ns_per_ms;
                    const prefix = blk: {
                        if (Equal(got, output)) break :blk "ok"
                        else {
                            self.pass = false;
                            break :blk "### fail";
                        }
                    };
                    // compare `solution:case`
                    print(
                        "{s} {d}:{d} | {d:.0}ms {d:.0}us {d:.0}ns | {d} ticks\n",
                        .{ prefix, i, j, ms, us, elapsed, ticks_elapsed },
                    );
                }
            }
        }
    };
}
