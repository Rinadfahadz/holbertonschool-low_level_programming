#include "main.h"

/**
 * main - check the _islower function
 *
 * Return: Always 0
 */
int main(void)
{
    int r;

    r = _islower('H');  /* حرف كبير */
    _putchar(r + '0');
    r = _islower('o');  /* حرف صغير */
    _putchar(r + '0');
    r = _islower(108);  /* حرف صغير بالرقم ASCII */
    _putchar(r + '0');
    _putchar('\n');

    return (0);
}
