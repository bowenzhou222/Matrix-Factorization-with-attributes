#include "MF.h"

#define TRUE 1
#define FALSE 0

int numberOfUsersWhole(char *fileName){
    FILE *fp = fopen(fileName, "r");
    char line[100];
    char delimiter[]="\t";
    char *token, *delimited_line[3];
    int num = 0, i = 0;
    
    while(!feof(fp)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),fp);
        //printf("%s\n",lineoffile);
        token =strtok(line, delimiter);
        
        while (token !=NULL){
            for(i=0;i<4;i++){
                delimited_line[i]=token;
                token=strtok(NULL,delimiter);
            }
        }
        
        if (atoi(delimited_line[0]) > num) num = atoi(delimited_line[0]);
        
    }
    fclose(fp);
    
    
    return num;
}

//------------------------------------------
int numberOfItemsWhole(char *fileName){
    FILE *fp = fopen(fileName, "r");
    char line[100];
    char delimiter[]="\t";
    char *token, *delimited_line[3];
    int num = 0;
    int i = 0;
    while(!feof(fp)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),fp);
        //printf("%s\n",lineoffile);
        token =strtok(line, delimiter);
        
        while (token !=NULL){
            for(i=0;i<4;i++){
                delimited_line[i]=token;
                token=strtok(NULL,delimiter);
            }
        }
        
        if (atoi(delimited_line[1]) > num) num = atoi(delimited_line[1]);
        
    }
    fclose(fp);
    
    
    
    return num;
}


