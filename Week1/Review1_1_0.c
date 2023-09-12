#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void print_reverse(char* str, int end)
{
	if (end < 0)
		return;	//문자열 끝 도달하면 종료

	putchar(str[end]);	//마지막 문자 출력
	print_reverse(str, end - 1);	//나머지 부분 역순 출력
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