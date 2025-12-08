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
    
        //exit 
        if (strcmp(buffer, "exit") == 0){
            const char* exit_msg = "Bye bye...\n";
            const int len_exit_msg = strlen(exit_msg);
            write(STDOUT_FILENO, exit_msg, len_exit_msg);
            return 0;
        }
        else if (n == 0){
            const char* exit_msg = "\nBye bye...\n";
            const int len_exit_msg = strlen(exit_msg);
            write(STDOUT_FILENO, exit_msg, len_exit_msg);
            return 0;
        }
        // fortune
        else if (strcmp(buffer, "fortune") == 0){
            int pid, statuts;
            pid = fork();

            if (pid!=0){
                wait(&statuts);
            }
            else {
                execlp("fortune","fortune",(char*)NULL);
            }
        }
        // date
        else if (strcmp(buffer, "date") == 0){
            int pid, statuts;
            pid = fork();

            if (pid!=0){
                wait(&statuts);
            }
            else {
                execlp("date","date",(char*)NULL);
            }
        }
        // recopiage
        else {
            write(STDOUT_FILENO, buffer, n);
        }
    }

    return 0;
}
