#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h> 
//compile with -lreadline -lhistory

int main() {
    char *line;

    while ((line = readline("(readline) $ ")) != NULL) {
        printf("You entered: %s\n", line);
        add_history(line); // Add the input to history
        free(line); // Free the allocated memory
    }

    return 0;
}

/*int main()
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("Enter a line: ");
	read = getline(&line, &len, stdin);
	if (read != -1) {
    	printf("You entered: %s", line);
	}
	free(line);
}*/