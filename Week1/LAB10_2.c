#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
	char name[20];
	int midterm;
	int final;
} Student;

int main(void)
{
	Student* sp;	//����ü ������ ����
	sp = malloc(sizeof(Student));	//�����Ҵ�

	if (sp == NULL)
		return 1;	//�޸� �Ҵ� ���� �� ����

	printf("Enter student name: ");
	scanf("%s", sp->name); 
	printf("Enter midterm and final score: ");
	scanf("%d %d", &sp->midterm, &sp->final); 
	printf("\n�̸�\t�߰�\t�б⸻\n");
	printf("%s\t%d\t%d\n", sp->name, sp->midterm, sp->final); 

	free(sp);

	return 0;
}