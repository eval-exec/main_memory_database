#include <stdio.h>
#include <stdlib.h>
#include "ttree.h"
#include "ttreebuffer.h"
#include "uthash.h"
#include "hash_table.h"
#include <time.h>
#include <errno.h>

struct hash_struct *test1_users;

struct hash_struct *s;

struct item_keyvalue {
    long int key;
    char *value;
};

struct item_json {
    long int key;
    char *jobtitle;
    char *email;
    char *firstlastname;
};


static int __cmpfunc(void *key1, void *key2) {
    return (*(int *) key1 - *(int *) key2);
}

static void usage(const char *appname) {
    fprintf(stderr, "Usage: %s <positive number of keys>\n", appname);
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]) {
    clock_t start, finish;
    double totol_time;

    int bcount = 0;

    int num_keys, i, ret;
    Ttree ttree;
    Ttree ttree_keyvalue;

    TtreeNode *tnode;
    TtreeNode *tnode_keyvalue;
    struct item_keyvalue *all_items, *cur_item;
    struct item_json *json_items, *json_items_insert;

//    num_keys = 12278;
    num_keys = 9999999;

    FILE *fp;
    fp = NULL;

    int tables_select = 0;

    char *buf;
    par1 = malloc(50 * sizeof(char));
    memset(par1, 0, 50 * sizeof(char));
    par2 = malloc(50 * sizeof(char));
    memset(par2, 0, 50 * sizeof(char));
    par3 = malloc(50 * sizeof(char));
    memset(par3, 0, 50 * sizeof(char));
    par4 = malloc(50 * sizeof(char));
    memset(par4, 0, 50 * sizeof(char));
    par5 = malloc(50 * sizeof(char));
    memset(par5, 0, 50 * sizeof(char));

    all_items = calloc(5 * num_keys, sizeof(all_items));
    int json_nums = 1000;
    int json_nums_max = 1000;


    json_items = calloc(5 * json_nums, sizeof(json_items));
    json_items_insert = calloc(5, sizeof(struct item_json));

    file_line = malloc(1000 * sizeof(char));
    memset(file_line, 0, 1000 * sizeof(char));

    parf0 = malloc(500 * sizeof(char));
    memset(parf0, 0, 500 * sizeof(char));

    parf1 = malloc(500 * sizeof(char));
    memset(parf1, 0, 500 * sizeof(char));

    char * inputline;

    inputline = (char *) malloc(150 * sizeof(char));
    memset(inputline, 0, 150 * sizeof(char));


    int find_par2;
    int insert_par2_key;
    int insert_count = 0;
    int delete_par2_key;
/////////////////////////////////////////////////////////////////
    printf("PLEASE INPUT HERE:");
    do {
        fgets(inputline, 100, stdin);
        parseinput(inputline);
        if (!strncmp(par1, "EXIT", 4)) break;
        char *out_buff;
        out_buff = malloc(1000);
        memset(out_buff, 0, 1000);

        void *res;
        if (strncmp(par1, "FIND", 4) == 0) {
            if (tables_select == 0) {
                printf("Please select tables,(KEYVALUE or JSON)\n");
                continue;
            }
            printf("receive FIND \n");
            COMMANDS = FIND;
            if (par2 == NULL) {
                printf("FIND WHAT? \n");
                continue;
            }
        } else if (strncmp(par1, "INSERT", 6) == 0) {
            if (tables_select == 0) {
                printf("Please select tables,(KEYVALUE or JSON)\n");
                continue;
            }
            printf("receive INSERT\n");
            COMMANDS = INSERT;
        } else if (strncmp(par1, "DELETE", 6) == 0) {
            if (tables_select == 0) {
                printf("Please select tables,(KEYVALUE or JSON)\n");
                continue;
            }
            printf("receive DELETE \n");
            COMMANDS = DELETE;
        } else if (strncmp(par1, "PRINT", 5) == 0) {
            if (tables_select == 0) {
                printf("Please select tables,(KEYVALUE or JSON)\n");
                continue;
            }
            printf("receive PRINT \n");
            COMMANDS = PRINT;
        } else if (strncmp(par1, "SELECT", 6) == 0) {

            printf("receive SELECT \n");
            COMMANDS = SELECT;
            tables_select = 1;
        } else {
            if (tables_select == 0) {
                printf("Please select tables,(KEYVALUE or JSON)\n");
                continue;
            }
            printf("%s is not allowed", par1);
            continue;
        }

        switch (COMMANDS) {
            case SELECT:
                if (strncmp(par2, "KEYVALUE", 7) == 0) {
                    TABLES = KEYVALUE;
                    start = clock();
//                    fp = fopen("/home/vory/programing/c/key_value_mmdb/xlarge.del", "r");

//                    fp = fopen("/home/vory/programing/c/mmdb_A/key_value_mmdb/data.del", "r");
                    fp = fopen("/home/vory/programing/c/mmdb_A/key_value_mmdb/data_chaos_1000W.del", "r");
                    if (fp == NULL) {
                        printf("fp null ");
                        return 0;
                    }

                    ret = ttree_init(&ttree_keyvalue, 8, false, __cmpfunc, struct item_keyvalue, key);
                    if (ret < 0) {
                        fprintf(stderr, "Failed to initialize T*-tree. [ERR=%d]\n", ret);
                        free(all_items);
                        exit(EXIT_FAILURE);
                    }

//                    printf("file line = %s",);

                    while (bcount < 9999999) {
                        fgets(file_line, 1000, fp);
                        parse_file(file_line);
                        all_items[bcount].key = strtol(parf0, NULL, 10);
                        all_items[bcount].value = malloc(500 * sizeof(char));
                        memset(all_items[bcount].value, 0, 500);
//                        printf("parf1 = %s\n", parf1);

                        strcpy(all_items[bcount].value, parf1);

//                        printf("key =%ld, value = %s\n",  all_items[bcount].key, all_items[bcount].value);
                        bcount++;
                        memset(file_line, 0, 1000 * sizeof(char));
                    }
                    free(file_line);

                    for (i = 0; i < num_keys; i++) {
                        ret = ttree_insert(&ttree_keyvalue, &all_items[i]);
                        //printf("aaaInserting keys to the tree...\n");

                        if (ret < 0) {
                            fprintf(stderr, "Failed to insert item %d with key %ld! [ERR=%d]\n", i, all_items[i].key,
                                    ret);
                            free(all_items);
                            exit(EXIT_FAILURE);
                        }
                    }
                    finish = clock();
                    totol_time = (double) (finish - start) / CLOCKS_PER_SEC;
                    printf("KEYVALUE  INITIALIZED\nTIME USED = %fs\n", totol_time);

                    break;
                } else if (strncmp(par2, "JSON", 4) == 0) {
                    start = clock();

                    TABLES = JSON;
                    FILE *json_fp;
                    json_fp = fopen("/home/vory/programing/c/cjson_parser/ExportJson.json", "r");
                    fseek(json_fp, 0, SEEK_END);
                    json_file_length = ftell(json_fp);
                    char *file_string;
                    file_string = (char *) malloc(json_file_length * sizeof(char));
                    fseek(json_fp, 0, SEEK_SET);
                    fread(file_string, 1, json_file_length, json_fp);
                    parse_json_file(file_string);

                    char *delim = NULL;
                    char *getidcopy = NULL;
                    char *token = NULL;

                    delim = "\"";
                    ret = ttree_init(&ttree, 8, false, __cmpfunc, struct item_json, key);
                    if (ret < 0) {
                        fprintf(stderr, "Failed to initialize T*-tree. [ERR=%d]\n", ret);
                        free(json_items);
                        exit(EXIT_FAILURE);
                    }

//                    printf("array index size = %d", cJSON_GetArraySize(get1));
//                    printf("here\n");

                    for (array_index = 0; array_index < cJSON_GetArraySize(get1); array_index++) {

//                        printf("array index = %d\n", array_index);
                        get2 = cJSON_GetArrayItem(get1, array_index);
                        get3id = cJSON_GetObjectItem(get2, "ID");
                        get3jobtitile = cJSON_GetObjectItem(get2, "JobTitle");
                        get3email = cJSON_GetObjectItem(get2, "EmailAddress");
                        get3name = cJSON_GetObjectItem(get2, "FirstNameLastName");

                        json_items[array_index].jobtitle = (char *) malloc(50 * sizeof(char));
                        if (json_items[array_index].jobtitle == NULL) {
                            printf("malloc fail ");
                            break;
                        }
                        memset(json_items[array_index].jobtitle, 0, 50 * sizeof(char));

                        json_items[array_index].email = (char *) malloc(50 * sizeof(char));
                        if (json_items[array_index].email == NULL) {
                            printf("malloc fail ");
                            break;
                        }
                        memset(json_items[array_index].email, 0, 50 * sizeof(char));


                        json_items[array_index].firstlastname = (char *) malloc(50 * sizeof(char));
                        if (json_items[array_index].firstlastname == NULL) {
                            printf("malloc fail ");
                            break;
                        }
                        memset(json_items[array_index].firstlastname, 0, 50 * sizeof(char));

                        getidcopy = (char *) malloc(100 * sizeof(char));
                        memset(getidcopy, 0, 100 * sizeof(char));
                        strcpy(getidcopy, cJSON_Print(get3id));

                        token = strtok(getidcopy, delim);

                        json_items[array_index].key = strtol(token, NULL, 10);


//                        printf("json_array key = %ld\n", json_items[array_index].key);
                        free(getidcopy);


                        strcpy(json_items[array_index].jobtitle, cJSON_Print(get3jobtitile));

                        strcpy(json_items[array_index].email, cJSON_Print(get3email));
                        strcpy(json_items[array_index].firstlastname, cJSON_Print(get3name));

//                        printf("json id = %ld\n", json_items[array_index].key);

//                        printf("email = %s\n", json_items[array_index].email);
//                        printf("job = %s\n", json_items[array_index].jobtitle);
//                        printf("name = %s\n", json_items[array_index].firstlastname);
//                        printf("_________________________________\n");

                        ret = ttree_insert(&ttree, &json_items[array_index]);

                        if (ret < 0) {
                            fprintf(stderr, "Failed to insert item %d with key %ld! [ERR=%d]\n", array_index,
                                    json_items[array_index].key, ret);
                            free(json_items);
                            exit(EXIT_FAILURE);
                        }

                    }
                    finish = clock();
                    totol_time = (double) (finish - start) / CLOCKS_PER_SEC;
                    printf("JSON INITIALIZED\nTIME USED = %fs\n", totol_time);

                } else {
                    printf("SELECT %s IS NOT ALLOWED\n", par2);
                }
                break;

            case FIND:
                if (TABLES == KEYVALUE) {
                    if (strlen(par2) == 0) {
                        printf("FIND WHAT?\n");
                        continue;
                    }
                    struct item_keyvalue *item_find;
                    item_find = (struct item_keyvalue *) malloc(sizeof(struct item_keyvalue));
                    memset(item_find, 0, sizeof(struct item_keyvalue));
                    find_par2 = (int) strtol(par2, NULL, 10);

                    item_find = ttree_lookup(&ttree_keyvalue, &find_par2, NULL);
                    if (item_find == NULL) {
                        printf("find null\n");
                        break;

                    }
                    printf("find %ld,value  = %s\n", item_find->key, item_find->value);


                } else if (TABLES == JSON) {

                    if (strlen(par2) == 0) {
                        printf("FIND WHAT?\n");
                        continue;
                    }

                    while (1) {

                        struct item_json *item_find;
                        item_find = (struct item_json *) malloc(sizeof(struct item_json));
                        memset(item_find, 0, sizeof(struct item_json));
                        find_par2 = (int) strtol(par2, NULL, 10);

                        item_find = ttree_lookup(&ttree, &find_par2, NULL);
                        if (item_find == NULL) {
                            printf("find null\n");
                            break;

                        }
                        printf("find %ld\n", item_find->key);

                        get2 = cJSON_GetArrayItem(get1, (int) strtol(par2, NULL, 10) - 1);

                        item_find = ttree_lookup(&ttree, &find_par2, NULL);
                        printf("find id = %ld\n", item_find->key);
                        printf("find job = %s\n", item_find->jobtitle);
                        printf("find enail = %s\n", item_find->email);
                        printf("find firstname = %s\n", item_find->firstlastname);
                        break;
                    }
                }
                break;
            case INSERT:
                printf("RECEIVE INSERT\n");

                if (TABLES == KEYVALUE) {
                    if ((strlen(par2) == 0) || (strlen(par3) == 0)) {
                        printf("INSERT WHAT?\n");
                        continue;
                    }

                    if (strlen(par3) == 0) {
                        printf("DIDN'T GET par3, CANNOT INSERT WITHOUT par3\n");
                        break;
                    }

                    struct item_keyvalue *insert_find;
                    struct item_keyvalue *insertitem;
                    find_par2 = (int) strtol(par2, NULL, 10);
                    insert_find = ttree_lookup(&ttree_keyvalue, &find_par2, NULL);
                    if (insert_find != NULL) {
                        printf("exites\n");
                        break;
                    } else {
                        insertitem = (struct item_keyvalue *) malloc(sizeof(struct item_keyvalue));
                        memset(insertitem, 0, sizeof(struct item_keyvalue));
                        insertitem->key = strtol(par2, NULL, 10);
                        insertitem->value = malloc(50 * sizeof(char));
                        memset(insertitem->value, 0, 50);
                        par3[strlen(par3) - 1] = '\0';
                        strcpy(insertitem->value, par3);
                        ret = ttree_insert(&ttree_keyvalue, insertitem);
                        if (ret < 0) {
                            fprintf(stdout, "Failed to insert  key %ld!\n", strtol(par2, NULL, 100));
                        } else {
                            printf("SUCCESSFULLY INSERTED %ld", hash_user_id);
                        }
                    }
                } else if (TABLES == JSON) {
                    if ((strlen(par2) == 0) || (strlen(par3) == 0)) {
                        printf("INSERT WHAT?\n");
                        continue;
                    }
                    insert_count++;

                    insert_par2_key = (int) strtol(par2, NULL, 10);
                    if (insert_par2_key > json_nums_max) {
                        json_nums_max = insert_par2_key;
                        json_items = realloc(json_items, 5 * json_nums_max);

                        json_items[insert_par2_key].jobtitle = malloc(50);
                        memset(json_items[insert_par2_key].jobtitle, 0, 50);
                        json_items[insert_par2_key].email = malloc(50);
                        memset(json_items[insert_par2_key].email, 0, 50);
                        json_items[insert_par2_key].firstlastname = malloc(50);
                        memset(json_items[insert_par2_key].firstlastname, 0, 50);

                        json_items[insert_par2_key].key = strtol(par2, NULL, 10);
                        strcpy(json_items[insert_par2_key].jobtitle, par3);
                        strcpy(json_items[insert_par2_key].email, par4);
                        strcpy(json_items[insert_par2_key].firstlastname, par5);
                        ttree_insert(&ttree, &json_items[insert_par2_key - 1]);
                    } else {
                        memset(json_items[insert_par2_key - 1].jobtitle, 0, 50);
                        memset(json_items[insert_par2_key - 1].email, 0, 50);
                        memset(json_items[insert_par2_key - 1].firstlastname, 0, 50);
                        json_items[insert_par2_key - 1].key = strtol(par2, NULL, 10);
                        printf("inser key = %ld\n", json_items[insert_par2_key - 1].key);
                        printf("par3 = %s", par3);
                        strcpy(json_items[insert_par2_key - 1].jobtitle, par3);
                        strcpy(json_items[insert_par2_key - 1].email, par4);
                        strcpy(json_items[insert_par2_key - 1].firstlastname, par5);
                        ttree_insert(&ttree, &json_items[insert_par2_key - 1]);
                    }
                    ret = ttree_insert(&ttree, &json_items[insert_par2_key]);
                    if (ret < 0) {
                        fprintf(stdout, "Failed to insert  key %ld!\n", strtol(par2, NULL, 100));
                    } else {
                        printf("SUCCESSFULLY INSERTED %ld", hash_user_id);
                    }
                }
                break;
            case DELETE:
                if (TABLES == KEYVALUE) {
                    if ((strlen(par2) == 0)) {
                        printf("DELETE WHAT?\n");
                        continue;
                    }
                    if (ttree_lookup(&ttree_keyvalue, par2, NULL) == NULL) {
                        printf("KEY DOESN'T EXIT\n");
                        break;
                    } else {
                        delete_par2_key = (int) strtol(par2, NULL, 10);
                        res = ttree_delete(&ttree_keyvalue, &delete_par2_key);
                        if (res == NULL) {
                            printf("Failed to delete item %ld on step ", strtol(par2, NULL, 10));
                        } else {
                            printf("key  %d deleted ! ", delete_par2_key);
                        }
                    }
                } else if (TABLES == JSON) {
                    if ((strlen(par2) == 0)) {
                        printf("DELETE WHAT?\n");
                        continue;
                    }
                    delete_par2_key = (int) strtol(par2, NULL, 10);
                    ttree_delete(&ttree, &delete_par2_key);
                }
                break;
            case PRINT:
                if (TABLES == KEYVALUE) {

                    struct item_keyvalue *print_keyvalue;
                    print_keyvalue = malloc(sizeof(struct item_keyvalue));
                    memset(print_keyvalue, 0, sizeof(struct item_keyvalue));

                    tnode = ttree_node_leftmost(ttree_keyvalue.root);
                    while (tnode) {
                        tnode_for_each_index(tnode, i) {

                            print_keyvalue = ttree_key2item(&ttree_keyvalue, tnode_key(tnode, i));
                            if (strncmp(par2, "FROM", 4) == 0) {
//                                printf("par3 = %d\npar 5 = %d\n",strtol(par3,NULL,10),strtol(par5,NULL,10));

                                while (strtol(par3, NULL, 10) <= print_keyvalue->key &&
                                       print_keyvalue->key <= strtol(par5, NULL, 10)) {

                                    printf("key = %ld, value = %s\n", print_keyvalue->key, print_keyvalue->value);
                                    break;
                                }
                            } else {
                                printf("key = %ld, value = %s\n", print_keyvalue->key, print_keyvalue->value);
                            }
                        }
                        tnode = tnode->successor;
                    }
                } else if (TABLES == JSON) {
                    struct item_json *print_item;

                    print_item = malloc(sizeof(struct item_json));
                    memset(print_item, 0, sizeof(struct item_json));
                    tnode = ttree_node_leftmost(ttree.root);

                    while (tnode) {
                        tnode_for_each_index(tnode, i) {
                            print_item = ttree_key2item(&ttree, tnode_key(tnode, i));

                            if (strncmp(par2, "FROM", 4) == 0) {
                                if (strtol(par3, NULL, 10) <= print_item->key &&
                                    print_item->key <= strtol(par5, NULL, 10)) {

                                    printf("key = %d \n", *(int *) tnode_key(tnode, i));
                                    printf("jobtitle = %s\n", print_item->jobtitle);
                                    printf("email = %s\n", print_item->email);
                                    printf("name = %s\n_______________________\n", print_item->firstlastname);
                                }
                            } else {
                                printf("key = %d \n", *(int *) tnode_key(tnode, i));
                                printf("jobtitle = %s\n", print_item->jobtitle);
                                printf("email = %s\n", print_item->email);
                                printf("name = %s\n_______________________\n", print_item->firstlastname);
                            }
                        }
                        tnode = tnode->successor;
                    }
                }
                break;
            default:
                printf("this is default\n");
                strcpy(out_buff, "switch go to default");
                break;
        }

        printf("PLEASE INPUT HERE:");
        free(out_buff);
        free(inputline);

    } while ((strncmp(inputline, "EXIT", 4)) != 0);

    if (par1 != NULL) free(par1);
    if (par2 != NULL) free(par2);
    if (par3 != NULL) free(par3);
    if (par4 != NULL) free(par4);
    if (par5 != NULL) free(par5);
    if (TABLES == KEYVALUE) {
        fclose(fp);
        ttree_destroy(&ttree);
        free(all_items);
        free(parf0);
        free(parf1);
    } else if (TABLES == JSON) {
//        fclose();
        ttree_destroy(&ttree_keyvalue);
        free(json_items);
    }
    exit(EXIT_SUCCESS);
}