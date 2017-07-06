

//----------------------------------------------------------
int numberOfRatings(char *fileName) {
	FILE *trainFile = fopen(fileName,"r");
	
	char line[100];
	int num = 0;
	while(!feof(trainFile)){
		memset(line,0x0,sizeof(line));
	    fgets(line,sizeof(line),trainFile);
        //printf("%s",line);
		if(strlen(line)<=0) break;
		num++;
	}
    fclose(trainFile);
    //printf("%d\n",num);
	return num;
}
//----------------------------------------------------------
void rmse_mae_eval(char *testFileName, char *predictionFileName){
    int number_of_ratings = numberOfRatings(testFileName);
    
    FILE *testFile = fopen(testFileName, "r");
    FILE *predictionFile = fopen(predictionFileName, "r");
    char line[100];
    double sum =0.00, mae_sum = 0.00, rating_test, rating_predicted;
    int u, v;
    while(!feof(testFile) && !feof(predictionFile)){
        fgets(line, sizeof(line), testFile);
        if (strlen(line) <= 0) break;
        sscanf(line, "%d\t%d\t%lf", &u, &v, &rating_test);
        
        fgets(line, sizeof(line), predictionFile);
        if(strlen(line) <= 0) break;
        sscanf(line, "%d\t%d\t%lf", &u, &v, &rating_predicted);
        
        sum += (rating_predicted - rating_test)*(rating_predicted - rating_test);
        mae_sum += fabs(rating_predicted - rating_test);
    }
    
    double rmse = sqrt(sum/number_of_ratings);
    double mae = mae_sum/number_of_ratings;
    printf("%lf\t%lf\t", rmse, mae);
    //printf("%lf\n", rmse);
    fclose(testFile);
    fclose(predictionFile);
}
//-----------------------------------------------------

void store_file_to_array(char *fileName, int *user_array, int *item_array, double *rating_array) {
    FILE *file = fopen(fileName, "r");
    char line[100];
    int i = 0;
    while(!feof(file)) {
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),file);
        if(strlen(line)<=0) break;
        sscanf(line, "%d\t%d\t%lf", &user_array[i], &item_array[i], &rating_array[i]);
        
        i++;
    }
    fclose(file);
}
//-----------------------------------------------------


int numberOfUsersTrain(char *fileName){
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
int numberOfUsers(char *fileName, char *fileName2){
    FILE *fp = fopen(fileName, "r");
    FILE *fp2 = fopen(fileName2, "r");
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
    
    while(!feof(fp2)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),fp2);
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
    fclose(fp2);
    
    return num;
}

//------------------------------------------
int numberOfItems(char *fileName, char *fileName2){
    FILE *fp = fopen(fileName, "r");
    FILE *fp2 = fopen(fileName2, "r");
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
    
    
    while(!feof(fp2)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),fp2);
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
    fclose(fp2);

    
    return num;
}
//----------------------------------------------------------
double randn (double mu, double sigma) {
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
  
  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }
 
  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);
 
  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}
//-----------------------------------------------------------

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
//-----------------------------------------------------------


