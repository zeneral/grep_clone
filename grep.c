#include <stdint.h>
#include <stdio.h>
#include <magic.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#define RED "\x1b[31m"
#define C_RESET "\x1b[0m"

typedef struct {
    int w_count;
    int l_count;
} GRET;

uint8_t find_file_type(const char *file_path,  char *t){
   magic_t m = magic_open(MAGIC_MIME_TYPE);
   uint8_t ok = 0;
    magic_load(m, NULL); // Load the default magic number database

    const char* file = file_path; // Example file name
    const char* type = magic_file(m, file);

    if (type) {
        strcpy(t, type);
        ok = 1;
    } else {
        printf("An error occurred: %s\n", magic_error(m));
    }

    magic_close(m);
    return ok;
}


GRET grep(const char* file_path, const char *string_pattern, uint8_t is_print){
    GRET g = {
        .l_count = 0,
        .w_count = 0
    };
    char file_type[10];
    regex_t regex;
    regmatch_t matched_position[2] = {0}; // stores postion of matched string or word
    if((regcomp(&regex, string_pattern, 0))){
        printf("Compilation error");
        return g;
    }
   if(!find_file_type(file_path, file_type)) return g; // checking either file is in text format or not
    
   if(strstr(file_type, "text") != NULL){
        FILE *file = fopen(file_path, "read"); // opening file in read only mode
        size_t bufsize = 100;
        char * line = NULL;
        if(file != NULL){
            int is_found;
            int offset;
            while(getline(&line, &bufsize, file) != -1){
                is_found = false;
                offset = 0;
                int value = regexec(&regex, line + offset, 1, matched_position, 0);
                if(!value){
                    is_found = true;
                    g.l_count++; // counting line in which word appeard
                }
                while(value == 0){
                    g.w_count++; // conting when pattern is found
                    offset += matched_position[0].rm_eo;
                    if(is_print){
                     printf("%.*s", matched_position[0].rm_so, line);
                     printf(RED);
                     printf("%.*s",
                             matched_position[0].rm_eo - matched_position[0].rm_so,
                             &line[matched_position[0].rm_so]);
                     printf(C_RESET);
                    } 
                    value = regexec(&regex, line + offset, 1, matched_position, 0);
                }
                if(is_found && is_print) printf("%s",line + offset);
            }
        }
        free(line);
        fclose(file);
   }
   regfree(&regex);
   return g;
}


