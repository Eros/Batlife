#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<dirent.h>
#include<linux/limits.h>
#include<regex.h>

//this code will be reading the data from a file that linux provides for us
#define DATA_DIR "sys/class/power_supply"

int main(int argc, char **argv) {

    //file reading and general setup of the code
    FILE *fc, *ff;
    DIR *d;
    struct dirent *dp;
    long current, full;
    char b[PATH_MAX];

    //ensure that the directory actually exists, it should seeing as
    //it's one that is provided by Linux lol
    if((d = opendir(DATA_DIR)) == NULL) {
        fprintf(stderr, "Could not open dir: %s\n", sterror(errno));
        return 3;
    }
    return 0;
}