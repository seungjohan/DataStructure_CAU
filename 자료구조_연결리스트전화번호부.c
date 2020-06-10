/*

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
	char name[11];
	char phone[14];

	struct ListNode* link;
} ListNode;

// phead: 리스트의 헤드 포인터의 포인터
// p : 선행 노드
// new_node : 삽입될 노드 
void insert_node(ListNode** phead, ListNode* p, ListNode* new_node)
{
	if (*phead == NULL) {	// 공백리스트인 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p가 NULL이면 첫번째 노드로 삽입
		new_node->link = *phead;
		*phead = new_node;
	}
	else {			 // p 다음에 삽입
		new_node->link = p->link;
		p->link = new_node;
	}
}

// phead : 헤드 포인터에 대한 포인터 
// p: 삭제될 노드의 선행 노드
// removed: 삭제될 노드 
void remove_node(ListNode** phead, ListNode* p, ListNode* removed)
{
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;
	free(removed);
}



void main()
{
	// 처음 실행하면 10명분의 데이터는 랜덤하게 생성하여 추가한다.
	ListNode* head = NULL;
	ListNode* before = (ListNode*)malloc(sizeof(ListNode));

	int i = 0, j = 0;
	int phone1, phone2;

	while (i < 10) {
		ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));

		insert_node(&head, before, new_node);

		for (j = 0; j < 10; j++) {
			new_node->name[j] = rand() % 26 + 'A';
		} new_node->name[j] = 0;

		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(new_node->phone, "010-%04d-%04d", phone1, phone2);

		before = new_node;
		i++;
	}

	ListNode* p = head;
	int count = 10;
	char name[11];
	char phone[14];

	char part1[10], part2[10], * token;

	while (1) {

		printf("(%d명의 데이터가 있습니다)\n", count);
		printf(">> ");
		gets(name);

		// 삭제 기능 사용을 대비하여, token을 사용하여 "삭제" 문자열과 삭제할 이름 문자열을 구분짓도록 한다.
		token = strtok(name, " ");
		strcpy(part1, token);
		if (!strcmp(part1, "삭제")) {
			token = strtok(NULL, " ");
			strcpy(part2, token);
		}

		p = head;

		// 목록 보기
		if (!strcmp(name, "목록")) {
			i = 0;

			while (p != NULL) {
				printf("%d. %s %s\n", ++i, p->name, p->phone);
				p = p->link;
			}
			printf("\n");
		}
		// 삭제하기
		else if (!strcmp(part1, "삭제")) {
			while (p != NULL) {
				if (!strcmp(p->name, part2)) {
					printf("%s %s 가 삭제되었습니다\n", p->name, p->phone);

					if (p == head) remove_node(&head, NULL, p);
					else remove_node(&head, before, p);

					count--;
					break;
				}
				before = p;
				p = p->link;

			}

		}
		// 정렬하기
		// 임시 노드 변수 두 개를 생성하여, 정렬 시 연결 리스트가 끊어지는 상황이 없도록 한다.
		else if (!strcmp(name, "정렬")) {
			ListNode* cur = (ListNode*)malloc(sizeof(ListNode));

			ListNode* tmp1 = (ListNode*)malloc(sizeof(ListNode));
			ListNode* tmp2 = (ListNode*)malloc(sizeof(ListNode));

			for (i = count - 1; i > 0; i--) {
				cur = head;
				for (j = 0; j < i; j++) {
					if (strcmp(cur->name, cur->link->name) == 1) {
						if (j == 0) {
							tmp1 = cur;
							tmp2 = cur->link->link;

							cur = cur->link;
							cur->link = tmp1;
							cur->link->link = tmp2;
							head = cur; // 중요!!!!
						}
						else if (j == count - 2) {
							tmp1 = cur;
							before->link = cur->link;
							before->link->link = tmp1;
							cur = before->link;
							cur->link->link = NULL;
						}
						else {
							tmp1 = cur;
							tmp2 = cur->link->link;

							before->link = cur->link;
							before->link->link = tmp1;
							cur = before->link;
							cur->link->link = tmp2;
						}
					}
					before = cur;
					cur = cur->link;
				}
			}
		}
		else {
			// 이름으로 찾기
			while (p != NULL) {
				if (!strcmp(p->name, name)) {
					printf("(찾았습니다) %s\n", p->phone);
					break;
				}
				p = p->link;
			}

			// 없으면 추가하기
			if (p == NULL) {
				printf("(존재하지 않는 이름입니다. 전화번호를 입력하세요)\n");
				printf("전화번호 >>> ");
				gets(phone);
				printf("(%s %s 가 입력되었습니다)\n", name, phone);

				// p는 NULL이므로 데이터가 실행 예와 같이 리스트의 처음에 추가된다.
				ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
				insert_node(&head, p, new_node);
				strcpy(new_node->name, name);
				strcpy(new_node->phone, phone);
				count++;
			}
		}
	}

	printf("20160499 한승조\n");
}
