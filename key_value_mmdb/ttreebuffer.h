//
// Created by vory on 3/9/19.
//

#ifndef __TTREEBUFFER_H__
#define __TTREEBUFFER_H__

#include <cjson/cJSON.h>


int token1;

char * parf0;
char * parf1;

void parseinput(char *string);
void parse_file(char *string);
char * json_file_string;
void parse_json_file(char * json_file_string);

enum tables{
    KEYVALUE = 0,
    JSON
};
enum commands{
    FIND=0,
    INSERT,
    DELETE,
    PRINT,
    SELECT

};


enum commands COMMANDS;
enum tables TABLES;

char * file_line;
char * copy_string;

char * par1;
char * par2;
char * par3;
char * par4;
char * par5;
long int * insertkey;

long int json_file_length ;

cJSON *json_file ;

cJSON *get1 ;
cJSON *get2 ;
cJSON *get3id ;
cJSON *get3jobtitile;
cJSON *get3email;
cJSON *get3name;

int *num_get1 ;

cJSON *num1 ;
cJSON *jobtitle1 ;
cJSON *email1 ;
cJSON *name1 ;

cJSON *new_array1;
int array_index ;
char * object_string ;

#endif //__TTREEBUFFER_H__
