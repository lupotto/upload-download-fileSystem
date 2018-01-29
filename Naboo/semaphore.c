#include "semaphore.h"
#include <stdio.h>
/**
 * Method which creates a semaphore
 * @param sem The var where semaphore will be created
 * @return int The result of the operation executed 
 */
int SEM_constructor (semaphore * sem)
{
	assert (sem != NULL);
	sem->shmid = semget (IPC_PRIVATE, 1, IPC_CREAT | 0600);
	if (sem->shmid < 0) return sem->shmid;
    return 0;
}

/**
 * Method which initializes a semaphore
 * @param sem The semaphore to initialize
 * @param v The value to which the semaphores will be
 *          initialized
 * @return int The result of the operation executed 
 */
int SEM_init (const semaphore * sem, const int v) 
{
	unsigned short _v[1] = {v};
	assert (sem != NULL);
	return semctl (sem->shmid, 0, SETALL, _v);
}

/**
 * Method to destroy a semaphore
 * @param sem The semaphore to destroy
 * @return int The result of the operation executed 
 */
int SEM_destructor (const semaphore * sem)
{
	assert (sem != NULL);
	return semctl (sem->shmid, 0, IPC_RMID, NULL);
}

/**
 * Method to apply a wait operation, in order to warn that a 
 * process is going to use a common resource. The semaphore 
 * counter will be decreased. If counter has the value zero, the 
 * process will be added to the semaphore's queue 
 * @param sem The semaphore where wait operation will be applied 
 * @return int The result of the operation executed  
 */
int SEM_wait (const semaphore * sem)
{
	struct sembuf o = {0, -1, SEM_UNDO};
	
	assert (sem != NULL);
	return semop(sem->shmid, &o, 1);
}

/**
 * Method to apply a signal operation, in order to warn that a 
 * process has released a common resource. The semaphore counter
 * will be increased. If counter had the value zero and there 
 * are processes in the queue, the top one has the access to the 
 * common resource granted. 
 * @param sem The semaphore where signal operation will be 
 *            applied
 * @return int The result of the operation executed  
 */
int SEM_signal (const semaphore * sem)
{
	struct sembuf o = {0, 1, SEM_UNDO};	
	assert (sem != NULL);
	return semop(sem->shmid, &o, 1);
}