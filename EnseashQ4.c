// Un commentaire
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define PREFIXE_SIZE 256

static int build_prefix(char* prefix, int last_is_signal, int last_code, int last_sig){
    int pos = 0;
    
    pos += sprintf(prefix + pos, "\nenseash [");

    if (last_is_signal) {
        pos += sprintf(prefix + pos, "sign:%d", last_sig);
    } 
    else {
        pos += sprintf(prefix + pos, "exit:%d", last_code);
    }

    pos += sprintf(prefix + pos, "] %% ");
    return pos;
}

int main(int argc, char *argv[]) {
    // Message de bienvenue
    const char* welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.";
    const int len_welcome_msg = strlen(welcome_msg);
    write(STDOUT_FILENO, welcome_msg, len_welcome_msg);

    char* prefix_deb = "\nenseash % ";
    int len_prefix_deb = strlen(prefix_deb);

    int last_is_signal = 0;
    int last_code = 0;
    int last_sig  = 0;

    char buffer[BUFFER_SIZE];

    while (1){
        //prefix
        char prefix[PREFIXE_SIZE];
        int len_prefix = build_prefix(prefix,last_is_signal,last_code,last_sig);
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
        // Lancement un programme 
        else if (strcmp(buffer, "un_programme") == 0){
            int pid, statuts;
            pid = fork();

            if(pid!=0){
                wait(&statuts);
                if (WIFEXITED(statuts)) {
                    last_is_signal = 0;
                    last_code = WEXITSTATUS(statuts);
                } 
                else if (WIFSIGNALED(statuts)) {
                    last_is_signal = 1;
                    last_sig = WTERMSIG(statuts);
                }
            }
            else{
                execlp("./un_programme","./un_programme",(char*)NULL);
            }
        }
        // Lancement un autre programme 
        else if (strcmp(buffer, "un_autre_programme") == 0){
            int pid, statuts;
            pid = fork();
            
            char pid_buffer[32];
            int len_pid_buffer = sprintf(pid_buffer,"pid :+%d+",pid);
            write(STDOUT_FILENO, pid_buffer, len_pid_buffer);

            if(pid!=0){
                wait(&statuts);
                if (WIFEXITED(statuts)) {
                    last_is_signal = 0;
                    last_code = WEXITSTATUS(statuts);
                } 
                else if (WIFSIGNALED(statuts)) {
                    last_is_signal = 1;
                    last_sig = WTERMSIG(statuts);
                }
            }
            else{
                execlp("./un_autre_programme","./un_autre_programme",(char*)NULL);
            }
        }
        // recopiage
        else {
            int pid, statuts;
            pid = fork();

            if (pid!=0){
                wait(&statuts);
            }
            else {
                execlp(buffer,buffer,(char*)NULL);
            }
        }
    }

    return 0;
}
