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

// 리스트의 끝에 새로운 라인을 추가하는 함수
void addLine(ListNode** head, const element* newElement) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->data.line, newElement->line);
    newNode->link = NULL;

    if (*head == NULL) {
        // 리스트 비어 있는 경우
        *head = newNode;
    }
    else {
        // 리스트의 끝까지 이동해 새 노드 추가
        ListNode* current = *head;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = newNode;
    }
}

// 리스트의 지정된 위치에 새로운 라인 삽입
void insertLine(ListNode** head, int position, const element* newElement) {
    if (position < 1) {
        fprintf(stderr, "삽입 위치 올바르지 않다.\n");
        return;
    }

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->data.line, newElement->line);
    newNode->link = NULL;

    if (position == 1) {
        // 처음에 삽입
        newNode->link = *head;
        *head = newNode;
    }
    else {
        // 지정된 위치에 삽입
        ListNode* current = *head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->link;
        }

        if (current == NULL) {
            fprintf(stderr, "삽입 위치 올바르지 않다.\n");
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
        fprintf(stderr, "리스트가 비어 있다.삭제할 수 없다.\n");
        return;
    }

    if (position < 1) {
        fprintf(stderr, "삭제 위치 올바르지 않다.\n");
        return;
    }

    ListNode* temp = NULL;

    if (position == 1) {
        // 첫 번째 노드 삭제
        temp = *head;
        *head = (*head)->link;
    }
    else {
        // 지정된 위치에서 삭제
        ListNode* current = *head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->link;
        }

        if (current == NULL || current->link == NULL) {
            fprintf(stderr, "삭제 위치 올바르지 않다.\n");
            return;
        }

        temp = current->link;
        current->link = temp->link;
    }

    free(temp);
}


// 리스트의 지정된 위치에서 라인 출력
void viewLine(ListNode* head, int position) {
    if (head == NULL) {
        fprintf(stderr, "리스트가 비어 있다.삭제할 수 없다.\n");
        return;
    }

    if (position < 1) {
        fprintf(stderr, "출력 위치 올바르지 않다.\n");
        return;
    }

    ListNode* current = head;

    for (int i = 1; i < position && current != NULL; i++) {
        current = current->link;
    }

    if (current == NULL) {
        fprintf(stderr, "출력 위치 올바르지 않다.\n");
    }
    else {
        printf("(%d) %s", position, current->data.line);
    }
}

// 리스트에 할당된 메모리 해제
void freeList(ListNode* head) {
    ListNode* current = head;
    ListNode* next = NULL;

    while (current != NULL) {
        next = current->link;
        free(current);
        current = next;
    }
}

// 리스트 전체 상태 출력
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
    printf("a: 텍스트 끝에 라인 추가\n");
    printf("i: 라인 번호로 라인 추가\n");
    printf("d: 라인 번호로 라인 삭제\n");
    printf("v: 라인 번호로 해당 라인 출력\n");
    printf("p: 전체 텍스트 출력\n");
    printf("q: 끝\n");
    printf("메뉴 선택:");
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
            printf("텍스트 끝에 삽입할 라인: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
            addLine(&list, &newElement);
            printf("----------text edited---------\n");
            display_te(list);
            break;
        case 'i':
            printf("삽입할 라인 번호: ");
            scanf("%d", &lineNb);
            printf("삽입할 라인: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
            insertLine(&list, lineNb, &newElement);
            printf("----------text edited---------\n");
            display_te(list);
            break;
        case 'd':
            printf("삭제할 라인 번호: ");
            scanf("%d", &lineNb);
            deleteLine(&list, lineNb);
            printf("----------text edited---------\n");
            display_te(list);
            break;
        case 'v':
            printf("출력할 라인 번호: ");
            scanf("%d", &lineNb);
            viewLine(list, lineNb);
            break;
        case 'p':
            printf("----------text edited---------\n");
            display_te(list);
            break;
        default:
            printf("올바르지 않은 메뉴입니다. 다시 선택해주세요.\n");
        }

        if (choice != 'a' && choice != 'i')
            while (getchar() != '\n');
    }

    freeList(list);

    return 0;
}