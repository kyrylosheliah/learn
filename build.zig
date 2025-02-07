const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const test_file_option = b.option(
        []const u8,
        "o",
        "Specify the test file to run (defaults to all tests)",
    );

    const test_file_name = if (test_file_option) |test_file| test_file else blk: {
        const file_name = "###_dynamic_main.zig";
        try generate_tests(file_name, "leetcode");
        break :blk file_name;
    };

    const test_cmd = b.addTest(.{
        .root_source_file = b.path(test_file_name),
        .target = target,
        .optimize = optimize,
    });

    const test_suite_module_name = "test_suite";
    const test_suite = b.addModule(test_suite_module_name, .{
        .root_source_file = b.path("test_suite.zig"),
    });

    test_cmd.root_module.addImport(
        test_suite_module_name,
        test_suite,
    );
    const run_test = b.addRunArtifact(test_cmd);
    run_test.has_side_effects = true; // ensure the output is always shown

    const test_step = b.step("test", "Run tests");
    test_step.dependOn(&run_test.step);
}

fn generate_tests(filename: []const u8, dir_name: []const u8) !void {
    var file = try std.fs.cwd().createFile(filename, .{});
    defer file.close();

    var bw = std.io.bufferedWriter(file.writer());
    const writer = bw.writer();

    var dir = try std.fs.cwd().openDir(dir_name, .{ .iterate = true });
    defer dir.close();

    var dir_iterator = dir.iterate();
    while (try dir_iterator.next()) |entry| {
        if (entry.kind != .file) continue;
        if (!std.mem.endsWith(u8, entry.name, ".zig")) continue;
        //const import_name = entry.name[0 .. entry.name.len - 4];
        //try writer.writeAll(import_name);
        try writer.writeAll(
            \\comptime { _ = @import("./
        );
        try writer.writeAll(dir_name);
        try writer.writeAll("/");
        try writer.writeAll(entry.name);
        try writer.writeAll(
            \\"); }
            \\
        );
    }
    try writer.writeAll("test { @import(\"std\").testing.refAllDecls(@This()); }\n");
    try bw.flush();
}
