#include <stdio.h>
#include <stdlib.h>

// Define the process structure
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

// Function to implement FCFS scheduling
void fcfsScheduling(struct Process *processes, int n) {
    int *completionTime = (int *)malloc(n * sizeof(int));
    int *waitingTime = (int *)malloc(n * sizeof(int));
    int *turnaroundTime = (int *)malloc(n * sizeof(int));

    completionTime[0] = processes[0].arrivalTime + processes[0].burstTime;
    for (int i = 1; i < n; i++) {
        if (processes[i].arrivalTime > completionTime[i - 1]) {
            completionTime[i] = processes[i].arrivalTime + processes[i].burstTime;
        } else {
            completionTime[i] = completionTime[i - 1] + processes[i].burstTime;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
    }

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].id, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               completionTime[i], 
               waitingTime[i], 
               turnaroundTime[i]);
    }

    // Free dynamically allocated memory
    free(completionTime);
    free(waitingTime);
    free(turnaroundTime);
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
    }

    fcfsScheduling(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
