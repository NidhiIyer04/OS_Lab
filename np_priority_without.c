#include <stdio.h>

int main() {
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int arrivalTime[n], burstTime[n], priority[n], completionTime[n], waitingTime[n], turnaroundTime[n];
    int isCompleted[n];
    
    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &arrivalTime[i], &burstTime[i], &priority[i]);
        isCompleted[i] = 0; // Initialize all processes as incomplete
    }
    
    int time = 0, completed = 0;
    while (completed != n) {
        // Find the highest priority process that has arrived and is incomplete
        int maxPriorityIndex = -1;
        for (i = 0; i < n; i++) {
            if (arrivalTime[i] <= time && isCompleted[i] == 0) {
                if (maxPriorityIndex == -1 || priority[i] < priority[maxPriorityIndex]) {
                    maxPriorityIndex = i;
                }
            }
        }

        // If no process is found, advance the time
        if (maxPriorityIndex == -1) {
            time++;
            continue;
        }

        // Execute the selected process
        time += burstTime[maxPriorityIndex];
        completionTime[maxPriorityIndex] = time;
        turnaroundTime[maxPriorityIndex] = completionTime[maxPriorityIndex] - arrivalTime[maxPriorityIndex];
        waitingTime[maxPriorityIndex] = turnaroundTime[maxPriorityIndex] - burstTime[maxPriorityIndex];
        isCompleted[maxPriorityIndex] = 1; // Mark the process as completed
        completed++;
    }
    
    // Print the results
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], priority[i], completionTime[i], waitingTime[i], turnaroundTime[i]);
    }
    
    return 0;
}
