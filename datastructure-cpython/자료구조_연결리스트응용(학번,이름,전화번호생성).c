#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATASIZE 10000

typedef struct ListNode
{
	char name[11];
	char phone[12];
	int id;

	struct ListNode* link_name;
	struct ListNode* link_id;
} ListNode;

void insert_node_name(ListNode** phead, ListNode* p, ListNode* new_node)
{
	if (*phead == NULL) {	// 공백리스트인 경우
		new_node->link_name = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p가 NULL이면 첫번째 노드로 삽입 (얜 필요없는듯)
		new_node->link_name = *phead;
		*phead = new_node;
	}
	else {			 // p 다음에 삽입
		new_node->link_name = p->link_name;
		p->link_name = new_node;
	}
}

void insert_node_id(ListNode** phead, ListNode* p, ListNode* new_node)
{
	if (*phead == NULL) {	// 공백리스트인 경우
		new_node->link_id = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p가 NULL이면 첫번째 노드로 삽입 (얜 필요없는듯)
		new_node->link_id = *phead;
		*phead = new_node;
	}
	else {			 // p 다음에 삽입
		new_node->link_id = p->link_id;
		p->link_id = new_node;
	}
}

void main()
{
	ListNode* head_name = NULL;
	ListNode* head_id = NULL;
	ListNode* before = (ListNode*)malloc(sizeof(ListNode));

	int i = 0, j = 0;
	int phone1, phone2;
	int	idnum1, idnum2;
	int year;

	char name[11], phone[12];
	int id;

	while (i < DATASIZE)
	{
		ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));

		for (j = 0; j < 10; j++) {
			name[j] = rand() % 26 + 'A';
		} name[j] = 0;

		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(phone, "010%04d%04d", phone1, phone2);

		year = rand() % 7 + 2013;
		idnum1 = rand() % 1000;
		idnum2 = rand() % 100;
		id = year * 100000 + idnum1 * 100 + idnum2;

		// 노드 생성, 데이터 추가, 이름으로 노드 연결은 insert_node_name() 함수를 통해 구현하였고,
		// 학번으로 노드 연결은 함수를 사용하지 않고 코드를 살짝 더 추가하여 구현했습니다.
		if (i == 0) {
			insert_node_name(&head_name, NULL, new_node);
			insert_node_id(&head_id, NULL, new_node);

			strcpy(new_node->name, name);
			strcpy(new_node->phone, phone);
			new_node->id = id;
		}
		else {
			ListNode* cur = head_name;
			before = NULL;

			while (cur != NULL)
			{
				if (strcmp(name, cur->name) == -1) {
					insert_node_name(&head_name, before, new_node);

					strcpy(new_node->name, name);
					strcpy(new_node->phone, phone);
					new_node->id = id;

					break;
				}
				else {
					before = cur;
					cur = cur->link_name;
				}
			}
			if (cur == NULL) {
				insert_node_name(&head_name, before, new_node);

				strcpy(new_node->name, name);
				strcpy(new_node->phone, phone);
				new_node->id = id;
			}

			cur = head_id;
			before = NULL;

			while (cur != NULL)
			{
				if (id < cur->id) {

					if (before == NULL) { // p가 NULL이면 첫번째 노드로 삽입 (얜 필요없는듯)
						new_node->link_id = head_id;
						head_id = new_node;
					}
					else {			 // p 다음에 삽입
						new_node->link_id = before->link_id;
						before->link_id = new_node;
					}

					break;
				}
				else {
					before = cur;
					cur = cur->link_id;
				}
			}
			if (cur == NULL) {
				new_node->link_id = before->link_id;
				before->link_id = new_node;
			}
		}
		i++;
	}

	int input;
	int count = 0;
	ListNode* cur = (ListNode*)malloc(sizeof(ListNode));

	while (1) {
		printf("(1) 학번순\n(2) 이름순\n메뉴 선택(0: 종료) : ");
		scanf("%d", &input);

		if (input == 1) {
			count = 0;
			cur = head_id;

			while (cur != NULL) {
				// 100개 씩 건너뛰며 출력.
				if (count % 100 == 0) printf("%d %s %s\n", cur->id, cur->name, cur->phone);

				cur = cur->link_id;

				count++;
			}
		}
		else if (input == 2) {
			count = 0;
			cur = head_name;

			while (cur != NULL) {
				// 100개 씩 건너뛰며 출력.
				if (count % 100 == 0) printf("%d %s %s\n", cur->id, cur->name, cur->phone);

				cur = cur->link_name;

				count++;
			}
		}
		else if (input == 0) {
			break;
		}
	}


	printf("20160499 한승조\n");
}
