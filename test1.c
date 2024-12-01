#include <stdio.h>
#include <math.h>

#define STEP_SIZE 0.001//定义瞬时值求解的步长
#define TOLERANCE 0.001//定义前后两个迭代结果之间的差值

double f(double y) // 微分方程的右侧
{
    return -y; // dy/dx = -y
}

int main() 
{
    double a, y, y1, x = 0.0;//y1代表上一个y
    printf("Enter the initial value a (y(0) = a): ");//输入a
    scanf("%lf", &a);

    y = a; //即 y(0) = a

    printf("Time\t\tValue\n");//次数，取值
    printf("-----------------------\n");

    while (1) //创造一个无限循环
    {
        printf("%.3f\t\t%.6f\n", x, y);
        
        y1 = y;// 保存前一个值以检查收敛
        y += STEP_SIZE * f(y);//y(t+h) ≈ y(t) + h * f(y(t))
        x += STEP_SIZE;//x = x + h

        // 检查收敛条件
        if (fabs(y - y1) < TOLERANCE * STEP_SIZE) //确保了收敛条件不仅依赖于固定的容差值，还考虑了当前步长的影响。
        {
            break;
        }
    }
    printf("\nSteady-State Value: %.6f\n", y);// 输出最终定态值
    return 0;
}