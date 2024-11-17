#include <stdio.h>

int main() {
    int n, time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n], remainingTime[n], priority[n];
    int completionTime[n], waitingTime[n], turnaroundTime[n];
    int isCompleted[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &arrivalTime[i], &burstTime[i], &priority[i]);
        remainingTime[i] = burstTime[i];
        isCompleted[i] = 0;  // Initialize all processes as incomplete
    }

    while (completed != n) {
        int minPriority = __INT_MAX__;
        int minPriorityIndex = -1;

        // Find the process with the highest priority that is ready to execute
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= time && remainingTime[i] > 0 && priority[i] < minPriority) {
                minPriority = priority[i];
                minPriorityIndex = i;
            }
        }

        if (minPriorityIndex != -1) {
            // Process the selected process for one unit of time
            time++;
            remainingTime[minPriorityIndex]--;

            // If the process is completed
            if (remainingTime[minPriorityIndex] == 0) {
                completionTime[minPriorityIndex] = time;
                turnaroundTime[minPriorityIndex] = completionTime[minPriorityIndex] - arrivalTime[minPriorityIndex];
                waitingTime[minPriorityIndex] = turnaroundTime[minPriorityIndex] - burstTime[minPriorityIndex];
                isCompleted[minPriorityIndex] = 1;  // Mark the process as completed
                completed++;
            }
        } else {
            // If no process is ready, advance the time
            time++;
        }
    }

    // Print the results
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], priority[i], completionTime[i], waitingTime[i], turnaroundTime[i]);
    }

    return 0;
}
