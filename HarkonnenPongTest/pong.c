#include "pong.h"
#include <stdio.h>

void physics(struct object_t *object, int xaccelmode, int yaccel, int ke_change, int plat_hm) {
    if(xaccelmode == 1)
    {
      object->xvel += 4;
    }
    else if(xaccelmode == 2)
    {
      object->xvel += 1;
    }
    else if(xaccelmode == 4)
    {
      object->xvel -= 1;
    }
    else if(xaccelmode == 8)
    {
      object->xvel -= 4;
    }     
    object->xpos += object->xvel;
    if(!plat_hm)
    {
      object->yvel -= yaccel;
      object->ypos += object->yvel;
    }
}

int bounds(struct object_t *object, int plat_hm, int border){
    if(object->ypos > border)
    {
        return 1;
    }
    return 0.0;
}

void reset_hm(struct object_t *object, int *hm_count) {
    (*hm_count)--;
    object->ypos = 0;
    object->yvel = 0;
}