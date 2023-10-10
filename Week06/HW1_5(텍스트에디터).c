#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 100

typedef struct {
    char line[MAX_CHAR_PER_LINE];
} element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// ����Ʈ�� ���� ���ο� ������ �߰��ϴ� �Լ�
void addLine(ListNode** head, const element* newElement) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->data.line, newElement->line);
    newNode->link = NULL;

    if (*head == NULL) {
        // ����Ʈ ��� �ִ� ���
        *head = newNode;
    }
    else {
        // ����Ʈ�� ������ �̵��� �� ��� �߰�
        ListNode* current = *head;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = newNode;
    }
}

// ����Ʈ�� ������ ��ġ�� ���ο� ���� ����
void insertLine(ListNode** head, int position, const element* newElement) {
    if (position < 1) {
        fprintf(stderr, "���� ��ġ �ùٸ��� �ʴ�.\n");
        return;
    }

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->data.line, newElement->line);
    newNode->link = NULL;

    if (position == 1) {
        // ó���� ����
        newNode->link = *head;
        *head = newNode;
    }
    else {
        // ������ ��ġ�� ����
        ListNode* current = *head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->link;
        }

        if (current == NULL) {
            fprintf(stderr, "���� ��ġ �ùٸ��� �ʴ�.\n");
            free(newNode);
            return;
        }

        newNode->link = current->link;
        current->link = newNode;
    }
}

// Function to delete a line at a specified position in the list
void deleteLine(ListNode** head, int position) {
    if (*head == NULL) {
        fprintf(stderr, "����Ʈ�� ��� �ִ�.������ �� ����.\n");
        return;
    }

    if (position < 1) {
        fprintf(stderr, "���� ��ġ �ùٸ��� �ʴ�.\n");
        return;
    }

    ListNode* temp = NULL;

    if (position == 1) {
        // ù ��° ��� ����
        temp = *head;
        *head = (*head)->link;
    }
    else {
        // ������ ��ġ���� ����
        ListNode* current = *head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->link;
        }

        if (current == NULL || current->link == NULL) {
            fprintf(stderr, "���� ��ġ �ùٸ��� �ʴ�.\n");
            return;
        }

        temp = current->link;
        current->link = temp->link;
    }

    free(temp);
}


// ����Ʈ�� ������ ��ġ���� ���� ���
void viewLine(ListNode* head, int position) {
    if (head == NULL) {
        fprintf(stderr, "����Ʈ�� ��� �ִ�.������ �� ����.\n");
        return;
    }

    if (position < 1) {
        fprintf(stderr, "��� ��ġ �ùٸ��� �ʴ�.\n");
        return;
    }

    ListNode* current = head;

    for (int i = 1; i < position && current != NULL; i++) {
        current = current->link;
    }

    if (current == NULL) {
        fprintf(stderr, "��� ��ġ �ùٸ��� �ʴ�.\n");
    }
    else {
        printf("(%d) %s", position, current->data.line);
    }
}

// ����Ʈ�� �Ҵ�� �޸� ����
void freeList(ListNode* head) {
    ListNode* current = head;
    ListNode* next = NULL;

    while (current != NULL) {
        next = current->link;
        free(current);
        current = next;
    }
}

// ����Ʈ ��ü ���� ���
void display_te(ListNode* head)
{
    int lineNum = 1;
    ListNode* current = head;
    while (current != NULL) {
        printf("(%d) %s", lineNum, current->data.line);
        current = current->link;
        lineNum++;
    }
}

char askChoice(void)
{
    char choice;
    printf("------------------------------\n");
    printf("a: �ؽ�Ʈ ���� ���� �߰�\n");
    printf("i: ���� ��ȣ�� ���� �߰�\n");
    printf("d: ���� ��ȣ�� ���� ����\n");
    printf("v: ���� ��ȣ�� �ش� ���� ���\n");
    printf("p: ��ü �ؽ�Ʈ ���\n");
    printf("q: ��\n");
    printf("�޴� ����:");
    scanf(" %c", &choice);  
    return choice;
}

int main(void) {
    ListNode* list = NULL;
    char choice;
    int lineNb;
    element newElement;

    while ((choice = askChoice()) != 'q') {
        switch (choice) {
        case 'a':
            printf("�ؽ�Ʈ ���� ������ ����: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
            addLine(&list, &newElement);
            printf("----------text edited---------\n");
            display_te(list);
            break;
        case 'i':
            printf("������ ���� ��ȣ: ");
            scanf("%d", &lineNb);
            printf("������ ����: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
            insertLine(&list, lineNb, &newElement);
            printf("----------text edited---------\n");
            display_te(list);
            break;
        case 'd':
            printf("������ ���� ��ȣ: ");
            scanf("%d", &lineNb);
            deleteLine(&list, lineNb);
            printf("----------text edited---------\n");
            display_te(list);
            break;
        case 'v':
            printf("����� ���� ��ȣ: ");
            scanf("%d", &lineNb);
            viewLine(list, lineNb);
            break;
        case 'p':
            printf("----------text edited---------\n");
            display_te(list);
            break;
        default:
            printf("�ùٸ��� ���� �޴��Դϴ�. �ٽ� �������ּ���.\n");
        }

        if (choice != 'a' && choice != 'i')
            while (getchar() != '\n');
    }

    freeList(list);

    return 0;
}