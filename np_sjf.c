#include <stdio.h>
#include <stdlib.h>

// Define the process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to sort processes by burst time
void sortProcessesByBurstTime(struct Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to implement Non-Preemptive SJF scheduling
void sjfScheduling(struct Process *processes, int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        // Find the process with the shortest burst time that has arrived
        int shortestJobIndex = -1;
        for (int j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].completionTime == 0) {
                if (shortestJobIndex == -1 || processes[j].burstTime < processes[shortestJobIndex].burstTime) {
                    shortestJobIndex = j;
                }
            }
        }
        
        // If no job is found, advance time
        if (shortestJobIndex == -1) {
            currentTime++;
            i--;
            continue;
        }

        // Execute the shortest job
        currentTime += processes[shortestJobIndex].burstTime;
        processes[shortestJobIndex].completionTime = currentTime;
        processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].completionTime - processes[shortestJobIndex].arrivalTime;
        processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].turnaroundTime - processes[shortestJobIndex].burstTime;
    }

    // Print the results
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].id, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
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
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].completionTime = 0; // Initialize completion time to 0
    }

    sjfScheduling(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
