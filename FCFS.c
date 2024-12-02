#include<stdio.h>

void main(){
    int pn[10];
    int arr[10], bur[10], star[10], finish[10], tat[10], wt[10], i, n;
    int totwt=0, tottat=0;

    printf("Enter the number of processes:");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        printf("Enter the Process Name, Arrival Time & Burst Time:");
        scanf("%d%d%d",&pn[i],&arr[i],&bur[i]);
    }
    
    for(i=0;i<n;i++) {
        if(i==0) {
            star[i]=arr[i];
        } 
        else{
            star[i]=finish[i-1];
        }
        wt[i]=star[i]-arr[i];
        finish[i]=star[i]+bur[i];
        tat[i]=finish[i]-arr[i];
    }

    // In tiêu đề cột với độ dài cố định
    printf("%-8s %-8s %-8s %-8s %-8s %-8s\n", "PName", "Arrtime", "Burtime", "Start", "TAT", "Finish");

    for(i=0;i<n;i++) {
        printf("%-8d %-8d %-8d %-8d %-8d %-8d\n",pn[i],arr[i],bur[i],star[i],tat[i],finish[i]);
        totwt+=wt[i];
        tottat+=tat[i];
    }
}