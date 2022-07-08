# Implementation-and-Performance-of-KNN-Algorithm

## Brief Introduction:
1) Project in the domain of Supervised learning.
2) Implemented K-Nearest Neighbors Algorithm in C language, and the KNN Algorithm was applied to the given data sets based on that Accuracy and Standard Deviations were calculated.
3) Observed performance of KNN Algorithm in different cases like Weighted Euclidean, Unweighted Euclidean, Weighted Manhattan, and Unweighted Manhattan distances using graphs while taking x-axis as K-Value and y-axis as Accuracy.

## Full Explanation:
 * We will find Average Accuracy and Standard Deviation for a given data set
 * Average Accuracy is calculated with the accuracies that are calculated(based on comparison of predicted and given class i.e.correctly prediction of class)
 * Predicted values were calculated using KNN(K-Nearest Neighbors) Algorithm
 
 * KNN(K-Nearest Neighbors) Algorithm is a type of supervised ML Algorithm which can be used for both classification as well as regression predictive problems
 * KNN Algorithm is a Lazy learning algorithm and Non-parametric learning algorithm
 * It is Lazy Learning algorithm because it does not have a specialized training phase and uses all the data for training while classification
 * It is Non-parametric Learning Algorithm because it doesn't assume anything about the underlying data
 * KNN uses 'feature similarity' to predict the values of new datapoints
 * The new data point will be assigned a value based on how closely it matches the points in the training set
 
 ### Procedure For Implementation Of Entire Code
 * First we will read the given data set
 * If there are question marks(i.e. unknown data) in the data file than question;marks(i.e. the unknown data) will be assigned
 * After assigning the new data will be stored in "name of the file"_assign.datafile
 * Before assigning
 * If the discrete variables of a column in the namefile of the data file are either letters or words other than in class column then
 * Those letters or words other than class column in the data file are changed to respective sequence numbers of the discrete variables in that column of name file
 * Then after changing new data will be stored in "name of the file"_change.datafile
 * Else if the discrete variables of a column in the namefile of the data file are neither letters nor words other than in class column then
 * The data in data file will be stored as it is without changing anything in "name of the file"_change.datafile
 * If there are question marks in the data file then
 
 #### Assigning Question marks
 * We will read "name of the file"_change.datafile and then store maximum value of each column in an array except class column
 * If the values are continous in respective column of the data file then
 * the question marks in the respective column will be assigned with (maximum value of that column + 1)
 * Else if the discrete values in respective column of the data file are less than one(<1) then
 * the question marks in the respective column will be assigned with (maximum value of that column + 0.1)
 * Else if the discrete values in respective column of the data file are greater than or equal to one(>=1) then
 * the question marks in the respective column will be assigned with (maximum value of that column + 1)
 * then the new data after assigning will be stored in "name of the file"_assign.datafile
 * then that "name of the file"_assign.datafile will be converted into scaled data set:
 * Else if there are no question marks in the given data set then
 * the given data set itself is converted into scaled data set

 * After that we will read the scaled data set
 * Then divide the scaled data set into 'n'(which is given as input from the argument) number of folds randomly
 * Then one off the fold was written in the test data set and remaining(n-1) folds were written in the training data set
 * To avoid biased selection we will find accuracy for n times because for each time a different fold is written in the test data set
 * So to cover every fold it we will be calculated for n times as the number of folds are n
 * After dividing the testing data set and training data set
 * Afterwards we apply the KNN Algorithm
 
 #### Implementation of KNN Algorithm
 * We read the test and training data set
 * We also have a input K value from the argument(i.e the number of nearest data points to be taken) while calculating the K-Nearest Neighbors
 * After that for each point in the test data we have to do the following:-
 * Calculate the distance between test data and each row of training data with the help of any of the method namely Euclidean or Manhattan
 * Now,based on the distance value,sort them in ascending order
 * Next,choose the top K rows from the sorted array
 * Now it will assign a class to the test point(i.e. predicted class) based on most frequent class of the these rows if it is Unweighted
 * Otherwise if Weighted then selection of class will be done based on the distances
 
 * After KNN Algorithm implementation we will get a predicted class for each test data point
 * Then we will compare the each predicted class of test data point with its given class
 * Then we will find the accuracy for which predicted class and given class in the data set is same i.e.correctly prediction
 * Then for avoiding biased calculation we repeat the finding of accuracies 'N'times(which is given as input for the argument)
 * Finally we will find Average Accuracy and Standard Deviation
 
