#include "main.h"

int execute_command(const std::string& command) {
    info_out(1);
    printf("Executing command: %s\n", command.c_str());
#ifdef _WIN32
    FILE* pipe = _popen(command.c_str(), "r");
#else
    FILE* pipe = popen(command.c_str(), "r");
#endif
    if (!pipe) {
        info_out(3);
        printf("System problem.\n");
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
        info_out(3);
        printf("System problem.\n");
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
        info_out(3);
        printf("System problem.\n");
        printf("Try to pclose. Failed. Stop.\n");
        return -3;
    }

    if (return_code == 0) {
        return 0;
    }
    else {
        
        return return_code;
    }
}

int execute(const std::vector<std::string>& task, std::string target, int depth) {
    if (depth > 30){
        info_out(3);
        printf("Too deep recursion. Stop.\n");
        return -4;
    }
    for (int i = 0; i < task.size(); i++) {
        std::string pass = command_paser(task[i]);
        if(pass == "123" && !target.empty()){ 
			/* Direct command execute */
            int res = execute_command(task[i]);
            if (res != 0){
                info_out(3);
                printf("\n  In task '%s':",target.c_str());
                printf("\n    Command:");
                printf("\n        %s\n", task[i].c_str());
                printf("Command execute error with code %d. Stop.\n", res);
                return 1;
            }
        }
        else{
            /* Sub-task execute */
            info_out(1);
            printf("Executing sub-task: %s\n", target.c_str());
            std::vector<std::string> sub_task = get_task(target);
            int res = execute(sub_task, target);
            if (res != 0){
                return res;
            }
        }
    }
    return 0; //default return
}