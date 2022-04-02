#include "pong.h"
#include <stdio.h>

void physics(struct object_t *object, int xaccelmode, int yaccel, int ke_change, int plat_hm) {
    // struct node_t *queue_head;
    // int time = 0;
    // int keep_cycle = 1;

}

int bounds(struct object_t *object, int plat_hm, int border){
    // return 0.0 so it compiles
    // if(size > 0)
    // {
    //     float wait_avg = 0;
    //     for(int i = 0; i < size; i++)
    //     {
    //         wait_avg += task[i].waiting_time;
    //     }
    //     wait_avg = wait_avg/(float)size;
    //     return wait_avg;
    // }
  return 0.0;
}

void reset_hm(struct object_t *object, int *hm_count) {
    (*hm_count)--;
    // return 0.0 so it compiles
    // if(size > 0)
    // {
    //     float turn_time_avg = 0;
    //     for(int i = 0; i < size; i++)
    //     {
    //         turn_time_avg += task[i].turnaround_time;
    //     }
    //     turn_time_avg = turn_time_avg/(float)size;
    //     return turn_time_avg;
    // }
 //   return 0.0;
}