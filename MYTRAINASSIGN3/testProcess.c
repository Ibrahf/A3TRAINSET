/*
 * testProcess.c
 *
 *
 * These functions are the process which run synchronously
 * they are used for testing the other software
 * Each process is a C function of type void
 *
 * Any Function can be written here and registered in main as long as
 * it is of type void with no return value
 *
 *  Created on: Nov 4, 2019
 *      Author: AWhit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UART0.h"
#include "Kernel_Calls.h"
#include "ServiceCalls.h"
#include "testProcess.h"




/*
 * These two test functions are used to demonstrate nice
 * The are to be initialized at the same priority that is not
 * priority 4. When spamDisplay 2 writes B 10 times, it calls nice
 * at which time it holds priority and writes nice the remaining
 * 20 times. these are arbitrary numbers
 */
void spamDisplay1(){
    char *out = "A";
    int i;
    for(i=0;i<30;i++){
        writeStringToConsole("\n");
        writeStringToConsole(out);
    }
}
void spamDisplay2(){
    char *out = "B";
    int i;
    for(i=0;i<10;i++){
        writeStringToConsole("\n");
        writeStringToConsole(out);
    }
    nice(4);
    for(i=0;i<20;i++){
        writeStringToConsole("\n");
        writeStringToConsole(out);
    }
}


/*
 * Test process: Writes X directly to the console
 * and then terminates
 */
void spamDisplayX_DIE(){
    unsigned int i;
    char *out = "X";
    for(i=0;i<100;i++){
        writeStringToConsole(out);
    }
}


/*
 * Process that gets its PID from kernel
 * and sends it to the communications process
 * which writes to UART0
 */
void writePID(){

    unsigned long pid;
    pid = get_pid();
    char * out = malloc(sizeof(char)*2);
    bind(4);
    sprintf(out, "%i", pid);
    send(1, 4, out, 2);

}

/*
 * The communication process
 * Receives from any, writes contents to UART0
 */
void communications(){
    bind(1);
    line_cursor line = {ESC, '[', '0', '1', ';', '0', '0', 'H', NUL};
    char * out = malloc(sizeof(char) * MAX_LETTER_SIZE);
    int cur_line = 1;
    while(1){
        if(recv(ANY, ANY, out, MAX_LETTER_SIZE ) > 0){
//            writeStringToConsole("\n");
            writeStringToConsole((char *)&line);
            writeStringToConsole(out);
            cur_line++;
            line.line[1] = '0' + cur_line%10;
            line.line[0] = '0' + cur_line/10;
        }
    }
}

