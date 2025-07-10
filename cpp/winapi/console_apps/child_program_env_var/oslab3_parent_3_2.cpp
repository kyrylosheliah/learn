#include <process.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char* argv[], char* envp[])
{
	const char* new_env[] = { "USERNAME=PARENT_2", "COMPUTERNAME=OS-LAB-3", "MYPATH=D:\\TEMP", NULL };
	const char child_string_path[] = "oslab3_child.exe";
	printf("\n[!] BEGIN of oslab3_parent_3_2\n");
	printf("[?] process pid: ");
	printf("%d", _getpid());
	printf("\n[?] passing envp** to ");
	printf(child_string_path);
	printf("\n");
	intptr_t code = _spawnle(P_WAIT, child_string_path, child_string_path, NULL, new_env);
	printf("\n[?] execution code:");
	printf(" %d", code);
	printf("\n[!] enter any character >>");
	system("pause>>void");
	printf("\n[!] oslab3_parent_3_2 END\n");
	return 0;
}