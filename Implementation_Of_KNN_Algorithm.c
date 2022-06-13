/*
 *We will find Average Accuracy and Standard Deviation for a given data set
 *Average Accuracy is calculated with the accuracies that are calculated(based on comparison of predicted and given class i.e.correctly prediction of class)
 *Predicted values were calculated using KNN(K-Nearest Neighbors) Algorithm
 *
 *KNN(K-Nearest Neighbors) Algorithm is a type of supervised ML Algorithm which can be used for both classification as well as regression predictive problems
 *KNN Algorithm is a Lazy learning algorithm and Non-parametric learning algorithm
 *It is Lazy Learning algorithm because it does not have a specialized training phase and uses all the data for training while classification
 *It is Non-parametric Learning Algorithm because it doesn't assume anything about the underlying data
 *KNN uses 'feature similarity' to predict the values of new datapoints
 *The new data point will be assigned a value based on how closely it matches the points in the training set
 *
 *                             "PROCEDURE FOR IMPLEMENTAION OF ENTIRE CODE"
 *First we will read the given data set
 *
 *If there are question marks(i.e. unknown data) in the data file than question;marks(i.e. the unknown data) will be assigned
 *After assigning the new data will be stored in "name of the file"_assign.datafile
 *Before assigning
 *If the discrete variables of a column in the namefile of the data file are either letters or words other than in class column then
 *Those letters or words other than class column in the data file are changed to respective sequence numbers of the discrete variables in that column of name file
 *Then after changing new data will be stored in "name of the file"_change.datafile
 *Else if the discrete variables of a column in the namefile of the data file are neither letters nor words other than in class column then
 *The data in data file will be stored as it is without changing anything in "name of the file"_change.datafile
 *If there are question marks in the data file then
 *                      "Assigning Question marks"
 *We will read "name of the file"_change.datafile and then store maximum value of each column in an array except class column
 *If the values are continous in respective column of the data file then
 *the question marks in the respective column will be assigned with (maximum value of that column + 1)
 *Else if the discrete values in respective column of the data file are less than one(<1) then
 *the question marks in the respective column will be assigned with (maximum value of that column + 0.1)
 *Else if the discrete values in respective column of the data file are greater than or equal to one(>=1) then
 *the question marks in the respective column will be assigned with (maximum value of that column + 1)
 *then the new data after assigning will be stored in "name of the file"_assign.datafile
 *then that "name of the file"_assign.datafile will be converted into scaled data set
 *Else if there are no question marks in the given data set then
 *the given data set itself is converted into scaled data set
 *
 *After that we will read the scaled data set
 *Then divide the scaled data set into 'n'(which is given as input from the argument) number of folds randomly
 *Then one off the fold was written in the test data set and remaining(n-1) folds were written in the training data set
 *To avoid biased selection we will find accuracy for n times because for each time a different fold is written in the test data set
 *So to cover every fold it we will be calculated for n times as the number of folds are n
 *After dividing the testing data set and training data set
 *Afterwards we apply the KNN Algorithm
 *
 *                           "Implementation of KNN Algorithm"
 *we read the test and training data set
 *We also have a input K value from the argument(i.e the number of nearest data points to be taken) while calculating the K-Nearest Neighbors
 *After that for each point in the test data we have to do the following:-
 *Calculate the distance between test data and each row of training data with the help of any of the method namely Euclidean or Manhattan
 *Now,based on the distance value,sort them in ascending order
 *Next,choose the top K rows from the sorted array
 *Now it will assign a class to the test point(i.e. predicted class) based on most frequent class of the these rows if it is Unweighted
 *Otherwise if Weighted then selection of class will be done based on the distances
 *
 *After KNN Algorithm implementation we will get a predicted class for each test data point
 *Then we will compare the each predicted class of test data point with its given class
 *Then we will find the accuracy for which predicted class and given class in the data set is same i.e.correctly prediction
 *Then for avoiding biased calculation we repeat the finding of accuracies 'N'times(which is given as input for the argument)
 *Finally we will find Average Accuracy and Standard Deviation
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//Input was given as arguments of main function
int main(int argc,char* argv[])
{

    FILE *fte,*ftr,*file,*sfile,*ofile,*nfile,*cfile,*afile,*checkfile;

    char *colptr,*fileptr;

    char *fp,*ft,*ptr;

    char namefile[50],changefile[50],assignfile[50],checkarr[50];

    char ch,cha,array[10];

    int lte=0,ltr=0,dim=0,k=0,dig=0,p=0,s=0,u=0,v=0,kvalue,l=0,q=0,im=0,imm=0,maxx=0,nvalue,nacc=0,nparts,b=0,g=0;

    int i=0,j=0,m,n=0,r,t,w,x,y,z,comp,comma=0,ij=0,ltra=0,aacc=0,alphabets=0,questionmark=0;

    float corr=0,*acc,dist,effdis=0,min,minn,number,scalednum,totsum=0,avacc,tdiff,tsum=0,sdiv,max=0;

    int a=0,count=0,d=0,f=0;

    //checking whether input having required number of arguments or not
    if(argc!=7)
    {
        printf("WRONG INPUT\n");
        printf("Input should be in the form %s <Filename> <Kvalue> <Type of distance> <Number of times accuracy should be calculated> <Number of folds> <Type of class selection Weighted/Unweighted>\n",argv[0]);
        exit(1);  //if the number of arguments are not of required number then program exits
    }

    strcpy(checkarr,argv[1]);   //copies the string in argv[1] to checkarr array

    strcat(checkarr,".data");

    checkfile=fopen(checkarr,"r");  //opening file given by checkarr in reading format

    //this checking is to know whether there are question marks in the data file or not
    //Also to know that whether the discrete variables are letters or words or numbers
    //if there are question marks in the file then the "questionmark" int variable is assigned to one else it will be zero only
    //if there are either letters or words in the data file other than class column then then "alphabets" int variable is assigned to one else it will be zero only
    while(!feof(checkfile))
    {
        ch=fgetc(checkfile);

        if(i==0 && ch==',')
            j++;

        if(ch==',')
            k++;

        if(i>=1 && k<j)
        {
            //checking for question marks,also checking for either letters or words in the data file
            if(ch=='?')
                questionmark=1;
            else if(ch>='a' && ch<='z' || ch>='A' && ch<='Z')
                alphabets=1;
        }

        if(questionmark==1 && alphabets==1)
            break;

        if(ch=='\n')
        {
            i++;
            k=0;
        }

    }

    i=0;
    j=0;
    k=0;
    fclose(checkfile);

    //"questionmark" int value one means that there are question marks in the data file else no question marks
    //Also "alphabets" int value one means that there are letters or words in the data file else no letters or words
    if(questionmark==0 && alphabets==0)
    {
        strcat(argv[1],".data"); //strcat function will do string concatenation
        file=fopen(argv[1],"r"); //opening the given data file in reading format
    }
    else if(questionmark==1 && alphabets==0 || questionmark==1 && alphabets==1 || questionmark==0 && alphabets==1)
    {
        strcpy(namefile,argv[1]);   //copies the string in argv[1] to namefile array

        strcpy(changefile,argv[1]);    //copies the string in argv[1] to changefile array

        strcpy(assignfile,argv[1]);    //copies the string in argv[1] to assignfile array

        strcat(assignfile,"_assign.data");

        strcat(argv[1],".data");

        strcat(namefile,".names");

        strcat(changefile,"_change.data");

        cfile=fopen(changefile,"w");    //opening file given by changefile array in writing format

        if(cfile==NULL)
        {
            printf("The file %s cannot be opened\n",changefile);
            exit(2)   ;
        }
        else
            printf("The file %s successfully opened\n",changefile);

        nfile=fopen(namefile,"r")  ;    //opening file given by namefile array in reading format

        if(nfile==NULL)
        {
            printf("The file %s cannot be opened\n",namefile);
            exit(3)   ;
        }
        else
            printf("The file %s successfully opened\n",namefile);

        ofile=fopen(argv[1],"r");   //opening file given by argv[1] in reading format

        if(ofile==NULL)
        {
            printf("The file %s cannot be opened\n",argv[1]);
            exit(4)   ;
        }
        else
            printf("The file %s successfully opened\n",argv[1]);

        int i=0,comma=0,letters=0,j=0,semicolon=0,ncomma=0,namelines=0,filelines=0,nmaxcomma=0,maxcomma=0,k=0,z=0;
        char ch,nchr;

        //reading original file(ofile) then finding number of lines in the given data file and assigning to "filelines" int variable
        //Also finding dimension of the data point which is assigned to maxcomma
        while(!feof(ofile))
        {
            ch=fgetc(ofile);

            if(comma>maxcomma && ch=='\n')
                maxcomma=comma+1;   //finding dimension of the data point

            if(ch=='\n')
            {
                filelines++;    //finding number of lines in the given data file
                comma=0;
            }

            if(ch==',')
                comma++;
        }

        comma=0;

        rewind(ofile);

        char filedata[filelines][maxcomma][50],changefiledata[filelines][maxcomma][50];

        //reading the given data file and storing the data in "filedata" 3D array
        //1st dimension of "filedata" is for row number and 2nd dimension of "filedata" is for column number and 3rd dimension is to store data of respective row and column
        //we know that column value changes when crossing comma(',')
        //Also we know that row value changes when crossing end of line('\n')
        while(!feof(ofile))
        {
            ch=fgetc(ofile);

            if(ch=='\n')
            {
                filedata[j][comma][z]='\0';

                comma=0;

                j++;

                z=0;

                continue;
            }

            if(ch==',')
            {
                filedata[j][comma][z]='\0';

                comma++;

                z=0;

                continue;
            }

            filedata[j][comma][z]=ch; //storing data of respective row and column

            z++;

        }

        rewind(ofile);

        j=0;

        comma=0;

        z=0;

        //reading namefile(nfile) of the given data file then finding number of lines in namefile and assigning to "namelines" int variable
        //Also finding maximum number of discrete variables in one column with maximum discrete variables in overall namefile
        while(!feof(nfile))
        {
            nchr=fgetc(nfile);

            if(comma>nmaxcomma && nchr=='\n')
                nmaxcomma=comma+1;

            if(nchr=='\n')
            {
                namelines++; //finding number of lines in the given data file
                comma=0;
            }
            if(nchr==',' && namelines>0)
                comma++;
        }

        rewind(nfile);

        comma=0;

        char ncoldata[namelines-1][nmaxcomma][50];

        j=0;

        nchr=fgetc(nfile);

        //Knowing whether column values are "continuous" or "discrete variables"
        //If they are continuous then storing "continuous" in "ncoldata" array with respective column number
        //If they are discrete variables then storing those discrete variables in respective column number
        //By observing both we data file and name file we can understand that
        //Here "j" represents column number in the data file which will become row number in name file
        while(!feof(nfile))
            {
                    //Here we are taking j>0 because if we observe namefile we can understand that first row contains classes
                    //we know that at this point there is no use of storing classes because we will not change values of classes in the data file
                    while(nchr!='.' && nchr!='\n' && j>0)
                    {
                        //After watching namefile we can understand that discrete variables are after crossing semicolon in the name file
                        //so if we reached semicolon then changing "semicolon" int value to one else it will be zero
                        if(nchr==':')
                                semicolon=1;

                        if(nchr==',')
                            {
                                comma++;
                                z=0;
                            }

                        //"semicolon" int value one means that it crossed semicolon and it is time to store accordingly
                        if(semicolon==1 && nchr>='a' && nchr<='z' || semicolon==1 && nchr>='A' && nchr<='Z' || semicolon==1 && nchr>='0' && nchr<='9')
                        {
                            ncoldata[j-1][comma][z]=nchr;   //storing "continuous" if the values in the column are continous else storing discrete variables of respective column
                            z++;
                        }

                            nchr=fgetc(nfile);

                    }

                    if(nchr=='\n')
                    {
                        j++;    //here "j" represents column number in the data file which will become row number in name file
                    }

                    semicolon=0;

                    comma=0;

                    z=0;

                    nchr=fgetc(nfile);
            }

        j=0;

        i=0;

        comma=0;

        z=0;

        rewind(nfile);

        //If values of the column in the data file are continuous then the values are stored as it is and printed in "name of the file"_change.datafile as it is
        //Else if the values in the data file are discrete variables
        //And if discrete variables are either letters or words then those are replaced with respective sequence number of discrete variables starting with one in name file of respective column number(of data file)
        //i.e. if first variable of respective column number(of data file) in name file is occurred in data file then that variable should be replaced with one
        //if second variable of respective columnn number(of data file) in name file is occurred in data file then that variable should be replaced with two
        //similarly sequencially respective variable of respective column number(of data file)in name file if occurred in data file then that variable should be replaced with respective sequence number
        //After changing new data will be stored in "name of the file"_change.datafile
        //Else if discrete variables are neither letter nor words then the values are stored as it is and printed in "name of the file"_change.datafile as it is
        for(i=0;i<filelines;i++)
        {
            for(j=0;j<maxcomma-1;j++)
            {
                //if values of column are continous then data will be printed in "name of the file"_change.datafile as it is without changing
                //And also stored as it is without changing
                if(strcmp(ncoldata[j][0],"continuous")==0)
                {
                        fprintf(cfile,"%s,",filedata[i][j]);

                        strcpy(changefiledata[i][j],filedata[i][j]);
                }
                else if(ncoldata[j][0][0]>='a' && ncoldata[j][0][0]<='z' || ncoldata[j][0][0]>='A' && ncoldata[j][0][0]<='Z')
                {
                    //if value in data file is question mark then it will be printed and stored as it is
                    if(strcmp(filedata[i][j],"?")==0)
                    {
                        fprintf(cfile,"%s,",filedata[i][j]);

                        strcpy(changefiledata[i][j],filedata[i][j]);
                    }
                    else
                        {
                            for(k=0;k<nmaxcomma;k++)
                            {
                                //checking which sequence variable(of namefile) of respective column(of data file) is occurred in data file
                                if(strcmp(ncoldata[j][k],filedata[i][j])==0)
                                {
                                    fprintf(cfile,"%d,",k+1);//printing respective sequence number of sequence variable(of namefile)

                                    sprintf_s(changefiledata[i][j],50,"%d",k+1);    //storing the number to replace the letter or word in data file

                                    break;
                                }
                            }
                        }
                }
                else
                {
                    fprintf(cfile,"%s,",filedata[i][j]); //printing as it if the discrete values of respective column are numbers (i.e. neither letters nor words)

                    strcpy(changefiledata[i][j],filedata[i][j]); //storing
                }

            }

            fprintf(cfile,"%s\n",filedata[i][j]);

            strcpy(changefiledata[i][j],filedata[i][j]);

        }


        fclose(ofile);

        fclose(nfile);

        fclose(cfile);

        /*
         *If there are question marks in the data file then
         *We will read "name of the file"_change.datafile and then store maximum value of each column in an array except class column
         *If the values are continous in respective column of the data file then
         *the question marks in the respective column will be assigned with (maximum value of that column + 1)
         *Else if the discrete values in respective column of the data file are less than one(<1) then
         *the question marks in the respective column will be assigned with (maximum value of that column + 0.1)
         *Else if the discrete values in respective column of the data file are greater than or equal to one(>=1) then
         *the question marks in the respective column will be assigned with (maximum value of that column + 1)
         *then the new data after assigning will be stored in "name of the file"_assign.datafile
         */
        if(questionmark==1 && alphabets==0 || questionmark==1 && alphabets==1)
        {
                z=0;

                char colmaxvalue[maxcomma][50];

                float filenumber,colnumber;

                //Finding maximum value of respective column and storing them in "colmaxvalue" array
                for(j=0;j<maxcomma-1;j++)
                {
                    for(i=0;i<filelines;i++)
                    {
                        if(strcmp(changefiledata[i][j],"?")==0)
                            continue;
                        else if(z==0)
                        {
                            strcpy(colmaxvalue[j],changefiledata[i][j]);
                            z=1;
                        }
                        else
                        {
                            filenumber=strtod(changefiledata[i][j],&fileptr);   //strtod function converts the string pointed to by the argument array to a floating point number
                                                                                //Then the floating point number is stored in the location referred by 'fileptr'

                            colnumber=strtod(colmaxvalue[j],&colptr);

                            if(colnumber<filenumber)
                                strcpy(colmaxvalue[j],changefiledata[i][j]);

                        }
                    }

                    z=0;

                }

                i=0;

                j=0;

                //maximum values which are stored in "colmaxvalue" array will be incremented accordingly for purpose of assigning question marks
                //we can understand that if maximum value of respective column is less than one(<1) then all the values in that column are less than one(<1)
                //so the maximum value of that column will be incremented by 0.1
                //Else if maximum value of respective column is greater than or equal to one(>=1)
                //then the maximum value of that column will be incremented by 1
                for(j=0;j<maxcomma-1;j++)
                {
                    colnumber=strtod(colmaxvalue[j],&colptr) ;

                    if(colnumber<1)
                        colnumber=colnumber+0.1;
                    else
                        colnumber=colnumber+1;

                    sprintf_s(colmaxvalue[j],50,"%.4f",colnumber); //storing those incremented values in "colmaxvalue" for assigning question marks in data file
                }

                afile=fopen(assignfile,"w");    //opening file given by assignfile array in writing format

                //assigning i.e. printing all maximum values of respective column in respective places of question marks
                for(i=0;i<filelines;i++)
                {
                for(j=0;j<maxcomma-1;j++)
                    {
                        if(strcmp(changefiledata[i][j],"?")==0)
                            fprintf(afile,"%s,",colmaxvalue[j]);
                        else
                        {
                            filenumber=strtod(changefiledata[i][j],&fileptr);

                            fprintf(afile,"%.4f,",filenumber);
                        }
                    }

                    fprintf(afile,"%s\n",changefiledata[i][j]);
                }
                fclose(afile);

                file=fopen(assignfile,"r"); //If question marks are there in the data file then file given by assignfile array will be opened in reading format and assigned to "file" pointer
        }
        else
           file=fopen(changefile,"r"); //If question marks are not there in the data file then file given by changefile array will be opened in reading format and assigned to "file" pointer

    }

    comma=0;
    i=0;
    j=0;
    k=0;
    z=0;

    nvalue=atoi(argv[4]);   //atoi function takes a string(which represents an integer)as an argument and returns its value of type int
                            //We know that here argv[4] gives number of times accuracy should be calculated which is now assigned to 'nvalue'

    nparts=atoi(argv[5]);   //We know that here argv[5] gives number of folds which is now assigned to 'nparts'

    acc=(float*)malloc((nvalue*nparts)*sizeof(float));  //'acc'pointer to store all different accuracies that are calculated

    sfile=fopen("scaled.data","w"); //opening a new file called scaled.data for writing the scaled data of given data set
            if(sfile==NULL)
            {
                printf("The scaled file cannot be opened\n");
                exit(5) ;
            }
            else
            printf("The scaled file successfully opened\n");

            if(file==NULL)
                {
                    printf("The file cannot be opened\n");
                    exit(6)   ;
                }
            else
                printf("The file successfully opened\n");

            kvalue=atoi(argv[2]);   //we know that argv[2] gives the number of nearest data points to be taken while implementing KNN algorithm
                                    //Now it was assigned to 'kvalue'

            float sort[kvalue];     //'sort' is an array made for storing the K nearest data points in ascending order

            ch=fgetc(file); //fgetc function is used to read the character from the file
                            //After reading the character,the file pointer is advanced to next character

            //from this we know the dimension of the given each data point
            while(ch!='\n')
                {
                    if(ch==',')
                       a++;

                    ch=fgetc(file);
                }
            a--;
            rewind(file);       //rewind function will sets the file position to the beginning of the file

            float *maxi;

            float *mini;

            maxi=(float*)malloc((a+1)*sizeof(float));     //'maxi' is a float pointer of size 'a' created to store the maximum values of each column

            mini=(float*)malloc((a+1)*sizeof(float));     //'mini' is a float pointer of size 'a' created to store the minimum values of each column

            //Finding maximum and minimum values from each columns(without class column)
            //And storing them in 'maxi' and 'mini' pointers within their respective column number
            while(!feof(file))
                {
                    ch=fgetc(file);

                    if((ch>='0'&&ch<='9'||ch=='.') && i<=a)
                    {
                        array[f]=ch;
                        f++;
                    }
                    else if(ch==',' && i<=(a+1))
                    {
                        number=strtod(array,&ptr);      //strtod function converts the string pointed to by the argument array to a floating point number
                                                        //Then the floating point number is stored in the location referred by 'ptr'

                        memset(array,0,strlen(array));  //memset function is used to fill a block of memory with a particular value
                                                        //Here it is filled with zero

                        if(count<=a)
                        {
                            maxi[d]=number;

                            mini[d]=number;

                            count++;
                        }
                        else if(maxi[d]<number)
                            maxi[d]=number;
                        else if(mini[d]>number)
                             mini[d]=number;

                        d++;
                        f=0;
                        i++;
                    }
                    else if(ch=='\n')
                    {
                        memset(array,0,strlen(array));

                        d=0;
                        i=0;
                    }
                    else if(i==(a+1))
                    {
                        continue;
                    }
                }
            f=d=0;
            i=0;

            rewind(file);

            /*After finding maximum and minimum values of each column
             *we will find scaled number of each dimension of each data point in the data set
             *scaled number for a number is calculated using this formula:
             *(number-mini[d])/(maxi[d]-mini[d])
             *where d is the column number to which the number belongs to
             *After finding the scaled number to every dimension of every data point in the data set
             *In the same sequence the scaled number will be printed in the new scaled data file
             */
            while(!feof(file)) //here feof means that end of the file it returns one if it ends and zero if not
                {
                     ch=fgetc(file);

                    if((ch>='0'&&ch<='9'||ch=='.') && i<=a)
                    {
                        array[f]=ch;
                        f++;
                    }
                    else if(ch==',' && i<=(a+1))
                    {
                        number=strtod(array,&ptr);

                        memset(array,0,strlen(array));

                        if(maxi[d]==mini[d])
                            scalednum=number;
                        else
                            scalednum=(number-mini[d])/(maxi[d]-mini[d]);     //Here scaled number of each dimension of every data points are calculated

                        fprintf(sfile,"%f,",scalednum);       //fprintf function prints the scaled number into the scaled data file in same order    
                    
                        d++;  //'d' will say the column number
                        f=0;
                        i++;

                    }
                    else if(ch=='\n')
                    {
                            fprintf(sfile,"%c",ch);

                            memset(array,0,strlen(array));

                            d=0;
                            i=0;
                    }
                    else if(i==(a+1))   //It is used to print the class name of each data point as same order as given in data set
                        fprintf(sfile,"%c",ch);
                }

            i=0;

            fclose(sfile);  //fclose function will closes the file which is pointed by the file pointer

            fclose(file);

            sfile=fopen("scaled.data","r");     //Here scaled.data file is opened in reading format

            //Checking whether scaled.data file opened successfully or not in reading format
            if(sfile==NULL)
                {
                    printf("scaled data file doesnot opened\n");
                    exit(7);
                }
            else
                printf("scaled data file is successfully opened\n");

            int nch=0,lnch=0,nlines=0;

            while(!feof(sfile))
                    {
                        nch++;   //number of characters in a line

                        ch=fgetc(sfile);

                        if(ch=='\n')
                        {
                            nlines++;     //number of lines in the given data set

                            if(nch>lnch)  //checking for large number of characters for data point
                                lnch=nch;

                            nch=0;
                        }
                    }

            rewind(sfile);

            char parts[nparts][(nlines/nparts)+1][lnch+1];  //'parts' is a 3D character Array
                                                            //It is created as 3D array because
                                                            //One says which fold it belongs and one says the number of lines in each fold and other to store the data point values
                                                            //Here 'parts' array is made of 'nparts' size because to store 'nparts' folds
                                                            //For every fold equally and randomly the total lines are distributed

            int partlines[nparts],nl=0,c,e,h,tes,tra,trai,linleft=0;    //'partlines' int array is made to say the number of lines in each fold

        //calculation of accuracy for 'nvalue' times
        for(aacc=0;aacc<nvalue;aacc++)
                {
                    linleft=0;

                    memset(partlines,0,sizeof(partlines));

                    printf("%d nlines\n",nlines);

                    /*
                     *Here we are going to divide the data set into 'nparts' folds randomly
                     *By storing the each data point to a random fold number in 'parts' 3D array
                     *parts array is created in such a way that to store the each data point randomly to a random fold without bias
                     */
                    while(nl<nlines)
                        {
                            /*
                             *If in case after dividing equally at last if there are data points left which cannot be equally distributed
                             *Then data points will be distributed successively from first fold
                             *i.e.first data point will be added to first fold next data point will be added to next fold(if data point is left)up to so on......
                             *This will happen if remainder is other than zero when 'nlines' is divided with 'nparts'
                             *i.e. if total lines cannot be distributed equally to total folds
                             */

                            if(nl>=(nlines-(nlines%nparts)))
                                    {
                                            ch=fgetc(sfile);

                                        for(e=0;ch!='\n';e++)
                                        {
                                            parts[linleft][partlines[linleft]][e]=ch;

                                            ch=fgetc(sfile);
                                        }

                                        if(ch=='\n')
                                            parts[linleft][partlines[linleft]][e]=ch;

                                        partlines[linleft]++;        //This will increment number of lines of the respective fold after the data point is added to that fold

                                        nl++;       //this 'nl' int value says how many lines are already distributed

                                        linleft++;
                                    }
                            else
                                {
                                    c=(rand()%nparts);      //This will decide to which fold the data point should be added

                                    if(partlines[c]==(nlines/nparts))   //This will helps in saying the upper limit reached to this fold for equally division of folds
                                        continue;                       //Then no more data points will be added to this fold as it continues

                                    ch=fgetc(sfile);

                                    for(e=0;ch!='\n';e++)
                                    {
                                        parts[c][partlines[c]][e]=ch;

                                        ch=fgetc(sfile);
                                    }

                                    if(ch=='\n')
                                        parts[c][partlines[c]][e]=ch;

                                    partlines[c]++;         //This will increment number of lines of the respective fold after the data point is added to that fold

                                    nl++;       //this 'nl' int value says how many lines are already distributed
                                }
                        }
                        rewind(sfile);

                        e=0;

                    //Calculation of accuracy 'nparts' times because for avoiding bias we will choose different fold for each time as testing data file
                    for(h=0;h<nparts;h++)
                            {
                                ftr=fopen("training.data","w"); //opening the training.data file in writing format

                                fte=fopen("testing.data","w");  //opening the testing.data file in writing format

                                if(ftr==NULL)
                                    {
                                        printf("training data file doesnot opened\n");
                                        exit(8);
                                    }
                                else
                                    printf("training data file is successfully opened\n");

                                if(fte==NULL)
                                    {
                                        printf("testing data file doesnot opened\n");
                                        exit(9);
                                    }
                                else
                                    printf("testing data file is successfully opened\n");

                                //In this loop we are going to write data points of one fold into testing data file
                                //For first time of finding accuracy we will write first fold data points into testing data file
                                //For next time of finding accuracy a different fold successively is taken and write its data points into testing data file
                                for(tes=0;tes<partlines[h];tes++)
                                        {
                                            //Here 'h' indicates which fold number is taken into testing data file
                                            //'tes' indicates which line(i.e.which data point) of the fold
                                            ch=parts[h][tes][e];

                                            while(ch!='\n')
                                                {
                                                    fprintf(fte,"%c",parts[h][tes][e]);

                                                    e++;

                                                    ch=parts[h][tes][e];
                                                }

                                            fprintf(fte,"%c",parts[h][tes][e]);

                                            e=0;
                                        }

                                e=0;

                                //In this loop we will write all data points of all folds into training data file
                                //Except the data points of one fold which were already written in testing data file
                                //'tra' indicates the fold number
                                //'trai' indicates which line of the fold
                                for(tra=0;tra<nparts;tra++)
                                        {
                                            //This 'if' condition is checked for avoiding rewriting of data points of a fold which were already written in testing data file
                                            if(tra==h)
                                                continue;
                                            else
                                            {
                                                for(trai=0;trai<partlines[tra];trai++)
                                                            {
                                                                ch=parts[tra][trai][e];

                                                                while(ch!='\n')
                                                                    {
                                                                        fprintf(ftr,"%c",parts[tra][trai][e]);

                                                                        e++;

                                                                        ch=parts[tra][trai][e];
                                                                    }

                                                                fprintf(ftr,"%c",parts[tra][trai][e]);

                                                                e=0;
                                                            }
                                            }
                                        }

                                fclose(fte);

                                fclose(ftr);

                                //Now after closing the testing and training data files in writing format
                                //Both data files now are opened in reading format
                                fte=fopen("testing.data","r");

                                ftr=fopen("training.data","r");

                                if(fte==NULL || ftr==NULL)
                                    {
                                        printf("files cannot be opened\n");
                                        exit(10);
                                    }
                                else
                                    printf("testing and training data files sucessfully opened\n");

                                //Finding number of lines in the testing data file
                                while(!feof(fte))
                                    {
                                            ch=fgetc(fte);

                                            if(ch=='\n')
                                            lte++;
                                    }

                                printf("%d number of testing file lines\n",lte);

                                rewind(fte);

                                //Finding number of lines in the training data file
                                while(!feof(ftr))
                                        {
                                            ch=fgetc(ftr);

                                            if(ch=='\n')
                                            ltr++;
                                        }

                                rewind(ftr);

                                printf("%d number of training file lines\n",ltr);

                                ch=fgetc(fte);

                                //Finding dimension and number of digits in each dimension of the data point of testing data file
                                while(ch!='\n')
                                        {
                                            if(ch==',')
                                                dim++;

                                            if(dim==0)
                                                dig++;

                                            ch=fgetc(fte);
                                        }

                                rewind(fte);

                                char classes[lte+ltr][30],dummy[1][30];     //'classes' character array is created for storing different classes of given data set if classes exists

                                //In this while loop we will collect all different classes in the testing data file
                                while(!feof(fte))
                                    {
                                            ch=fgetc(fte);

                                            if(ch=='\n')
                                                {
                                                    dummy[0][q]='\0';
                                                    q=0;

                                                    ij=0;

                                                    if(l!=0)
                                                        {
                                                        //Here 'l' indicates number of different classes in the data set up to now
                                                        for(im=0;im<l;im++)
                                                                {
                                                                    //In this loop we will compare the 'dummy' class with 'classes' array so that:
                                                                    //if the 'dummy' class is different from classes that are present in 'classes' array then that 'dummy' class will be added to the 'classes' array
                                                                    //we will do this to get different classes in the given data set
                                                                    comp=strcmp(dummy[0],classes[im]); //strcmp is a function which is used to compare two strings

                                                                    if(comp==0)
                                                                        break;
                                                                    else if(im==(l-1))
                                                                    {
                                                                        strcpy(classes[l],dummy[0]);  //strcpy is a function which is used to copy the second pointed string to the first pointed string
                                                                        l++;
                                                                    }

                                                                }
                                                        }
                                                    else
                                                        {
                                                            strcpy(classes[l],dummy[0]);
                                                            l++;
                                                        }

                                                    //'dummy' character array is made empty after comparing and copying(if different class is present) process was done each time
                                                    for(imm=0;imm<30;imm++)
                                                        dummy[0][imm]=NULL;

                                                }

                                            //This 'if' condition is made for taking the class of a data point into dummy character array
                                            //We know that when we are reading a data point from a file then we get class of the data point at some point of time if:
                                            //the column number is equal to dimension of the data point
                                            //That's what we are checking in this 'if' condition
                                            if(ij==dim)
                                                {
                                                    dummy[0][q]=ch;
                                                    q++;
                                                }

                                            if(ch==',')
                                                ij++;      //'ij' indicates column number of the data set

                                    }
                                rewind(fte);

                                q=0;

                                im=0;

                                ij=0;

                                //In this loop we will collect classes that are different and that are not in the testing data file from the training data file into 'classes' array itself
                                //In this loop all the variables indicates as same as that are used in finding different classes in testing data file
                                while(!feof(ftr))
                                        {
                                                ch=fgetc(ftr);

                                                if(ch=='\n')
                                                    {
                                                        dummy[0][q]='\0';

                                                        q=0;

                                                        ij=0;

                                                        //Here 'l' indicates number of different classes in the data set
                                                        for(im=0;im<l;im++)
                                                                {
                                                                    //In this loop we will compare the 'dummy' class with 'classes' array so that:
                                                                    //if the 'dummy' class is different from classes that are present in 'classes' array then that 'dummy' class will be added to the 'classes' array
                                                                    //we will do this to get different classes in the given data set
                                                                    comp=strcmp(dummy[0],classes[im]);

                                                                    if(comp==0)
                                                                        break;
                                                                    else if(im==(l-1))
                                                                    {
                                                                        strcpy(classes[l],dummy[0]);
                                                                        l++;
                                                                    }
                                                                }

                                                        //'dummy' character array is made empty after comparing and copying(if different class is present) process was done each time
                                                        for(imm=0;imm<30;imm++)
                                                            dummy[0][imm]=NULL;

                                                    }

                                                //This 'if' condition is made for taking the class of a data point into dummy character array
                                                //We know that when we are reading a data point from a file then we get class of the data point at some point of time if:
                                                //the column number is equal to dimension of the data point
                                                //That's what we are checking in this 'if' condition
                                                if(ij==dim)
                                                    {
                                                        dummy[0][q]=ch;
                                                        q++;
                                                    }

                                                if(ch==',')
                                                ij++;        //'ij' indicates column number of the data set

                                        }

                                rewind(ftr);

                                char trclass[ltr][30],teclass[lte][30],preteclass[lte][30],same[lte];       //'trclass' array stores classes of each data point in same order of the training data file
                                                                                                            //'teclass' array stores classes of each data point in same order of the testing data file
                                                                                                            //'preteclass' array stores predicted class of each data point in same order of testing data file
                                                                                                            //'same' array is created to store '1' if predicted class and given class are same for a each specific data point else '0' will be stored to each in same order of testing data file

                                //In this loop we will collect different classes into 'trclass' array from training data file
                                for(u=0;u<ltr;u++)
                                        {
                                            ch=fgetc(ftr);

                                            while(ch!='\n')
                                                    {
                                                        if(comma==dim)
                                                        {
                                                        trclass[u][v]=ch;
                                                        v++;
                                                        }

                                                        if(ch==',')
                                                            comma++;

                                                        ch=fgetc(ftr);
                                                    }
                                            trclass[u][v]=NULL;

                                            v=0;

                                            comma=0;
                                        }

                                rewind(ftr);

                                //In this loop we will collect different classes into 'teclass' array from testing data file
                                for(u=0;u<lte;u++)
                                            {
                                                ch=fgetc(fte);

                                                while(ch!='\n')
                                                        {
                                                            if(comma==dim)
                                                                {
                                                                    teclass[u][v]=ch;
                                                                    v++;
                                                                }

                                                            if(ch==',')
                                                                comma++;

                                                            ch=fgetc(fte);
                                                        }

                                                teclass[u][v]=NULL;

                                                v=0;

                                                comma=0;
                                            }

                                rewind(fte);

                                char arr[dig]; //It is created to store every digit of each dimension value of each data point

                                float occurclass[l];    //'occurclass' array is made to store the count of occurrence of each type of class

                                memset(occurclass,0,sizeof(occurclass));

                                memset(arr,0,strlen(arr));

                                float te[dim],tr[dim],effdist[lte][ltr]; //'te' array is made to store all dimension values of each data point of testing data set
                                                                        //'tr' array is made to store all dimension values of each data point of training data set

                                //In this loop we implement KNN(K-Nearest Neighbors) algorithm
                                while(i<lte)
                                    {
                                        //we will calculate the distance between test data and each row of training data with the help of any of the method namely Euclidean or Manhattan for each time
                                        //'i' indicates line number of testing data file that we are going to read now
                                        ch=fgetc(fte);      //Reading character from the testing data file

                                        //In this loop we collect each dimension value(a float number) of each data point of testing data file
                                        while(ch!='\n')
                                                {
                                                    if((ch=='.')|| (ch>='0' && ch<='9'))
                                                            {
                                                                arr[j]=ch;
                                                                j++;
                                                            }
                                                    else if(ch==',')
                                                            {
                                                                te[k]=strtod(arr,&fp)  ; //strtod function will converts a sequence of characters representing a floating point value to a double
                                                                j=0;
                                                                k++; //'k' represents that which column in the testing data set it belongs
                                                            }

                                                    ch=fgetc(fte);
                                                }

                                        k=0;

                                        j=0;

                                        for(m=0;m<ltr;m++)
                                                {
                                                    ch=fgetc(ftr);      //Reading character from training data file

                                                    //In this loop we collect each dimension value(a float number) of each data point of training data file
                                                    while(ch!='\n')
                                                            {
                                                            if(ch=='.'||(ch>='0' && ch<='9'))
                                                                    {
                                                                        arr[n]=ch;
                                                                        n++;
                                                                    }
                                                            else if(ch==',')
                                                                    {
                                                                        tr[p]=strtod(arr,&ft);
                                                                        n=0;
                                                                        p++;      //'p' represents that which column in the training data set it belongs
                                                                    }

                                                                ch=fgetc(ftr);
                                                            }

                                                    p=0;


                                                    n=0;

                                                    //We had a input as argument from main function that contains which type of distance we have to choose i.e either Euclidean or Manhattan
                                                    //If the type of distance is Euclidean then distance is calculated using the formula:
                                                    //square root of(sum of squares of(difference between each dimension value of data points(i.e.one from testing data file and one from training data file)))
                                                    //Else if type of distance is Manhattan then distance is measured along axes of right angles
                                                    //i.e.sum of(Mod of difference between each dimension value of data points(i.e.one from testing data file and one from training data file))

                                                    if(strcmp(argv[3],"Euclidean")==0)      //This will be work if type of distance is Euclidean
                                                                    {
                                                                        for(r=0;r<=dim;r++)
                                                                                {
                                                                                    if(r<dim)
                                                                                        {
                                                                                        dist=te[r]-tr[r];        //difference between each dimension value of data points(i.e.one from testing data file and one from training data file)

                                                                                        dist=dist*dist;

                                                                                        effdis=effdis+dist;      //sum of squares of(difference between each dimension value of data points(i.e.one from testing data file and one from training data file))
                                                                                        }
                                                                                    else
                                                                                        {
                                                                                            effdist[i][m]=sqrt(effdis);    //calculation of square root of(sum of squares of(difference between each dimension value of data points(i.e.one from testing data file and one from training data file)))
                                                                                                                        //Then its value is assigned to 'effdist' array to its respective testing data file line number and training data file line number
                                                                                                                        //i.e.here 'i' indicates testing data file line number and 'm' indicates training data file line number
                                                                                            effdis=0;
                                                                                        }
                                                                                }

                                                                    }
                                                    else if(strcmp(argv[3],"Manhattan")==0)     //This will be work if type of distance is Manhattan
                                                                {
                                                                    for(r=0;r<=dim;r++)
                                                                        {
                                                                            if(r<dim)
                                                                                {
                                                                                dist=te[r]-tr[r];        //calculation of difference between each dimension value of data points(i.e.one from testing data file and one from training data file)

                                                                                if(dist<0)
                                                                                    dist=dist*(-1);      //calculation of Mod of difference between each dimension value of data points(i.e.one from testing data file and one from training data file)

                                                                                effdis=effdis+dist;     //sum of(Mod of difference between each dimension value of data points(i.e.one from testing data file and one from training data file))
                                                                                }
                                                                            else
                                                                                {
                                                                                    effdist[i][m]=effdis;       //Then its value is assigned to 'effdist' array to its respective testing data file line number and training data file line number
                                                                                                                //i.e.here 'i' indicates testing data file line number and 'm' indicates training data file line number
                                                                                    effdis=0;
                                                                                }
                                                                        }

                                                                }
                                                    else
                                                    {
                                                        printf("Enter distance only either Euclidean or Manhattan");        //if entered type of distance is neither Euclidean nor Manhattan then program exits
                                                        exit(11);
                                                    }
                                                }

                                        rewind(ftr);

                                        //Now,based on the distance value 'K' distance values are taken into 'sort' array in ascending order
                                        for(t=0;t<kvalue;t++)
                                                {
                                                    //Here 't' value indicates positions of 'sort' array
                                                    if(t!=0)
                                                        {
                                                            for(u=0;;u++)
                                                                    {
                                                                        if(effdist[i][u]>sort[t-1])
                                                                                {
                                                                                min=effdist[i][u];   //Now we will assign any one distance value to 'min' which is greater than largest distance in the 'sort' array
                                                                                                        //we take greater than the largest distance in the 'sort' array because to get the successive minimum distance of all other distances
                                                                                                        //And consider that 'min' is the minimum distance
                                                                                break;
                                                                                }
                                                                    }

                                                            //Here we are going to get the successive minimum distance to store in 'sort' array
                                                            //Now we will get the successive minimum distance by comparing,
                                                            //Distances which are greater than the largest distance in 'sort' array and minimum of all remaining distances other than distances in 'sort' array
                                                            for(s=0;s<ltr;s++)
                                                                    {
                                                                        if(effdist[i][s]>sort[t-1] && min>effdist[i][s])    //If any other distance value is less than 'min' which is also greater than largest distance in 'sort' array then it means that 'min' is not the minimum distance of all remaining distances other than distances in 'sort' array
                                                                            min=effdist[i][s];          //Then we will change the 'min' value to that distance because we are considering that 'min' is the minimum distance
                                                                                                        //Like this 'min' value go on changes until we get the minimum distance of all remaining distances other than distances in 'sort' array
                                                                    }
                                                            sort[t]=min;        //After that the 'min' value is stored in the 'sort' array as the successive minimum distance
                                                        }
                                                    else
                                                        {
                                                            min=effdist[i][t];  //For first time we will assign any one distance value to 'min' and consider that 'min' is the minimum distance

                                                            for(s=0;s<ltr;s++)
                                                                {
                                                                    //we are going to get the minimum distance value of all distance values found between one test data and each row of training data with the help of any of the method namely Euclidean or Manhattan for each time
                                                                    //We will get the minimum distance by comparing one distance value with other
                                                                    //Atlast after all comparisons we get minimum distance value
                                                                    if(effdist[i][s]<min)       //If any other distance value is less than 'min' then it means that 'min' is not the minimum distance
                                                                        min=effdist[i][s];      //Then we will change the 'min' value to that distance because we are considering that 'min' is the minimum distance
                                                                                                //Like this 'min' value go on changes until we get the minimum distance of all distances values
                                                                }

                                                            sort[t]=min;    //After that the 'min' value is stored in the 'sort' array
                                                        }
                                                }
                                        /*
                                        *Here we are going to count the occurrence of each type of class of all data points from training data file whose distances are in 'sort' array
                                        *we will take all the data points(lines) from training data file whose distances are in 'sort' array
                                        *Then we see the classes of those data points
                                        *Then for every occurrence of each type of class the count of each type of class will be incremented
                                        *This incrementation will vary with the type of selection that was given as input
                                        *we had an input as argument from main function that type of selection of class either Weighted or Unweighted
                                        *If it is Weighted then count will be incremented by (1/square of that data point distance)
                                        *Else if it Unweighted then count will be incremented by 1
                                        */
                                        if(strcmp(argv[6],"Weighted")==0)
                                                    {
                                                        //This loop is made for 'kvalue' times because there are 'kvalue' distances in the 'sort' array
                                                        //For each time each class of data point of each distance in 'sort' array is known and then increments the count of that class type
                                                    for(w=0;w<kvalue;w++)
                                                            {
                                                                for(x=0;x<ltr;x++)
                                                                        {
                                                                            //'x' indicates the line number of the training data file
                                                                            if(effdist[i][x]==sort[w])   //From this we are going to know the data points(lines) from training data file whose distances are in 'sort' array
                                                                                        {
                                                                                            //This loop is made to know the class of that data point
                                                                                            for(g=0;g<l;g++)
                                                                                                {
                                                                                                    comp=strcmp(trclass[x],classes[g]);

                                                                                                    if(comp==0)
                                                                                                        {
                                                                                                        occurclass[g]=occurclass[g]+(1/(sort[w]*sort[w]));       //for every occurrence of each type of class the count of each type of class will be incremented
                                                                                                                                                                    //As it is Weighted then count will be incremented by (1/square of that data point distance)
                                                                                                        break;
                                                                                                        }
                                                                                                }
                                                                                            break;
                                                                                        }
                                                                        }
                                                            }
                                                    }
                                        else if(strcmp(argv[6],"Unweighted")==0)
                                                    {
                                                    //This loop is made for 'kvalue' times because there are 'kvalue' distances in the 'sort' array
                                                    //For each time each class of data point of each distance in 'sort' array is known and then increments the count of that class type
                                                    for(w=0;w<kvalue;w++)
                                                            {
                                                                for(x=0;x<ltr;x++)
                                                                {
                                                                    //'x' indicates the line number of the training data file
                                                                    if(effdist[i][x]==sort[w])        //From this we are going to know the data points(lines) from training data file whose distances are in 'sort' array
                                                                    {
                                                                        //This loop is made to know the class of that data point
                                                                        for(g=0;g<l;g++)
                                                                            {
                                                                                comp=strcmp(trclass[x],classes[g]);

                                                                                if(comp==0)
                                                                                    {
                                                                                        occurclass[g]++;       //for every occurrence of each type of class the count of each type of class will be incremented
                                                                                                            //As it is Unweighted then count will be incremented by 1
                                                                                        break;
                                                                                    }
                                                                            }
                                                                        break;
                                                                    }
                                                                }
                                                            }
                                                    }

                                        b=0;

                                        //After the counting process the class with highest count will be the predicted class for the data point of the testing data file
                                        max=occurclass[0]; //we will assume that some count of class is maximum and is assigned to 'max'
                                        for(b=0;b<l;b++)
                                                {
                                                    if(occurclass[b]>max) //If any other count of class is maximum than 'max' then it means that our assumption was wrong
                                                        {
                                                            max=occurclass[b];  //Then we will change the 'max' to that value
                                                            maxx=b;             //And note the type of class which has highest count
                                                        }
                                                }

                                        strcpy(preteclass[i],classes[maxx]);    //Then as we noted the highest count class that class will be copied to the predicted class of the data point of testing data file

                                        comp=strcmp(teclass[i],preteclass[i]);  //we will compare the predicted class of the data point with the given class of the data point in the data set
                                                                                //strcmp function returns zero if both are equal

                                        if(comp==0)
                                        same[i]='1';     //As we know that 'same' array is made to store '1' or '0' where '1' says that predicted and given classes are same else different
                                        else
                                        same[i]='0';
                                        //So 'same' array says that predicted and given classes are same or not for each data point of testing data file i.e.correctly predicted or not

                                        memset(occurclass,0,sizeof(occurclass));

                                        maxx=0;

                                        i++;
                                    }

                                rewind(fte);

                                //Here we are counting how many are correctly predicted(i.e.predicted and given classes of each data point of testing data file are same)
                                for(z=0;z<lte;z++)
                                        {
                                            if(same[z]=='1')
                                                corr++;
                                        }

                                i=0;

                                //Here we are printing the testing data set and its predicted classes of each data point in the same order
                                while(i<lte)
                                    {
                                        ch=fgetc(fte);

                                        if(ch=='\n')
                                            {
                                                printf("  %s",preteclass[i]);
                                                i++;
                                            }

                                        printf("%c",ch);
                                    }

                                rewind(fte);

                                printf("Number of instances successfully predicted are %.2f\n",corr);

                                printf("Total number of instances are %d\n",lte);

                                acc[nacc]=(corr*100)/lte;  //we know that accuracy is found using the formula:
                                                            //(number of classes of data points of testing data file that are correctly predicted/total number of data points in testing data file)*100
                                                            //After calculating every accuracy is stored in 'acc' array for finding the average accuracy and standard deviation
                                                            //And we are calculating the accuracy more number times for avoiding bias

                                printf("Accuracy for instances successfully predicted is %0.2f percentage\n",acc[nacc]);

                                printf("KNN\n");

                                printf("Kvalue= %d\n",kvalue);

                                printf("Filename= %s\n",argv[1]);

                                printf("Accuracy= %0.2f%%\n",acc[nacc]);

                                printf("\n\n");

                                totsum=totsum+acc[nacc];  //Every time we calculate the accuracy we will add the value to 'totsum' which is useful for calculating the average accuracy

                                //These variables are assigned to zero because as we are repeating the process of calculation of accuracy some of variables have to be redefined to zero
                                i=0;

                                corr=0;

                                s=0;

                                r=0;

                                t=0;

                                m=0;

                                b=0;

                                g=0;

                                w=0;

                                x=0;

                                n=0;

                                p=0;

                                c=0;

                                dim=0;

                                dig=0;

                                im=0;

                                l=0;

                                imm=0;

                                q=0;

                                ij=0;

                                u=0;

                                v=0;

                                comma=0;

                                k=0;

                                lte=0;

                                ltr=0;

                                fclose(fte);    //closing the testing data file pointer

                                fclose(ftr);    //closing the training data file pointer

                                nacc++;
                            }

                            nl=0;
                            e=0;
                }

                fclose(sfile);      //closing the scaled data file pointer


                avacc=totsum/(nvalue*nparts); //Calculation of average accuracy
                                              //formula for it is (sum of all accuracies/total number of accuracies)

                //This loop is made for calculating the Standard Deviation
                //Formula for it is (square root of(sum of(square of(difference between(each accuracy and average accuracy)))/total number of accuracies))
                for(aacc=0;aacc<(nvalue*nparts);aacc++)
                            {
                               tdiff=acc[aacc]-avacc;       //calculation of difference between(each accuracy and average accuracy)

                               tdiff=tdiff*tdiff;           //calculation of square of(difference between(each accuracy and average accuracy))

                               tsum=tsum+tdiff;             //calculation of sum of(square of(difference between(each accuracy and average accuracy)))
                            }

                sdiv=sqrt(tsum/(nvalue*nparts));        //calculation of standard deviation
                                                        //calculation of square root of(sum of(square of(difference between(each accuracy and average accuracy)))/total number of accuracies)

                printf("KNN\n");

                printf("Kvalue= %d\n",kvalue);

                printf("Filename= %s\n",argv[1]);

                printf("Distance type= %s\n",argv[3]);

                printf("Type of selection of class= %s\n",argv[6]);

                printf("Average accuracy= %0.2f%%\n",avacc);

                printf("Standard deviation= %0.2f\n",sdiv);

                return 0;
}
