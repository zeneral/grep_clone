#include <stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "grep.c"


int main(int argc, char *argv[]){

    if(argc < 2)
        return 0;

    int opt, is_print = 0;
    uint8_t wc_flag = 0;
    uint8_t lc_flag = 0;
    const char * optstring = "w:l:";
    while((opt = getopt(argc, argv, optstring)) != -1){
        switch(opt){
            case 'w':
                wc_flag = 1;
                break;
            case 'l':
                lc_flag = 1;
                break;
            case ':':
                exit(1);
                break;
            case '?':
                exit(1);
                break;
            default:
                break;
        }
    }
    char *file_path = argv[argc - 1]; 
    char *pattern = argv[argc - 2];
    if(!wc_flag && !lc_flag) is_print = 1; 
    GRET g = grep(file_path, pattern, is_print);

    if(wc_flag){
        printf("%d  ",g.w_count);
    }

    if(lc_flag){
        printf("%d  ",g.w_count);
    }

    printf("\n");

   return 0;
}
