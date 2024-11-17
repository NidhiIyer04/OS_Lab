#include <stdio.h>

int main() {
    int n, i, qt, time = 0, remaining;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    remaining = n;
    
    int arrivalTime[n], burstTime[n], remainingTime[n];
    
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i];
    }
    
    printf("Enter the time quantum: ");
    scanf("%d", &qt);
    
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    
    int waitingTime[n], turnaroundTime[n], completionTime[n];
    
    while (remaining != 0) {
        for (i = 0; i < n; i++) {
            if (arrivalTime[i] <= time && remainingTime[i] > 0) {
                if (remainingTime[i] > qt) {
                    time += qt;
                    remainingTime[i] -= qt;
                } else {
                    time += remainingTime[i];
                    completionTime[i] = time;
                    remainingTime[i] = 0;
                    remaining--;
                    
                    turnaroundTime[i] = completionTime[i] - arrivalTime[i];
                    waitingTime[i] = turnaroundTime[i] - burstTime[i];
                }
            }
        }

        // If no process is currently executing, move time forward
        int nextArrival = 0;
        for (i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                if (nextArrival == 0 || arrivalTime[i] < nextArrival) {
                    nextArrival = arrivalTime[i];
                }
            }
        }
        if (nextArrival > time) {
            time = nextArrival;
        }
    }
    
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], completionTime[i], waitingTime[i], turnaroundTime[i]);
    }
    
    return 0;
}
