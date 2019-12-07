/**
 *
 * This Software allows for multiple processes, at given priority levels,
 * to operate pseudo-simultaneously.
 * Each process must be of type void with no return value.
 * These processes can:
 *      Request their process ID
 *      Change priority Levels
 *      terminate
 *
 * and this software supports inter-process communication where
 * each process can request a mailbox from the kernel, once
 * a mailbox is allocated to the process, the process can
 *      Send Messages
 *      Receive Messages
 *      relieve control over their mailbox
 *
 * Author: Alexander Whittaker
 * Fall 2019
 */

#include <stdio.h>
#include <stdlib.h>

#include "UART0.h"
#include "sysTick.h"
#include "Process.h"
#include "registerProcess.h"
#include "testProcess.h"
#include "priorityQueue.h"
#include "ServiceCalls.h"

/*  -------------------------   */
#include "trainsetInstructionTable.h"
#include "UART1.h"
#include "User_Controller.h"

//Initializes the UART interrupts and SysTick
void main (void){

    /* initializes each priority level  */
    initPriorityQueue();
    /*  Initializes Mailbox Messaging Structure   */
    initMailBoxList();

    func_name testT = &test_table;
    reg_proc(testT,2,3);

    func_name communication = &communications;
    reg_proc(communication, 1, 4);


    UART0_Init();                                // Initialize UART0
    InterruptEnable(INT_VEC_UART0);              // Enable UART0 interrupts
    UART0_IntEnable(UART_INT_RX | UART_INT_TX);  // Enable Receive and Transmit interrupts

    /* Sets the period at which the System Clock Increments*/
    SysTickPeriod(MAX_WAIT);

    /*  Initializes PendSV For Context Switching between processes  */
    init_PendSVPriority();


    /*  Traps to the kernel to instance first process   */
    SVC();

    /*  Never Reaches This point   */

}






