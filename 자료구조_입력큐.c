/* 
키보드로부터 문자를 입력 받아 사용자가 원하면 그 개수만큼 빼서 사용자에게 돌려주는 표준입력 큐를 만들고 동작을 표시하는 프로그램
scanf 와 같은 표준 입력 함수는 키보드로부터 입력 받은 내용을 입력 큐에 담아두고, scanf 함수의 요구에 따라 필요한 만큼 입력 큐에서 가져온다.
입력 큐는 20 글자 크기를 갖는다. 입력 큐의 범위를 초과하면 받아들일 수 없다(에러 표시).
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define	FALSE	0

// 큐 구현.

#define QUE_LEN	20 // 한 칸을 비워둔다고 생각하고, 문자는 총 19칸에 저장하는 것으로 생각했습니다.
typedef int Data;

typedef struct {
	Data QueueArr[QUE_LEN];
	int front;
	int rear;
} Queue;


void CreateQueue(Queue* cqueue)	// 텅 빈 경우 front와 rear은 동일위치를 가리킴.
{
	cqueue->front = 0;
	cqueue->rear = 0;
}

int IsEmpty(Queue* cqueue)
{
	if (cqueue->front == cqueue->rear)
		return TRUE;
	else
		return FALSE;
}

int NextPosIdx(int pos)
{
	if (pos == QUE_LEN - 1)	// 배열의 마지막 요소의 인덱스 값이라면
		return 0;
	else
		return pos + 1;
}

void Enqueue(Queue* cqueue, Data data)
{
	if (!(NextPosIdx(cqueue->rear) == cqueue->front))
	{
		cqueue->rear = NextPosIdx(cqueue->rear); // rear을 한 칸 이동
		cqueue->QueueArr[cqueue->rear] = data; // rear이 가리키는 곳에 데이터 저장
	}
}

Data Dequeue(Queue* cqueue)
{
	cqueue->front = NextPosIdx(cqueue->front); // front를 한 칸 이동

	return cqueue->QueueArr[cqueue->front];
}

Data QPeek(Queue* cqueue) {
	if (IsEmpty(cqueue)) {
		printf("Queue Memeory Error");
		exit(-1);
	}

	return cqueue->QueueArr[NextPosIdx(cqueue->front)];
}


int main(void) {

	int i;

	// 문자열을 입력 받으면, 그 뒤에 0(null) 값이 있으므로 문자열의 끝임을 알립니다.
	// gets로 받으면 문자열 끝에 자동으로 null 값을 넣어주는 것 같습니다다. 꼭 초기화 시킬 필요 없을 것 같지만 혹시 모르니 넣어놓기.
	char input[30] = { 0, };

	// Dequeue를 할 때 문자들을 저장하는 문자열을 지정.
	int delq[20];

	int len; // 문자열 길이 구하기

	Queue cq;
	CreateQueue(&cq);

	int stoi;

	printf("20160499 한승조\n\n");

	while (TRUE) {

		printf(">>> ");
		gets(input);

		// 숫자가 아닌 문자열에 atoi() 함수를 사용하려고 하면 null 값이 return되는 것을 이용해 숫자와 문자구분.
		stoi = atoi(input);

		if (stoi) // 숫자를 받았을 때, 큐를 삭제하는 과정.
		{
			printf("%d\n", stoi);
			int del = 0;

			for (i = 0; i < stoi; i++) {

				if (!(IsEmpty(&cq))) {

					delq[del++] = QPeek(&cq); // 여기서 Dequeue를 하면 2칸씩 건너뛰게되므로 Peek만 하여 Dequeue할 문자만 저장.
					printf("DELETEQUEUE() = %c  Front = %d, Rear = %d\n", Dequeue(&cq), (&cq)->front, (&cq)->rear);
				}
				else
					printf("Fail : Queue Empty  Front = %d, Rear = %d\n \n", (&cq)->front, (&cq)->rear);
			}

			// Dequeue한 문자열만 따로 출력
			printf("RESULT = ");
			for (int i = 0; i < del; i++)
				printf("%c", delq[i]);
			printf("\n");

			// 큐에 남아있는 문자만 출력
			// front-rear가 경우에 따라 위치가 뒤바뀔 수 있으므로 경우를 나눠주어 출력
			printf("QUEUE = ");
			if ((&cq)->rear < (&cq)->front) { // front가 rear보다 클 경우 
				for (int i = (&cq)->front + 1; i < 20; i++)
					printf("%c", (&cq)->QueueArr[i]);
				for (int i = 0; i <= (&cq)->rear; i++)
					printf("%c", (&cq)->QueueArr[i]);
			}
			else { // rear가 front보다 큰 일반적으로 생각할 수 있는 경우
				for (int i = (&cq)->front + 1; i <= (&cq)->rear; i++)
					printf("%c", (&cq)->QueueArr[i]);
			}
			printf("\n");
		} // End of if(stoi)
		else // 문자를 받았을 때, 큐에 추가하는 과정.
		{

			len = 0; //입력 받은 문자열 길이를 저장할 변수.

			for (i = 0; i < 30; i++) {

				if (input[i] == 0)
					break;
				len++;
			}

			// 문자가 들어오면 큐에 추가.
			for (i = 0; i < len; i++) {

				if (!(NextPosIdx((&cq)->rear) == (&cq)->front)) {

					Enqueue(&cq, input[i]);

					printf("ADDQUEUE(%c)  Front = %d, Rear = %d\n", input[i], (&cq)->front, (&cq)->rear);
				}
				else
					printf("ADDQUEUE(%c), Fail : Queue Full  Front = %d, Rear = %d\n", input[i], (&cq)->front, (&cq)->rear);
			}

			// 큐에 남아있는 문자만 출력
			// front-rear가 경우에 따라 위치가 뒤바뀔 수 있으므로 경우를 나눠주어 출력
			printf("QUEUE = ");
			if ((&cq)->rear < (&cq)->front) { // front가 rear보다 클 경우 
				for (int i = (&cq)->front + 1; i < 20; i++)
					printf("%c", (&cq)->QueueArr[i]);
				for (int i = 0; i <= (&cq)->rear; i++)
					printf("%c", (&cq)->QueueArr[i]);
			}
			else { // rear가 front보다 큰 일반적으로 생각할 수 있는 경우
				for (int i = (&cq)->front + 1; i <= (&cq)->rear; i++)
					printf("%c", (&cq)->QueueArr[i]);
			}
			printf("\n");
		} //End of if(stoi)-else
	} // End of While(Ture)
}
