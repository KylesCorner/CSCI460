/*
 * File: pager-predict.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a predictive pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 
    
    static int initialized = 0;
    static int tick = 1;
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    int proc, pc, page, pred_page;

    if (!initialized) {
        for (proc = 0; proc < MAXPROCESSES; proc++) {
            for (page = 0; page < MAXPROCPAGES; page++) {
                timestamps[proc][page] = 0;
            }
        }
        initialized = 1;
    }

    for (proc = 0; proc < MAXPROCESSES; proc++) {
        if (q[proc].active) {
            pc = q[proc].pc;
            page = pc / PAGESIZE;
            timestamps[proc][page] = tick;

            // If current page isn't in memory, bring it in
            if (!q[proc].pages[page]) {
                if (!pagein(proc, page)) {
                    int lruTick = tick;
                    int lruPage = -1;
                    for (int i = 0; i < MAXPROCPAGES; i++) {
                        if (q[proc].pages[i] && timestamps[proc][i] < lruTick) {
                            lruTick = timestamps[proc][i];
                            lruPage = i;
                        }
                    }
                    if (lruPage != -1) {
                        pageout(proc, lruPage);
                        pagein(proc, page);
                    }
                }
            }

            // Predictive: pre-load the next page
            pred_page = page + 1;
            if (pred_page < MAXPROCPAGES && !q[proc].pages[pred_page]) {
                if (!pagein(proc, pred_page)) {
                    int lruTick = tick;
                    int lruPage = -1;
                    for (int i = 0; i < MAXPROCPAGES; i++) {
                        if (q[proc].pages[i] && timestamps[proc][i] < lruTick) {
                            lruTick = timestamps[proc][i];
                            lruPage = i;
                        }
                    }
                    if (lruPage != -1) {
                        pageout(proc, lruPage);
                        pagein(proc, pred_page);
                    }
                }
            }
        }
    }

    tick++;
} 
