/*********************************************************************
* Description: API for UID.
* Name: HRD20
* Date: 24.8.21
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - up to date - ready for review
*********************************************************************/ 
#ifndef __UID_H__
#define __UID_H__

#include <time.h>      /* time_t */
#include <sys/types.h> /* pid_t */
#include <stddef.h>    /* size_t */

 typedef struct uid uid_ty;

/*******************************************************************************
* Function Description: This function creates a unique identifier.
			       
* Arguments: None.

* Return value: a unique identifier.
   
* Notes: in case of failure in create function, the time segment of the uid will be -1.
        
* Time Complexity:	O(1)
*******************************************************************************/
uid_ty UidCreate(void);

/*******************************************************************************
* Function Description: This function compares two identifiers and check for equality.
			       
* Arguments: uid1 : Uid to compare.
* 			 uid2 : uid the compare.

* Return value: 1 if they are the same , else 0.
   
* Notes: 
        
* Time Complexity:	O(1)
*******************************************************************************/
int UidIsSame(uid_ty uid1, uid_ty uid2);

/*******************************************************************************
* Function Description: This function generates a non-valid uid for the user.
			       
* Arguments: None.

* Return value: a non valid uid.
   
* Notes: 
        
* Time Complexity:	O(1)
*******************************************************************************/
uid_ty UidGetBadUid(void);



/*Nothing to see here Mem!*/

struct uid
{
	time_t time;
	size_t counter;
	pid_t pid; 
};

#endif /* __UID_H__ */
