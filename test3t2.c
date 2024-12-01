#include <stdio.h>

// 定义高阻态Z为-1
#define Z -1

// 实现X门的逻辑
int gate_X(int A, int B) {
    if (A == 0 && B == 0) return 1;
    return Z;  // 其他情况返回高阻态
}

// 实现Y门的逻辑
int gate_Y(int A, int B) {
    if (A == 1 && B == 1) return 0;
    return Z;  // 其他情况返回高阻态
}

// 实现并联输出的XOR功能
int XOR(int A, int B) {
    int out_X = gate_X(A, B);
    int out_Y = gate_Y(A, B);
    
    // 如果X输出不是高阻态，使用X的输出
    if (out_X != Z) return out_X;
    // 如果Y输出不是高阻态，使用Y的输出
    if (out_Y != Z) return out_Y;
    // 如果都是高阻态，返回1（对应输入不同的情况）
    return 1;
}

int main() {
    // 测试所有可能的输入组合
    printf("A B | XOR\n");
    printf("---------\n");
    for (int A = 0; A <= 1; A++) {
        for (int B = 0; B <= 1; B++) {
            printf("%d %d | %d\n", A, B, XOR(A, B));
        }
    }
    return 0;
}