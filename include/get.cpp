#include "main.h"

YAML::Node yml_paser() {
#ifdef DEBUG // Note: test.yml won't be checked in future.
    const std::vector<std::string> files = { "maker.yml", "Maker.yml", "maker.yaml", "Maker.yaml", "test.yml" };
#else
    const std::vector<std::string> files = { "maker.yml", "Maker.yml", "maker.yaml", "Maker.yaml" };
#endif
    YAML::Node config;

    for (const auto& filename : files) {
        try {
            config = YAML::LoadFile(filename);
            break;
        }
        catch (const YAML::BadFile&) {}
    }

    if (!config) {
        infoout(3);
        printf("Configuration files not found. Stop.\n");
        return YAML::Node();
    }

    YAML::Node tasks = config["tasks"];
    if (!tasks) {
        infoout(3);
        printf("'tasks' key not found in configuration. Stop.\n");
        return YAML::Node();
    }

    // Check if default in tasks
    if (!tasks["default"]) {
        infoout(2);
        printf("No 'default' task found. Continuing execution.\n");
    }

    return tasks;
}

std::string command_paser(std::string command) {
    infoout(1);
    printf("Parsing command: %s\n", command.c_str());
    std::string target;
    if (command.find("tasks.") != std::string::npos) {
        target = command.substr(6, command.length());
        return target;
    }
    return "123";
}

#include <string>

std::string cleaner(const std::string& input) {
    size_t newline_pos = input.find('\n');
    
    // If a newline is found, return the substring up to that position
    if (newline_pos != std::string::npos) {
        return input.substr(0, newline_pos);
    }
    // If no newline is found, return the entire string
    return input;
}

std::vector<std::string> get_task(std::string target) {
    infoout(1);
    printf("Getting tasks for target: %s\n", target.c_str());
    YAML::Node tasks;
    tasks = yml_paser();

    if (!tasks) {
        return std::vector<std::string>();
    }
    // Note: Because the var target always has some unknown char, need to clean.
    std::string cleaned_target = cleaner(target);
    std::vector<std::string> task;

    if (!tasks.IsMap()){
        infoout(3);
        printf("Invalid tasks format in configuration. Stop.\n");
        return task;
    }
    if (tasks[cleaned_target].IsNull()) {
        infoout(3);
        printf("Unkown target. Stop.\n");
        return task;
    }
    
    YAML::Node list = tasks[cleaned_target];

    for (int i = 0; i < list.size(); i++) {
        infoout(1);
        printf("Adding task: %s\n", list[i].as<std::string>().c_str());
        task.push_back(list[i].as<std::string>());
    }
    return task;
}