#include "battery.h"
#include<stdbool.h>

bool windows;

#ifdef _WIN32
windows = true;
#endif

#ifdef LINUX 
windows = false;
#endif

int main(int argc, char **argv) {
    if(windows) {
        fprintf("[X] You cannot run this program on windows!");
        exit(0);
    } else {
        while(true) {
            display_battery();
            sleep(30);
        }
    }
    return 0;
}