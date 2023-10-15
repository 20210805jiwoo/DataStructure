#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

/*
void print_list(ListNode* head) // 틀림: 수정해봅시다
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("%d->", p->data); // 마지막 노드 출력
	printf("\n");
}
*/

//리스트의 처음 노드부터 끝까지 출력되게 하라.
//리스트의 끝을 표시하도록 하라.예: 10->20->30->리스트의 끝
void print_list(ListNode* head)
{
	ListNode* p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("리스트의 끝\n");
}

//리스트의 마지막 노드를 삭제하고 헤드노드를 반환한다.
//리스트가 비어있으면 “리스트가 비어있어 삭제를 못함”이라 출력한다.
ListNode* delete_last(ListNode* head)
{
	if (head == NULL) {
		printf("리스트가 비어있어 삭제를 못함\n");
		return NULL;
	}
	if (head->link == head) {
		free(head);
		return NULL;
	}

	ListNode* temp = head->link;
	ListNode* prev = NULL;

	while (temp->link != head) {
		prev = temp;
		temp = temp->link;
	}

	prev->link = head;
	free(temp);

	return head;
}

//리스트의 길이를 반환한다. 
int get_size(ListNode* head)
{
	if (head == NULL) return 0;

	int cnt = 0;
	ListNode* p = head->link;

	do {
		cnt++;
		p = p->link;
	} while (p != head);

	return cnt;
}

//data 를 가지고 있는 첫번째 노드를 찾아서 반환한다
ListNode* search(ListNode* head, element data)
{
	if (head == NULL) return NULL;

	ListNode* p = head->link;
	do {
		if (p->data == data)
			return p;
		p = p->link;
	} while (p != head);

	return NULL;
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; // (1)
		head->link = node; // (2)
	}
	return head; // 변경된 헤드 포인터를 반환한다. 
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; // (1)
		head->link = node; // (2)
		head = node; // (3)
	}
	return head; // 변경된 헤드 포인터를 반환한다. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}
	else if (head == head->link) {
		//즉 하나의 노드가 남았을때
		temp = head;
		head = NULL;
		free(temp);
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;
}

// 원형 연결 리스트 테스트 프로그램

int main(void)
{
	ListNode* head = NULL;
	// list = 10->20->30->40
	head = insert_last(head, 20);
	print_list(head);
	head = insert_last(head, 30);
	print_list(head);
	head = insert_last(head, 40);
	print_list(head);
	head = insert_first(head, 10);
	print_list(head);
	head = delete_first(head);
	print_list(head);
	
	printf("리스트의 길이: %d\n", get_size(head));

	ListNode* searchResult = search(head, 30);
	if (searchResult != NULL)
		printf("찾은 값: %d\n", searchResult->data);
	else
		printf("찾는 값이 없음\n");

	head = delete_last(head);
	print_list(head);

	return 0;
}
