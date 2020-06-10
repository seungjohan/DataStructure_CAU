/*
2차원배열로 하여 전체 항을 표시하는게 아닌
계수가 0이 아닌 항들만 배열에 담아 두 다항식의 합과 곱을 계산하는 방법을 찾아보자.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAX_TERMS 26

typedef struct {
    float coef;
    int exp;
} polynomial;

polynomial C[MAX_TERMS] = { {0,0}, };
polynomial D[MAX_TERMS] = { {0,0}, };


int poly2_add(polynomial* A, polynomial* B, int Anum, int Bnum) {

    int Apos = 0, Bpos = 0, Cpos = 0;

    while (Anum >= 0 && Bnum >= 0) {

        if (A[Apos].exp > B[Bpos].exp) {
            C[Cpos].exp = A[Apos].exp;
            C[Cpos++].coef = A[Apos++].coef;
            Anum--;
        }
        else if (A[Apos].exp == B[Bpos].exp) {
            C[Cpos].exp = A[Apos].exp;
            C[Cpos++].coef = A[Apos++].coef + B[Bpos++].coef;
            Anum--;
            Bnum--;
        }
        else {
            C[Cpos].exp = B[Bpos].exp;
            C[Cpos++].coef = B[Bpos++].coef;
            Bnum--;
        }
    }
    while (Anum >= 0) {
        C[Cpos].exp = A[Apos].exp;
        C[Cpos++].coef = A[Apos++].coef;
        Anum--;
    }
    while (Bnum >= 0) {
        C[Cpos].exp = B[Bpos].exp;
        C[Cpos++].coef = B[Bpos++].coef;
        Bnum--;
    }
    return Cpos;
}

int poly2_mul(polynomial* A, polynomial* B, int Anum, int Bnum) {

    int avail = 0;
    int Apos = 0, Bpos = 0;;
    int state[MAX_TERMS] = { 0, };

    while (Apos < Anum) {
        if (avail == 0) {
            for (int i = 0; i < Bnum; i++) {
                D[i].coef = A[Apos].coef * B[i].coef;
                D[i].exp = A[Apos].exp + B[i].exp;
                avail++;
            }
            Apos++;
        }
        else
        {
            for (int i = 0; i < avail; i++) {
                state[i] = 0;
            }

            Bpos = 0;

            while (Bpos < Bnum)
            {
                for (int i = 0; i < avail; i++) {
                    if (D[i].exp == A[Apos].exp + B[Bpos].exp) {
                        D[i].coef += A[Apos].coef * B[Bpos++].coef;
                        state[i] = 1;
                    }
                }

                for (int i = 0; i < avail; i++) {
                    if (state[i] == 0) {
                        D[avail].exp = A[Apos].exp + B[Bpos].exp;
                        D[avail++].coef = A[Apos].coef * B[Bpos++].coef;

                        if (Bpos >= Bnum) break;
                    }
                }
            }
            Apos++;
        }
    }

    //곱셈에서 입력받은 무작위한 배열을 내림차순으로 정렬
    float temp1;
    int temp2;
    for (int i = 0; i < avail - 1; i++) {
        for (int j = i + 1; j < avail; j++) {
            if (D[i].exp < D[j].exp) {
                temp2 = D[j].exp;
                temp1 = D[j].coef;
                D[j].exp = D[i].exp;
                D[j].coef = D[i].coef;
                D[i].exp = temp2;
                D[i].coef = temp1;
            }
        }
    }
    return avail;
}


int main()
{
    polynomial A[MAX_TERMS] = { {0,0} };
    polynomial B[MAX_TERMS] = { {0,0} };

    int Anum, Bnum;
    int x, num; //나중에 수식에 대입할 값, 수식 선택을 위한 변수지정
    double result = 0; // 결과값 출력

    printf("수식 1은 몇 개의 항으로 구성되어 있나요? : ");
    scanf("%d", &Anum);
    printf("수식 1을 입력하세요 : ");
    for (int i = 0; i < Anum; i++) {
        scanf("%f %d", &A[i].coef, &A[i].exp);
    }

    printf("수식 2은 몇 개의 항으로 구성되어 있나요? : ");
    scanf("%d", &Bnum);
    printf("수식 2을 입력하세요 : ");
    for (int i = 0; i < Bnum; i++) {
        scanf("%f %d", &B[i].coef, &B[i].exp);
    }

    // C와 D에서 각각 전체 항의 개수를 반환하기 위해 함수자료형을 int로 하고 변수를 반환받음.
    int Cpos = poly2_add(A, B, Anum, Bnum);
    int avail = poly2_mul(A, B, Anum, Bnum);

    printf("\n수식 1 add 2는 ");
    for (int i = 0; i < Cpos - 1; i++) {
        printf("%1.fx^%d ", C[i].coef, C[i].exp);
    }

    printf("\n수식 1 mul 2는 ");
    for (int i = 0; i < avail; i++) {
        printf("%1.fx^%d ", D[i].coef, D[i].exp);
    }printf("\n");


    //if조건문을 이용한 수식 선택 후 연산 과정
    printf("\n몇 번 수식에 어떤 값을 넣으세요 ");
    scanf("%d %d", &num, &x);

    if (num == 1) {
        for (int i = 0; i < Anum; i++) {
            double k = pow(x, A[i].exp);
            result += A[i].coef * k;
        }
    }
    else if (num == 2) {
        for (int i = 0; i < Bnum; i++) {
            double k = pow(x, B[i].exp);
            result += B[i].coef * k;
        }
    }
    else if (num == 3) {
        for (int i = 0; i < Cpos - 1; i++) {
            double k = pow(x, C[i].exp);
            result += C[i].coef * k;
        }
    }
    else if (num == 4) {
        for (int i = 0; i < avail; i++) {
            double k = pow(x, D[i].exp);
            result += D[i].coef * k;
        }
    }

    printf("결과값은 %1.0lf", result);


    return 0;
}
