#include "main.h"

int execute_command(const std::string& command) {
    infoout(1);
    printf("Executing command: %s\n", command.c_str());
#ifdef _WIN32
    FILE* pipe = _popen(command.c_str(), "r");
#else
    FILE* pipe = popen(command.c_str(), "r");
#endif
    if (!pipe) {
        infoout(3);
        printf("Try to popen. Failed. Stop.\n");
        return -1;
    }
 
    try {
        // read output
        char buffer[128];
        std::string result;
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            std::cout << buffer;  // print result
            result += buffer;
        }
    } catch (...) {
#ifdef _WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
        infoout(3);
        printf("Error during command execution. Stop.\n");
        return -2;
    }
 
    // get status
#ifdef _WIN32
    int return_code = _pclose(pipe);
#else
    int return_code = pclose(pipe);
#endif
    if (return_code == -1) {
        infoout(3);
        printf("Try to pclose. Failed. Stop.\n");
        return -3;
    }

    if (return_code == 0) {
        return 0;
    }
    else {
        infoout(3);
        printf("Command execute error with code %d. Stop.\n", return_code);
        return return_code;
    }
}

int execute(std::vector<std::string> task, int depth) {
    if (depth > 30){
        infoout(3);
        printf("Too deep recursion. Stop.\n");
        return -4;
    }
    for (int i = 0; i < task.size(); i++) {
        std::string target = command_paser(task[i]);
        if(target == "123" && !target.empty()){ 
            printf("%d\n",i);
            infoout(1);
            printf("Executing direct command.\n");
            int res = execute_command(task[i]);
            if (res != 0){
                return res;
            }
        }
        else{
            infoout(1);
            printf("Executing sub-target: %s\n", target.c_str());
            std::vector<std::string> sub_task = get_task(target);
            int res = execute(sub_task);
            if (res != 0){
                return res;
            }
        }
    }
    return 0; //default return
}