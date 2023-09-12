#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void print_reverse(char* str, int end)
{
	if (end < 0)
		return;	//���ڿ� �� �����ϸ� ����

	putchar(str[end]);	//������ ���� ���
	print_reverse(str, end - 1);	//������ �κ� ���� ���
}

int main()
{
	char str[100];

	printf("Enter any string:");
	scanf("%s", str);

	printf("Reversed String is: ");
	print_reverse(str, strlen(str) - 1);
	return 0;
}