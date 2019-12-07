/*
 * User_Controller.c
 *
 *  Created on: Dec 5, 2019
 *      Author: AWhit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "UART0.h"
#include "UART1.h"
#include "trainsetInstructionTable.h"
#include "User_Controller.h"
#include "ServiceCalls.h"
#include "Kernel_Calls.h"

static TRAIN train;

/*  Communicates to the user through UART0  */
/*
 * The user enters their desired stop
 * returns: TRUE  if valid
 *          FALSE if invalid
 */

void writeInstruction(INSTRUCTION * instruction){
    char * out = malloc(sizeof(char) * 16);
    if(instruction->rule != STOP){
        writeStringToConsole("\n");
        sprintf(out, "Direct: %i\n",instruction->state.direction);
        writeStringToConsole(out);
        sprintf(out, "Switch: %i\n",instruction->state.swtch);
        writeStringToConsole(out);
        sprintf(out, "Switch State: %i\n",instruction->state.swtch_state);
        writeStringToConsole(out);
    }
    else{
        writeStringToConsole("\n");
        strcpy(out, "STOP:     \n");
        writeStringToConsole(out);
    }
}

void test_table(){
    train.destination = 1;
    train.location = 1;
    INSTRUCTION temp;
    temp = getInstruction(train.destination, train.location);
    writeInstruction(&temp);
}

void testUart1(){
    unsigned char temp = 2;
    setData(temp);
//    unsigned char * = [5,6,9,STX, 1];
}

/*
 * TODO: Gets info from user
 */
void getTrainState(){
    train.location = 1;
    train.destination = 20;
    train.speed = 5;
}

/*
 * This is the process that allows communication between
 * the user and the train set
 */
void Controller_UI(){
    bind(APP_MAILBOX);

    char * msg = malloc(sizeof(char) * MAX_MSG_SZ);

    unsigned char msg_to_train[MAX_CODE_SIZE];

    unsigned char sensor;
    unsigned char swtch;

    /*  Needs initial Train State   */
    getTrainState();
    while(1){
        recv(ANY,ANY,msg, MAX_MSG_SZ);
        switch(msg[CODE])
        {
        case HSENSOR_TRG_IN:
            /*
             * received message - Hall sensor was Triggered by Train
             * Send ACK
             */
            sensor = (unsigned char)msg[ARG1];

            msg_to_train[CODE] = HSENSOR_ACK_OT;
            msg_to_train[ARG1] = sensor;

            break;
        case HSENSOR_ACK_IN:
            /* Train Sent Ack of Sensor Reset */
            break;
        case TRAIN_VEL_ACK:
            /*  Train Sent Ack of Velocity Change   */
            break;
        case SWITCH_THRW_A:
            /*  Train Sent Ack of Switch Throw  */
            break;
        default:
            break;
        }
    }

}
