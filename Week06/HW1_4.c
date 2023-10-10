#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

/*
void print_list(ListNode* head) // Ʋ��: �����غ��ô�
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("%d->", p->data); // ������ ��� ���
	printf("\n");
}
*/

//����Ʈ�� ó�� ������ ������ ��µǰ� �϶�.
//����Ʈ�� ���� ǥ���ϵ��� �϶�.��: 10->20->30->����Ʈ�� ��
void print_list(ListNode* head)
{
	ListNode* p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("����Ʈ�� ��\n");
}

//����Ʈ�� ������ ��带 �����ϰ� ����带 ��ȯ�Ѵ�.
//����Ʈ�� ��������� ������Ʈ�� ����־� ������ ���ԡ��̶� ����Ѵ�.
ListNode* delete_last(ListNode* head)
{
	if (head == NULL) {
		printf("����Ʈ�� ����־� ������ ����\n");
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

//����Ʈ�� ���̸� ��ȯ�Ѵ�. 
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

//data �� ������ �ִ� ù��° ��带 ã�Ƽ� ��ȯ�Ѵ�
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
	return head; // ����� ��� �����͸� ��ȯ�Ѵ�. 
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
	return head; // ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head == head->link) {
		//�� �ϳ��� ��尡 ��������
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

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�

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
	
	printf("����Ʈ�� ����: %d\n", get_size(head));

	ListNode* searchResult = search(head, 30);
	if (searchResult != NULL)
		printf("ã�� ��: %d\n", searchResult->data);
	else
		printf("ã�� ���� ����\n");

	head = delete_last(head);
	print_list(head);

	return 0;
}