double globalMean(char *fileName) {
    int u, v, n, i = 0;
    double r, sum = 0.00;
    char line[100];
    FILE *file = fopen(fileName, "r");
    while(!feof(file)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),file);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf\t%d", &u, &v, &r, &n);
        sum += r;
        
        i++;		
    }
    double global_mean = sum/i;
    return global_mean;
}
//----------------------------------------------------------
void user_mean(int *user_id_array_train, int *item_id_array_train, double *rating_array_train, double *mean_train, int number_of_users, int number_of_ratings_train) {
    
    int i = 0, j =0;
    int num = 0;
    double sum = 0.00, mean = 0.00;
    for(i = 0; i < number_of_users; i++) {
        sum = 0.00;
        num = 0;
        for(j = 0; j < number_of_ratings_train; j++) {
            if(user_id_array_train[j] == i+1) {
                sum += rating_array_train[j];
                num++;
            }
        }
        if (num != 0) mean = sum/num;
        else mean = 0.00;
        mean_train[i] = mean;
    }
    
}
//-----------------------------------------------
void user_num_ratings(int *user_id_array_train, int *item_id_array_train, double *rating_array_train, int *num_rating_each_user, int number_of_users, int number_of_ratings_train) {
    
    int i = 0, j =0;
    int num = 0;
    double sum = 0.00, mean = 0.00;
    for(i = 0; i < number_of_users; i++) {
        sum = 0.00;
        num = 0;
        for(j = 0; j < number_of_ratings_train; j++) {
            if(user_id_array_train[j] == i+1) {
                sum += rating_array_train[j];
                num++;
            }
        }

        num_rating_each_user[i] = mean;
    }
    
}
//-----------------------------------------------
void MF(char *trainFileName, char *testFileName) {
    int ratingNumber = numberOfRatings(trainFileName);//printf("%d\n", ratingNumber);
    int num_user = numberOfUsers(trainFileName, testFileName), num_item = numberOfItems(trainFileName, testFileName);//printf("%d\n",num_user);
    
	int *userIDVector = (int *) malloc(ratingNumber*sizeof(int));
	int *itemIDVector = (int *) malloc(ratingNumber*sizeof(int));
	double *ratingVector = (double *) malloc(ratingNumber*sizeof(double));
	int no_use;
	FILE *trainFile = fopen(trainFileName,"r");
	
	char line[100];
	int num = 0, i = 0, j = 0 , k = 0;
	double sum = 0.00, global_mean = 0.00;
	while(!feof(trainFile)){
		memset(line,0x0,sizeof(line));
	    fgets(line,sizeof(line),trainFile);
		if(strlen(line)<=0) break;
		//if(feof(trainFile)) break;
		sscanf(line, "%d\t%d\t%lf", &userIDVector[i], &itemIDVector[i], &ratingVector[i]);
		sum += ratingVector[i];

		//if (userIDVector[i] > num_user) num_user = userIDVector[i];
		//if (itemIDVector[i] > num_item) num_item = itemIDVector[i];

		i++;		
	}
	global_mean = sum/ratingNumber;

    
    //calculate mean of each user in training file
    int number_of_users=numberOfUsersTrain(trainFileName);
    int *num_rating_each_user = malloc(number_of_users * sizeof(int));
    double *mean_train = malloc(number_of_users * sizeof(double));
    for(int c = 0; c < number_of_users; c++) mean_train[c] = 0;
    user_mean(userIDVector, itemIDVector, ratingVector, mean_train, number_of_users, ratingNumber);
    user_num_ratings(userIDVector, itemIDVector, ratingVector, num_rating_each_user, number_of_users, ratingNumber);
    
    
    
    
	int userID, itemID;
	double predicted_rating = 0.00, dot_product = 0.00, prediction_error = 0.00;
	double rating, initStDev = 0.1, initMean = 0.00;
	double learn_rate = 0.05, regularization = 0.15;
	int num_iteration = 50, num_factors = 5;
	double **user_factor_matrix = malloc(num_user * sizeof *user_factor_matrix + (num_user * (num_factors * sizeof **user_factor_matrix)));
	double **item_factor_matrix = malloc(num_item * sizeof *item_factor_matrix + (num_item * (num_factors * sizeof **item_factor_matrix)));
	

	double *data = user_factor_matrix + num_user;
	for(i = 0; i < num_user; i++)
		user_factor_matrix[i] = data + i * num_factors;
	
	double *data2 = item_factor_matrix + num_item;
	for(i = 0; i < num_item; i++)
		item_factor_matrix[i] = data2 + i * num_factors;

    
    //array to store number of ratings of each user
    //int *num_rating_each_user = malloc(num_user_train * sizeof(int));
    //array to store the mean rating of each user
    //double *mean_each_user = malloc(num_user_train * sizeof(double));
    //mean_each_user_eval(userIDVector, itemIDVector, ratingVector, num_user_train, ratingNumber, mean_each_user, num_rating_each_user);
    
	//initialize user factor matrix and item factor matrix
	srand((unsigned long)time);
	for(i = 0; i < num_user; i++) {
		for(j = 0; j < num_factors; j++) {
			user_factor_matrix[i][j] = randn(initMean, initStDev);
		}
	}
	for(i = 0; i < num_item; i++) {
		for(j = 0; j < num_factors; j++) {
			item_factor_matrix[i][j] = randn(initMean, initStDev);
		}
	}

	int *random_array = malloc(ratingNumber*sizeof(int));
	for(i = 0; i < ratingNumber; i++) random_array[i] = i;
	
	for(k = 0; k < num_iteration; k++) {
        
        shuffle(random_array, ratingNumber);
		for(num = 0; num < ratingNumber; num++) {
			i = random_array[num];
			userID = userIDVector[i];
			itemID = itemIDVector[i];
			rating = ratingVector[i];

			//dot product of rows of the two factor matrices
			dot_product = 0.00;
			for(j = 0; j < num_factors; j++) {
				dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
			}
            //predicted_rating = dot_product + mean_train[userID-1];
            //else predicted_rating = dot_product + global_mean;
            predicted_rating = dot_product + global_mean;
            //if (num_rating_each_user[userID-1] < 10) predicted_rating = dot_product + global_mean;
            //else predicted_rating = dot_product + mean_train[userID-1];
			//if (predicted_rating > 5) predicted_rating = 5;
			//if (predicted_rating < 1) predicted_rating = 1;
			prediction_error = rating - predicted_rating;
			//printf("%lf\t%lf\t%lf\n",rating, predicted_rating, prediction_error);
			//update user factors and item factors
			for(j = 0; j < num_factors; j++) {
				user_factor_matrix[userID-1][j] += learn_rate * (prediction_error*item_factor_matrix[itemID-1][j] - regularization*user_factor_matrix[userID-1][j]);
				item_factor_matrix[itemID-1][j] += learn_rate * (prediction_error*user_factor_matrix[userID-1][j] - regularization*item_factor_matrix[itemID-1][j]);
			}
		
		}
	}

	//predict ratings listed in testFile
	int ratingNumber_test = numberOfRatings(testFileName);
	int *userIDVector_test = (int *) malloc(ratingNumber_test*sizeof(int));
	int *itemIDVector_test = (int *) malloc(ratingNumber_test*sizeof(int));
	double *ratingVector_test = (double *) malloc(ratingNumber_test*sizeof(double));
	double *predicted_ratingVector_test = (double *) malloc(ratingNumber_test*sizeof(double));
	//FILE *testFile = fopen(testFileName,"r");
	i = 0;
    store_file_to_array(testFileName, userIDVector_test, itemIDVector_test, ratingVector_test);
	

	sum = 0.00;
    double mae_sum = 0.00;
    
    FILE *rating_file = fopen("predicted_ratings.txt", "w");
	for(i = 0; i < ratingNumber_test; i++) {
		userID = userIDVector_test[i];
		itemID = itemIDVector_test[i];
		rating = ratingVector_test[i];

		dot_product = 0.00;
		for(j = 0; j < num_factors; j++) {
            //if(user_factor_matrix[userID-1][j] < 0) printf("%lf\n", user_factor_matrix[userID-1][j]);
			dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
		}
		//predicted_ratingVector_test[i] = dot_product + mean_train[userID-1];
        predicted_ratingVector_test[i] = dot_product + global_mean;
        //if (num_rating_each_user[userID-1] < 10) predicted_ratingVector_test[i] = dot_product + global_mean;
        //else predicted_ratingVector_test[i] = dot_product + mean_train[userID-1];
        
		if (predicted_ratingVector_test[i] > 5) predicted_ratingVector_test[i] = 5;
		if (predicted_ratingVector_test[i] < 1) predicted_ratingVector_test[i] = 1;
        
        fprintf(rating_file, "%d\t%d\t%lf\n", userID, itemID, predicted_ratingVector_test[i]);
        
		//sum += pow((sqrt(6-ratingVector_test[i]) - sqrt(6-predicted_ratingVector_test[i])), 2);
        sum += pow((-ratingVector_test[i] - -predicted_ratingVector_test[i]), 2);
        mae_sum += fabs(ratingVector_test[i] - predicted_ratingVector_test[i]);
	}
	double rmse = sqrt(sum/ratingNumber_test);
    double mae = mae_sum/ratingNumber_test;
	printf("%lf\t%lf\t", rmse, mae);
    //printf("%lf\n", rmse);
    
    fclose(rating_file);
	fclose(trainFile);
	//fclose(testFile);
    free(userIDVector);
    free(itemIDVector);
    free(ratingVector);
    free(user_factor_matrix);
    free(item_factor_matrix);
    free(random_array);
    free(userIDVector_test);
    free(itemIDVector_test);
    free(ratingVector_test);
    free(predicted_ratingVector_test);
    //free(num_rating_each_user);
    //free(mean_each_user);
    free(num_rating_each_user);
}

