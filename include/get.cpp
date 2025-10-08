#include "main.h"

std::vector<std::string> paser(YAML::Node config, const std::string& target) {
    try {
        YAML::Node tasks = config["tasks"];
        if (!config) {
            printf("Error syntax, root tasks not found. Stop.\n");
            return {};
        }
        if (!tasks[target]) {
            printf("Target not found. Stop.\n");
            return {};
        }
        YAML::Node targetNode = tasks[target];
        std::vector<std::string> result;

        if (targetNode.IsSequence()) { //Is a list
            for (auto&& node : targetNode) {
                result.push_back(node.as<std::string>());
            }
        }
        else if (targetNode.IsScalar()) { //Is a constant
            result.push_back(targetNode.as<std::string>());
        }
        return result;
    }
    catch (...) {
        return {};
    }
}
int make(YAML::Node config,std::string target,bool pass) {
    std::vector<std::string> commands; //List for storage commands
    std::string command; //Single command in commands
    commands = paser(config, target);
    if (size(commands) == 0) {
        printf("Error found in config file. All the tasks stop.\n");
        return -2;
    }
    printf("Done!!!");
    
    for (int i = 0; i < size(commands); i++) {
        command = commands[i];
        if (command.find("tasks.")) {
            std::string result;
            size_t pos = command.find("tasks.");
            if (pos != std::string::npos) {
                result = command.substr(pos + target.length());
            }
            else return -1;
            make(config, result);
        }
        std::string ret = execute(command, pass);
        if (ret.empty() == 0) {
            printf("Error found in execute. All the tasks stop.\n");
            return -3;
        }
        printf(ret.c_str()); //From std::string to char*
    }
    return 0;
}