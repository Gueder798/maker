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