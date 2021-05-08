/*
최고차항부터 상수항까지 모든 계수의 항을 다 표현해서 배열에 저장하고
두 다항식의 합과 곱을 구해보자.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX1(a,b) (((a) > (b))?(a):(b))
#define MAX_DEGREE 26

typedef struct {
    int degree;
    float coef[MAX_DEGREE];
}polynomial;

polynomial poly_add1(polynomial A, polynomial B)
{
    polynomial C;
    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;
    C.degree = MAX1(A.degree, B.degree);

    for (int Apos = 0; Apos <= A.degree; Apos++) {
        if (degree_a > degree_b) {
            C.coef[Cpos++] = A.coef[Apos];
            degree_a--;
        }
        else if (degree_a == degree_b) {
            C.coef[Cpos++] = A.coef[Apos] + B.coef[Bpos++];
            degree_a--;
            degree_b--;
        }
        else {
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

polynomial poly_mul1(polynomial A, polynomial B)
{
    polynomial D;
    int Apos = 0, Bpos = 0, Dpos;
    D.degree = A.degree + B.degree;
    memset(D.coef, 0, sizeof(float) * (D.degree + 1));

    int i = 0;

    while (Apos <= A.degree) {

        Dpos = i;
        Bpos = 0;

        while (Bpos <= B.degree) {
            D.coef[Dpos++] += A.coef[Apos] * B.coef[Bpos++];
        }
        i++;
        Apos++;
    }
    return D;
}

int main()
{
    polynomial a;
    polynomial b;
    polynomial c;
    polynomial d;

    int x, num; //나중에 수식에 대입할 값, 수식 선택을 위한 변수지정
    double result = 0; // 결과값 출력

    printf("수식 a의 최고차항은 어떻게 되나요? : ");
    scanf("%d", &a.degree);
    printf("수식 a의 계수들을 입력하세요(계수 0도 포함하여) : ");
    for (int i = 0; i <= a.degree; i++)
        scanf("%f", &a.coef[i]);

    printf("수식 b의 최고차항은 어떻게 되나요 : ");
    scanf("%d", &b.degree);
    printf("수식 b의 계수들을 입력하세요(계수 0도 포함하여) : ");
    for (int i = 0; i <= b.degree; i++)
        scanf("%f", &b.coef[i]);

    //add, mul의 결과값을 받은 후 출력하는 과정
    c = poly_add1(a, b);
    d = poly_mul1(a, b);

    printf("\n수식 a add b는\n");
    for (int i = 0; i <= c.degree; i++)
    {
        int add = c.degree - i;
        printf("%1.0fx^%d ", c.coef[i], add);
    }

    printf("\n수식 a mul b는\n");
    for (int i = 0; i <= d.degree; i++)
    {
        int mul = d.degree - i;
        printf("%1.0fx^%d ", d.coef[i], mul);
    }

    //if조건문을 이용한 수식 선택 후 연산 과정
    printf("\n몇 번 수식에 어떤 값을 넣으세요 ");
    scanf("%d %d", &num, &x);

    if (num == 1) {
        for (int i = 0; i <= a.degree; i++) {
            int y = a.degree - i;
            double k = pow(x, y);
            result += a.coef[i] * k;
        }
    }
    else if (num == 2) {
        for (int i = 0; i <= b.degree; i++) {
            int y = b.degree - i;
            double k = pow(x, y);
            result += b.coef[i] * k;
        }
    }
    else if (num == 3) {
        for (int i = 0; i <= c.degree; i++) {
            int y = c.degree - i;
            double k = pow(x, y);
            result += c.coef[i] * k;
        }
    }
    else if (num == 4) {
        for (int i = 0; i <= d.degree; i++) {
            int y = d.degree - i;
            double k = pow(x, y);
            result += d.coef[i] * k;
        }
    }

    printf("결과값은 %1.0lf", result);
}
