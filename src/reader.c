#include "reader.h"
#include <stdlib.h>
#include <stdio.h>
long find_file_size(char* file_name){
    FILE* file = fopen(file_name, "r");
    if (file == NULL) return  -1;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

char* read_as_string(char* file_name){
    unsigned long long file_size = find_file_size(file_name);
    FILE* file = fopen(file_name,"r");
    if (file == NULL){
        printf("FILE NOT DEFINED\n");
        return  NULL;
    }
    
    char* str = malloc(file_size + 1);
    int c;
    int n = 0;
    while((c = fgetc(file)) != EOF){
        str[n++] = (char)c;
    }
    str[n] = '\0';
    fclose(file);
    return str;
}