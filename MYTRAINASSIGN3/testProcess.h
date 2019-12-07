/*
 * testProcess.h
 *
 * header file for testProcess
 *
 * used to declare different functions that are accessible to main where
 * they become registered as processes as required
 *
 * various testing processes are declared here
 *  Created on: Nov 4, 2019
 *      Author: AWhit
 */

#ifndef TESTPROCESS_H_
#define TESTPROCESS_H_

void communications();      //Receives from any and writes contents to UART0
                            //Used to demo receive
void writePID();            //gets process ID and sends to communications
                            //Used to demo send and get pid
/*  T1  */
void spamDisplay1();        //used to demo nice, writes A
void spamDisplay2();        //used to demo nice, writes B
/*  T3  */
void spamDisplayX_DIE();    //use to demo terminate

#endif /* TESTPROCESS_H_ */
