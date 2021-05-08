#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 10000

typedef struct TreeNode {
	char name[11];
	char phone[12];
	int id;

	struct TreeNode* left, * right;
} TreeNode;

void insert_node(TreeNode** root, int key, char* name, char* phone)
{
	TreeNode* p, * t; // p는 부모노드, t는 현재노드 
	TreeNode* n;	 // n은 새로운 노드
	t = *root;
	p = NULL;
	// 탐색을 먼저 수행 
	while (t != NULL) {
		if (key == t->id) return;
		p = t;
		if (key < t->id) t = t->left;
		else t = t->right;
	}
	// key가 트리 안에 없으므로 삽입 가능
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	// 데이터 복사
	n->id = key;
	strcpy(n->name, name);
	strcpy(n->phone, phone);
	n->left = n->right = NULL;
	// 부모 노드와 링크 연결
	if (p != NULL)
		if (key < p->id)
			p->left = n;
		else p->right = n;
	else *root = n;
}

void inorder(TreeNode** root, int* check)
{
	TreeNode* t = *root;

	if (t != NULL) {
		inorder(&(t->left), check);
		if (*check < t->id)
			*check = t->id;

		else
			*check = t->id;

		inorder(&(t->right), check);
	}
}

// 반복적인 탐색 함수
TreeNode* search(TreeNode* node, int key)
{
	while (node != NULL) {
		if (key == node->id) return node;
		else if (key < node->id)
			node = node->left;
		else
			node = node->right;
	}
	return NULL; 	// 탐색에 실패했을 경우 NULL 반환
}


void main()
{
	int i = 0, j = 0, k = 0;
	int phone1, phone2;
	int	idnum1, idnum2;
	int year;

	int saveID[100];

	char name[11], phone[12];
	int id;

	TreeNode* n = NULL;
	int check = 0;

	while (i < DATASIZE)
	{
		for (j = 0; j < 10; j++) {
			name[j] = rand() % 26 + 'A';
		} name[j] = 0;

		phone1 = rand() % 10000;
		phone2 = rand() % 10000;
		sprintf(phone, "010-%04d-%04d", phone1, phone2);

		year = rand() % 7 + 2013;
		idnum1 = rand() % 100;
		idnum2 = rand() % 100;
		id = year * 10000 + idnum1 * 100 + idnum2;

		insert_node(&n, id, name, phone);

		if (i >= (DATASIZE - 10000)) {
			saveID[k++] = id;
		}

		i++;
	}

	// 중위 순회
	inorder(&n, &check);

	TreeNode* d = NULL;
	TreeNode* p = NULL;


	// 데이터 검색
	TreeNode* s = NULL;


	for (i = 0; i < 1000; i++) {
		s = search(n, saveID[i]);
		printf("%d. %d %s\n", i + 1, s->id, s->name);
	}


	// 랜덤한 학번으로 검색


	int number;

	while (1) {

		for (int i = 0; i < 100; i++) {

			year = rand() % 7 + 2013;
			idnum1 = rand() % 100;
			idnum2 = rand() % 100;
			id = year * 10000 + idnum1 * 100 + idnum2;

		}


		printf("순번을 입력하세요 > ");
		scanf("%d", &number);

		d = search(n, saveID[number]);
		p = search(n, phone);

		printf("%d. %d %c %d", number, d->id, d->name, p->phone);

	} // End of while(1)

}
