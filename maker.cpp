/* Maker Gueder798
This is under GNU GPLv3+ license.
The file is the main function.*/

/*  If you cannot find a function, you can see
include directory for more details.

Note: 
1.If one function is used to get, look for get.cpp.
2.If one function is used to execute, look for execute.cpp.
3.If one function is used to show information, look for print.cpp.
*/

#include "include/main.h"

int main(int argc, char** argv) {

#ifdef DEBUG // Check if is debug mode
	infout(2);
	printf("You are using debug release.\n"); // Give a warning
#endif

	std::string target;

	//Colorful print will come out soon
	if (argc == 1) {
		infoout(3);
		printf("No actions input. Stop.\n");
		return -1;
	}
	else if (argc == 2) {
		if(strcmp(argv[1], "make") == 0) {
			infoout(2);
			printf("No actions input. Using default actions.\n");
			target = "default";
		}
		else if (strcmp(argv[1], "-v") == 0) {
			about();
			return 0;
		}
		else if (strcmp(argv[1], "-h") == 0) {
			usage();
			return 0;
		}
		else {
			printf("E:Unkown actions. Stop.\n");
			return -1;
		}
	}
	else if (argc == 3) {
		if (strcmp(argv[1], "make") == 0) {
			target = argv[2];
			printf("%s\n",argv[2]);
		}
		else if (strcmp(argv[1], "-h") == 0) {
			about();
			return 0;
		}
		else if (strcmp(argv[1], "-v") == 0) {
			usage();
			return 0;
		}
		else {
			printf("E:Unkown actions. Stop.\n");
			return -1;
		}
	}
	else {
		printf("E:Too many arguments. Stop.\n");
		return -1;
	}

	std::vector<std::string> list;

	list = get_task(target);
	int res = execute(list);

	if (res == 0) {
		infoout(1);
		printf("All tasks executed successfully.\n");
	}
	else if(res == -1 || res == -2 || res == -4){
		infoout(1);
		printf("Execution errors decteted.\n");
		return -1;
	}
	else if(res == -3){
		infoout(1);
		printf("Command execution failed.\n");
	}
	return 0;
}