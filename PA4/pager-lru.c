/*
 * File: pager-lru-stack.c
 * Author:       Based on Andy Sayler / Dr. Alva Couch
 * Description:
 *     LRU implementation using a stack per process.
 */

#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

#define STACK_SIZE MAXPROCPAGES

void moveToTop(int stack[], int *size, int page) {
    int i;
    for (i = 0; i < *size; i++) {
        if (stack[i] == page) {
            // Shift everything above this page down
            for (int j = i; j < *size - 1; j++) {
                stack[j] = stack[j + 1];
            }
            (*size)--;
            break;
        }
    }
    // Put the page on top
    stack[(*size)++] = page;
}

void pageit(Pentry q[MAXPROCESSES]) {
    static int initialized = 0;
    static int stacks[MAXPROCESSES][STACK_SIZE];     // LRU stacks per process
    static int stack_sizes[MAXPROCESSES] = {0};      // Number of pages in each stack

    int proc, pc, page;

    if (!initialized) {
        for (proc = 0; proc < MAXPROCESSES; proc++) {
            stack_sizes[proc] = 0;
            for (int i = 0; i < STACK_SIZE; i++) {
                stacks[proc][i] = -1;
            }
        }
        initialized = 1;
    }

    for (proc = 0; proc < MAXPROCESSES; proc++) {
        if (!q[proc].active)
            continue;

        pc = q[proc].pc;
        page = pc / PAGESIZE;

        if (q[proc].pages[page]) {
            // Page is already in memory — update LRU stack
            moveToTop(stacks[proc], &stack_sizes[proc], page);
        } else {
            // Not in memory — try to page it in
            if (pagein(proc, page)) {
                moveToTop(stacks[proc], &stack_sizes[proc], page);
            } else {
                // Need to evict LRU page
                if (stack_sizes[proc] > 0) {
                    int victim = stacks[proc][0];
                    pageout(proc, victim);
                    // Shift stack left
                    for (int i = 0; i < stack_sizes[proc] - 1; i++) {
                        stacks[proc][i] = stacks[proc][i + 1];
                    }
                    stack_sizes[proc]--;
                }

                // Retry pagein after eviction
                if (pagein(proc, page)) {
                    moveToTop(stacks[proc], &stack_sizes[proc], page);
                }
            }
        }
    }
}