void allbut(char *dataset_name, int n){
    char line[100];
    int num = 0, i = 0, j = 0 , k = 0, m = 0;
    int user_id = 0, item_id = 0, no_use = 0;
    int number_of_users = numberOfUsersWhole(dataset_name), number_of_items = numberOfItemsWhole(dataset_name), number_of_ratings = numberOfRatings(dataset_name);
    //printf("%d\t%d\t%d\n", number_of_users, number_of_items, number_of_ratings);
    double sum = 0.00, global_mean = 0.00;
    int rating = 0;
    
    int *rating_vector = malloc(number_of_items * sizeof(int));
    
    int *user_array_total = malloc(number_of_ratings*sizeof(int));
    int *item_array_total = malloc(number_of_ratings*sizeof(int));
    double *rating_array_total = malloc(number_of_ratings*sizeof(double));
    
    FILE *dataset = fopen(dataset_name, "r");
    
    while(!feof(dataset)) {
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line), dataset);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf", &user_array_total[i], &item_array_total[i], &rating_array_total[i]);
        i++;
    }
    
    rewind(dataset);
    
    
    FILE *all_but_base_file = fopen("all_but_base.txt", "w");
    FILE *all_but_test_file = fopen("all_but_test.txt", "w");
   
    
    int *random_array;
    int *item_vector;
    item_vector = (int*)malloc(number_of_items*sizeof(int));
    for(i = 1; i <= number_of_users; i++) {
        //rewind(dataset);
        k = 0;
        for(j = 0; j < number_of_ratings; j++) {//store all ratings of this user into the vector
            //fgets(line, sizeof(line), dataset);
            //if (strlen(line) <= 0) break;
            //sscanf(line, "%d\t%d\t%d\t%d", &user_id, &item_id, &rating, &no_use);
            //printf("%d\t%d\t%d\n", user_id, item_id, rating);
            user_id = user_array_total[j];
            if (user_id == i) {
                rating_vector[k] = rating_array_total[j];
                item_vector[k] = item_array_total[j];
                k++; //number of ratings of this user
            }
        }
        
        random_array = (int*)malloc(k*sizeof(int));
        
        
        //rewind(dataset);
        //k = 0;
        //for(j = 0; j < number_of_ratings; j++) {//store all items of this user into the vector
            //fgets(line, sizeof(line), dataset);
            //if (strlen(line) <= 0) break;
            //sscanf(line, "%d\t%d\t%d\t%d", &user_id, &item_id, &rating, &no_use);
            //printf("%d\t%d\t%lf\n", user_id, item_id, rating);
            //user_id = user_array_total[j];
            //if (user_id == i) {
                
               // k++;
            //}
        //}
        
        srand((unsigned long) time(NULL));
        for(num = 0; num < k; num++) random_array[num] = num;
        //for(num = 0; num < k; num++) printf("%d\n",random_array[num]);
        shuffle(random_array, k);//radndomly sort the indices of ratings of this user
        
        
        for(m = 0; m < n && m < k; m++) {//randomly pick up n ratings of this user
            if (m < k) {
                fprintf(all_but_test_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
            }
        }
        for(; m < k; m++) {
            fprintf(all_but_base_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
        }
        
        free(random_array);
        //free(item_vector);
    }

    
    fclose(dataset);
    fclose(all_but_base_file);
    fclose(all_but_test_file);
    free(rating_vector);
    free(user_array_total);
    free(item_array_total);
    free(rating_array_total);
    free(item_vector);
}

//---------------------------------
void given_n(char *dataset_name, int n){
    char line[100];
    int num = 0, i = 0, j = 0 , k = 0, m = 0;
    int user_id = 0, item_id = 0, no_use = 0;
    int number_of_users = numberOfUsersWhole(dataset_name), number_of_items = numberOfItemsWhole(dataset_name), number_of_ratings = numberOfRatings(dataset_name);
    //printf("%d\t%d\t%d\n", number_of_users, number_of_items, number_of_ratings);
    double sum = 0.00, global_mean = 0.00;
    int rating = 0;
    
    int *rating_vector = malloc(number_of_items * sizeof(int));
    
    int *user_array_total = malloc(number_of_ratings*sizeof(int));
    int *item_array_total = malloc(number_of_ratings*sizeof(int));
    double *rating_array_total = malloc(number_of_ratings*sizeof(double));
    
    FILE *dataset = fopen(dataset_name, "r");
    
    while(!feof(dataset)) {
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line), dataset);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf", &user_array_total[i], &item_array_total[i], &rating_array_total[i]);
        i++;
    }
    
    rewind(dataset);
    
    
    FILE *all_but_base_file = fopen("all_but_base.txt", "w");
    FILE *all_but_test_file = fopen("all_but_test.txt", "w");
    
    int c = 0;
    
    int *random_array;
    int *item_vector;
    item_vector = (int*)malloc(number_of_items*sizeof(int));
    for(i = 1; i <= 500; i++) {
        k = 0;
        for(j = 0; j < number_of_ratings; j++) {//store all ratings of this user into the vector
            user_id = user_array_total[j];
            if (user_id == i) {
                rating_vector[k] = rating_array_total[j];
                item_vector[k] = item_array_total[j];
                k++; //number of ratings of this user
            }
        }
        if(i <= 300) {
            for(c = 0; c < k; c++) {
                fprintf(all_but_base_file, "%d\t%d\t%d\n", i, item_vector[c], rating_vector[c]);
            }
        } else {
            random_array = (int*)malloc(k*sizeof(int));
    
            srand((unsigned long) time(NULL));
            for(num = 0; num < k; num++) random_array[num] = num;
            //for(num = 0; num < k; num++) printf("%d\n",random_array[num]);
            shuffle(random_array, k);//radndomly sort the indices of ratings of this user
        
        
            for(m = 0; m < n && m < k; m++) {//randomly pick up n ratings of this user
                if (m < k) {
                    fprintf(all_but_base_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
                }
            }
            for(; m < k; m++) {
                fprintf(all_but_test_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
            }
        
            free(random_array);
        }
        //free(item_vector);
    }
    
    
    fclose(dataset);
    fclose(all_but_base_file);
    fclose(all_but_test_file);
    free(rating_vector);
    free(user_array_total);
    free(item_array_total);
    free(rating_array_total);
    free(item_vector);
}

//---------------------------------

void cold(char *dataset_name, int n, int user){
    char line[100];
    int num = 0, i = 0, j = 0 , k = 0, m = 0;
    int user_id = 0, item_id = 0, no_use = 0;
    int number_of_users = numberOfUsersWhole(dataset_name), number_of_items = numberOfItemsWhole(dataset_name), number_of_ratings = numberOfRatings(dataset_name);
    //printf("%d\t%d\t%d\n", number_of_users, number_of_items, number_of_ratings);
    double sum = 0.00, global_mean = 0.00;
    int rating = 0;
    
    int *rating_vector = malloc(number_of_items * sizeof(int));
    
    int *user_array_total = malloc(number_of_ratings*sizeof(int));
    int *item_array_total = malloc(number_of_ratings*sizeof(int));
    double *rating_array_total = malloc(number_of_ratings*sizeof(double));
    
    FILE *dataset = fopen(dataset_name, "r");
    
    while(!feof(dataset)) {
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line), dataset);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf", &user_array_total[i], &item_array_total[i], &rating_array_total[i]);
        i++;
    }
    
    rewind(dataset);
    
    
    FILE *all_but_base_file = fopen("all_but_base.txt", "w");
    FILE *all_but_test_file = fopen("all_but_test.txt", "w");
    
    
    int *random_array;
    int *item_vector;
    item_vector = (int*)malloc(number_of_items*sizeof(int));
    for(i = 1; i <= number_of_users; i++) {
        //rewind(dataset);
        k = 0;
        for(j = 0; j < number_of_ratings; j++) {
            user_id = user_array_total[j];
            if (user_id == i) {
                rating_vector[k] = rating_array_total[j];
                item_vector[k] = item_array_total[j];
                k++; //number of ratings of this user
            }
        }
        
        random_array = (int*)malloc(k*sizeof(int));
        
        
        srand((unsigned long) time(NULL));
        for(num = 0; num < k; num++) random_array[num] = num;
        //for(num = 0; num < k; num++) printf("%d\n",random_array[num]);
        shuffle(random_array, k);//radndomly sort the indices of ratings of this user
        
        m = 0;
        if(i == user) {
            for(m = 0; m < n && m < k; m++) {//randomly pick up n ratings of this user
                if (m < k) {
                    fprintf(all_but_test_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
                }
            }
            for(; m < k; m++) {
                fprintf(all_but_base_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
            }
        } else {
            for(m = 0; m < k; m++) {
                fprintf(all_but_test_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
            }
        }
        
        
        free(random_array);
        //free(item_vector);
    }
    
    
    fclose(dataset);
    fclose(all_but_base_file);
    fclose(all_but_test_file);
    free(rating_vector);
    free(user_array_total);
    free(item_array_total);
    free(rating_array_total);
    free(item_vector);
}

//---------------------------------
void leave_n(char *dataset_name, int n, int user){
    char line[100];
    int num = 0, i = 0, j = 0 , k = 0, m = 0;
    int user_id = 0, item_id = 0, no_use = 0;
    int number_of_users = numberOfUsersWhole(dataset_name), number_of_items = numberOfItemsWhole(dataset_name), number_of_ratings = numberOfRatings(dataset_name);
    //printf("%d\t%d\t%d\n", number_of_users, number_of_items, number_of_ratings);
    double sum = 0.00, global_mean = 0.00;
    int rating = 0;
    
    int *rating_vector = malloc(number_of_items * sizeof(int));
    
    int *user_array_total = malloc(number_of_ratings*sizeof(int));
    int *item_array_total = malloc(number_of_ratings*sizeof(int));
    double *rating_array_total = malloc(number_of_ratings*sizeof(double));
    
    FILE *dataset = fopen(dataset_name, "r");
    
    while(!feof(dataset)) {
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line), dataset);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf", &user_array_total[i], &item_array_total[i], &rating_array_total[i]);
        i++;
    }
    
    rewind(dataset);
    
    
    FILE *all_but_base_file = fopen("all_but_base.txt", "w");
    FILE *all_but_test_file = fopen("all_but_test.txt", "w");
    
    
    int *random_array;
    int *item_vector;
    item_vector = (int*)malloc(number_of_items*sizeof(int));
    for(i = 1; i <= number_of_users; i++) {
        //rewind(dataset);
        k = 0;
        for(j = 0; j < number_of_ratings; j++) {
            user_id = user_array_total[j];
            if (user_id == i) {
                rating_vector[k] = rating_array_total[j];
                item_vector[k] = item_array_total[j];
                k++; //number of ratings of this user
            }
        }
        
        random_array = (int*)malloc(k*sizeof(int));
        
        
        srand((unsigned long) time(NULL));
        for(num = 0; num < k; num++) random_array[num] = num;
        //for(num = 0; num < k; num++) printf("%d\n",random_array[num]);
        shuffle(random_array, k);//radndomly sort the indices of ratings of this user
        
        m = 0;
        if(i == user) {
            for(m = 0; m < n && m < k; m++) {//randomly pick up n ratings of this user
                fprintf(all_but_base_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
            }
            for(; m < k; m++) {
                fprintf(all_but_test_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
            }
        } else {
            for(m = 0; m < k; m++) {
                fprintf(all_but_test_file, "%d\t%d\t%d\n", i, item_vector[random_array[m]], rating_vector[random_array[m]]);
            }
        }
        
        
        free(random_array);
        //free(item_vector);
    }
    
    
    fclose(dataset);
    fclose(all_but_base_file);
    fclose(all_but_test_file);
    free(rating_vector);
    free(user_array_total);
    free(item_array_total);
    free(rating_array_total);
    free(item_vector);
}

