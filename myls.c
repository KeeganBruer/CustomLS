#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include "linked_list.h"



void getFlags(int *flags, char **dirString, int argc, char**argv) {
    if (argc > 1) { //if program is run with arguments.
        int dirI = -1, i; //set an initial argument index to take in directory as second argument.
        for (i = 1; i < argc; i++) { //check every argument to check for flags.
            if (strstr(argv[i], "-") != NULL) { //if argument is a flag
                if (strstr(argv[i], "l") != NULL) {//check if flag contains l.
                    *flags |= 0x1; //flip first bit
                }
                if (strstr(argv[i], "a") != NULL) {
                    *flags |= 0x2; //flip second bit
                }
            } else {
                dirI = i;
            }
        }
        printf("%i %x\n",dirI, *flags); //debug print to show flag as hex
        if (dirI > 0) {
            *dirString = argv[dirI];//get search directory from arguments
        }
    }
}
int main(int argc, char**argv){
    int maxStringSize = 30;
    char *dirString = ".";
    int flags = 0x0;
    getFlags(&flags, &dirString, argc, argv);
    
    if ((flags & 0x1) == 0x1) {
        maxStringSize = 50;
    }

    linked_list* ll = create_linked_list(); //create a new linked list.
    struct stat statbuf;
    DIR *d; //irectory pointer.
    struct dirent *dir; //sub directory pointer.
    d = opendir(dirString); //open the directory found from arguments.
    if (d)//if the directory is opened
    {
        while ((dir = readdir(d)) != NULL) //while there are still directories to be read.
        {
            if ((dir->d_name[0] != '.') || ((flags & 0x2) == 0x2)) {

            char *buffer = (char*)malloc(maxStringSize * sizeof(char));
            int i = 0;
            if ((flags & 0x1) == 0x1) {
                buffer[i++] = '-';
                stat(dir->d_name, &statbuf);
                if (statbuf.st_mode & R_OK) {
                    buffer[i++] = 'r';
                } else {
                    buffer[i++] = '-';
                }
                if (statbuf.st_mode & W_OK) {
                    buffer[i++] = 'w';
                } else {
                    buffer[i++] = '-';
                }
                if (statbuf.st_mode & X_OK) {
                    buffer[i++] = 'x';
                } else {
                    buffer[i++] = '-';
                }

                buffer[i++] = ' ';
	        struct passwd *pw = getpwuid(statbuf.st_uid);
		for (int j = 0; j < strlen(pw->pw_name); j++)
                    buffer[i++] = pw->pw_name[j];
                buffer[i++] = ' ';
                struct group  *gr = getgrgid(statbuf.st_gid);
                for (int j = 0; j < strlen(gr->gr_name); j++)
                    buffer[i++] = gr->gr_name[j];
                buffer[i++] = ' ';
                char sizeT[10];
                sprintf(sizeT, "%7ld", statbuf.st_size);
                for (int j = 0; j < strlen(sizeT); j++)
                    buffer[i++] = sizeT[j];
                buffer[i++] = ' '; 
            }
            //for (i=0; i < ) {
                //buffer[i];
            //}
            int offset = i;
            for (; (dir->d_name[i-offset] != 0) && (i < maxStringSize); i++) {
                buffer[i] = dir->d_name[i-offset];
            }
            for (; i < maxStringSize; i++) {
                buffer[i] = ' ';
            }
            linked_list_add(ll, buffer); //add the directory to the linked list.
            }
        }
        closedir(d);//close the opened directory.
    }
    linked_list_sort(ll);//sort the linked list (Made in the linked_list.c for reusability).
    Node *n;//Node used for printing.
    for (int i = 0; i < ll->size; i++) { //for every node in the sub-directories linked list
        n = linked_list_get(ll, i);
        printf("%s", n->value); //print the sub-directory name format in 25 spaces left aligned.
        if ((flags & 0x1) == 0x1)
            printf("\n");
        else if ((i % 5) ==4 && i > 0)
            printf("\n");
    }
    printf("\n");
    free_list(ll);//free the linked list.
    return(0);
}
