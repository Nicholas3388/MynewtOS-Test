# This is just a test for MynewtOS on Mac OS X

From Apache Mynewt
----------------------------

In the example, each task works in a ping-pong like fashion: task 1 wakes up,
adds a token to semaphore 1 and then waits for a token from semaphore 2.
Task 2 waits for a token on semaphore 1 and once it gets it, adds a token to semaphore 2.
Notice that the semaphores are initialized by the application specific task initialization
functions and not inside the task handler functions. If task 2 (being lower in priority than task 1)
had called `os_sem_init()` for task2_sem inside `task2_handler()`, task 1 would have
called `os_sem_pend()` using task2_sem before task2_sem was initialized.
