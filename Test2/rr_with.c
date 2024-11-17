#include <stdio.h>
#include <stdlib.h>

// Define the process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to implement Round Robin scheduling
void roundRobinScheduling(struct Process *processes, int n, int qt) {
    int time = 0, remaining = n;

    while (remaining != 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime > qt) {
                    time += qt;
                    processes[i].remainingTime -= qt;
                } else {
                    time += processes[i].remainingTime;
                    processes[i].completionTime = time;
                    processes[i].remainingTime = 0;
                    remaining--;
                    
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                }
            }
        }

        // Move time forward if no process is ready
        int nextArrival = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                if (nextArrival == 0 || processes[i].arrivalTime < nextArrival) {
                    nextArrival = processes[i].arrivalTime;
                }
            }
        }
        if (nextArrival > time) {
            time = nextArrival;
        }
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
    int n, qt;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    printf("Enter the time quantum: ");
    scanf("%d", &qt);

    roundRobinScheduling(processes, n, qt);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
