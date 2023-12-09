#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PATH_MAX 64

int ft_execvp(const char *file, char *const argv[])
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, ":");

    while (token != NULL) {
        size_t path_len = strlen(token);
        size_t file_len = strlen(file);
        
        if (path_len + file_len + 2 > PATH_MAX) {
            printf("Path length exceeds maximum allowed.\n");
            free(path_copy);
            return -1; // Return if path length exceeds the limit
        }
        char full_path[path_len + file_len + 2]; // +2 for '/' and null terminator
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, file);

        if (access(full_path, X_OK) == 0) {
            execve(full_path, argv, NULL);
            perror("execve failed");
            free(path_copy);
            return -1; // Return in case of failure
        }
        token = strtok(NULL, ":");
    }
    free(path_copy);
    printf("Command not found: %s\n", file);
    return -1; // Return if command not found
}

/*int main() {
    char *args[] = {"ls", "-l", NULL}; // Example arguments
    execute_simple("ls", args); // Example usage of my_execvp

    return 0;
}*/
