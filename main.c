#include "battery.h"
#include<stdbool.h>

bool is_linux;

#ifdef _WIN32
is_linux = false;
#endif

#ifdef LINUX 
is_linux = true;
#endif

#ifdef DARWIN 
is_linux = false;
#endif

int main(int argc, char **argv) {
    if(!is_linux) {
        fprintf("[X] You cannot run this program on windows!", "");
        exit(0);
    } else {
        while(true) {
            display_battery();
            sleep(30);
        }
    }
    return 0;
}