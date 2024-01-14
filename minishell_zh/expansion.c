#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARGS 10
#define WHITESPACE " \t\r\n\v"

// Function to expand environment variables in a string
char* expand_environment_variables(const char* input) {
    char* result = malloc(strlen(input) + 1);
    char* result_ptr = result;
    const char* input_ptr = input;

    while (*input_ptr != '\0') {
        if (*input_ptr == '$' && *(input_ptr + 1) == '{') {
            // Found the start of an environment variable
            input_ptr += 2;
            const char* end_brace = strchr(input_ptr, '}');
            if (end_brace != NULL) {
                // Extract the variable name
                size_t var_length = end_brace - input_ptr;
                char var_name[var_length + 1];
                strncpy(var_name, input_ptr, var_length);
                var_name[var_length] = '\0';

                // Get the value of the environment variable
                char* var_value = getenv(var_name);
                if (var_value != NULL) {
                    // Replace the variable with its value
                    strcpy(result_ptr, var_value);
                    result_ptr += strlen(var_value);
                }

                input_ptr = end_brace + 1;  // Move to the character after '}'
            } else {
                // Malformed variable reference, ignore and continue
                *result_ptr = *input_ptr;
                result_ptr++;
                input_ptr++;
            }
        } else {
            // Copy normal characters
            *result_ptr = *input_ptr;
            result_ptr++;
            input_ptr++;
        }
    }

    *result_ptr = '\0';
    return result;
}

// Example usage in your get_cmd function:
int get_cmd(char *buf, int nbuf) {
    char *input;
    // ...

    if (isatty(0))
        input = readline("minishell> ");
    else
        input = readline("");

    if (input == NULL || strlen(input) == 0) {
        if (input != NULL)
            free(input);
        return (-1);
    }

    char* expanded_input = expand_environment_variables(input);
    strcpy(buf, expanded_input);
    free(expanded_input);

    // Rest of your code...
}

