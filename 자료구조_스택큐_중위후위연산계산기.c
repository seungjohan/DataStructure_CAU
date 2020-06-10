/*
사람이 사용하는 일반적인 식인 중위연산를
컴퓨터가 이해하기 쉽게 후위연산으로 바꾼 후 후위연산을 이용해 연산을 하는 계산기를 만들어보자.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> // strlen, strcat 함수 선언을 위해
#include <stdlib.h> // atoi 함수 선언을 위해

#define MAX_STACK_SIZE 100
#define True 1 // Bool을 사용하기 위해
#define False 0


typedef int ele;
typedef int Bool;

typedef struct {
    ele stackarr[MAX_STACK_SIZE];
    int top;
}stack;

stack* CreateStack(void) {
    stack* exstack;

    exstack = malloc(sizeof(stack));
    exstack->top = -1;

    return exstack;
}

Bool is_full(stack* pstack) {
    if (pstack->top == MAX_STACK_SIZE - 1)
        return True;
    else
        return False;
}

Bool is_empty(stack* pstack) {
    if (pstack->top == -1)
        return True;
    else
        return False;
}

void push(stack* pstack, int data) {
    if (is_full(pstack))
        return False;

    pstack->stackarr[++pstack->top] = data;
}

int pop(stack* pstack) {
    if (is_empty(pstack))
        return False;

    return pstack->stackarr[pstack->top--];
}

ele peek(stack* pstack) {
    if (is_empty(pstack))
        return False;
    else
        return   pstack->stackarr[pstack->top];
}

// 문자로 받은 연산자를 switch문을 통해 case별로 연산을 정의해줍니다.
void eval(stack* operator, stack* operand)
{
    char ch = pop(operator);
    int num1, num2;
    num1 = pop(operand);
    num2 = pop(operand);

    switch (ch)
    {
    case '+':
    {
        push(operand, num1 + num2);

        break;
    }
    case '-':
    {
        push(operand, num2 - num1);

        break;
    }
    case '*':
    {
        push(operand, num1 * num2);

        break;
    }
    case '^':
    {
        int num3 = 1;

        for (int i = 0; i < num1; i++)
        {
            num3 *= num2;
        }

        push(operand, num3);

        break;
    }
    }
}

int error_check_func(char* ex)
{

    Bool error = False;

    for (int i = 0; i < strlen(ex); i++)
    {
        if (ex[i] == '(')
        {
            error = True;

            for (int j = 0; j < strlen(ex); j++)
            {
                if (ex[j] == ')')
                {
                    error = False;
                }
            }
        }
    }

    if (error == True)
    {
        strcat(ex, "(!) 이 위치에 ')'가 부족합니다");

        return False;
    }

    char last_ch = ex[strlen(ex) - 1];
    char first_ch = ex[0];

    switch (last_ch)
    {
    case '+':
    case '-':
    case '^':
    case '(':
    {
        strcat(ex, "(!) 마지막에 연산자가 올 수 없습니다 ");

        return False;
    }

    }

    switch (first_ch)
    {
    case '+':
    case '-':
    case '^':
    case ')':
    {
        strcat(ex, "(!) 처음에 연산자가 올 수 없습니다 ");

        return False;
    }

    }


    for (int i = 0; i < strlen(ex); i++)
    {
        switch (ex[i])
        {
        case '+':
        case '-':
        case '*':
        case '^':
            switch (ex[i + 1])
            {
            case '+':
            case '-':
            case '*':
            case '^':
            {
                char str1[100], str2[100];

                for (int j = 0; j < i + 1; j++)
                {
                    str1[j] = ex[j];

                    if (j == i)
                        str1[j + 1] = 0;
                }

                int k = 0;

                for (int j = i + 1; j < strlen(ex); j++)
                {

                    str2[k++] = ex[j];

                    if (j == strlen(ex) - 1)
                        str2[k] = 0;

                    //k++;
                }

                strcat(str1, "(!)");
                strcat(str1, str2);
                strcat(str1, "이 위치에 숫자가 필요합니다.");

                strcpy(ex, str1);

                return False;
            }

            }
        }
    }

    return True;
}

int main(void)
{
    stack* s_operator = CreateStack();
    stack* s_operand = CreateStack();

    char ex[MAX_STACK_SIZE];
    char ex2[MAX_STACK_SIZE];
    scanf("%s", ex);


    // 에러가 발생되었을 경우 함수 error_check
    Bool error_check = error_check_func(ex);

    if (!error_check)
    {
        printf("%s 오류가 발생하였습니다.\n", ex);

        return 0;
    }

    int i = 0;
    char tmp_op;
    char* token;
    int num;

    strcpy(ex2, ex);

    token = strtok(ex2, "+-*^()");

    while (ex[i] != 0)
    {
        char ch = ex[i];

        if (ch != '+' && ch != '-' && ch != '*' && ch != '^' && ch != '(' && ch != ')') {
            num = atoi(token);
            push(s_operand, num); // 피연산자는 피연산자 스택을 따로 만들어 push한다.
            token = strtok(NULL, "+-*^()");

            if (num / 1) i++; // 연산자의 자리수를 감안해주기 위해
            if (num / 10) i++;
            if (num / 100) i++;

            continue;
        }
        else
        {
            switch (ch)
            {
            case '+':
            {
                if (is_empty(s_operator)) // 연산자는 스택이 비었으면 스택에 push한다.
                    push(s_operator, ch);
                else
                    // 스택이 비어있지 않을 때, '+'는 '('를 제외한 스택에 있는 연산자의 우선순위와 무조건 같거나 크므로 스택에 있는 연산자를 pop을 한 후 '+'를 스택에 push한다.
                {
                    tmp_op = peek(s_operator);

                    // 여는 괄호가 스택에 push된 후 닫는 괄호가 나올 때 까지 여는 괄호가 pop이 되면 안되므로 여는 괄호의 우선순위는 제일 작다.
                    // if (tmp_op != '(')  
                    // 처음에는 이렇게 만들어줬으나, stack에 예를 들어 +, *, ( 순으로 우선순위가 높은 연산자가 들어가있는데 + 또는 -가 오게 되면
                    // 조건에 맞춰 pop을 여러번 해줘야하기 때문에 if문이 아닌 while문으로 수정하였습니다.
                    while (tmp_op != '(')
                    {
                        //printf("%c", pop(s_operator)); // 초기에 중위 -> 후위연산으로 바뀌는지 확인하기 위해 printf를 먼저 해줘보았습니다.
                        eval(s_operator, s_operand);

                        tmp_op = peek(s_operator);

                        if (tmp_op == 0)
                            break;
                    }

                    push(s_operator, ch);
                }

                break;
            }
            case '-':
            {
                if (is_empty(s_operator)) // 연산자는 스택이 비었으면 스택에 push한다.
                    push(s_operator, ch);
                else // 스택이 비어있지 않을 때, '-'는 '('를 제외한 스택에 있는 연산자의 우선순위와 무조건 같거나 크므로 스택에 있는 연산자를 pop을 한 후 '-'를 스택에 push한다.
                {
                    tmp_op = peek(s_operator);

                    //if (tmp_op != '(')
                    while (tmp_op != '(')
                    {
                        // printf("%c", pop(s_operator));
                        eval(s_operator, s_operand);

                        tmp_op = peek(s_operator);

                        if (tmp_op == 0)
                            break;
                    }

                    push(s_operator, ch);

                }

                break;
            }
            case '*':
            {
                if (is_empty(s_operator)) // 연산자는 스택이 비었으면 스택에 push한다.
                    push(s_operator, ch);
                else
                    // 스택이 비어있지 않을 때, 
                    // 스택에 있는 연산자와의 우선순위를 비교해 스택에 있는 연산자의 우선순위가 같거나 크다면 스택에 있는 연산자를 pop을 한 후 출력하고 
                    // 현재 연산자는 스택에 push한다.
                {
                    tmp_op = peek(s_operator);

                    while (tmp_op == '^' || tmp_op == '*')
                    {
                        // printf("%c", pop(s_operator));
                        eval(s_operator, s_operand);

                        tmp_op = peek(s_operator);

                        if (tmp_op == 0)
                            break;
                    }

                    push(s_operator, ch);
                }

                break;
            }
            case '^':
            {
                if (is_empty(s_operator)) // 연산자는 스택이 비었으면 스택에 push한다.
                    push(s_operator, ch);
                else
                    // 스택이 비어있지 않을 때, 
                    // 스택에 있는 연산자와의 우선순위를 비교해 스택에 있는 연산자의 우선순위가 같거나 크다면 스택에 있는 연산자를 pop을 한 후 출력하고 
                    // 현재 연산자는 스택에 push한다.
                {
                    tmp_op = peek(s_operator);

                    while (tmp_op == '^')
                    {
                        //printf("%c", pop(s_operator));
                        eval(s_operator, s_operand);

                        tmp_op = peek(s_operator);

                        if (tmp_op == 0)
                            break;
                    }

                    push(s_operator, ch);
                }

                break;
            }
            case '(':
            {
                push(s_operator, ch); // 괄호가 여는 괄호 '('이면 무조건 스택에 push한다.

                break;
            }
            case ')':
            {
                while (peek(s_operator) != '(')
                {
                    //printf("%c", pop(s_operator));
                    eval(s_operator, s_operand);
                }


                pop(s_operator); // 여는 괄호 '('는 출력하지 않으므로 pop하여 버린다.

                break;
            }
            /*default:
            {
                printf("%c", ch); // 피연산자는 스택에 넣지 않고 그냥 출력한다.
            }*/

            }
        }

        //printf("%s\n", ex);
        i++;
    } // End of While (ex[i] != 0)

    while (!is_empty(s_operator)) // 수식이 끝나면 스택이 빌 때까지 pop을 한 후 출력한다.
    {
        eval(s_operator, s_operand);
        //printf("%c", pop(s_operator));
    }

    printf("\n= %d\n", pop(s_operand));

}
