const std = @import("std");

//fn stack_overflow() !void {
//    try stack_overflow();
//}

//fn alloc_var_on_heap() !void {
//    const allocator = std.heap.page_allocator;
//    while (true) {
//        const ptr = try allocator.alloc(u8, 1024);
//        ptr[0] = 1;
//    }
//}

fn alloc_var_on_heap() void {
    const allocator = std.heap.page_allocator;
    while (true) {
        var ptr: []u8 = undefined;
        ptr = allocator.alloc(u8, 1024) catch |err| {
            switch (err) {
                error.OutOfMemory => {
                    std.debug.warn("Caught an OutOfMemory error.\n");
                    return;
                },
                else => {},
            }
        };
        ptr[0] = 1;
    }
}

//test "stack_allocation_test" {
//    std.testing.expectError(error.OutOfMemory, stack_overflow());
//}

//test "heap_allocation_test" {
//    std.testing.expectError(error.OutOfMemory, alloc_var_on_heap());
//}

test "heap_allocation_test" {
    alloc_var_on_heap();
}
