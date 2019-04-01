//
// Created by slarsar on 3/9/19.
//
//created ttreebuffer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tkPort.h>
#include "ttreebuffer.h"

void parseinput(char *string){
    char * delim;
    delim = " ";

    copy_string = malloc(250*sizeof(char));
    memset(copy_string,0,250* sizeof(char));
    char * token;
    token = NULL;
    memset(par1,0,50*sizeof(char));
    memset(par2,0,50*sizeof(char));
    memset(par3,0,50*sizeof(char));
    memset(par4,0,50*sizeof(char));
    memset(par5,0,50*sizeof(char));


    strcpy(copy_string,string);
//    printf("copystring is %s\n ",copy_string);
//    printf("string  is %s   \n",string);
    token = strtok(copy_string,delim);
    if (token != NULL){
//        printf(" token1 is %s\n",token);
        strcpy(par1,token);
    }
    token = strtok(NULL,delim);
    if (token != NULL){
//        printf(" token2 is %s \n",token);
        strcpy(par2,token);
    }
    token = strtok(NULL,delim);
    if (token != NULL){
//        printf("token3 is %s\n",token);
        strcpy(par3,token);
    }
    token = strtok(NULL,delim);
    if (token != NULL){
//        printf(" token2 is %s \n",token);
        strcpy(par4,token);
    }
    token = strtok(NULL,delim);
    if (token != NULL){
//        printf("token3 is %s\n",token);
        strcpy(par5,token);
    }






    free(copy_string);
}

void parse_file(char * string){
    char * buf;
    char * delim;

    delim = NULL;
    delim = ",";
    char * token;
    token = NULL;

    buf = malloc(1000*sizeof(char));
    memset(buf,0, 1000*sizeof(char));

    if (!parf0){
        parf0 =malloc(500*sizeof(char));
    }
    memset(parf0,0, 500*sizeof(char));
    if (!parf1){
        parf1 =malloc(500*sizeof(char));
    }
    memset(parf1,0, 500*sizeof(char));
    strcpy(buf, string);

    strcpy(parf1 , strstr(buf,delim));

    token = strtok(buf, delim);
    if(token != NULL) {
        strcpy(parf0, token);
    }

    int fori = 0;
    for (fori = 0;fori < strlen(parf1) - 2;fori++){
        parf1[fori] = parf1[fori + 2];
    }
    parf1[fori -2] = '\0';
//    printf("parf0 = %s,parf1 = %s\n",parf0,parf1);
    free(buf);
}

void parse_json_file(char * json_file_string){
    json_file = cJSON_Parse(json_file_string);
    get1 = cJSON_GetObjectItem(json_file,"objects");
//    num_get1 = (int *)malloc(sizeof(cJSON_GetArraySize(get1)));
//    printf("%s",cJSON_Print(get1));

//    get2 = cJSON_GetArrayItem(get1,array_index);
//
//    get3 = cJSON_GetObjectItem(get2,);
//

}