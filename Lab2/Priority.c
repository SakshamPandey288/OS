#include <stdio.h>

struct Process {
    int id, burstTime, priority, waitingTime, turnaroundTime, arrivalTime, remainingTime;
};

void sortProcesses(struct Process p[], int n, int isPreemptive) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((isPreemptive && p[i].arrivalTime > p[j].arrivalTime) || 
                (!isPreemptive && p[i].priority > p[j].priority)) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void priorityScheduling(struct Process p[], int n, int isPreemptive) {
    sortProcesses(p, n, isPreemptive);
    int currentTime = 0, completed = 0, minPriorityIndex;
    
    while (completed < n) {
        minPriorityIndex = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0) {
                if (minPriorityIndex == -1 || p[i].priority < p[minPriorityIndex].priority) {
                    minPriorityIndex = i;
                }
            }
        }
        
        if (minPriorityIndex == -1) {
            currentTime++;
            continue;
        }
        
        if (isPreemptive) {
            p[minPriorityIndex].remainingTime--;
            currentTime++;
            if (p[minPriorityIndex].remainingTime == 0) {
                completed++;
                p[minPriorityIndex].turnaroundTime = currentTime - p[minPriorityIndex].arrivalTime;
                p[minPriorityIndex].waitingTime = p[minPriorityIndex].turnaroundTime - p[minPriorityIndex].burstTime;
            }
        } else {
            currentTime += p[minPriorityIndex].remainingTime;
            p[minPriorityIndex].remainingTime = 0;
            completed++;
            p[minPriorityIndex].turnaroundTime = currentTime - p[minPriorityIndex].arrivalTime;
            p[minPriorityIndex].waitingTime = p[minPriorityIndex].turnaroundTime - p[minPriorityIndex].burstTime;
        }
    }

    printf("\nID\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].priority, p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime);
    }
}

int main() {
    int n, isPreemptive;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].remainingTime = p[i].burstTime;
    }
    
    printf("Choose Scheduling Type: 1 for Preemptive, 0 for Non-Preemptive: ");
    scanf("%d", &isPreemptive);
    
    priorityScheduling(p, n, isPreemptive);
    return 0;
}
