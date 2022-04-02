
#ifndef __PRIORITY_SCHEDULE__
#define __PRIORITY_SCHEDULE__

//----------------------------------------------------------------------------------------------------------------------------------
/// @brief Structure which holds the Task information
//----------------------------------------------------------------------------------------------------------------------------------
struct object_t {

    /// Process number for the task
    int xpos;

    // Amount of time the task takes to execute
    int ypos;

    // Amount of time the task spends waiting to be executed
    int xvel;

    // Amount of time the task spends in the queue
    int yvel;

	// Priority for the current task
    int mass;

    int plat_or_hm; //1 is plat, 0 is hm

};

//----------------------------------------------------------------------------------------------------------------------------------
/// @brief Run the priority scheduling algorithm and
/// calculate the wait and turn around time for each task
///
/// @param[in] object The buffer containing object data
/// @param[in] size The size of the buffer
//----------------------------------------------------------------------------------------------------------------------------------
void physics(struct object_t *object, int xaccelmode, int yaccel, int ke_change, int plat_hm);

//----------------------------------------------------------------------------------------------------------------------------------
/// @brief Calculates if and which boundry is violated.
///
/// @param[in] object The object info
/// @param[in] plat_hm which object type
///
/// @return 0 if no crash, 1 if crash, 2 if ejected.
//----------------------------------------------------------------------------------------------------------------------------------
int bounds(struct object_t *object, int plat_hm, int border);
void reset_hm(struct object_t *object, int *hm_count);
#endif // __PRIORITY_SCHEDULE__