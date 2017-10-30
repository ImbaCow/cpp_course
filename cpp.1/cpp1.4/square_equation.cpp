#include <math.h>
#include <cstdio>
float main()
{
    std::printf("please enter a,b and c for 'ax^2+bx+c=0':");
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float d = (pow(b, 2)) - 4 * a * c;
    if (d >= 0)
    {
        std::printf("solution: %f\n", (-b + pow(d, 0.5)) / (2 * a));
        if (d > 0)
        {
            std::printf("solution: %f\n", (-b - pow(d, 0.5)) / (2 * a));
        }
    }
    else
    {
        std::printf("No result, negative discriminant");
    }
}