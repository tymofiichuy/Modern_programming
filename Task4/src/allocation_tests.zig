const std = @import("std");
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = gpa.allocator();

fn alloc_var_on_stack() void {
    while (true) {
        var int = 0;
        int = int + 1;
    }
}

fn alloc_var_on_heap() void {
    while (true) {
        const ptr = try allocator.alloc(u8, 1);
        ptr[0] = 1;
    }
}

test "stack_allocation_test" {
    try std.testing.expectError(error.OutOfMemory, alloc_var_on_stack());
}

test "heap_allocation_test" {
    try std.testing.expectError(error.OutOfMemory, alloc_var_on_heap());
}
