#include "main.h"

std::string ver = "0.1";

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

inline void coloredout(const std::string& str, int color) {
	// Attention: Some systems may not support ANSI escape codes.
    std::cout << "\033[38;5;" << color << "m" << str;
    // Reset to default color
    std::cout << "\033[0m";
}


/*Note:
Status 1: Info. Users can ignore it.
Status 2: Warning. Users need to attention.
Status 3: Error. Execution stop.
*/
void infoout(int tape) {
    if (tape == 1){
        coloredout("I:", 46); //Info, Green
    }
    else if (tape == 2){
        coloredout("W:", 208); //Warning, Orange
    }
    else if (tape == 3){
        coloredout("E:", 196); //Error, Red
    }
}