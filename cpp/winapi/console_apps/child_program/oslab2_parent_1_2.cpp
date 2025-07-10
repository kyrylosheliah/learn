#include <process.h>
#include <stdlib.h>
#include <iostream>

#define __five_params argv[0],argv[1],argv[2],argv[3],argv[4]
#define __six_params argv[0],argv[1],argv[2],argv[3],argv[4],argv[5]
#define __seven_params argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]
#define __eight_params argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]
#define __nine_params argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8]
#define __ten_params argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],argv[9]

#define __spawnl_unfolding(child_path, child_string, _PARAMS_) { code = _spawnl(P_WAIT, child_path, child_string, _PARAMS_, NULL);};

int main(int argc, char* argv[])
{
	printf("\n[!] BEGIN of oslab2_parent_1_2\n");
	printf("[?] process pid: ");
	printf(" %d", _getpid());
	printf("\n[?] passing its own arguments to ");
	char child_string_path[] = "oslab2_child.exe";
	char child_string[] = "\"oslab2_child.exe\"";
	printf(child_string_path); printf("\n");
	intptr_t code;
	switch (argc) {
	case 5: __spawnl_unfolding(child_string_path, child_string, __five_params) break;
	case 6: __spawnl_unfolding(child_string_path, child_string, __six_params) break;
	case 7: __spawnl_unfolding(child_string_path, child_string, __seven_params) break;
	case 8: __spawnl_unfolding(child_string_path, child_string, __eight_params) break;
	case 9: __spawnl_unfolding(child_string_path, child_string, __nine_params) break;
	case 10: __spawnl_unfolding(child_string_path, child_string, __ten_params) break;
	default: __spawnl_unfolding(child_string_path, child_string, "\"There was <5 or >10 parameters\"")
	}
	printf("\n[?] execution code:");
	printf(" %d", code);
	printf("\n[!] enter any character >>");
	system("pause>>void");
	printf("\n[!] oslab2_parent_1_2 END\n");
	return 0;
}