/*
 * trainsetInstructionTable.c
 *
 *  Created on: Dec 4, 2019
 *      Author: AWhit
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "trainsetInstructionTable.h"

#define INSTRUCTION_SIZE 24
#define OFFSET -1

/*
 * Returns instruction detailing next step for train
 * called by handler when Crossing Hall Sensor
 */
INSTRUCTION getInstruction(short to, short from){
    static const INSTRUCTION lookupTable[INSTRUCTION_SIZE][INSTRUCTION_SIZE] =
    {
/*        1            2         3        4        5          6         7         8        9        10         11         12        13       14       15        16         17        18       19        20         21        22        23        24                                         */
/* 1 */{{.rule = STOP},{CCW,6,S},       {CCW,6,S},      {CCW,6,S},      {CCW,6,S},      {CCW,6,S},  {CCW,6,S},{CCW,6,S},{CCW,6,S},{CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CCW,6,D},{CCW,6,D},{CW},     {CW},     {CCW,6,S},{CCW,6,S},{CW},     {CW}     },
/* 2 */{{CW},          {.rule = STOP},  {CW},           {CW},           {CW},           {CW},       {CW},     {CW},     {CW},     {CW},     {CW,6,S}, {CW,6,S}, {CW,6,S}, {CW,6,S}, {CW,6,S}, {CW,6,S}, {CW,6,S}, {CW},     {CW},     {CW,6,S}, {CW},     {CW},     {CW,6,S}, {CW,6,S} },
/* 3 */{{CW},          {CCW,5,S},       {.rule = STOP}, {CCW,5,S},      {CCW,5,S},      {CCW,5,S},  {CCW,5,S},{CCW,5,S},{CCW,5,S},{CCW,5,S},{CCW,5,S},{CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CCW,5,S},{CCW,5,S},{CCW,5,S},{CW},     {CCW,5,S},{CCW,5,S},{CCW,5,S}},
/* 4 */{{CW,5,S},      {CW,5,S},        {CW,5,S},       {.rule = STOP}, {CCW},          {CCW},      {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW,5,S}, {CW,5,S}, {CW,5,S}, {CW,5,S}, {CW,5,S}, {CCW},    {CCW},    {CW,5,S}, {CW,5,S}, {CW,5,S}, {CCW},    {CCW}    },
/* 5 */{{CW},          {CW},            {CW},           {CW},           {.rule = STOP}, {CCW,4,S},  {CCW,4,S},{CCW,4,S},{CCW,4,S},{CCW,4,S},{CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CCW,4,S},{CCW,4,S},{CW},     {CW},     {CW},     {CCW,4,S},{CCW,4,S}},
/* 6 */{{CW,4,S},      {CW,4,S},        {CW,4,S},       {CW,4,S},       {CW,4,S},       {.rule = STOP},   {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW,4,S}, {CW,4,S}, {CW,4,D}, {CW,4,D}, {CW,4,S}, {CCW},    {CW,4,S}, {CW,4,S}, {CW,4,S}, {CCW},    {CCW}    },
/* 7 */{{CW},          {CW},            {CW},           {CW},           {CW},           {CW},     {.rule = STOP},   {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW},     {CW},     {CW},     {CW},     {CCW},    {CCW},    {CW},     {CW},     {CCW},    {CCW}    },
/* 8 */{{CW},          {CW},            {CW},           {CW},           {CW},           {CW},     {CW},     {.rule = STOP},   {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW},     {CW},     {CCW},    {CCW},    {CW},     {CW},     {CCW},    {CCW}    },
/* 9 */{{CW},          {CW},            {CW},           {CW},           {CW},           {CW},     {CW},     {CW},     {.rule = STOP},   {CCW,3,S},{CCW,3,S},{CCW,3,S},{CCW,3,S},{CCW,3,S},{CCW,3,S},{CCW,3,S},{CW},     {CW},     {CCW,3,D},{CCW,3,D},{CW},     {CW},     {CCW,3,S},{CCW,3,S}},
/* 10*/{{CCW},         {CW,3,S},        {CW,3,S},       {CW,3,S},       {CW,3,S},       {CW,3,S}, {CW,3,S}, {CW,3,S}, {CW,3,S}, {.rule = STOP},   {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW,3,S}, {CW,3,S}, {CW,3,S}, {CW,3,S}, {CW,3,S}, {CCW},    {CCW}    },
/* 11*/{{CCW,2,S},     {CCW,2,S},       {CW},           {CW},           {CW},           {CW},     {CW},     {CW},     {CW},     {CW},     {.rule = STOP},   {CCW,2,S},{CCW,2,S},{CCW,2,S},{CCW,2,S},{CCW,2,S},{CCW,2,S},{CW},     {CW},     {CCW,2,S},{CW},     {CW},     {CCW,2,D},{CCW,2,D}},
/* 12*/{{CCW},         {CCW},           {CCW},          {CCW},          {CW,2,S},       {CW,2,S}, {CW,2,S}, {CW,2,S}, {CW,2,S}, {CW,2,S}, {CW,2,S}, {.rule = STOP},   {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW,2,S}, {CCW},    {CW,2,S}, {CCW},    {CCW},    {CW,2,S}, {CW,2,S} },
/* 13*/{{CCW,1,S},     {CCW,1,S},       {CCW,1,S},      {CCW,1,S},      {CW},           {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {.rule = STOP},   {CCW,1,S},{CCW,1,S},{CCW,1,S},{CCW,1,S},{CW},     {CW},     {CW},     {CCW,1,S},{CCW,1,S},{CW},     {CW}     },
/* 14*/{{CCW},         {CCW},           {CCW},          {CCW},          {CCW},          {CW,1,S}, {CW,1,S}, {CW,1,S}, {CW,1,S}, {CW,1,S}, {CW,1,S}, {CW,1,S}, {CW,1,S}, {.rule = STOP},   {CCW},    {CCW},    {CCW},    {CW,1,S}, {CW,1,S}, {CW,1,D}, {CCW},    {CCW},    {CW,1,S}, {CW,1,S} },
/* 15*/{{CCW},         {CCW},           {CCW},          {CCW},          {CCW},          {CCW},    {CCW},    {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {.rule = STOP},   {CCW},    {CCW},    {CW},     {CW},     {CW},     {CCW},    {CCW},    {CW},     {CW}     },
/* 16*/{{CCW},         {CCW},           {CCW},          {CCW},          {CCW},          {CCW},    {CCW},    {CCW},    {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {.rule = STOP},   {CCW},    {CCW},    {CW},     {CW},     {CCW},    {CCW},    {CW},     {CW}     },
/* 17*/{{CW,6,D},      {CW,6,D},        {CW,6,D},       {CCW},          {CCW},          {CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW,6,D}, {CW,6,D}, {CW,6,D}, {CW,6,D}, {CW,6,D}, {CW,6,D}, {.rule = STOP},   {CCW},    {CCW},    {CW,6,D}, {CW,6,D}, {CW,6,D}, {CW,6,D}, {CW,6,D} },
/* 18*/{{CW},          {CW},            {CW},           {CCW,4,D},      {CCW,4,D},      {CCW,4,D},{CCW,4,D},{CCW,4,D},{CCW,4,D},{CCW,4,D},{CCW,4,D},{CCW,4,D},{CCW,4,D},{CW},     {CW},     {CW},     {CW},     {.rule = STOP},   {CCW,4,D},{CW},     {CW},     {CW},     {CCW,4,D},{CCW,4,D}},
/* 19*/{{CCW},         {CCW},           {CCW,3,D},      {CCW,3,D},      {CCW,3,D},      {CCW,3,D},{CCW,3,D},{CCW,3,D},{CCW,3,D},{CCW,3,D},{CCW,3,D},{CCW,3,D},{CCW},    {CCW},    {CCW},    {CCW},    {CCW},    {CW,3,D}, {.rule = STOP},   {CCW},    {CCW,3,D},{CCW,3,D},{CCW,3,D},{CCW,3,D}},
/* 20*/{{CCW,1,D},     {CCW,1,D},       {CCW,1,D},      {CCW,1,D},      {CW},           {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CCW,1,D},{CCW,1,D},{CCW,1,D},{CCW,1,D},{CCW,1,D},{CCW,1,D},{CCW},    {CCW},    {.rule = STOP},   {CCW},    {CCW},    {CCW},    {CCW}    },
/* 21*/{{CW,5,D},      {CW,5,D},        {CW,5,D},       {CW,5,D},       {CW,5,D},       {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {CW,5,D}, {.rule = STOP},   {CCW},    {CW,5,D}, {CW,5,D} },
/* 22*/{{CW},          {CW},            {CW},           {CW},           {CW},           {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {.rule = STOP},   {CW},     {CW},    },
/* 23*/{{CW,2,D},      {CW,2,D},        {CW,2,D},       {CW,2,D},       {CW,2,D},       {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {CW,2,D}, {.rule = STOP},   {CCW}    },
/* 24*/{{CW},          {CW},            {CW},           {CW},           {CW},           {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {CW},     {.rule = STOP}   }
    };

    return lookupTable[from+OFFSET][to+OFFSET];
}



