#include "main.h"

std::string ver = "1.1";

void about() {
    printf("maker %s",ver.c_str());
std::cout << R"(Copyright (C) 2025  Gueder
This program comes with ABSOLUTUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions; 
License GPLv3+: GNU GPL version 3 or later 
<http://gnu.org/licenses/gpl.html> for details.
)";
}

void usage(){
    std::cout << R"(          
Usage: maker [actions] [options] [rule]

Tips: 
1. If the actions is make, config file DO NOT define default rule,
the rule is nessessary.

Actions:
    make         Make the project following the rule in maker.yml.

Options:
    -h           Show help.
    -v           Show version.
)";
}

inline void colored_out(const std::string& str, int color) {
	// Attention: Some systems may not support ANSI escape codes.
    std::cout << "\033[38;5;" << color << "m" << str;
    // Reset to default color
    std::cout << "\033[0m";
}

//inline void colored_out_extra(const std::string& str) {
    //Same in colored_out
//    std::cout << "\033[1;37m" << str;
//    std::cout << "\033[0m";
//}


/*Note:
Status 1: Info. Users can ignore it.
Status 2: Warning. Users need to attention.
Status 3: Error. Execution stop.
*/
void info_out(int tape) {
    if (tape == 1){
        colored_out("I:", 255); //Info, White
        printf("\n  ");
    }
    else if (tape == 2){
        colored_out("Warning at: ", 208); //Warning, Orange
    }
    else if (tape == 3){
        colored_out("Error at: ", 196); //Error, Red
    }
}
void command_out(int argc, char**& argv, int status, int tape) {
    info_out(status);
    /* Print command*/
    //Start
    printf("\n  ");
    if (tape == 1) {
        printf("User Command: ");
    }else if (tape == 2) {
        printf("Command: ");
    }
    printf("\n    ");
    for (int i = 0; i < argc; i++) {
        printf(" %s", argv[i]);
    }
    printf("\n");
    //End
}