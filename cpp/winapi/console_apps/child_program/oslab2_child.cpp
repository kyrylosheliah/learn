#include <process.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char* argv[])
{
	printf("\n[!] BEGIN of oslab2_child\n");
	printf("[?] process pid: ");
	printf(" %d", _getpid());
	printf("\n[?] with these command line arguments: ");
	for (int i = 0; i < argc; ++i) {
		printf("\n\"");
		printf(argv[i]);
		printf("\"");
	}
	printf("\n[!] enter any character >>");
	system("pause>>void");
	printf("\n[!] oslab2_child END\n");
	return 0;
}