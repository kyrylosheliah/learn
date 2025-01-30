// thanks to taylorh140
// https://ziggit.dev/t/unable-to-run-test-that-uses-import-outside-current-directory/3286/16

const std = @import("std");

fn replaceBackslashes(path: []u8) void {
    for (path) |*c| {
        if (c.* == '\\') c.* = '/';
    }
}

pub fn main() !void {

    // Get allocator
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    defer _ = gpa.deinit();

    // Parse args into string array (error union needs 'try')
    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);

    // Generate a temporary filename with a `.zig` extension
    const temp_file = "testTemp_zzqqzzq.zig";

    const file_path = try std.fs.cwd().createFile(temp_file, .{});
    defer {
        std.fs.cwd().deleteFile(temp_file) catch unreachable;
        file_path.close();
    }

    replaceBackslashes(args[1]);

    // Write content to the file
    try file_path.writer().print(
        \\comptime {{
        \\_ = @import("{s}");
        \\}}
    ,
        .{args[1]},
    );

    const argv = [_][]const u8{ "zig", "test", temp_file };
    var child = std.process.Child.init(&argv, std.heap.page_allocator);
    try child.spawn();
    _ = try child.wait();
}