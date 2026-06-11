#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

#define MIN_COST 5
#define MAX_COST 22

#define STEPS_AMOUNT 6

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef int Index;
typedef unsigned int Natural, Cost;
typedef struct ladder Ladder;

struct ladder {
    Cost* steps;
    int steps_amount;
};

bool init_ladder(Ladder* ladder, Cost* costs, int steps_amount) {
    if (steps_amount <= 0) {
        ladder->steps = NULL;
        ladder->steps_amount = 0;
        return true;
    }
    
    ladder->steps_amount = steps_amount;

    ladder->steps = (Cost *) calloc(ladder->steps_amount, sizeof(Cost));

    if (!ladder->steps) {
        return false;
    }

    if (costs == NULL) {
        for (Index i=0; i<ladder->steps_amount; i++) {
            ladder->steps[i] = (rand() % (MAX_COST - MIN_COST + 1)) + MIN_COST;
        }

        return true;
    }

    for (Index i=0; i<ladder->steps_amount; i++) {
        ladder->steps[i] = costs[i];
    }

    return true;
}

void print_costs(Ladder ladder) {
    for (Index i=0; i<ladder.steps_amount; i++) {
        printf("El costo del escalón %d es %u\n", i+1, ladder.steps[i]);
    }
}

Cost greedy_optimal_cost(Ladder ladder) {
    if (ladder.steps_amount <= 0) {
        return 0;
    }

    Index current_step = -1;
    Natural total_cost = 0;

    while (current_step + 2 < ladder.steps_amount) {
        if (ladder.steps[current_step + 1] < ladder.steps[current_step + 2]) {
            current_step = current_step + 1;
        }

        else {
            current_step = current_step + 2;
        }

        total_cost += ladder.steps[current_step];
    }

    current_step = ladder.steps_amount;

    return total_cost;
}

Cost dp_optimal_cost(Ladder ladder) {
    if (ladder.steps_amount <= 0) {
        return 0;
    }

    Cost dp[ladder.steps_amount + 1];

    dp[ladder.steps_amount] = 0;
    dp[ladder.steps_amount - 1] = dp[ladder.steps_amount - 1];

    for (Index i=ladder.steps_amount-2; i>=0; i--) {
        dp[i] = ladder.steps[i] + MIN(dp[i+1], dp[i+2]);
    }

    return (dp[0] < dp[1]) ? dp[0] : dp[1];
}

int main() {
    srand(time(NULL));

    Ladder ladder;
    Cost costs[] = {1, 1, 100, 100, 100, 1};

    if (!init_ladder(&ladder, costs, STEPS_AMOUNT)) {
        perror("Allocation memory error.");
        return 1;
    }

    print_costs(ladder);
    printf("El costo óptimo Greedy es: %u\n", greedy_optimal_cost(ladder));
    printf("El costo óptimo con Programación Dinámica es: %u\n", dp_optimal_cost(ladder));

    free(ladder.steps);
    ladder.steps = NULL;

    ladder.steps_amount = 0;

    return 0;
}