//----------------------------------------------------------
void user_KNN_file_to_array(char *user_KNN_file_name, int **user_KNN_matrix, int num_neighbour, int num_user){
    FILE *user_KNN_file = fopen(user_KNN_file_name, "r");
    int i = 0, j = 0, distance = 0, userID = 0, userID_neighbour;
    
    for(i = 0; i < num_user; i++) {
        for(j = 0; j < num_neighbour; j++) {
            fscanf(user_KNN_file, "%d\t%d\t%d", &userID, &userID_neighbour, &distance);
            user_KNN_matrix[userID-1][j] = userID_neighbour;
        }
    }
    
    fclose(user_KNN_file);
}
//----------------------------------------------------------
void mean_each_user_eval(int *user_ID_array, int *item_ID_array, double *rating_array, int num_user, int num_rating, double *mean_array, int *num_rating_each_user){
    int i = 0, j = 0;
    double *rating_sum_array = malloc(num_user * sizeof(double));
    //int *num_rating_each_user = malloc(num_user * sizeof(int));
    for(i = 0; i < num_user; i++) {
        rating_sum_array[i] = 0.00;
        num_rating_each_user[i] = 0;
    }
    for(i = 0; i < num_rating; i++) {
        rating_sum_array[user_ID_array[i]-1] += rating_array[i];
        num_rating_each_user[user_ID_array[i]-1] ++;
    }
    for(i = 0; i < num_user; i++) {
        mean_array[i] = rating_sum_array[i]/num_rating_each_user[i];
        //printf("%d\t%lf\n", i+1, mean_array[i]);
        //printf("%d\n", num_rating_each_user[i]);
    }
    
    free(rating_sum_array);
    //free(num_rating_each_user);
}

