/*
두 개의 스택이 있다고 할 때, input되는 열차의 번호가 무작위일 때
output되는 열차의 번호를 순차적으로 만들어보자.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define NUM_TRAIN 9

#define True 1
#define False 0

#define MAX_CAL_LENGTH 100
#define MAX_STACK_SIZE 100

typedef int Bool;
typedef int Element;

typedef struct {
    int top;
    Element stackArr[MAX_STACK_SIZE];

}Stack;

Bool isElement(Stack* stack, Element data) {

    int i = 0;
    for (i = 0; i <= stack->top; i++) {
        if (stack->stackArr[i] == data) {
            return True;
            break;
        }
    }
    return False;
}

Stack* Create() {

    Stack* temp;
    temp = malloc(sizeof(Stack));
    temp->top = -1;
    return temp;
}

Bool isEmpty(Stack* stack) {

    if (stack->top == -1) {
        return True;
    }

    else {
        return False;
    }
}

Bool isFull(Stack* stack) {

    if (stack->top == MAX_STACK_SIZE - 1) {
        return True;
    }
    else {
        return False;
    }
}

void Push(Stack* stack, Element data) {

    stack->stackArr[++stack->top] = data;
}

Element Pop(Stack* stack) {
    if (stack->top == -1) {
        return False;
    }
    else {
        return stack->stackArr[stack->top--];
    }
}

Element Look(Stack* stack) {
    if (stack->top == -1) {
        return False;

    }
    else {
        return stack->stackArr[stack->top];
    }
}

void goTrain(int* train) {

    int i = 1;  // 나가는 기차.   // 들어오는 기차. 
    int k;  //스택에 쌓는 기차순서. 
    int num = 1; //기차 이동 -> 움직일때마다 증가.
    int num_stack1 = 0;             // stack1 최대 적재량. 
    int num_stack2 = 0;             // stack2 최대 적재량. 

    Stack* In = Create(); // 기차 입구(스택)  
    Stack* stack1 = Create(); //기차 스택2
    Stack* stack2 = Create(); //기차 스택2

    for (k = 0; k < NUM_TRAIN; k++) { //기차 입구스택에 기차넣기   

        Push(In, train[NUM_TRAIN - 1 - k]);
    }

    while (In->top != -1 || stack1->top != -1 || stack2->top != -1) {

        if (Look(In) == i) {
            printf("%d : IN(%d)\n", num++, Look(In));
            printf("%d : OUT(%d)\n", num++, Pop(In));
            i++;

        }
        else if (Look(stack1) == i) {
            printf("%d : POP(1)\n", num++);
            printf("%d : OUT(%d)\n", num++, Pop(stack1));
            i++;
        }

        else if (Look(stack2) == i) {
            printf("%d : POP(2)\n", num++);
            printf("%d : OUT(%d)\n", num++, Pop(stack2));     // 여기까지가 입구 혹은 스택에 해당 열차가 있었을 때.
            i++;
        }

        else {                                       // 해당 열차가 없을 때.          
            if (Look(In) > Look(stack2)) {  // In의 숫자가 stack2 보다 클때, 

                if (Look(stack2) > Look(stack1)) {  // stack2의 숫자가 stack1보다 클때, 

                    if (Look(stack1) == False) {   // stack1이 비어있을 때. 

                        printf("%d : IN(%d)\n", num++, Look(In));
                        printf("%d : PUSH(1, %d)\n", num++, Look(In));
                        Push(stack1, Pop(In));
                        if (stack1->top + 1 > num_stack1) {
                            num_stack1 = stack1->top + 1;
                        }

                    }
                    else {                            // stack2의 숫자가 크고 , stack1이 비어있지 않고 In의 숫자가 크다. -> In을 stack2에 넣는다
                        printf("%d : IN(%d)\n", num++, Look(In));
                        printf("%d : PUSH(2, %d)\n", num++, Look(In));
                        Push(stack2, Pop(In));
                        if (stack2->top + 1 > num_stack2) {
                            num_stack2 = stack2->top + 1;
                        }
                    }
                }
                else if (Look(stack2) == False) {            // stack2가 비어있고, In이 stack2 보다 클때, 

                    printf("%d : IN(%d)\n", num++, Look(In));
                    printf("%d : PUSH(2, %d)\n", num++, Look(In));
                    Push(stack2, Pop(In));
                    if (stack2->top + 1 > num_stack2) {
                        num_stack2 = stack2->top + 1;
                    }
                }
                else {
                    printf("%d : IN(%d)\n", num++, Look(In));
                    printf("%d : PUSH(1, %d)\n", num++, Look(In));
                    Push(stack1, Pop(In));
                    if (stack1->top + 1 > num_stack1) {
                        num_stack1 = stack1->top + 1;
                    }
                }
            }
            else if (Look(In) > Look(stack1)) {
                if (Look(stack1) < Look(stack2)) {

                    printf("%d : IN(%d)\n", num++, Look(In));
                    printf("%d : PUSH(1, %d)\n", num++, Look(In));
                    Push(stack1, Pop(In));
                    if (stack1->top + 1 > num_stack1) {
                        num_stack1 = stack1->top + 1;
                    }
                }
            }
            else if (Look(In) == False) {                  //In이 비어있고 
                if (isElement(stack1, i) == True) {          //stack1밑에 i번쨰 기차가 깔려있으면, stack1 -> stack2
                    printf("%d : POP(1)\n", num++);
                    printf("%d : PUSH(2, %d)\n", num++, Look(stack1));
                    Push(stack2, Pop(stack1));
                    if (stack2->top + 1 > num_stack2) {
                        num_stack2 = stack2->top + 1;
                    }
                }
                else if (isElement(stack2, i) == True) {
                    printf("%d : POP(2)\n", num++);
                    printf("%d : PUSH(1, %d)\n", num++, Look(stack2));
                    Push(stack1, Pop(stack2));
                    if (stack1->top + 1 > num_stack1) {
                        num_stack1 = stack1->top + 1;
                    }

                }
            }
            else {
                if (Look(stack1) > Look(stack2)) {
                    printf("%d : IN(%d)\n", num++, Look(In));
                    printf("%d : PUSH(1, %d)\n", num++, Look(In));
                    Push(stack1, Pop(In));
                    if (stack1->top + 1 > num_stack1) {
                        num_stack1 = stack1->top + 1;
                    }

                }
                else if (Look(stack1) < Look(stack2)) {

                    printf("%d : IN(%d)\n", num++, Look(In));
                    printf("%d : PUSH(2, %d)\n", num++, Look(In));
                    Push(stack2, Pop(In));
                    if (stack2->top + 1 > num_stack2) {
                        num_stack2 = stack2->top + 1;
                    }


                }

            }


        }
    }
    printf("종료 총 %d 회\n", num - 1);
    printf("최대 적재량\n1번 : %d대\n2번 : %d대", num_stack1, num_stack2);



}

int main(int argc, char* argv[]) {

    int train[NUM_TRAIN];

    int i;

    printf("열차의 순서를 입력하세요. \n\n");

    for (i = 0; i < NUM_TRAIN; i++) {

        scanf("%1d", &train[i]);
    }

    goTrain(train);


    return 0;

}
