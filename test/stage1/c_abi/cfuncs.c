#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

void zig_panic();

static void assert_or_panic(bool ok) {
    if (!ok) {
        zig_panic();
    }
}

void zig_u8(uint8_t);
void zig_u16(uint16_t);
void zig_u32(uint32_t);
void zig_u64(uint64_t);
void zig_i8(int8_t);
void zig_i16(int16_t);
void zig_i32(int32_t);
void zig_i64(int64_t);

void zig_f32(float);
void zig_f64(double);

void zig_ptr(void *);

void zig_bool(bool);

void zig_array(uint8_t[10]);

struct BigStruct {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint8_t e;
};

void zig_big_struct(struct BigStruct);

union BigUnion {
    struct BigStruct a;
};

void zig_big_union(union BigUnion);

struct SmallStructInts {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
};
void zig_small_struct_ints(struct SmallStructInts);

struct SplitStructInts {
    uint64_t a;
    uint8_t b;
    uint32_t c;
};
void zig_split_struct_ints(struct SplitStructInts);

struct BigStruct zig_big_struct_both(struct BigStruct);

void run_c_tests(void) {
    zig_u8(0xff);
    zig_u16(0xfffe);
    zig_u32(0xfffffffd);
    zig_u64(0xfffffffffffffffc);

    zig_i8(-1);
    zig_i16(-2);
    zig_i32(-3);
    zig_i64(-4);

    zig_f32(12.34f);
    zig_f64(56.78);

    zig_ptr((void*)0xdeadbeefL);

    zig_bool(true);

    uint8_t array[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    zig_array(array);

    {
        struct BigStruct s = {1, 2, 3, 4, 5};
        zig_big_struct(s);
    }

    {
        struct SmallStructInts s = {1, 2, 3, 4};
        zig_small_struct_ints(s);
    }

    {
        struct SplitStructInts s = {1234, 100, 1337};
        zig_split_struct_ints(s);
    }

    {
        struct BigStruct s = {30, 31, 32, 33, 34};
        struct BigStruct res = zig_big_struct_both(s);
        assert_or_panic(res.a == 20);
        assert_or_panic(res.b == 21);
        assert_or_panic(res.c == 22);
        assert_or_panic(res.d == 23);
        assert_or_panic(res.e == 24);
    }
}

void c_u8(uint8_t x) {
    assert_or_panic(x == 0xff);
}

void c_u16(uint16_t x) {
    assert_or_panic(x == 0xfffe);
}

void c_u32(uint32_t x) {
    assert_or_panic(x == 0xfffffffd);
}

void c_u64(uint64_t x) {
    assert_or_panic(x == 0xfffffffffffffffcULL);
}

void c_i8(int8_t x) {
    assert_or_panic(x == -1);
}

void c_i16(int16_t x) {
    assert_or_panic(x == -2);
}

void c_i32(int32_t x) {
    assert_or_panic(x == -3);
}

void c_i64(int64_t x) {
    assert_or_panic(x == -4);
}

void c_f32(float x) {
    assert_or_panic(x == 12.34f);
}

void c_f64(double x) {
    assert_or_panic(x == 56.78);
}

void c_ptr(void *x) {
    assert_or_panic(x == (void*)0xdeadbeefL);
}

void c_bool(bool x) {
    assert_or_panic(x);
}

void c_array(uint8_t x[10]) {
    assert_or_panic(x[0] == '1');
    assert_or_panic(x[1] == '2');
    assert_or_panic(x[2] == '3');
    assert_or_panic(x[3] == '4');
    assert_or_panic(x[4] == '5');
    assert_or_panic(x[5] == '6');
    assert_or_panic(x[6] == '7');
    assert_or_panic(x[7] == '8');
    assert_or_panic(x[8] == '9');
    assert_or_panic(x[9] == '0');
}

void c_big_struct(struct BigStruct x) {
    assert_or_panic(x.a == 1);
    assert_or_panic(x.b == 2);
    assert_or_panic(x.c == 3);
    assert_or_panic(x.d == 4);
    assert_or_panic(x.e == 5);
}

void c_big_union(union BigUnion x) {
    assert_or_panic(x.a.a == 1);
    assert_or_panic(x.a.b == 2);
    assert_or_panic(x.a.c == 3);
    assert_or_panic(x.a.d == 4);
}

void c_small_struct_ints(struct SmallStructInts x) {
    assert_or_panic(x.a == 1);
    assert_or_panic(x.b == 2);
    assert_or_panic(x.c == 3);
    assert_or_panic(x.d == 4);
}

void c_split_struct_ints(struct SplitStructInts x) {
    assert_or_panic(x.a == 1234);
    assert_or_panic(x.b == 100);
    assert_or_panic(x.c == 1337);
}

struct BigStruct c_big_struct_both(struct BigStruct x) {
    assert_or_panic(x.a == 1);
    assert_or_panic(x.b == 2);
    assert_or_panic(x.c == 3);
    assert_or_panic(x.d == 4);
    assert_or_panic(x.e == 5);
    struct BigStruct y = {10, 11, 12, 13, 14};
    return y;
}