//----------------------------------------------------------
void mean_user_KNN(int **user_KNN_matrix, double *mean_each_user, double *mean_user_KNN_array, int *num_rating_each_user, int num_neighbour, int num_user){
    int i = 0, j = 0, num = 0;
    double rating_sum = 0.00, sum = 0.00;
    int userID = 0;
    for(i = 0; i < num_user; i++) {
        rating_sum = 0.00;
        num = 0;
        for(j = 0; j < num_neighbour; j++){
            userID = user_KNN_matrix[i][j];
            //printf("%d\n", userID);
            rating_sum += mean_each_user[userID - 1]*num_rating_each_user[userID - 1];
            sum += mean_each_user[userID - 1]*num_rating_each_user[userID - 1];

            num += num_rating_each_user[userID - 1];
            //printf("%d\n", num_rating_each_user[userID - 1]);
        }
        mean_user_KNN_array[i] = rating_sum/num;
        //printf("%lf\n", rating_sum);
        //printf("%d\n", num);
    }
    //printf("%lf\n", sum/943);
}
//----------------------------------------------------------
void reduce(char *trainFileName, char *testFileName, double threshold) {
    int ratingNumber = numberOfRatings(trainFileName);//printf("%d\n", ratingNumber);
    int num_user = numberOfUsers(trainFileName, testFileName), num_item = numberOfItems(trainFileName, testFileName);//printf("%d\n",num_user);
    
    int *userIDVector = (int *) malloc(ratingNumber*sizeof(int));
    int *itemIDVector = (int *) malloc(ratingNumber*sizeof(int));
    double *ratingVector = (double *) malloc(ratingNumber*sizeof(double));
    int no_use;
    FILE *trainFile = fopen(trainFileName,"r");
    
    char line[100];
    int num = 0, i = 0, j = 0 , k = 0;
    double sum = 0.00, global_mean = 0.00;
    while(!feof(trainFile)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),trainFile);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf", &userIDVector[i], &itemIDVector[i], &ratingVector[i]);
        sum += ratingVector[i];
        
        //if (userIDVector[i] > num_user) num_user = userIDVector[i];
        //if (itemIDVector[i] > num_item) num_item = itemIDVector[i];
        
        i++;
    }
    global_mean = sum/ratingNumber;
    
    int userID, itemID;
    double t = threshold;
    double predicted_rating = 0.00, dot_product = 0.00, prediction_error = 0.00;
    double rating, initStDev = 0.1, initMean = 0.00;
    double learn_rate = 0.01, regularization = 0.15;
    int num_iteration = 50, num_factors = 5;
    double **user_factor_matrix = malloc(num_user * sizeof *user_factor_matrix + (num_user * (num_factors * sizeof **user_factor_matrix)));
    double **item_factor_matrix = malloc(num_item * sizeof *item_factor_matrix + (num_item * (num_factors * sizeof **item_factor_matrix)));
    
    
    double *data = user_factor_matrix + num_user;
    for(i = 0; i < num_user; i++)
        user_factor_matrix[i] = data + i * num_factors;
    
    double *data2 = item_factor_matrix + num_item;
    for(i = 0; i < num_item; i++)
        item_factor_matrix[i] = data2 + i * num_factors;
    
    //initialize user factor matrix and item factor matrix
    srand((unsigned long)time);
    for(i = 0; i < num_user; i++) {
        for(j = 0; j < num_factors; j++) {
            user_factor_matrix[i][j] = randn(initMean, initStDev);
        }
    }
    for(i = 0; i < num_item; i++) {
        for(j = 0; j < num_factors; j++) {
            item_factor_matrix[i][j] = randn(initMean, initStDev);
        }
    }
    
    int *random_array = malloc(ratingNumber*sizeof(int));
    for(i = 0; i < ratingNumber; i++) random_array[i] = i;
    
    for(k = 0; k < num_iteration; k++) {
        
        shuffle(random_array, ratingNumber);
        for(num = 0; num < ratingNumber; num++) {
            i = random_array[num];
            userID = userIDVector[i];
            itemID = itemIDVector[i];
            rating = ratingVector[i];
            
            //dot product of rows of the two factor matrices
            dot_product = 0.00;
            for(j = 0; j < num_factors; j++) {
                dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
            }
            predicted_rating = dot_product + global_mean;
            //if (predicted_rating > 5) predicted_rating = 5;
            //if (predicted_rating < 1) predicted_rating = 1;
            prediction_error = rating - predicted_rating;
            //printf("%lf\t%lf\t%lf\n",rating, predicted_rating, prediction_error);
            //update user factors and item factors
            for(j = 0; j < num_factors; j++) {
                user_factor_matrix[userID-1][j] += learn_rate * (prediction_error*item_factor_matrix[itemID-1][j] - regularization*user_factor_matrix[userID-1][j]);
                item_factor_matrix[itemID-1][j] += learn_rate * (prediction_error*user_factor_matrix[userID-1][j] - regularization*item_factor_matrix[itemID-1][j]);
            }
            
        }
    }
    
    int *reduced_user_array = malloc(ratingNumber*sizeof(int));
    int *reduced_item_array = malloc(ratingNumber*sizeof(int));
    double *reduced_urating_array = malloc(ratingNumber*sizeof(double));
    
    int c = 0;
    FILE *reduced_base_file = fopen("reduced_base.txt", "w");
    for(num = 0; num < ratingNumber; num++) {
        //i = random_array[num];
        i = num;
        userID = userIDVector[i];
        itemID = itemIDVector[i];
        rating = ratingVector[i];
        
        //dot product of rows of the two factor matrices
        dot_product = 0.00;
        for(j = 0; j < num_factors; j++) {
            dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
        }
        predicted_rating = dot_product + global_mean;
        //if (predicted_rating > 5) predicted_rating = 5;
        //if (predicted_rating < 1) predicted_rating = 1;
        prediction_error = fabs(rating - predicted_rating);
        if(prediction_error < t) {
            fprintf(reduced_base_file, "%d\t%d\t%lf\n", userID, itemID, rating);
        }
        
    }
    
    
    fclose(reduced_base_file);
    fclose(trainFile);
    free(userIDVector);
    free(itemIDVector);
    free(ratingVector);
    free(user_factor_matrix);
    free(item_factor_matrix);
    free(random_array);
    free(reduced_user_array);
    free(reduced_item_array);
    free(reduced_urating_array);
    
}
//-------------------------------------------------------
void reduce_top_N(char *trainFileName, char *testFileName) {
    int ratingNumber = numberOfRatings(trainFileName);//printf("%d\n", ratingNumber);
    int num_user = numberOfUsers(trainFileName, testFileName), num_item = numberOfItems(trainFileName, testFileName);//printf("%d\n",num_user);
    
    int *userIDVector = (int *) malloc(ratingNumber*sizeof(int));
    int *itemIDVector = (int *) malloc(ratingNumber*sizeof(int));
    double *ratingVector = (double *) malloc(ratingNumber*sizeof(double));
    double *prediction_error_array = (double *) malloc(ratingNumber*sizeof(double));

    int no_use;
    FILE *trainFile = fopen(trainFileName,"r");
    
    char line[100];
    int num = 0, i = 0, j = 0 , k = 0;
    double sum = 0.00, global_mean = 0.00;
    while(!feof(trainFile)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),trainFile);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf", &userIDVector[i], &itemIDVector[i], &ratingVector[i]);
        sum += ratingVector[i];
        
        //if (userIDVector[i] > num_user) num_user = userIDVector[i];
        //if (itemIDVector[i] > num_item) num_item = itemIDVector[i];
        
        i++;
    }
    global_mean = sum/ratingNumber;
    
    int userID, itemID;
    double predicted_rating = 0.00, dot_product = 0.00, prediction_error = 0.00;
    double rating, initStDev = 0.1, initMean = 0.00;
    double learn_rate = 0.01, regularization = 0.15;
    int num_iteration = 50, num_factors = 5;
    double **user_factor_matrix = malloc(num_user * sizeof *user_factor_matrix + (num_user * (num_factors * sizeof **user_factor_matrix)));
    double **item_factor_matrix = malloc(num_item * sizeof *item_factor_matrix + (num_item * (num_factors * sizeof **item_factor_matrix)));
    
    
    double *data = user_factor_matrix + num_user;
    for(i = 0; i < num_user; i++)
        user_factor_matrix[i] = data + i * num_factors;
    
    double *data2 = item_factor_matrix + num_item;
    for(i = 0; i < num_item; i++)
        item_factor_matrix[i] = data2 + i * num_factors;
    
    //initialize user factor matrix and item factor matrix
    srand((unsigned long)time);
    for(i = 0; i < num_user; i++) {
        for(j = 0; j < num_factors; j++) {
            user_factor_matrix[i][j] = randn(initMean, initStDev);
        }
    }
    for(i = 0; i < num_item; i++) {
        for(j = 0; j < num_factors; j++) {
            item_factor_matrix[i][j] = randn(initMean, initStDev);
        }
    }
    
    int *random_array = malloc(ratingNumber*sizeof(int));
    for(i = 0; i < ratingNumber; i++) random_array[i] = i;
    
    for(k = 0; k < num_iteration; k++) {
        
        shuffle(random_array, ratingNumber);
        for(num = 0; num < ratingNumber; num++) {
            i = random_array[num];
            userID = userIDVector[i];
            itemID = itemIDVector[i];
            rating = ratingVector[i];
            
            //dot product of rows of the two factor matrices
            dot_product = 0.00;
            for(j = 0; j < num_factors; j++) {
                dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
            }
            predicted_rating = dot_product + global_mean;
            //if (predicted_rating > 5) predicted_rating = 5;
            //if (predicted_rating < 1) predicted_rating = 1;
            prediction_error = rating - predicted_rating;
            //printf("%lf\t%lf\t%lf\n",rating, predicted_rating, prediction_error);
            //update user factors and item factors
            for(j = 0; j < num_factors; j++) {
                user_factor_matrix[userID-1][j] += learn_rate * (prediction_error*item_factor_matrix[itemID-1][j] - regularization*user_factor_matrix[userID-1][j]);
                item_factor_matrix[itemID-1][j] += learn_rate * (prediction_error*user_factor_matrix[userID-1][j] - regularization*item_factor_matrix[itemID-1][j]);
            }
            
        }
    }
    
    int *reduced_user_array = malloc(ratingNumber*sizeof(int));
    int *reduced_item_array = malloc(ratingNumber*sizeof(int));
    double *reduced_urating_array = malloc(ratingNumber*sizeof(double));
    
    int c = 0;
    int N = 100000;
    FILE *reduced_base_file = fopen("reduced_base.txt", "w");
    for(num = 0; num < ratingNumber; num++) {
        //i = random_array[num];
        i = num;
        userID = userIDVector[i];
        itemID = itemIDVector[i];
        rating = ratingVector[i];
        
        //dot product of rows of the two factor matrices
        dot_product = 0.00;
        for(j = 0; j < num_factors; j++) {
            dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
        }
        predicted_rating = dot_product + global_mean;
        prediction_error = fabs(rating - predicted_rating);
        
        prediction_error_array[i] = prediction_error;
    }
    
    double minimum = 1000;
    int location = 0;
    for(c = 0; c < N; c++) {
        minimum = 1000;
        for(i = 0; i < ratingNumber; i++) {
            userID = userIDVector[i];
            itemID = itemIDVector[i];
            rating = ratingVector[i];
            prediction_error = prediction_error_array[i];
        
            if(prediction_error < minimum) {
                minimum = prediction_error;
                location = i;
            }
        }
        prediction_error_array[location] = 1000;
        fprintf(reduced_base_file, "%d\t%d\t%lf\n", userIDVector[location], itemIDVector[location], ratingVector[location]);
        
    }
    
    fclose(reduced_base_file);
    fclose(trainFile);
    free(userIDVector);
    free(itemIDVector);
    free(ratingVector);
    free(user_factor_matrix);
    free(item_factor_matrix);
    free(random_array);
    free(prediction_error_array);
}
//-------------------------------------------------------
void MF_KNN(char *trainFileName, char *testFileName, int num_neighbour, int num_user_train) {
    int ratingNumber = numberOfRatings(trainFileName);//printf("%d\n", ratingNumber);
    int num_user = numberOfUsers(trainFileName, testFileName), num_item = numberOfItems(trainFileName, testFileName);//printf("%d\n",num_user);
    
    int *userIDVector = (int *) malloc(ratingNumber*sizeof(int));
    int *itemIDVector = (int *) malloc(ratingNumber*sizeof(int));
    double *ratingVector = (double *) malloc(ratingNumber*sizeof(double));
    int no_use;
    FILE *trainFile = fopen(trainFileName,"r");
    
    char line[100];
    int num = 0, i = 0, j = 0 , k = 0;
    double sum = 0.00, global_mean = 0.00;
    while(!feof(trainFile)){
        memset(line,0x0,sizeof(line));
        fgets(line,sizeof(line),trainFile);
        if(strlen(line)<=0) break;
        //if(feof(trainFile)) break;
        sscanf(line, "%d\t%d\t%lf", &userIDVector[i], &itemIDVector[i], &ratingVector[i]);
        sum += ratingVector[i];
        
        //if (userIDVector[i] > num_user) num_user = userIDVector[i];
        //if (itemIDVector[i] > num_item) num_item = itemIDVector[i];
        
        i++;
    }
    global_mean = sum/ratingNumber;
    global_mean = 3.582;
    //printf("%d\n",sum);
    int userID, itemID;
    double predicted_rating = 0.00, dot_product = 0.00, prediction_error = 0.00;
    double rating, initStDev = 0.1, initMean = 0.00;
    double learn_rate = 0.01, regularization = 0.15;
    int num_iteration = 40, num_factors = 10;
    double **user_factor_matrix = malloc(num_user * sizeof *user_factor_matrix + (num_user * (num_factors * sizeof **user_factor_matrix)));
    double **item_factor_matrix = malloc(num_item * sizeof *item_factor_matrix + (num_item * (num_factors * sizeof **item_factor_matrix)));
    
    
    double *data = user_factor_matrix + num_user;
    for(i = 0; i < num_user; i++)
        user_factor_matrix[i] = data + i * num_factors;
    
    double *data2 = item_factor_matrix + num_item;
    for(i = 0; i < num_item; i++)
        item_factor_matrix[i] = data2 + i * num_factors;
    
    //array to store number of ratings of each user
    int *num_rating_each_user = malloc(num_user_train * sizeof(int));
    //array to store the mean rating of each user
    double *mean_each_user = malloc(num_user_train * sizeof(double));
    mean_each_user_eval(userIDVector, itemIDVector, ratingVector, num_user_train, ratingNumber, mean_each_user, num_rating_each_user);
    for(i=0;i<num_user_train;i++) printf("%d\n", num_rating_each_user[i]);
    
    //a matrix to store KNN of each user
    int **user_KNN_matrix = malloc(num_user_train * sizeof *user_KNN_matrix + (num_user_train * (num_neighbour
 * sizeof **user_KNN_matrix)));
    
    int *KNN_array = user_KNN_matrix + num_user_train;
    for(i = 0; i < num_user_train; i++)
        user_KNN_matrix[i] = KNN_array + i * num_neighbour;

    user_KNN_file_to_array("userKNN.txt", user_KNN_matrix, num_neighbour, num_user_train);
    
    double *mean_user_KNN_array = malloc(num_user_train * sizeof(double));
    
    mean_user_KNN(user_KNN_matrix, mean_each_user, mean_user_KNN_array, num_rating_each_user, num_neighbour, num_user_train);
    //for(i=0;i<num_user_train;i++) printf("%lf\n", mean_user_KNN_array[i]);
    free(num_rating_each_user);
    free(mean_each_user);
    free(user_KNN_matrix);
    //free(KNN_array);
    
    
    //initialize user factor matrix and item factor matrix
    srand((unsigned long)100);
    for(i = 0; i < num_user; i++) {
        for(j = 0; j < num_factors; j++) {
            user_factor_matrix[i][j] = randn(initMean, initStDev);
        }
    }
    for(i = 0; i < num_item; i++) {
        for(j = 0; j < num_factors; j++) {
            item_factor_matrix[i][j] = randn(initMean, initStDev);
        }
    }
    
    int *random_array = malloc(ratingNumber*sizeof(int));
    for(i = 0; i < ratingNumber; i++) random_array[i] = i;
    shuffle(random_array, ratingNumber);
    for(k = 0; k < num_iteration; k++) {
        for(num = 0; num < ratingNumber; num++) {
            i = random_array[num];
            userID = userIDVector[i];
            itemID = itemIDVector[i];
            rating = ratingVector[i];
            
            //dot product of rows of the two factor matrices
            dot_product = 0.00;
            for(j = 0; j < num_factors; j++) {
                dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
            }
            //predicted_rating = dot_product + global_mean;
            predicted_rating = dot_product + mean_user_KNN_array[userID-1];
            //if (predicted_rating > 5) predicted_rating = 5;
            //if (predicted_rating < 1) predicted_rating = 1;
            prediction_error = rating - predicted_rating;
            //printf("%lf\t%lf\t%lf\n",rating, predicted_rating, prediction_error);
            //update user factors and item factors
            for(j = 0; j < num_factors; j++) {
                user_factor_matrix[userID-1][j] += learn_rate * (prediction_error*item_factor_matrix[itemID-1][j] - regularization*user_factor_matrix[userID-1][j]);
                item_factor_matrix[itemID-1][j] += learn_rate * (prediction_error*user_factor_matrix[userID-1][j] - regularization*item_factor_matrix[itemID-1][j]);
            }
            
        }
    }
    
    //predict ratings listed in testFile
    int ratingNumber_test = numberOfRatings(testFileName);
    int *userIDVector_test = (int *) malloc(ratingNumber_test*sizeof(int));
    int *itemIDVector_test = (int *) malloc(ratingNumber_test*sizeof(int));
    double *ratingVector_test = (double *) malloc(ratingNumber_test*sizeof(double));
    double *predicted_ratingVector_test = (double *) malloc(ratingNumber_test*sizeof(double));
    //FILE *testFile = fopen(testFileName,"r");
    i = 0;
    store_file_to_array(testFileName, userIDVector_test, itemIDVector_test, ratingVector_test);
    
    
    sum = 0.00;
    double mae_sum = 0.00;
    
    FILE *rating_file = fopen("predicted_ratings.txt", "w");
    for(i = 0; i < ratingNumber_test; i++) {
        userID = userIDVector_test[i];
        itemID = itemIDVector_test[i];
        rating = ratingVector_test[i];
        
        dot_product = 0.00;
        for(j = 0; j < num_factors; j++) {
            dot_product += user_factor_matrix[userID-1][j] * item_factor_matrix[itemID-1][j];
        }
        //predicted_ratingVector_test[i] = dot_product + global_mean;
        predicted_ratingVector_test[i] = dot_product + mean_user_KNN_array[userID-1];
        if (predicted_ratingVector_test[i] > 5) predicted_ratingVector_test[i] = 5;
        if (predicted_ratingVector_test[i] < 1) predicted_ratingVector_test[i] = 1;
        
        fprintf(rating_file, "%d\t%d\t%lf\n", userID, itemID, predicted_ratingVector_test[i]);
        
        sum += pow((ratingVector_test[i] - predicted_ratingVector_test[i]), 2);
        mae_sum += fabs(ratingVector_test[i] - predicted_ratingVector_test[i]);
    }
    double rmse = sqrt(sum/ratingNumber_test);
    double mae = mae_sum/ratingNumber_test;
    printf("%lf\t%lf\n", rmse, mae);
    //printf("%lf\n", rmse);
    
    fclose(rating_file);
    fclose(trainFile);
    //fclose(testFile);
    free(userIDVector);
    free(itemIDVector);
    free(ratingVector);
    free(user_factor_matrix);
    free(item_factor_matrix);
    free(random_array);
    free(userIDVector_test);
    free(itemIDVector_test);
    free(ratingVector_test);
    free(predicted_ratingVector_test);
    free(mean_user_KNN_array);
}
//----------------------------------------------------------
