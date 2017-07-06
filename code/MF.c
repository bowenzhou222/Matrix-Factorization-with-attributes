#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include <time.h>
//#include "MF.h"
#include "useKNN.h"
//int numberOfRatings(char *fileName);
//double randn (double mu, double sigma);
//void MF(char *trainFileName, char *testFileName);

void add_attributes(char *fileName);

//./MF     train_file     test_file     all_but_n     all-but/given      y/n      KNN/noKNN


int main(int argc, char *argv[]) {
    int n = atoi(argv[3]);
    int num_KNN = 10;
    double alpha = 0.05;
    double threshold = 1.7;
    //MF(argv[1], argv[2]);
    int i = 0, j = 0;
    if(!strcmp(argv[4], "cold-start")) {
        for(i = 0; i < 5; i++) {
            for(j = 0; j < 10; j++) {
                cold("udata.txt", n, i+1);//all_but_n; given_n
                if(!strcmp(argv[5], "y")) add_attributes(argv[2]);
                MF(argv[2], argv[1]);
                if(!strcmp(argv[6], "KNN")) {
                    useKNN("predicted_ratings.txt", "testKNN.txt", argv[1], num_KNN, alpha);
                    rmse_mae_eval(argv[1], "predicted_ratings_KNN.txt");
                    printf("\n");
                }
            }
            //printf("\n");
        }
    }
    if(!strcmp(argv[4], "leave-n")) {
        for(i = 0; i < 5; i++) {//for this number of user
            for(j = 0; j < 10; j++) {
                leave_n("udata.txt", n, i+1);//randomly leave n ratings of this user as test dataset
                if(!strcmp(argv[5], "y")) add_attributes(argv[2]);
                MF(argv[2], argv[1]);
                if(!strcmp(argv[6], "KNN")) {
                    useKNN("predicted_ratings.txt", "testKNN.txt", argv[1], num_KNN, alpha);
                    rmse_mae_eval(argv[1], "predicted_ratings_KNN.txt");
                    printf("\n");
                }
            }
            //printf("\n");
        }
    }

    
    
    
    for(i = 0; i < 10; i++) {
        if(!strcmp(argv[4], "all-but")) {
            allbut("udata.txt", n);//all_but_n; given_n
            //if(!strcmp(argv[5], "y")) add_attributes(argv[1]);//argv[1]--all_but_n;   argv[2]--given_n
            //MF
            MF(argv[1], argv[2]);//argv[1],argv[2] -- all_but_n;
            
            //MF_KNN
            useKNN("predicted_ratings.txt", "testKNN.txt", argv[1], num_KNN, alpha);
            //reduce(argv[1], argv[2]);//use the mean of reduced train data to use KNN to modify MF
            //useKNN("predicted_ratings.txt", "testKNN.txt",argv[1], num_KNN, alpha);
            rmse_mae_eval(argv[2], "predicted_ratings_KNN.txt");//argv[2] is the test file
            
            //MFA
            add_attributes(argv[1]);
            //reduce(argv[1], argv[2]);
            //MF("reduced_base.txt", argv[2]);
            MF(argv[1], argv[2]);
            
            //MFA_KNN
            //if(!strcmp(argv[6], "KNN")) {
                useKNN("predicted_ratings.txt", "testKNN.txt", argv[1], num_KNN, alpha);
                rmse_mae_eval(argv[2], "predicted_ratings_KNN.txt");//argv[2] is the test file
                printf("\n");
            //}
        }
        if (!strcmp(argv[4], "given")){
            given_n("udata.txt", n);//all_but_n; given_n
            //MF
            //MF(argv[1], argv[2]);
            //printf("\n");
            //MF_KNN
            //useKNN("predicted_ratings.txt", "testKNN.txt", argv[1], num_KNN, alpha);
            //rmse_mae_eval(argv[2], "predicted_ratings_KNN.txt");//argv[2] is the test file

            //MFA
            if(!strcmp(argv[5], "y")) add_attributes(argv[1]);
            //MF(argv[1], argv[2]);
            
            //MFA_KNN
            //useKNN("predicted_ratings.txt", "testKNN.txt", argv[1], num_KNN, alpha);
            //rmse_mae_eval(argv[2], "predicted_ratings_KNN.txt");//argv[2] is the test file
            
            //MFAR
            //for(threshold = 0.1;threshold < 3;threshold += 0.1){
            reduce(argv[1], argv[2], threshold);
            MF("reduced_base.txt", argv[2]);
            
            //MFAR_KNN
            //if(!strcmp(argv[6], "KNN")) {
                //useKNN("predicted_ratings.txt", "testKNN.txt", "reduced_base.txt", num_KNN, alpha);
                //rmse_mae_eval(argv[2], "predicted_ratings_KNN.txt");
                printf("\n");
            //}
            //}
            //printf("\n");
            printf("\n");
            
        }

        if (!strcmp(argv[4], "n")){//simply apply MF
            //allbut("udata.txt", n);//all_but_n; given_n
            //if(!strcmp(argv[5], "y")) add_attributes(argv[2]);//argv[1]--all_but_n;   argv[2]--given_n
            //add_attributes(argv[1]);
            //reduce(argv[1], argv[2]);
            //reduce_top_N(argv[1], argv[2]);
            MF(argv[1], argv[2]);//argv[1],argv[2] -- all_but_n;   argv[2],argv[1]--given_n
            if(!strcmp(argv[6], "KNN")) {
                useKNN("predicted_ratings.txt", "testKNN.txt", argv[1], num_KNN, alpha);
                rmse_mae_eval(argv[2], "predicted_ratings_KNN.txt");//argv[2] is the test file
                printf("\n");
            }
            break;
        }

    }
	return 0;
}


void add_attributes(char *fileName) {
    FILE *attribute_file = fopen("attribute.txt", "r");
    FILE *fp = fopen(fileName, "a");
    char line[100];
    while(!feof(attribute_file)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),attribute_file);
        //printf("%s",line);
        if(strlen(line)<=0) break;
        fprintf(fp, "%s",line);
    }

    fclose(attribute_file);
    fclose(fp);
}