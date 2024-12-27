#include <stdio.h>

int main() {
    int n, quantum, time = 0, done = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int bt[n], rem[n], wt[n], tat[n];
    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) scanf("%d", &bt[i]), rem[i] = bt[i];
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    while (!done) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = 0;
                if (rem[i] > quantum) time += quantum, rem[i] -= quantum;
                else time += rem[i], wt[i] = time - bt[i], rem[i] = 0;
            }
        }
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    float avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avgWT += wt[i], avgTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", avgWT / n, avgTAT / n);
    return 0;
}

