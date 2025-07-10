#include <process.h>
#include <stdlib.h>
#include <iostream>

void printVariable(const char name[]) {
	char* soughtValue = nullptr;
	size_t size = 0;
	if (_dupenv_s(&soughtValue, &size, name) == 0 && soughtValue != nullptr) {
		printf("\n%s=%s", name, soughtValue);
		free(soughtValue);
	}
	else {
		printf("\n%s not found", name);
	}
}

int main(int argc, char* argv[], char* envp[])
{
	const char child_string_path[] = "oslab3_child.exe";
	printf("\n[!] BEGIN of oslab3_parent_3_1\n");
	printf("[?] process pid: ");
	printf("%d", _getpid());
	printf("\n[?] setting variable \"MYPATH\" with value \"D:\\TEMP\"");
	_putenv_s("MYPATH", "D:\\TEMP");
	printVariable("MYPATH");
	printf("\n[?] passing envp** to ");
	printf(child_string_path);
	printf("\n");
	intptr_t code = _spawnl(P_WAIT, child_string_path, child_string_path, NULL);
	printf("\n[?] execution code:");
	printf(" %d", code);
	printf("\n[!] enter any character >>");
	system("pause>>void");
	printf("\n[!] oslab3_parent_3_1 END\n");
	return 0;
}