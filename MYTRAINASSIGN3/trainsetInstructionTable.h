/*
 * trainsetInstructionTable.h
 *
 *  Created on: Dec 4, 2019
 *      Author: AWhit
 */

#ifndef TRAINSETINSTRUCTIONTABLE_H_
#define TRAINSETINSTRUCTIONTABLE_H_


#define STOP 0x20

#define CW  0   // -
#define CCW 1   // +

#define S 0     //straight
#define D 1     //diverge

/*
 * Defines an Instruction
 * used to store state
 * state can either be explicit (stop)
 * or a series of instructions
 *          Direction       ->required direction of travel  [CCW | CW]
 *          switch          ->id of switch to operate upon  [1-6]
 *          switch state    ->state of switch   [S | D]
 *  If switch id is zero, no switch requires state change
 *
 */

typedef struct tr_state{
    unsigned short direction    : 1;
    unsigned short swtch        : 3;
    unsigned short swtch_state  : 1;
}STATE;

typedef union instruction{
        STATE state;
        short rule;
}INSTRUCTION;

INSTRUCTION getInstruction(short to, short from);


#endif /* TRAINSETINSTRUCTIONTABLE_H_ */
