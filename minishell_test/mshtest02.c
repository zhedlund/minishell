#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

char *get_location(char *command){
    char *path, *path_copy, *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    path = getenv("PATH");
    if (path){
        /* Duplicate the path string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/ 
        path_copy = strdup(path);
        /* Get length of the command that was passed */
        command_length = strlen(command);
        /* Let's break down the path variable and get all the directories available*/
        path_token = strtok(path_copy, ":");

        while(path_token != NULL){
            /* Get the length of the directory*/
            directory_length = strlen(path_token);
            /* allocate memory for storing the command name together with the directory name */
            file_path = malloc(command_length + directory_length + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
            /* to build the path for the command, let's copy the directory path and concatenate the command to it */
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, command);
            strcat(file_path, "\0");

            /* let's test if this file path actually exists and return it if it does, otherwise try the next directory */
            if (stat(file_path, &buffer) == 0){
                /* return value of 0 means success implying that the file_path is valid*/

                /* free up allocated memory before returning your file_path */
                free(path_copy);
                return (file_path);
            }
            else{
                /* free up the file_path memory so we can check for another path*/
                free(file_path);
                path_token = strtok(NULL, ":");
            }
        }
        /* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for path_copy */ 
        free(path_copy);

        /* before we exit without luck, let's see if the command itself is a file_path that exists */
        if (stat(command, &buffer) == 0)
        {
            return (command);
        }
        return (NULL);
    }
    return (NULL);
}

void execmd(char **argv)
{
    char *command = NULL, *actual_command = NULL;

    if (argv){
        /* get the command */
        command = argv[0];

        /* generate the path to this command before passing it to execve */
        actual_command = get_location(command);

        /* execute the actual command with execve */
        if (execve(actual_command, argv, NULL) == -1){
            perror("Error:");
        }
    }
}

int main(int argc, char **argv)
{
    char *prompt = "(minishell) $ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    int num_tokens = 0;
    char *token;
    int i;

    // declaring void variables
    (void)argc;

    while (1) {
        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin);
        
        // Check for exit command or EOF
        if (nchars_read == -1 || (nchars_read == 5 && strncmp(lineptr, "exit\n", 5) == 0)) {
            printf("Exiting shell...\n");
           // break; // Break out of the loop
		   return (-1);
        }

        // allocate space for a copy of the lineptr
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL){
            perror("tsh: memory allocation error");
            return (-1);
        }

        // copy lineptr to lineptr_copy
        strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        // calculate the total number of tokens
        token = strtok(lineptr, " \n");

        while (token != NULL){
            num_tokens++;
            token = strtok(NULL, " \n");
        }
        num_tokens++;

        // Allocate space to hold the array of strings
        argv = malloc(sizeof(char *) * num_tokens);

        // Store each token in the argv array
        token = strtok(lineptr_copy, " \n");

        for (i = 0; token != NULL; i++){
            argv[i] = malloc(sizeof(char) * (strlen(token) + 1)); // Include space for null terminator
            strcpy(argv[i], token);
            token = strtok(NULL, " \n");
        }
        argv[i] = NULL;

        // Execute the command if argv is populated
        if (argv != NULL) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                execmd(argv);
                exit(EXIT_FAILURE); // If exec fails
            } else {
                // Parent process
                wait(NULL); // Wait for the child to finish
            }
        }

        // Free allocated memory for argv
        for (i = 0; i < num_tokens; i++) {
            free(argv[i]);
        }
        free(argv);

        // Free allocated memory for lineptr_copy
        free(lineptr_copy);
        num_tokens = 0; // Reset num_tokens for the next iteration
    }

    // Free allocated memory for lineptr and exit
    free(lineptr);
    return 0;
}
