#include <stdio.h>

/* 计算第 n 个斐波那契数（递归版，便于演示断点单步） */
int fib(int n) {
    if (n < 2) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    printf("Hello from C!\n");

    for (int i = 0; i < 10; i++) {
        printf("fib(%d) = %d\n", i, fib(i));
    }

    return 0;
}
