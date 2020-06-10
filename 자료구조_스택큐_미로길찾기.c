/*
미로를 만들어보고 길찾는 해법을 찾아보자.
미로를 찾을 때는 스택을 이용
스택을 이용할 때마다 스택에서 어떤 정보를 push, pop하는지 화면에 표시
최종적으로 찾은 길을 화면에 표시

미로를 어떻게 저장할 것인지가 가장 핵심!!
*/

#include <stdio.h>
#include <stdlib.h>

#define True		1
#define False		0
#define STACK_LEN	100


// stack 구현

typedef int Data;

typedef struct {
	Data stackArr[STACK_LEN];
	int top;
}Stack;

void CreateStack(Stack* pstack)
{
	pstack->top = -1; // stack 초기화, top의 -1은 빈 상태를 의미.
}
int isEmpty(Stack* pstack)
{
	if (pstack->top == -1)
		return True;
	else
		return False;
}

void Push(Stack* pstack, Data data)
{
	pstack->stackArr[++pstack->top] = data;
}
Data Pop(Stack* pstack)
{
	if (isEmpty(pstack)) {
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->stackArr[pstack->top--];
}
Data Peek(Stack* pstack)
{
	if (isEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->stackArr[pstack->top];
}


int main() {

	printf("Start to find the goal in the MAZE!!\n\n");

	//갈림길이 나타났을 때, 현재 x 좌표를 저장하기 위한 스택.
	Stack stackX;
	CreateStack(&stackX);

	//갈림길이 나타났을 때, 현재 y 좌표를 저장하기 위한 스택.
	Stack stackY;
	CreateStack(&stackY);

	//갈림길이 나타났을 때, 위, 아래, 오른쪽, 왼쪽 중 이동가능한 위치를 저장하기 위한 스택.
	Stack stackP;
	CreateStack(&stackP);


	// 미로 2차원배열로 저장
	int Makemaze[12][9];
	int i = 0, j = 0;
	int k = 0, l = 0;

	Makemaze[0][0] = 0; Makemaze[0][1] = 1; Makemaze[0][2] = 1; Makemaze[0][3] = 1; Makemaze[0][4] = 0; Makemaze[0][5] = 1; Makemaze[0][6] = 1; Makemaze[0][7] = 1; Makemaze[0][8] = 0;
	Makemaze[1][0] = 2; Makemaze[1][1] = 1; Makemaze[1][2] = 1; Makemaze[1][3] = 2; Makemaze[1][4] = 0; Makemaze[1][5] = 1; Makemaze[1][6] = 3; Makemaze[1][7] = 2; Makemaze[1][8] = 2;
	Makemaze[2][0] = 0; Makemaze[2][1] = 1; Makemaze[2][2] = 3; Makemaze[2][3] = 2; Makemaze[2][4] = 3; Makemaze[2][5] = 0; Makemaze[2][6] = 3; Makemaze[2][7] = 2; Makemaze[2][8] = 2;
	Makemaze[3][0] = 2; Makemaze[3][1] = 0; Makemaze[3][2] = 2; Makemaze[3][3] = 0; Makemaze[3][4] = 0; Makemaze[3][5] = 2; Makemaze[3][6] = 0; Makemaze[3][7] = 3; Makemaze[3][8] = 2;
	Makemaze[4][0] = 2; Makemaze[4][1] = 2; Makemaze[4][2] = 0; Makemaze[4][3] = 3; Makemaze[4][4] = 2; Makemaze[4][5] = 1; Makemaze[4][6] = 3; Makemaze[4][7] = 0; Makemaze[4][8] = 3;
	Makemaze[5][0] = 2; Makemaze[5][1] = 3; Makemaze[5][2] = 2; Makemaze[5][3] = 2; Makemaze[5][4] = 1; Makemaze[5][5] = 1; Makemaze[5][6] = 1; Makemaze[5][7] = 3; Makemaze[5][8] = 0;
	Makemaze[6][0] = 2; Makemaze[6][1] = 1; Makemaze[6][2] = 3; Makemaze[6][3] = 2; Makemaze[6][4] = 0; Makemaze[6][5] = 1; Makemaze[6][6] = 1; Makemaze[6][7] = 1; Makemaze[6][8] = 3;
	Makemaze[7][0] = 0; Makemaze[7][1] = 0; Makemaze[7][2] = 1; Makemaze[7][3] = 3; Makemaze[7][4] = 2; Makemaze[7][5] = 0; Makemaze[7][6] = 1; Makemaze[7][7] = 3; Makemaze[7][8] = 2;
	Makemaze[8][0] = 2; Makemaze[8][1] = 2; Makemaze[8][2] = 1; Makemaze[8][3] = 1; Makemaze[8][4] = 3; Makemaze[8][5] = 2; Makemaze[8][6] = 1; Makemaze[8][7] = 1; Makemaze[8][8] = 1;
	Makemaze[9][0] = 2; Makemaze[9][1] = 1; Makemaze[9][2] = 1; Makemaze[9][3] = 2; Makemaze[9][4] = 1; Makemaze[9][5] = 0; Makemaze[9][6] = 2; Makemaze[9][7] = 0; Makemaze[9][8] = 2;
	Makemaze[10][0] = 2; Makemaze[10][1] = 1; Makemaze[10][2] = 2; Makemaze[10][3] = 2; Makemaze[10][4] = 2; Makemaze[10][5] = 2; Makemaze[10][6] = 1; Makemaze[10][7] = 3; Makemaze[10][8] = 2;
	Makemaze[11][0] = 0; Makemaze[11][1] = 3; Makemaze[11][2] = 2; Makemaze[11][3] = 3; Makemaze[11][4] = 2; Makemaze[11][5] = 3; Makemaze[11][6] = 0; Makemaze[11][7] = 1; Makemaze[11][8] = 3;


	i = 0;

	char maze[25][38] = { ' ', };
	char* ptr = &maze[0][0];

	// 미로표현은 포인터연산을 이용하여 모양을 표시
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 9; j++) {
			if (Makemaze[i][j] == 0) {
				*(ptr + k * 38 + l) = '+';
				*(ptr + k * 38 + (l + 1)) = '-';
				*(ptr + k * 38 + (l + 2)) = '-';
				*(ptr + k * 38 + (l + 3)) = '-';
				*(ptr + (k + 1) * 38 + l) = '|';
				*(ptr + (k + 1) * 38 + (l + 1)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 2)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 3)) = ' ';
				if (j < 8) {
					l += 4;
				}
				else {
					*(ptr + k * 38 + (l + 4)) = '+';
					*(ptr + k * 38 + (l + 5)) = '\n';
					*(ptr + (k + 1) * 38 + (l + 4)) = '|';
					*(ptr + (k + 1) * 38 + (l + 5)) = '\n';
					l = 0;
					k += 2;
				}
			} // End of (Makemaze[i][j] == 0)
			else if (Makemaze[i][j] == 1) {
				*(ptr + k * 38 + l) = '+';
				*(ptr + k * 38 + (l + 1)) = '-';
				*(ptr + k * 38 + (l + 2)) = '-';
				*(ptr + k * 38 + (l + 3)) = '-';
				*(ptr + (k + 1) * 38 + l) = ' ';
				*(ptr + (k + 1) * 38 + (l + 1)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 2)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 3)) = ' ';
				if (j < 8) {
					l += 4;
				}
				else {
					*(ptr + k * 38 + (l + 4)) = '+';
					*(ptr + k * 38 + (l + 5)) = '\n';
					*(ptr + (k + 1) * 38 + (l + 4)) = '|';
					*(ptr + (k + 1) * 38 + (l + 5)) = '\n';
					l = 0;
					k += 2;
				}


			} // End of (Makemaze[i][j] == 1)
			else if (Makemaze[i][j] == 2) {
				*(ptr + k * 38 + l) = '+';
				*(ptr + k * 38 + (l + 1)) = ' ';
				*(ptr + k * 38 + (l + 2)) = ' ';
				*(ptr + k * 38 + (l + 3)) = ' ';
				*(ptr + (k + 1) * 38 + l) = '|';
				*(ptr + (k + 1) * 38 + (l + 1)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 2)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 3)) = ' ';
				if (j < 8) {
					l += 4;
				}
				else {
					*(ptr + k * 38 + (l + 4)) = '+';
					*(ptr + k * 38 + (l + 5)) = '\n';
					*(ptr + (k + 1) * 38 + (l + 4)) = '|';
					*(ptr + (k + 1) * 38 + (l + 5)) = '\n';
					l = 0;
					k += 2;
				}


			} // End of (Makemaze[i][j] == 2)
			else if (Makemaze[i][j] == 3) {
				*(ptr + k * 38 + l) = '+';
				*(ptr + k * 38 + (l + 1)) = ' ';
				*(ptr + k * 38 + (l + 2)) = ' ';
				*(ptr + k * 38 + (l + 3)) = ' ';
				*(ptr + (k + 1) * 38 + l) = ' ';
				*(ptr + (k + 1) * 38 + (l + 1)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 2)) = ' ';
				*(ptr + (k + 1) * 38 + (l + 3)) = ' ';
				if (j < 8) {
					l += 4;
				}
				else {
					*(ptr + k * 38 + (l + 4)) = '+';
					*(ptr + k * 38 + (l + 5)) = '\n';
					*(ptr + (k + 1) * 38 + (l + 4)) = '|';
					*(ptr + (k + 1) * 38 + (l + 5)) = '\n';
					l = 0;
					k += 2;
				}
			} // End of (Makemaze[i][j] == 3)

		} // for (j = 0; j < 9; j++) 
	} // for (i = 0; i < 12; i++) 

	for (j = 0; j < 37; j++) {
		if (j % 4 == 0) maze[24][j] = '+';
		else maze[24][j] = '-';
	}


	//막힌 벽을 구분하기 위한 배열.
	//8은 위쪽 벽, 4는 오른쪽 벽, 2는 아래쪽 벽, 1은 왼쪽 벽이 막혔음을 의미.
	//해당 위치에서 막힌 벽에 해당하는 숫자를 다 더해준다.
	char mazewall[12][9] = { {9,  2,  2, 12, 11, 10,  8, 12, 13},
							  {3, 10, 12,  5,  9, 10,  4,  5,  5},
							  {9, 10,  4,  3,  6,  9,  6,  5,  5},
							  {5, 13,  7, 13, 13,  7,  9,  6,  5},
							  {5,  5,  9,  4,  3, 10,  6,  9,  6},
							  {1,  6,  5,  1, 10, 10, 10,  6,  13},
							  {3, 10,  6,  5,  9, 10, 10,  8 , 4},
							  {13, 9, 10,  6,  5,  9, 10,  6,  7},
							  {5,  3, 10,  8,  6,  3,  8, 10, 12},
							  {1, 10, 12,  1, 12, 13,  7, 13,  5},
							  {3, 12,  5,  5,  5,  1, 10,  6,  5},
							  {11, 6,  3,  6,  3,  6, 11, 10,  6} };



	//말의 좌표를 표현하기 위한 변수들.
	int userX = 0, userY = 0;

	//현재 막힌 벽을 확인하기 위한 변수.
	int wall = 0;

	//다른 이동 가능한 길이 있을 때, 이동했던 방향으로 다시 가는 것을 막기 위한 변수.
	int direction = 0;

	//갈림길의 갯수를 세기 위한 변수.
	int cross = 0;

	//아래 변수들 설명 넣자.
	int count = 0;

	//갈림길이 생겼을 때 부터, state를 True로 바꾸어 이동한 횟수를 세어준다.
	//길이 막혔을 경우, 이동 경로를 이동한 횟수만큼 없애주고 다른 갈림길로 이동한다.
	int state = False;
	int state2 = False;

	int temp1 = 0;
	int temp2 = 0;

	//최종 경로를 나타내기 위한 스택.
	Stack stackXF;
	Stack stackYF;

	CreateStack(&stackXF);
	CreateStack(&stackYF);

	//갈림길이 생겼을 때 부터, 이동한 횟수를 세어 길이 막혔을 경우, 잘못 이동한 횟수를 저장하기 위한 스택.
	Stack stackC;
	CreateStack(&stackC);

	//갈림길이 나타났을 때, 갈림길의 갯수를 세어주는 스택.
	Stack stackCross;
	CreateStack(&stackCross);

	//8은 위쪽 벽, 4는 오른쪽 벽, 2는 아래쪽 벽, 1은 왼쪽 벽이 막혔음을 뜻함.
	//막히지 않은 경우, 그 벽에 해당하는 숫자를 위치 스택에 해당하는 stackP에 넣어 그 쪽으로 이동 가능을 의미.
	while (!(userX == 8 && userY == 11)) {

		//direction를 더해줌으로 전에 이동했던 방향을 막힌 길로 인식.
		wall = mazewall[userY][userX] + direction;

		//wall이 15(8+4+2+1)인 경우 모든 벽이 막힌 상황이므로 다른 선택지를 Pop.
		if (wall == 15) {

			//현재 위치 저장.
			Push(&stackXF, userX);
			Push(&stackYF, userY);

			//현재까지 이동한 횟수 저장.
			//길이 막혔으므로, 이동한 좌표를 최종 경로에서 없애주기 위해.
			Push(&stackC, count);

			//이동한 횟수를 저장하는 임시 변수.
			temp1 = Pop(&stackC);

			if (isEmpty(&stackC)) state = False;

			if (!(isEmpty(&stackCross)) && temp2 == 0) {
				temp2 = Pop(&stackCross);
			}

			//아직 다른 선택지가 남은 경우.
			if (temp2 == 1) state2 = True;

			//잘못 이동한 경로를 최종 경로에서 제거.
			for (i = 0; i < temp1; i++) {
				Pop(&stackXF);
				Pop(&stackYF);
			}
			if (temp2 > 0) temp2--;

			if (state2) {

				temp1 = Pop(&stackC);

				if (isEmpty(&stackC)) state = False;

				for (i = 0; i < temp1; i++) {
					Pop(&stackXF);
					Pop(&stackYF);
				}
				state2 = False;
			}

			count = 0;

			//막힌 경우 다른 선택지 위치로 가야하므로 미리 Pop.
			userX = Pop(&stackX);
			userY = Pop(&stackY);

			if (!isEmpty(&stackP)) { //Push 할 땐 3개의 스택을 다 같이 한꺼번에 Push하므로, 하나의 스택만 Empty인지 확인.
				if (Peek(&stackP) == 8) {
					printf("POP(%d,%d, Move above)\n", userX, userY);
					Pop(&stackP);

					direction = 2; //위로 이동하니, 갔던 방향으로 다시 못 가게 아래 쪽을 막힌 벽이라 생각.

					userY -= 1; //위로 이동.
				}
				else if (Peek(&stackP) == 4) {
					printf("POP(%d,%d, Move right)\n", userX, userY);
					Pop(&stackP);

					direction = 1;

					userX += 1;
				}
				else if (Peek(&stackP) == 2) {
					printf("POP(%d,%d, Move beneath)\n", userX, userY);
					Pop(&stackP);

					direction = 8;

					userY += 1;
				}
				else if (Peek(&stackP) == 1) {
					printf("POP(%d,%d, Available to move left)\n", userX, userY);
					Pop(&stackP);

					direction = 4;

					userX -= 1;
				}
			}
			if (state) count++;
			continue;
		}

		//wall이 8보다 같거나 큰 경우, 윗쪽 벽이 막힌 경우므로 빼주고 다음 경우로.
		if (wall >= 8)
			wall -= 8;
		//wall이 8보다 작은 경우, 위로 이동 가능.
		//그러므로 현재 좌표와 이동 가능한 방향을 스택에 저장.
		else {
			Push(&stackX, userX);
			Push(&stackY, userY);
			Push(&stackP, 8);

			Push(&stackXF, userX);
			Push(&stackYF, userY);

			printf("PUSH(%d,%d, Available to move above)\n", userX, userY);

			cross++; //이동 가능한 길의 갯수를 세기 위한 변수.
		}

		if (wall >= 4)
			wall -= 4;
		else {
			Push(&stackX, userX);
			Push(&stackY, userY);
			Push(&stackP, 4);

			Push(&stackXF, userX);
			Push(&stackYF, userY);

			printf("PUSH(%d,%d, Available to move right)\n", userX, userY);

			cross++;
		}

		if (wall >= 2)
			wall -= 2;
		else {
			Push(&stackX, userX);
			Push(&stackY, userY);
			Push(&stackP, 2);

			Push(&stackXF, userX);
			Push(&stackYF, userY);

			printf("PUSH(%d,%d, Available to move beneath)\n", userX, userY);

			cross++;
		}


		if (wall >= 1)
			wall -= 1;
		else {
			Push(&stackX, userX);
			Push(&stackY, userY);
			Push(&stackP, 1);

			Push(&stackXF, userX);
			Push(&stackYF, userY);

			printf("PUSH(%d,%d, Available to move left)\n", userX, userY);

			cross++;
		}

		if (cross > 1) {

			// 여러 번 갈림길이 있었다면, 여러 번 push 되기 때문에, 1번만 남도록 Pop.
			for (i = 0; i < cross - 1; i++) {
				Pop(&stackXF); Pop(&stackYF);
			}

			// StackCross는 이동 가능한 경로가 2 이상 일 때, 스택에 저장.
			Push(&stackCross, cross);

			// state를 True(1, 참)으로 바꿈으로써, 여러 갈림길이 생겼을 때 부터 이동한 횟수를 카운팅.
			state = True;

			// 다른 갈림길이 생겼을 때, 이전에 이동한 횟수를 저장하는 스택.
			if (count != 0) Push(&stackC, count);

			count = 0;
		}
		cross = 0;

		if (!isEmpty(&stackX)) { // Push 할 땐 3개의 스택을 다 같이 한꺼번에 Push하므로, 하나의 스택만 Empty인지 확인.

			// state가 True이면 갈림길이 있었던 경우이고 후에 길이 막힐 경우를 생각해 이동한 횟수를 카운팅.
			if (state) count++;

			if (Peek(&stackP) == 8) {
				printf("POP(%d,%d, Move to above)\n", Pop(&stackX), Pop(&stackY));
				Pop(&stackP);

				direction = 2; //위로 이동하니, 갔던 방향으로 다시 못 가게 아래 쪽을 막힌 벽이라 생각.

				userY -= 1;
			}
			else if (Peek(&stackP) == 4) {
				printf("POP(%d,%d, Move to right)\n", Pop(&stackX), Pop(&stackY));
				Pop(&stackP);

				direction = 1;

				userX += 1;
			}
			else if (Peek(&stackP) == 2) {
				printf("POP(%d,%d, Move to beneath)\n", Pop(&stackX), Pop(&stackY));
				Pop(&stackP);

				direction = 8;

				userY += 1;
			}
			else if (Peek(&stackP) == 1) {
				printf("POP(%d,%d, Move to left)\n", Pop(&stackX), Pop(&stackY));
				Pop(&stackP);

				direction = 4;

				userX -= 1;
			}
		}
	} if (userX == 8 && userY == 11)
		printf("\nYEAH!! Here is the goal!!\n\n");



	while (!isEmpty(&stackXF)) {
		maze[Pop(&stackYF) * 2 + 1][Pop(&stackXF) * 4 + 2] = 'O';
	}

	maze[1][2] = 'S';
	maze[11 * 2 + 1][8 * 4 + 2] = 'E';
	maze[19][14] = ' ';
	for (i = 0; i < 25; i++) {
		for (j = 0; j < 38; j++) {
			printf("%c", maze[i][j]);
		}
	}
	printf("\n");

	printf("\n\n20160499 한승조");
}
