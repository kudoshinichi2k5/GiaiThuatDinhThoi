#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void main(){
    int pn[10];
    int arr[10], bur[10], start[10], finish[10], tat[10], wt[10], res[10], i, n;
    int totwt=0, tottat=0;

    printf("Enter the number of processes: ");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        printf("Enter the Process Name, Arrival Time & Burst Time: ");
        scanf("%d%d%d",&pn[i], &arr[i], &bur[i]);
    }
    bool check[10] = {0};
    int j;
    int flag;
    int time = 0;
    for(i=0;i<n;i++) {
        if(i==0) {
            for(j=0; j<n; j++)
            {
                if(arr[j] == 0)
                {
                    flag = j;
                    start[flag] = 0;
                    break;
                }
            }
        } 
        else{
            bool right[10] = {0};   
            for(j=0; j<n; j++)
            {
                if(check[j] == 1)
                    continue;
                if(arr[j] <= time)
                    right[j] = 1;
            }
            int minn = 999;
            for(j=0; j<n; j++)
            {
                if(right[j] == 1)
                    if(bur[j] < minn)
                    {
                        minn = bur[j];
                        flag = j;
                    }   
            }
            start[flag] = time;
        }
        finish[flag] = start[flag] + bur[flag];
        res[flag] = start[flag] - arr[flag];
        tat[flag] = finish[flag] - arr[flag];
        wt[flag] = tat[flag] - bur[flag];
        check[flag] = 1;
        time = finish[flag];
    }
    printf("%-8s %-10s %-10s %-12s %-8s %-8s\n", "PName", "ArriveTime", "BurstTime", "ResponseTime", "TAT", "WaitTime");
    for(i=0;i<n;i++) 
    {
        printf("%-8d %-10d %-10d %-12d %-8d %-8d\n", pn[i], arr[i], bur[i], res[i], tat[i], wt[i]);
        totwt+=wt[i];
        tottat+=tat[i];
    }
    printf("\nAverage waiting time: %f", totwt*1.0/n);
    printf("\nAverage turnaround time: %f", tottat*1.0/n);
}