//
//  useKNN.h
//  
//
//  Created by Bowen on 4/18/16.
//
//

#include "allbut.h"


void store_file_to_array_KNN(char *fileName, int *item_array_1, int *item_array_2, int *distance_array) {
    FILE *file = fopen(fileName, "r");
    char line[100];
    int i = 0;
    while(!feof(file)) {
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),file);
        if(strlen(line)<=0) break;
        sscanf(line, "%d\t%d\t%d", &item_array_1[i], &item_array_2[i], &distance_array[i]);
        
        i++;
    }
    fclose(file);
}
//-----------------------------------------------------


void useKNN(char *predicted_ratings_file_name, char *KNN_file_name, char *train_file_name, int k, double alpha) {
    int number_of_ratings_predicted = numberOfRatings(predicted_ratings_file_name);
    int *user_id_array_predicted = malloc(number_of_ratings_predicted*sizeof(int));
    int *item_id_array_predicted = malloc(number_of_ratings_predicted*sizeof(int));
    double *rating_array_predicted = malloc(number_of_ratings_predicted*sizeof(double));
    store_file_to_array(predicted_ratings_file_name, user_id_array_predicted, item_id_array_predicted, rating_array_predicted);
//printf("a\n");
    int number_of_users = numberOfUsersWhole(KNN_file_name);
    int *item_id_array_KNN_1 = malloc(number_of_users * k * sizeof(int));
    int *item_id_array_KNN_2 = malloc(number_of_users * k * sizeof(int));
    int *distance_array_KNN = malloc(number_of_users * k * sizeof(int));
    store_file_to_array_KNN(KNN_file_name, item_id_array_KNN_1, item_id_array_KNN_2, distance_array_KNN);
    
    double global_mean = globalMean(train_file_name);
    int number_of_ratings_train = numberOfRatings(train_file_name);
    int *user_id_array_train = malloc(number_of_ratings_train*sizeof(int));
    int *item_id_array_train = malloc(number_of_ratings_train*sizeof(int));
    double *rating_array_train = malloc(number_of_ratings_train*sizeof(double));
    store_file_to_array(train_file_name, user_id_array_train, item_id_array_train, rating_array_train);
    
    double *mean_train = malloc(number_of_users * sizeof(double));
    for(int c = 0; c < number_of_users; c++) mean_train[c] = 0;
    user_mean(user_id_array_train, item_id_array_train, rating_array_train, mean_train, number_of_users, number_of_ratings_train);
    
    /*FILE *predicted_ratings_file = fopen(predicted_ratings_file_name, "r");
    FILE *KNN_file = fopen(KNN_file_name, "r");

    FILE *train_file = fopen(train_file_name, "r");
     */
    FILE *predicted_ratings_KNN_file = fopen("predicted_ratings_KNN.txt", "w");
    
    int i = 0, j = 0, m = 0, n = 0;
    int user_id_predicted = 0, item_id_predicted = 0;
    double rating_predicted = 0.00;
    
    int item_id_KNN_1 = 0, item_id_KNN_2 = 0;
    
    int user_id_train = 0, item_id_train = 0;
    double rating_train = 0.00;
    
    
    for(i = 0; i < number_of_ratings_predicted; i++) {//go through the predicted file, for each prediction
        user_id_predicted = user_id_array_predicted[i];
        item_id_predicted = item_id_array_predicted[i];
        rating_predicted = rating_array_predicted[i];
        
        for(j = 0; j < number_of_users; j++) {//go through the KNN file, match prediction's movie id
            item_id_KNN_1 = item_id_array_KNN_1[j];
            item_id_KNN_2 = item_id_array_KNN_2[j];
            
            if(item_id_predicted == item_id_KNN_1) {//if the movie id of i-th prediction is reached in KNN file
                for(n = 0; n < number_of_ratings_train; n++) {
                    user_id_train = user_id_array_train[n];
                    item_id_train = item_id_array_train[n];
                    rating_train = rating_array_train[n];
                    
                    if(item_id_train == item_id_KNN_2 && user_id_train == user_id_predicted) {
                        //rating_predicted += (rating_train - mean_train[user_id_train-1])*alpha;
                        rating_predicted += (rating_train - global_mean)*alpha;
                        break;
                    }
                }
            }
        }
        
        fprintf(predicted_ratings_KNN_file, "%d\t%d\t%lf\n", user_id_predicted, item_id_predicted, rating_predicted);
    }
    fclose(predicted_ratings_KNN_file);
    free(user_id_array_predicted);
    free(item_id_array_predicted);
    free(rating_array_predicted);
    
    free(item_id_array_KNN_1);
    free(item_id_array_KNN_2);
    free(distance_array_KNN);
    
    free(user_id_array_train);
    free(item_id_array_train);
    free(rating_array_train);
}