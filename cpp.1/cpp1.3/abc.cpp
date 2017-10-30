#include <cstdio>

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    std::puts("please enter a, b and c for a+b+c");
    std::scanf("%d %d %d", &a, &b, &c);
    std::printf("solution: %d\n", a + b + c);
}