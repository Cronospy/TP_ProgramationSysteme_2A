// Un commentaire
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 128


int main(int argc, char *argv[]) {
    // Message de bienvenue
    const char* welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.";
    const int len_welcome_msg = strlen(welcome_msg);
    write(STDOUT_FILENO, welcome_msg, len_welcome_msg);

    const char* prefix = "\nenseash % ";
    const int len_prefix = strlen(prefix);

    char buffer[BUFFER_SIZE];

    while (1){
        //prefix
        write(STDOUT_FILENO, prefix, len_prefix);

        //read
        int n = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        buffer[n-1] = '\0';
        // recopiage
        write(STDOUT_FILENO, buffer, n);
    }

    return 0;
}
