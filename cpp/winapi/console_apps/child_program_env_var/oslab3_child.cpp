#include <process.h>
#include <stdlib.h>
#include <iostream>

void printVariable(const char name[]) {
	char* soughtValue = nullptr;
	size_t size = 0;
	if (_dupenv_s(&soughtValue, &size, name) == 0 && soughtValue != nullptr) {
		printf("\n%s=%s", name, soughtValue);
		free(soughtValue);
	} else {
		printf("\n%s not found", name);
	}
}

int main(int argc, char* argv[], char* envp[])
{
	printf("\n[!] BEGIN of oslab3_child\n");
	printf("[?] process pid: ");
	printf("%d", _getpid());
	printf("\n[?] with these %i command line arguments:", argc);
	for (int i = 0; i < argc; ++i) {
		printf("\n\"");
		printf(argv[i]);
		printf("\"");
	}
	printf("\n[?] checking three system environment variables:");
	printVariable("USERNAME");
	printVariable("COMPUTERNAME");
	printVariable("MYPATH");
	{
		printf("\n[?] checking local environment array of variables:");
		int i = 0;
		while (envp[i]) {
			printf("\n\"");
			printf(envp[i++]);
			printf("\"");
		}
		if (i == 0) {
			printf("\n[?] EMPTY");
		}
	}
	printf("\n[!] enter any character >>");
	system("pause>>void");
	printf("\n[!] oslab3_child END\n");
	return 0;
}