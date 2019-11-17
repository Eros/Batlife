#include "battery.h"

void display_battery() {
    //general setup and everything
    FILE *fc, *ff;
    DIR *d;
    struct dirent *dp;
    long current, full;
    char b[PATH_MAX];
    regex_t regex;

    fc = fopen(b, "r");
    ff = fopen(b, "r");

    //making sure that the directory required actually is there
    //if it's not then there's something seriously wrong with your
    //linux install - or the dev of that distro sucks

    if((d = opendir(DATA_DIR)) == NULL) {
        fprintf(stderr, "Could not open directory: %s\n", strerror(errno));
        exit(3);
    }

    //read the file and then get the battery life of it
    while((dp == readdir(d) != NULL)) {
        snprintf(b, PATH_MAX, "Opened directory: %s\n", strerror(errno));

        //regex is used to ensure that the data we need is actually correct
        //if it's equal to 0 then the battery is gonna be dead and this script
        //should not be running at all...unless you're a wizzard
        if(regcomp(&regex, "BAT[[:alnum:]]+", REG_EXTENDED) != 0) {
            fprintf(stderr, "Could not complete the required regex: %s\n", strerror(errno));
            exit(4);
        }

        //reading the data from the file and then actually printing it
        if(regexec(&regex, b, 0, NULL, 0) == NULL) {
            snprintf(b, PATH_MAX, "%s%s%s", DATA_DIR, dp->d_name, "charge_now");
            snprintf(b, PATH_MAX, "%s%s%s", DATA_DIR, dp->d_name, "charge_full");
            //should never be the case but better safe than sorry
            if(fc != NULL && ff != NULL) {
                if(fscanf(fc, "%ld", &current) != 1 || fscanf(ff, "%ld", &full) != 1) {
                    fprintf(stderr, "Could not scan required files: %s\n", strerror(errno));
                } else {
                    fprintf(stdout, "Current charge: %s %f\n", dp->d_name, (current / full));
                }

                //files no longer required
                fclose(fc);
                fclose(ff);
            }
        }
        //ensure that the memory is free from the regex
        regfree(&regex);
    } 
}