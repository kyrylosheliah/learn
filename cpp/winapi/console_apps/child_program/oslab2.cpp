/* перший файл - батько */
#include <stdio.h>
#include <process.h>
#include <stdlib.h>
int main(void)
{
	_execl("test.exe", "test.exe", "hello", "10", NULL);
	system("pause>>void");
	return 0;
}