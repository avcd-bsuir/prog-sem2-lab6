// License: CC BY-NC-SA 4.0
/*
 * task1.c
 *
 * Queues.
 *
 * Written by AlexeyFilich
 * 23 mar 2021
 */

#include <stdio.h>

#define STORAGE_OPTIMAL

#include "Interactions.h"
#include "storage/Storage.h"

void printQueue(Queue * queue) {
    while (queue) {
        printf("%d<-", *(int *)queue->data);
        queue = queue->next;
    }
    printf("END\n");
}

int makeNumber(char string[], int * idx) {
    int temp = 0;
    while (string[*idx] >= '0' && string[*idx] <= '9') {
        temp = temp * 10 + string[*idx] - '0';
        (*idx)++;
    }
    return temp;
}

void addNumber(int val, Queue ** q1, Queue ** q2) {
    if (val >= 0 && val <= 9) {
        aQueuePushI(q1, val);
    } else if (val >= 10 && val <= 99) {
        aQueuePushI(q2, val);
    } else {
        printf("%d is not single- nor double-digit number\n", val);
        exit(-1);
    }
}

void multiplyQueues(Queue ** q1, Queue ** q2, Queue ** q3) {
    int a, b;
    while (*q1 && *q2) {
        aQueuePushI(q3, aQueueFirstI(q1) * aQueueFirstI(q2));
        aQueuePop(q1);
        aQueuePop(q2);
    }
}

int main(int argc, char* args[]) {
    Queue * q1, * q2, * q3;
    char string[1024];
    int temp = 0, idx = 0;
    aQueueInit(&q1);
    aQueueInit(&q2);
    aQueueInit(&q3);

    printf("Input string: ");
    fgets(string, 1024, stdin);

    while (string[idx] != '\0' && idx < 1024) {
        if (string[idx] == ' ' || string[idx] == '\n') {
            idx++;
        } else if (string[idx] >= '0' && string[idx] <= '9') {
            addNumber(makeNumber(string, &idx), &q1, &q2);
        } else {
            printf("Character '%c' is unexpected (pos %d)\n", string[idx], idx + 1);
            exit(-1);
        }
    }

    printf("\nQueue of single-digit numbers:\n");
    printQueue(q1);
    printf("Queue of double-digit numbers:\n");
    printQueue(q2);

    multiplyQueues(&q1, &q2, &q3);

    printf("\nAfter multiplicaton:\n");
    printf("Queue of single-digit numbers:\n");
    printQueue(q1);
    printf("Queue of double-digit numbers:\n");
    printQueue(q2);
    printf("Queue of multiplied numbers:\n");
    printQueue(q3);

    return 0;
}
