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

    //the actual reading of the file and the battery life
    while((dp ==  readdir(d) != NULL)) {
        snprintf(b, PATH_MAX, "Opened dir: %s\n", strerror(errno));

        //define the regex to read the correct parts of the file otherwise
        //it will just print random crap that's not required
        regex_t regex;
        //esure that the data that we need is in there, otherwise it's pretty damn useless
        if(regcomp(&regex, "BAT[[:alnum:]]+", REG_EXTENDED) != 0) {
            fprintf(stderr, "Could not complete required regex: %s\n", sterror(errno));
            return 4;
        }

        //this is where things get messy
        if(regexec(&regex, b, 0, NULL, 0) == NULL) {
            snprintf(b, PATH_MAX, "%s%s%s", DATA_DIR, dp->d_name, "charge_now");
            fc = fopen(b, "r");
            snprintf(b, PATH_MAX, "%s%s%s", DATA_DIR, dp->d_name, "charge_full");
            ff = fopen(b, "r");
            if(fc != NULL && ff != NULL) {
                if(fscanf(fc, "%ld", &current) != 1 || fscanf(ff, "%ld", &full) != 1) {
                    fprintf(stderr, "Could not scan required fules: %s\n", sterror(errno));
                } else {
                    fprintf(stdout, "Current charge: %s %f\n", dp->d_name, (current / full) * 100.0);
                }
                //close the files now that we're done with them
                fclose(fc);
                fclose(ff);
            }   
        }

        //close the regex and free it from the memory block
        regfree(&regex);
    }
    return 0;
}