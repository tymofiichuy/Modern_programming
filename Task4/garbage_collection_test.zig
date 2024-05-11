const std = @import("std");
const allocator = std.testing.allocator;

//Test creates memory leak and detects it,
//so there are no garbage collector
test "memory_leak" {
    var list = std.ArrayList(u8).init(allocator);
    try list.append(0);

    try std.testing.expect(list.items.len == 1);
}
