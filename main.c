//
//  main.c
//  FireOne
//
//  Created by 李左甜 on 2019/8/7.
//  Copyright © 2019 李左甜. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

struct Line
{
    int lf, rt, v; //Define the left and right and value of each line.
}Line[100000001];

int compLine(const void *a, const void *b){
    return ((struct Line*)a)->rt - ((struct Line*)b)->rt;
}

int compValue(const void *a, const void *b){
    return *(int*)a-*(int*)b;
}

long int totalValue[10000001];
long int validValue[10000001];


int main(){
    char buff[1024]; // Number of Lines
    int i,j;
    int k=0;
    FILE* fp;
    FILE* fw;
    fp=fopen("9.in","r");
    fw = fopen("9.out","w");
    if (fp!=NULL)
        printf("open successfully\n");
    
    fgets(buff,1024,fp);
    int n=atoi(buff);
    printf("total line is %d\n",n);
    
    int flag = 1;
 
     //fscanf(fp, "%s", buff);
    // printf("1: %s\n", buff );
 
     //fgets(buff, 255, (FILE*)fp);
     //printf("2: %s\n", buff );
 
     //fgets(buff, 255, (FILE*)fp);
     //printf("3: %s\n", buff );
 

    while(!feof(fp)){
        fgets(buff,1024,fp);
        printf("%s\n", buff);
        char * pch;
        pch = strtok(buff, " ");
        Line[k].lf=atoi(pch);
        printf("left is %s\n", pch);
        pch = strtok(NULL, " ,.-");
        Line[k].rt=atoi(pch);
        printf("right is %s\n", pch);
        printf("%d %d", Line[k].lf, Line[k].rt);
        Line[k].v = Line[k].rt-Line[k].lf;
        k++;
    }
    
    //printf("[[Value 1: %d\n", Line[0].v);
    
    qsort(Line, n, sizeof(Line[0]), compLine);
    // printf("sort Value 1: %d\n", Line[0].rt);
    // printf("sort Value 1: %d\n", Line[1].lf);
    // printf("sort Value 1: %d\n", Line[2].v);
    
    
    totalValue[0] = Line[0].v;
    
    validValue[0] = Line[0].v-(Line[0].rt-Line[1].lf);
    validValue[n-1] = Line[n-1].v-(Line[n-2].rt-Line[n-1].lf);
    
    for (i = 1; i<n-1; i++) {
        // printf("??? 1: %d\n, %d", Line[i].v,Line[i].rt);
        if(Line[i].lf>=Line[i-1].rt){
            if(Line[i].rt<=Line[i+1].lf){
              validValue[i] = Line[i].v;
            }
            else
                validValue[i] = Line[i].v-(Line[i].rt-Line[i+1].lf);
            
        }
        else {
            if(Line[i].rt<=Line[i+1].lf){
            validValue[i] = Line[i].v-(Line[i-1].rt-Line[i].lf);
           }
            else
                 validValue[i] = Line[i].v-(Line[i-1].rt-Line[i].lf+Line[i+1].rt-Line[i].rt);
        }
       
        // printf("vaildValue 1: i= %d, validvalue: %d, = %d-(%d-%d+%d-%d)\n", i, validValue[i], Line[i].v,Line[i].lf,Line[i-1].rt,Line[i].rt,Line[i+1].lf);
        if(Line[i].v < 0){
            Line[i].v = 0;
        }
    }
    
    printf("vaildValue 1: %d\n", validValue[0]);
    printf("vaildValue 2: %d\n", validValue[1]);
    printf("vaildValue 3: %d\n", validValue[2]);
    
    for(i=1; i<n; i++){
        totalValue[i] = totalValue[i-1];
        printf("totalValue 1 i=%d: %d\n", i,totalValue[i]);
        
        
        if(Line[i-1].rt >= Line[i].lf && Line[i].lf >= Line[i-1].lf){
            totalValue[i] = Line[i].v+totalValue[i-1]-(Line[i-1].rt-Line[i].lf);
            printf("totalValue 3 i=%d: %d %d", i,totalValue[i], Line[i].v);
        }
        else if(Line[i].lf <= Line[i-1].lf){
             flag = 0;

            for(j=i-1; j>=0;j--){
                if(Line[j].rt >= Line[i].lf && Line[i].lf >= Line[j].lf){
                    totalValue[i] = Line[i].v+totalValue[j]-(Line[j].rt-Line[i].lf);
                    break;
                }
                else if(Line[i].lf>=Line[j].rt){
                    totalValue[i] = Line[i].v + totalValue[j];
                    break;
                }
                else
                    totalValue[i] = Line[i].v;
            }
            printf("totalValue is: %d\n", totalValue[i]);
            
        }
        
        printf("totalValue 2: %d\n", totalValue[i]);
        
    }
    
    qsort(validValue, n, sizeof(int), compValue);
    // printf("[vaild Value 1: %d\n", validValue[0]);
    // printf("[vaild Value 2: %d\n", validValue[1]);
    // printf("[vaild Value 3: %d\n", validValue[2]);
    if(flag==0||validValue[0]<=0){
        printf("Final result is %d\n",totalValue[n-1]);
        fprintf(fw, "%d\n", totalValue[n-1]);
    }
    else{
            printf("Final result is %d - %d = %d\n", totalValue[n-1], validValue[0], totalValue[n-1]-validValue[0]);
            int result = totalValue[n-1]-validValue[0];
            fprintf(fw, "%d\n", result);
    }

    return 0;
}

