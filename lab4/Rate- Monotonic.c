#include <stdio.h>

struct Task {
    int id, execution_time, period, remaining_time;
};

void rate_monotonic(struct Task tasks[], int n, int total_time) {
    printf("Time | Task\n");

    for (int t = 0; t < total_time; t++) {
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0)
                tasks[i].remaining_time = tasks[i].execution_time;
        }

        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                printf(" %2d   | T%d\n", t, tasks[i].id);
                tasks[i].remaining_time--;
                executed = 1;
                break;
            }
        }

        if (!executed)
            printf(" %2d   | Idle\n", t);
    }
}

int main() {
    struct Task tasks[] = {
        {1, 1, 4, 0},
        {2, 2, 5, 0}
    };
    int n = 2;
    int total_time = 20;

    rate_monotonic(tasks, n, total_time);
    return 0;
}
