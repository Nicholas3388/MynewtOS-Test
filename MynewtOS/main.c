//
//  main.c
//  MynewtOS
//
//  Created by apple on 16/7/6.
//  Copyright © 2016年 apple. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "os.h"

#define TASK1_PRIO (1)
#define TASK2_PRIO (2)
#define STACK_SIZE     1024

struct os_task task1;
struct os_task task2;
struct os_sem task1_sem;
struct os_sem task2_sem;

os_stack_t task1_stack[OS_STACK_ALIGN(STACK_SIZE)];
os_stack_t task2_stack[OS_STACK_ALIGN(STACK_SIZE)];

/* Task 1 handler function */
void
task1_handler(void *arg)
{
    while (1) {
        os_time_delay(1000);    // delay 1 seconds
        
        /* Release semaphore to task 2 */
        os_sem_release(&task1_sem);
        printf("In task1\n");
        
        /* Wait for semaphore from task 2 */
        os_sem_pend(&task2_sem, OS_TIMEOUT_NEVER);
    }
}

/* Task 2 handler function */
void
task2_handler(void *arg)
{
    while (1) {
        /* Wait for semaphore from task1 */
        os_sem_pend(&task1_sem, OS_TIMEOUT_NEVER);
        
        os_time_delay(1000);
        printf("In task2\n");
        
        /* Release task2 semaphore */
        os_sem_release(&task2_sem);
    }
}


/* Initialize task 1 exposed data objects */
void
task1_init(void)
{
    /* Initialize task1 semaphore */
    os_sem_init(&task1_sem, 0);
}

/* Initialize task 2 exposed data objects */
void
task2_init(void)
{
    /* Initialize task1 semaphore */
    os_sem_init(&task2_sem, 0);
}

/**
 * init_app_tasks
 *
 * Called by main.c after os_init(). This function performs initializations
 * that are required before tasks are running.
 *
 * @return int 0 success; error otherwise.
 */
static int
init_app_tasks(void)
{
    /*
     * Initialize tasks 1 and 2. Note that the task handlers are not called yet; they will
     * be called when the OS is started.
     */
    os_task_init(&task1, "task1", task1_handler, NULL, TASK1_PRIO,
                 OS_WAIT_FOREVER, task1_stack, STACK_SIZE);
    
    os_task_init(&task2, "task2", task2_handler, NULL, TASK2_PRIO,
                 OS_WAIT_FOREVER, task2_stack, STACK_SIZE);
    
    /* Call task specific initialization functions. */
    task1_init();
    task2_init();
    
    return 0;
}

/**
 * main
 *
 * The main function for the application. This function initializes the os, calls
 * the application specific task initialization function. then starts the
 * OS. We should not return from os start!
 */
int
main(void)
{
    int rc;
    
    /* Initialize OS */
    os_init();
    
    /* Initialize application specific tasks */
    init_app_tasks();
    
    /* Start the OS */
    os_start();
    
    /* os start should never return. If it does, this should be an error */
    assert(0);
    
    return rc;
}