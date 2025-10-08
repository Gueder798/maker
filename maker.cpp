#include "include/main.h"
// #define DEBUG //Define it when release Pre-Release

int main(int argc,char *argv) {

	/*Config Part*/

	YAML::Node config;
	std::vector<std::string> commands; //List for storage commands
	std::string command; //Single command in commands
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
	commands = paser(config,argv);
	if (size(commands) == 0) {
		printf("Error found in config file. All the tasks stop.\n");
		return -2;
	}
	printf("Done!!!");
	if (test == true && exemption == true) {
		pass = true;
	}
	/* Execute Part*/

	for (int i = 0; i < size(commands); i++) {
		std::string ret = execute(command,pass);
		if (ret.empty() == 0) {
			printf("Error found in execute. All the tasks stop.\n");
			return -3;
		}
		printf(ret.c_str()); //From std::string to char*
	}
	return 0;
}