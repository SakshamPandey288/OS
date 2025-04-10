#include <stdio.h>

struct Task {
    int id, execution_time, period, deadline, next_deadline, remaining_time;
};

void earliest_deadline_first(struct Task tasks[], int n, int total_time) {
    printf("Time | Task\n");

    for (int t = 0; t < total_time; t++) {
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = t + tasks[i].deadline;
            }
        }

        int min_deadline = 9999, selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].next_deadline < min_deadline) {
                min_deadline = tasks[i].next_deadline;
                selected = i;
            }
        }

        if (selected != -1) {
            printf(" %2d | T%d\n", t, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf(" %2d | Idle\n", t);
        }
    }
}

int main() {
    struct Task tasks[] = {
        {1, 1, 4, 4, 0, 0},
        {2, 2, 5, 5, 0, 0}
    };
    int n = 2;
    int total_time = 20;

    earliest_deadline_first(tasks, n, total_time);
    return 0;
}
