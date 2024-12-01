#include <stdio.h>
#include <stdbool.h>

// 定义结构体存储输出结果
typedef struct {
    bool not_a;
    bool not_b;
    bool not_c;
} G1_Output;

// G1电路实现函数
G1_Output G1_circuit(bool A, bool B, bool C) {
    G1_Output output = {
        .not_a = !A,
        .not_b = !B,
        .not_c = !C
    };
    return output;
}

int main() {
    printf("A B C | Not_A Not_B Not_C\n");
    printf("------------------------\n");

    // 测试所有可能的输入组合
    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            for (int c = 0; c <= 1; c++) {
                G1_Output result = G1_circuit(a, b, c);
                printf("%d %d %d |   %d     %d     %d\n", 
                    a, b, c, 
                    result.not_a, result.not_b, result.not_c);
            }
        }
    }
    
    return 0;
}