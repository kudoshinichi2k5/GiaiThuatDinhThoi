#include<stdio.h>
#include<stdbool.h>

int FindMinArr(int arr[], int n)
{
    int minn = 999;
    for(int i=0; i<n; i++)
    {
        if(arr[i] < minn)
            minn = arr[i];
    }
    return minn;
}

void FindMinRemainingTime(int arr[], int remain[], int n, bool check[], int time, int *flag)
{
    int minn = 999;
    for(int i=0; i<n; i++)
    {
        if(check[i] == true)
            continue;
        if(remain[i] < minn && arr[i] <= time)
        {
            minn = remain[i];
            *flag = i;
        }
    }
}

int Sum(int bur[], int n)
{
    int sum=0;
    for(int i=0; i<n; i++)
        sum+=bur[i];
    return sum;
}

bool CheckArrTime(int arr[], int n, int time, int *flag)
{
    for(int i=0; i<n; i++)
    {
        if(arr[i] == time)
        {
            *flag = i;
            return true;
        }
    }
    return false;
}

void main()
{
    int pn[10];
    int arr[10], bur[10], start[10], finish[10], tat[10], wt[10], res[10], remain[10], i, n;
    int totwt=0, tottat=0;
    bool check[10] = {false};
    int flag = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        printf("Enter the Process Name, Arrival Time & Burst Time: ");
        scanf("%d%d%d", &pn[i], &arr[i], &bur[i]);
        remain[i] = bur[i];
        start[i] = -1;
    }
    int time = 0;
    int minn = FindMinArr(arr, n);
    int sumTime = Sum(remain, n);
    int totalTime = minn + sumTime;
    int cnt=0;

    while(time < totalTime)
    {
        if(CheckArrTime(arr, n, time, &flag) == 1)
        {
            if(cnt==0)
            {
                cnt++;
                start[flag] = time;         //o lan dau tien, ko can check bursttime
            }
            else
            {
                FindMinRemainingTime(arr, remain, n, check, time, &flag);      //chuyen co cho bursttime phu hop
                if(start[flag] < 0)
                    start[flag] = time;
            }
        }
        remain[flag]--;     time++;
        if(remain[flag] == 0)
        {
            finish[flag] = time;
            check[flag] = true;
            FindMinRemainingTime(arr, remain, n, check, time, &flag);      //chuyen co cho bursttime phu hop
            if(start[flag] < 0)
                start[flag] = time;
        }
    }

    for(int i=0; i<n; i++)
    {
        res[i] = start[i] - arr[i];
        tat[i] = finish[i] - arr[i];
        wt[i] = tat[i] - bur[i];
    }

    printf("%-8s %-10s %-10s %-8s %-8s %-12s %-8s %-8s\n", "PName", "ArriveTime", "BurstTime", "Start", "Finish", "ResponseTime", "TAT", "WaitTime");
    for(i=0;i<n;i++) 
    {
        printf("%-8d %-10d %-10d %-8d %-8d %-12d %-8d %-8d\n", pn[i], arr[i], bur[i], start[i], finish[i], res[i], tat[i], wt[i]);
        totwt+=wt[i];
        tottat+=tat[i];
    }
    printf("\nAverage waiting time: %f", totwt*1.0/n);
    printf("\nAverage turnaround time: %f", tottat*1.0/n);
}