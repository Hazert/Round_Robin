#include <stdio.h>
#define SIZE  1024
#define ZERO 0

int main(int argc, char *argv[]) {
    int ProcessNumber=ZERO;
    int q=ZERO;
    int time = ZERO;
    int count = ZERO;
    int BurstTime[SIZE];
    int RT[SIZE];
    int pID[SIZE];
    int Signal = ZERO;//Used to tell system this process has finished
    int WaitTime = ZERO;//Calculate each process Wait Time
    int TurnaroundTime = ZERO;//Calculate each process Turnaround Time
    int remain = ZERO;                //Used to calculate how many processes has not finished
    int c = ZERO;
    printf("*************************************************************************\n");
    printf("* Enter the number of processes to schedule : ");
    scanf("%d",&ProcessNumber);
    remain = ProcessNumber;
    //Use for loop to ask Burst Time and save ID for each process
    for(count = 0 ; count < ProcessNumber ; count++ ){
        printf("* Enter the burst time of process %d : ",count+1);
        scanf ("%d", &BurstTime[count]);//Get each processes' Burst Time
        RT[count] = BurstTime[count];
        pID[count] = count;
    }
    printf("* Enter the Maximum length of the time quantun q : ");
    scanf("%d",&q);
    //This for loop is used to calculate quantun form 1 to the maximum value
    for (int n = 1; n <= q; n++) {
        printf("* q = %d *",n);
        //This for loop used to judge wether all processes has finished or not
        for(time=0,count=0;remain!=0;)
        {
            
            //If this process' burst time less than quantun that means this process can finish at one quantun and change signal to 1 which means this process has finished
            if(RT[count] <= n && RT[count] > 0)
            {
                
                for (int i = 0; i < RT[count] ; i++) {
                    c = pID[count] +1;
                    printf(" %d ",c);
                }
                time = time + RT[count];
                RT[count]=0;
                Signal=1;
            }
            //If this process' burst time larage than quantun that means this process can't finish at once. So we can not change the signal to 1
            else if(RT[count]>n)
            {
                for (int j=0; j < n; j++) {
                    c = pID[count] +1;
                    printf(" %d ",c);
                }
                
                RT[count] = RT[count] - n;
                time = time + n;
            }
            //If one process finish, we will calculate it's Wait Time and Turnaround Time
            if(RT[count]==0 && Signal==1)
            {
                remain--;
                WaitTime += time - pID[count] - BurstTime[count];
                TurnaroundTime += time - pID[count];
                Signal=0;
            }
            //If one process finished it will start a new loop to calculate those process which has not finished
            if(count==ProcessNumber-1){
                count=0;
            }else if(pID[count+1]<=time){
                count++;
            }else{
                count=0;
            }
        }
        printf("\n* q = %d * AWT = %f ATT = %f",n,WaitTime*1.0/ProcessNumber,TurnaroundTime*1.0/ProcessNumber);
    }
    printf("\n*************************************************************************\n");
}