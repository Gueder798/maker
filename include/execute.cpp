#include "main.h"

/* The define of popen and pclose are in main.h */
std::string execute(const std::string cmd,bool pass) {
    //pass asked to confirm if is debug
    char* val;
    
    /* Security Check Part*/

#ifdef WIN32
    if (cmd.find("rm") | cmd.find("rd") && pass == false) {
        printf("The command %s need to delete file.", cmd.c_str());
        printf("Please type y to confirm:");
        scanf_s("%s",&val);
        if (val != "y") {
            printf("Abort. Stop.\n");
            return "";
        }
    }
#else __LINUX__
    if (cmd.find("rm")) && pass == false) {
        printf("The command %s need to delete file.", cmd.c_str());
        printf("Please type y to confirm:");
        scanf("%s", &val);
        if (val != "y") {
            printf("Abort. Stop.\n");
            return "";
        }
    }
#endif
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r"); //Read command output, use r
    if (!pipe) {
        printf("Command excute failed. Stop.\n");
        return;
    }
    try {
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
    }
    catch (...) {
        pclose(pipe);
        printf("Command execute failed. Stop.\n");
        return "";
    }
    pclose(pipe);
    return result;
}