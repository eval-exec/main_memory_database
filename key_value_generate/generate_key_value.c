#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
int main(){
    FILE * fp;

    fp = fopen("/home/vory/programing/c/c_test_1/data_chaos.del","w+");
    char * string = "abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int len = (int)strlen(string);
    int count = 1;
    time_t t;
    srand((unsigned) time(&t));
    char * des_string = (char*)malloc(50);
    do {


        memset(des_string, 0, 50);
        for (int i = 0; i < 50; i++) {
            des_string[i] = string[rand() % (len-1)];
        }
        des_string[49] = '\0';



        char result[20];
        long int longint = 0;
        longint = rand()% LONG_MAX;

        sprintf(result,"%ld",longint);
        fprintf(fp,result);
        fprintf(fp,",\"");
        fprintf(fp, des_string);
        fprintf(fp,"\"");
        fprintf(fp, "\n");

        count++;
    }while (count < 10000000);



fclose(fp);
    return 0;
}




