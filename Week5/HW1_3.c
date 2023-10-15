#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

//오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

//노드 pre 뒤에 새로운 노드 삽입
/*
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}
*/

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

//pre가 가리키는 노드의 다음 노드를 삭제한다.
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

void delete_item(ListNode** phead, int weight)
{
	ListNode* pre = NULL;
	ListNode* current = *phead;
	while (current != NULL && current->data != weight) {
		pre = current;
		current = current->link;
	}

	if (current == NULL) {
		// 아이템을 찾지 못한 경우
		printf("아이템 %d는 보유하고 있지 않습니다.\n", weight);
		return;
	}

	if (pre == NULL) {
		// 첫 번째 노드를 삭제하는 경우
		*phead = delete_first(*phead);
	}
	else {
		// 중간이나 끝 노드를 삭제하는 경우
		pre->link = current->link;
		free(current);
	}
}

void display(ListNode* head)
{
	printf("< ");
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf(">\n");
}

void add_item(ListNode** phead, int new_item)
{
	//현재 가지고 있는 아이템의 총 무게 계산
	int total_weight = 0;
	for (ListNode* p = *phead; p != NULL; p = p->link)
		total_weight += p->data;

	if (total_weight + new_item <= 100) {
		*phead = insert_first(*phead, new_item);
	}
	else {
		printf("최대 무게 <100kg> 초과로 아이템 %d를 추가할 수 없음\n", new_item);
	}
	return *phead;
}

int main(void)
{
	ListNode* list = NULL;
	char choice;
	int weight;

	do {
		printf("enter a(dd). d(elete) or q(uit):");
		scanf(" %c", &choice);

		switch (choice) {
		case 'a':
			printf("enter the weight of the item:");
			scanf("%d", &weight);
			add_item(&list, weight);
			display(list);
			break;
		case 'd':
			printf("enter the weight of the item:");
			scanf("%d", &weight);
			delete_item(&list, weight);
			display(list);
			break;
		case 'q':
			break;
		default:
			printf("올바른 입력이 아니다.\n");
		}

	} while (choice != 'q');

	return 0;
}
