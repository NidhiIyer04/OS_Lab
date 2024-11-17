#include <stdio.h>
#include <stdlib.h>

// Define the process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to implement Non-Preemptive Priority scheduling
void priorityScheduling(struct Process *processes, int n) {
    int time = 0, completed = 0;

    while (completed != n) {
        // Find the highest priority process that has arrived and is incomplete
        int maxPriorityIndex = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].completionTime == 0) {
                if (maxPriorityIndex == -1 || processes[i].priority < processes[maxPriorityIndex].priority) {
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
        time += processes[maxPriorityIndex].burstTime;
        processes[maxPriorityIndex].completionTime = time;
        processes[maxPriorityIndex].turnaroundTime = processes[maxPriorityIndex].completionTime - processes[maxPriorityIndex].arrivalTime;
        processes[maxPriorityIndex].waitingTime = processes[maxPriorityIndex].turnaroundTime - processes[maxPriorityIndex].burstTime;
        completed++;
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
        processes[i].completionTime = 0; // Initialize completion time to 0
    }

    priorityScheduling(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
