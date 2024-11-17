#include <stdio.h>
int swap(int  *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort_by_at(int p[], int at[], int bt[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (at[j] > at[j + 1])
			{
				swap(&at[j], &at[j + 1]);
				swap(&bt[j], &bt[j + 1]);
				swap(&p[j], &p[j + 1]);
			}
		}
	}
}

void fcfs(int at[], int bt[], int wt[], int tat[], int n)
{
	int completion_time = 0;
	for (int i = 0; i < n; i++)
	{
		if (at[i] > completion_time)
		{
			completion_time = at[i];
		}
		wt[i] = completion_time - at[i];
		tat[i] = wt[i] + bt[i];
		completion_time += bt[i];
	}
}

void findAvgTime(int p[], int at[], int bt[], int n)
{
	int wt[100], tat[100];
	int total_wt = 0, total_tat = 0;

	fcfs(at, bt, wt, tat, n);

	for (int i = 0; i < n; i++)
	{
		total_wt += wt[i];
		total_tat += tat[i];
	}
	printf("P\tAT\tBT\tWT\tTAT\n");
	for (int i = 0; i < n; i++)
	{
 		printf("P%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], wt[i], tat[i]);
	}
	printf("\nAverage Waiting Time = %.2f", (float)total_wt / (float)n);
	printf("\nAverage Turn Around Time = %.2f \n", (float)total_tat / (float)n);
}
int main()
{
	int n;
	int p[100], bt[100], at[100];
	printf("Enter the number of processes:");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Process %d (Burst Time):", i + 1);
		scanf("%d",&bt[i]);
		at[i]=0;
		p[i] = i + 1;
	}
	sort_by_at(p, at, bt, n);
	findAvgTime(p, at, bt, n);
	return 0;
}
