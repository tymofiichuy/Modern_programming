const std = @import("std");
//var gpa = std.heap.GeneralPurposeAllocator(.{}){};
//const allocator = gpa.allocator();
const allocator = std.mem.Allocator;

//fn stack_overflow() !void {
//    try stack_overflow();
//}

fn alloc_var_on_heap() !void {
    while (true) {
        const ptr = try allocator.alloc(u8, 1024);
        ptr[0] = 1;
    }
}

//test "stack_allocation_test" {
//    std.testing.expectError(error.OutOfMemory, stack_overflow());
//}

test "heap_allocation_test" {
    std.testing.expectError(error.OutOfMemory, alloc_var_on_heap());
}
