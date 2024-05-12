//In Zig, function input is mean to be unmutable, so
//there are no pure reference types. Therefore, function can
//get a pointer to show similar to reference type behaviour.

const std = @import("std");

const point = struct {
    x: i8,
    y: i8,
};

fn return_address_int(int: u8) *const u8 {
    return &int;
}

fn return_address_int_by_pointer(int: *const u8) *const u8 {
    return int;
}

fn return_address_struct(p: point) *const point {
    return &p;
}

fn return_address_array(arr: [2]u8) *const u8 {
    return &arr[0];
}

test "integer_passed_by_value" {
    const int: u8 = 2;
    const actual: *const u8 = &int;
    const returned: *const u8 = return_address_int(int);

    std.testing.expect(actual != returned);
}

test "integer_passed_as_pointer" {
    const int: u8 = 2;
    const actual: *const u8 = &int;
    const returned: *const u8 = return_address_int_by_pointer(&int);

    std.testing.expect(actual == returned);
}

test "struct_passed_by_value" {
    const p = point{ .x = 1, .y = -1 };
    const actual: *const point = &p;
    const returned: *const point = return_address_struct(p);

    std.testing.expect(actual != returned);
}

test "array_passed_by_value" {
    const arr: [2]u8 = [2]u8{ 1, 2 };
    const actual: *const u8 = &arr[0];
    const returned: *const u8 = return_address_array(arr);

    std.testing.expect(actual != returned);
}

//fn add_1(int: u8) !void {
//    int = int + 1;
//}

//test "change_value_inside_function" {
//    var int: u8 = 0;
//    try add_1(int);
//    std.testing.expect(int == 0);
//}
