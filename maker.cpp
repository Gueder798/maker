#include "include/main.h"
// #define DEBUG //Define it when release Pre-Release

int main(int argc,char *argv) {
	std::string target;
	if (argc == 1) {
		printf("No actions input. Stop.\n");
		return -1;
	}
	else if (argc == 2) {
		if (stricmp((char*)argv[1], "make") == 0) {
			printf("No target input.\n");
			target = "default";
		}
		else if (stricmp((char*)argv[1], "make") != 0) {
			printf("Unknown action. Stop.\n");
			return -1;
		}
	} 
	else if (argc == 3) {
		if (stricmp((char*)argv[1], "make") == 0) {
			target = argv[2];
		}
		else if (stricmp((char*)argv[1], "make") != 0) {
			printf("Unknown action. Stop.\n");
			return -1;
		}
	}

	/*Config Part*/

	YAML::Node config;
	bool flag = false; //Judge if loaded file
	bool exemption = false;
	bool pass = false;
#ifdef DEBUG
	const char list[5][15] = { "maker.yml", "maker.yaml", "Maker.yml", "Maker.yaml","test.yml" };
	const int len = 5;
	const bool test = true;
#else
	const char list[4][15] = { "maker.yml", "maker.yaml", "Maker.yml", "Maker.yaml" };
	const int len = 4;
	const bool test = false;
#endif

	/*Load Config File Part*/

	for (int i = 0; i < len; i++) {
		try {
			config = YAML::LoadFile(list[i]);
		}
		catch (...) {
			continue;
		}
		printf("Config file %s loaded.\n",list[i]);
		if (list[i] == "test.yml") { // Check if is exeption file
			bool exemption = true;
		}
		flag = true;
		break;
	}
	if (flag != true) {
		printf("No config file found. Stop.\n");
		return -1;
	}
	if (test == true && exemption == true) {
		pass = true;
	}
	make(config,target,pass);
}