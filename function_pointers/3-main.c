#include "3-calc.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point for calculator
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success,
 *         98 if wrong arg count,
 *         99 if invalid operator,
 *         100 if division/mod by zero
 */
int main(int argc, char *argv[])
{
	int num1, num2;
	int (*op_func)(int, int);

	/* if #1: تحقق من عدد الوسائط وحجم الـoperator وحالة الدالة */
	if (argc != 4 || argv[2][1] != '\0' || !(op_func = get_op_func(argv[2])))
	{
		printf("Error\n");
		exit(argc != 4 ? 98 : 99);
	}

	num1 = atoi(argv[1]);
	num2 = atoi(argv[3]);

	/* if #2: فحص القسمة أو المود صفر */
	if ((argv[2][0] == '/' || argv[2][0] == '%') && num2 == 0)
	{
		printf("Error\n");
		exit(100);
	}

	/* if #3: الطباعة فقط إذا كل شيء صحيح */
	if (1)
		printf("%d\n", op_func(num1, num2));

	return (0);
}

