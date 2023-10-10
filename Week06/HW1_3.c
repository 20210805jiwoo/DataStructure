#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

//���� ó�� �Լ�
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

//��� pre �ڿ� ���ο� ��� ����
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

//pre�� ����Ű�� ����� ���� ��带 �����Ѵ�.
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
		// �������� ã�� ���� ���
		printf("������ %d�� �����ϰ� ���� �ʽ��ϴ�.\n", weight);
		return;
	}

	if (pre == NULL) {
		// ù ��° ��带 �����ϴ� ���
		*phead = delete_first(*phead);
	}
	else {
		// �߰��̳� �� ��带 �����ϴ� ���
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
	//���� ������ �ִ� �������� �� ���� ���
	int total_weight = 0;
	for (ListNode* p = *phead; p != NULL; p = p->link)
		total_weight += p->data;

	if (total_weight + new_item <= 100) {
		*phead = insert_first(*phead, new_item);
	}
	else {
		printf("�ִ� ���� <100kg> �ʰ��� ������ %d�� �߰��� �� ����\n", new_item);
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
			printf("�ùٸ� �Է��� �ƴϴ�.\n");
		}

	} while (choice != 'q');

	return 0;
}