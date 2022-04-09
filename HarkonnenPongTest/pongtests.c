#include <stdlib.h>
#include "ctest.h"
#include "pong.h"

CTEST_DATA(plat) {
    struct object_t plat;
    struct object_t plat_still;
    struct object_t plat_moveR;
    struct object_t plat_moveL;
    struct object_t plat_low_a;
    struct object_t plat_high_a;
    struct object_t plat_slower;
};

CTEST_SETUP(plat) {
    data->plat.xpos = 50;
    data->plat.ypos = 50;
    data->plat.xvel = 5;
    data->plat.yvel = 0;
    data->plat.mass = 20;
    data->plat.plat_or_hm = 1;
    
    data->plat_still = data->plat;
    data->plat_still.xvel = 0;   
    physics(&(data->plat_still), 0, 0, 0, 1); //no accel no xvel
    
    data->plat_moveR = data->plat;
    physics(&(data->plat_moveR), 0, 0, 0, 1); //no accel +5 xvel

    data->plat_moveL = data->plat;
    data->plat_moveL.xvel = -5;   
    physics(&(data->plat_moveL), 0, 0, 0, 1); //no accel -5 xvel
  
    physics(&(data->plat), 2, 0, 0, 1); //low left accel (+1 vel)
    data->plat_low_a = data->plat;
    physics(&(data->plat), 1, 0, 0, 1); //add high accel (+4 vel)
    data->plat_high_a = data->plat;
    physics(&(data->plat), 8, 0, 0, 1); //slow down (-4 vel)
    data->plat_slower = data->plat;
}

CTEST2(plat, test_still) {
    ASSERT_EQUAL(20, (int)data->plat_still.mass); //unchanged
    ASSERT_EQUAL(50, (int)data->plat_still.xpos);
    ASSERT_EQUAL(0, (int)data->plat_still.xvel);
    ASSERT_EQUAL(50, (int)data->plat_still.ypos);
    ASSERT_EQUAL(0, (int)data->plat_still.yvel);  
}

CTEST2(plat, test_move) { //left and right motion
    ASSERT_EQUAL(20, (int)data->plat_moveR.mass); //unchanged
    ASSERT_EQUAL(55, (int)data->plat_moveR.xpos);
    ASSERT_EQUAL(5, (int)data->plat_moveR.xvel);
    ASSERT_EQUAL(50, (int)data->plat_moveR.ypos);
    ASSERT_EQUAL(0, (int)data->plat_moveR.yvel); 

    ASSERT_EQUAL(20, (int)data->plat_moveL.mass); //unchanged
    ASSERT_EQUAL(45, (int)data->plat_moveL.xpos);
    ASSERT_EQUAL(-5, (int)data->plat_moveL.xvel);
    ASSERT_EQUAL(50, (int)data->plat_moveL.ypos);
    ASSERT_EQUAL(0, (int)data->plat_moveL.yvel); 
}

CTEST2(plat, test_slow_v_fast_accel) {
    ASSERT_EQUAL(1, ((int)data->plat_high_a.xvel - (int)data->plat_low_a.xvel) > ((int)data->plat_low_a.xvel - (int)data->plat.xvel)); 

    ASSERT_EQUAL(20, (int)data->plat_low_a.mass); //unchanged
    ASSERT_EQUAL(56, (int)data->plat_low_a.xpos);
    ASSERT_EQUAL(6, (int)data->plat_low_a.xvel);
    ASSERT_EQUAL(50, (int)data->plat_low_a.ypos);
    ASSERT_EQUAL(0, (int)data->plat_low_a.yvel);  

    ASSERT_EQUAL(20, (int)data->plat_high_a.mass);
    ASSERT_EQUAL(66, (int)data->plat_high_a.xpos);
    ASSERT_EQUAL(10, (int)data->plat_high_a.xvel);
    ASSERT_EQUAL(50, (int)data->plat_high_a.ypos);
    ASSERT_EQUAL(0, (int)data->plat_high_a.yvel);

}
CTEST2(plat, test_slow_down) {
    ASSERT_EQUAL(1, ((int)data->plat_high_a.xvel > (int)data->plat_slower.xvel));  

    ASSERT_EQUAL(20, (int)data->plat_slower.mass); //unchanged
    ASSERT_EQUAL(72, (int)data->plat_slower.xpos);
    ASSERT_EQUAL(6, (int)data->plat_slower.xvel);
    ASSERT_EQUAL(50, (int)data->plat_slower.ypos);
    ASSERT_EQUAL(0, (int)data->plat_slower.yvel); 
}
CTEST_DATA(hm_motion) {
    struct object_t hm;
    struct object_t hm_move;
    int grav;
    int border;
    int count;
};

CTEST_SETUP(hm_motion) {
    data->hm.xpos = 50;
    data->hm.ypos = 50;
    data->hm.xvel = 5;
    data->hm.yvel = -60;
    data->hm.mass = 20;
    data->hm.plat_or_hm = 0;
    data->grav = 9;
    data->border = 200;
    data->count = 5;
    
    data->hm_move = data->hm;
    physics(&(data->hm_move), 0, data->grav, 0,  data->hm_move.plat_or_hm);
    physics(&(data->hm_move), 0, data->grav, 0,  data->hm_move.plat_or_hm);
    physics(&(data->hm_move), 0, data->grav, 0,  data->hm_move.plat_or_hm);

}
CTEST2(hm_motion, test_x) { //left and right motion
    ASSERT_EQUAL((int)data->hm.xvel, (int)data->hm.xvel);
}

CTEST2(hm_motion, test_grav) { 
    ASSERT_EQUAL(20, (int)data->hm_move.mass); //unchanged
    ASSERT_EQUAL((int)data->hm.yvel - ((int)data->grav * 3), (int)data->hm_move.yvel);
}

CTEST2(hm_motion, test_crash) { 
    data->hm.ypos = 50;
    ASSERT_EQUAL(0, (int)bounds(&(data->hm), data->hm.plat_or_hm, data->border));
    data->hm.ypos = 201;
    ASSERT_EQUAL(1, (int)bounds(&(data->hm), data->hm.plat_or_hm, data->border));
}

CTEST2(hm_motion, test_reset){
    ASSERT_EQUAL(0, (int)bounds(&(data->hm_move), data->hm_move.plat_or_hm, data->border));
    reset_hm(&(data->hm_move), &(data->count));
    ASSERT_EQUAL(0, (int)data->hm_move.ypos);
    ASSERT_EQUAL(4, (int)data->count);
    reset_hm(&(data->hm_move), &(data->count));
    ASSERT_EQUAL(3, (int)data->count);
}