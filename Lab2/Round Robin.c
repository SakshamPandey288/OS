#include <stdio.h>

struct process {
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
};

void roundRobinScheduling(struct process proc[], int n, int quantum) {
    int time = 0;
    int completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time <= quantum) {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                    proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
                    completed++;
                } else {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                }
            }
        }
    }

    printf("PID  Burst Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d    %d           %d            %d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process proc[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter process %d details:\n", i + 1);
        proc[i].pid = i + 1;
        printf("Burst time: ");
        scanf("%d", &proc[i].burst_time);
        printf("Arrival time: ");
        scanf("%d", &proc[i].arrival_time);
        proc[i].remaining_time = proc[i].burst_time;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    roundRobinScheduling(proc, n, quantum);

    return 0;
}
