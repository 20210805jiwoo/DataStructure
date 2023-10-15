#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct {
    int num;
    char str[20];
} Element;

typedef struct StackNode {
    Element data;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s)
{
    s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
    return (s->top == NULL);
}

int is_full(LinkedStackType* s)
{
    return 0; // 링크드 리스트에서는 크기 제한이 없으므로 항상 false
}

void push(LinkedStackType* s, Element item)
{
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

void print_stack(LinkedStackType* s)
{
    if (is_empty(s)) {
        printf("<empty>\n");
    }
    else {
        printf("[%d, %s] <- top\n", s->top->data.num, s->top->data.str);
        for (StackNode* p = s->top->link; p != NULL; p = p->link)
            printf("[%d, %s]\n", p->data.num, p->data.str);
    }
    printf("--\n");
}

void pop(LinkedStackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else {
        StackNode* temp = s->top;
        s->top = s->top->link;
        free(temp);
    }
}

Element peek(LinkedStackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else {
        return s->top->data;
    }
}

int main(void)
{
    LinkedStackType s;
    init(&s);

    print_stack(&s);

    Element e1 = { 10, "ten" };
    push(&s, e1);
    print_stack(&s);

    Element e2 = { 20, "twenty" };
    push(&s, e2);
    print_stack(&s);

    Element e3 = { 30, "thirty" };
    push(&s, e3);
    print_stack(&s);

    Element e4 = { 40, "forty" };
    push(&s, e4);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    Element e5 = { 50, "fifty" };
    push(&s, e5);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    return 0;
}
