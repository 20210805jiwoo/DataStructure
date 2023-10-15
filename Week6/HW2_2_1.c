#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef int element;
typedef struct StackNode {
    element data;
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
    return 0;
}

void push(LinkedStackType* s, element item)
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
        printf("%d <- top\n", s->top->data);
        for (StackNode* p = s->top->link; p != NULL; p = p->link)
            printf("%d\n", p->data);
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

element peek(LinkedStackType* s)
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

    push(&s, 10);
    print_stack(&s);

    push(&s, 20);
    print_stack(&s);

    push(&s, 30);
    print_stack(&s);

    push(&s, 40);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    push(&s, 50);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    pop(&s);
    print_stack(&s);

    return 0;
}