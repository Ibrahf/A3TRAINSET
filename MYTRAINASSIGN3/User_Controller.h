/*
 * User_Controller.h
 *
 *  Created on: Dec 5, 2019
 *      Author: AWhit
 */

#ifndef USER_CONTROLLER_H_
#define USER_CONTROLLER_H_

/*  Train Codes */
#define HSENSOR_TRG_IN     0xA0
#define HSENSOR_ACK_OT     0xA2
#define HSENSOR_REQ_OT     0xA8
#define HSENSOR_ACK_IN     0xAA

#define TRAIN_SET_VEL      0xC0
#define TRAIN_VEL_ACK      0xC2

#define SWITCH_THRW_R      0xE0
#define SWITCH_THRW_A      0xE2

#define CODE    0
#define ARG1    1
#define ARG2    2

#define MAX_MSG_SZ      8

#define MAX_CODE_SIZE   3

#define APP_MAILBOX     2
/*
 * Struct that describes train state
 */
typedef struct train{
    short destination;
    short location;
    short speed;
}TRAIN;


void test_table();

#endif /* USER_CONTROLLER_H_ */
