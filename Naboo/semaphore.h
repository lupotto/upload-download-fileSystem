#ifndef _MOD_SEMAPHORE_H_
#define _MOD_SEMAPHORE_H_

/////////////////////////////////////////////////////////////////////////////
/**
 *  @file   semaphore.h
 *  @author Jorge Solanas
 *  @date   October 5, 2011
 *  @brief  Library to facilitate the use of semaphores
 *
 *  (c) Copyright La Salle BCN, 2011.
 *  All rights reserved. Copying or other reproduction of this program except 
 *  for archival purposes is prohibited without written consent of 
 *  La Salle BCN. 
 */
//////////////////////////////////////////////////////////////////////////////

//#define __USE_SVID
#define __USE_XOPEN

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <assert.h>
#include <stdlib.h>

/**
 * This file provides a simple but useful abstraction for 
 * controlling acces by multiple processes to a common resource.
 */

/**
 * Union which must be explicitly declared by the application.
 * It is the fourth argument of the semctl function, and it is
 * optional, depending upon the operation requested.
 */
union semun
{
	int val;
	struct semid_ds * buf;
	unsigned short  * array;
};

/**
 * Struct used to indicate to a semaphore which operation is 
 * going to be applied (number of the semaphore, operation and 
 * flags). 
 */
typedef struct
{
	unsigned short int sem_num;
	short int sem_op;
	short int sem_flg;
} sembuf;

/**
 * Struct with all the info about a semaphore. In this case, 
 * only the id is specified. 
 */
typedef struct
{
	int shmid;
} semaphore;


int SEM_constructor (semaphore * sem);
int SEM_init (const semaphore * sem, const int v);
int SEM_destructor (const semaphore * sem);
int SEM_wait (const semaphore * sem);
int SEM_signal (const semaphore * sem);



#endif /* _MOD_SEMAPHORE_H_ */
