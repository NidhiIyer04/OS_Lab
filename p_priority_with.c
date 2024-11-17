#include <stdio.h>
#include <stdlib.h>

// Define the process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to implement Preemptive Priority scheduling
void priorityScheduling(struct Process *processes, int n) {
    int time = 0, completed = 0;
    int minPriority, minPriorityIndex;

    while (completed != n) {
        minPriority = __INT_MAX__;
        minPriorityIndex = -1;

        // Find the process with the highest priority that is ready to execute
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0 && processes[i].priority < minPriority) {
                minPriority = processes[i].priority;
                minPriorityIndex = i;
            }
        }

        if (minPriorityIndex != -1) {
            // Process the selected process for one unit of time
            time++;
            processes[minPriorityIndex].remainingTime--;

            // If the process is completed
            if (processes[minPriorityIndex].remainingTime == 0) {
                processes[minPriorityIndex].completionTime = time;
                processes[minPriorityIndex].turnaroundTime = processes[minPriorityIndex].completionTime - processes[minPriorityIndex].arrivalTime;
                processes[minPriorityIndex].waitingTime = processes[minPriorityIndex].turnaroundTime - processes[minPriorityIndex].burstTime;
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
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].id, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].priority, 
               processes[i].completionTime, 
               processes[i].waitingTime, 
               processes[i].turnaroundTime);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    priorityScheduling(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
