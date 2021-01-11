#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


int main( int argc, char *argv[] ) {
    FILE *fp;
    char output[65535];
    char command[65535];
    int i;

    // try setuid
    if ( ( setuid(0) ) != 0 ) {
      perror ("error on setuid");
    }

    for(i = 1; i < argc; i++) {
       strcat(strcat(command, argv[i]), " ");
    }

    // open the command for reading
    fp = popen( command, "r");
    if (fp == NULL) {
        printf("failed to run command\n");
        exit(1);
    }

    // read the output a line at a time - output it
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    pclose(fp);
    return 0;
}

