#include "battery.h"

#ifdef _WIN32
#define WIN_IN_USE true
#endif

#ifdef LINUX 
#define LIN_IN_USE true
#endif

int main(int argc, char **argv) {
    if(WIN_IN_USE) {
        fprintf("[X] You cannot run this program on windows!");
        exit(0);
    } else {
        while(true) {
            display_battery();
        }
    }
    return 0;
}