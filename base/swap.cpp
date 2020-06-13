#include <iostream>

using namespace std;

void print(int a, int b) {
    printf("a=%d b=%d", a, b);
    printf("\n-----\n");
}

// 指针
void swap1(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 引用
void swap2(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// 数值过大可能会导致内存溢出
void swap3(int &a, int &b) {
    /*
        // a变量赋值为a + b
        a = a + b;
        // b变量赋值为a
        b = a - b; // (a + b) - b = a
        // a变量赋值为b
        a = a - b; // 原理同b赋值
    */
    // 简写方式
    b = a + b - (a = b);
}

void swap4(int &a, int &b) {
    /*
        // a变量赋值为a ^ b
        a = a ^ b;
        // b变量赋值为a
        b = a ^ b; // (a ^ b) ^ b = a ^ (b ^ b) = a ^ 0 = a
        // b变量赋值为a
        a = a ^ b; // 原理同b赋值
    */
    // 简写方式1
    // b = a ^ b ^ (a = b);
    // 简写方式2
    a ^= b ^= a ^= b;
}

/*
 * 交换两个变量的值
 */
int main() {
    int a = 0, b = 1;

    // 临时变量交换
    swap1(&a, &b);
    swap2(a, b);
    print(a, b);

    // 加减交换
    swap3(a, b);
    print(a, b);

    // 异或交换
    swap4(a, b);
    print(a, b);

    // c++库交换
    swap(a, b);
    print(a, b);
    return 0;
}