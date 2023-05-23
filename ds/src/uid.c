/*******************************************************************************
*  uid.c                                                                       *
*  Author: Ariel                                                               *
*  Reviewer: Eli                                                               *
*******************************************************************************/
#include <unistd.h> /* getpid, time */

#include "uid.h"

static size_t counter = 0;

#define TIME_FAILURE -1

/***** UidCreate **************************************************************/

uid_ty UidCreate(void)
{
	uid_ty new_uid = {0};
	
	new_uid.time = time(NULL);
	
	if( new_uid.time == TIME_FAILURE ) return UidGetBadUid();
	
	new_uid.counter = counter;
	++counter;
	
	new_uid.pid = getpid();
	
	return new_uid;
}

/***** UidIsSame **************************************************************/

int UidIsSame(uid_ty uid1, uid_ty uid2)
{
	return (uid1.time == uid2.time) &&
	       (uid1.counter == uid2.counter) &&
	       (uid1.pid == uid2.pid);
}

/***** UidGetBadData **********************************************************/

uid_ty UidGetBadUid(void)
{
	uid_ty bad_uid = {0};
	
	return bad_uid;
}
