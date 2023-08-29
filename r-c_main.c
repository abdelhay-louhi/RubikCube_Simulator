
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#include "r-c_data.c"
#include "r-c_move.c"


#define x1 1 // def       vector
#define y1 0 //    in  a  
#define z1 0 //      e 
#define s1 1 // vector sign: 1 or -1
#define l1 1 //  1 <= l1,l2 <= 3

#define x2 0
#define y2 -1
#define z2 0
#define s2 -1 
#define l2 1

#define sleepTime 1000/20
#define numberOfMoves 300


int main(void){

    RubikCube myRubikCube;

    defaultSidePropreties(&myRubikCube);

    enteringData(&myRubikCube);

    directionDefinition(&myRubikCube);
    
    Direction myMove;
    Direction myMove1, myMove2;
    myMove1.id[0] = x1; myMove2.id[0] = x2;
    myMove1.id[1] = y1; myMove2.id[1] = y2;
    myMove1.id[2] = z1; myMove2.id[2] = z2;
    myMove1.sign = s1;  myMove2.sign = s2;
    myMove1.len = l1;    myMove2.len = l2;
    
    int c = 2;
    RubikCube rc0 = myRubikCube;
    bool end;
    do{
        c++;
        myMove = getMove(c, myMove1, myMove2);
        rubikMove(&myRubikCube, myMove);
        cursorGoto(0, 0);
        printingData(myRubikCube);
        printf("\n -> counter = %d ", c-2);
        Sleep(sleepTime);
        end = stop(rc0, myRubikCube, numberOfMoves, c-2) || solved(rc0, myRubikCube);
    }while( !end );

    if ( numberOfMoves - (c-2) > 0 )
        printf(" \n\n \" SOLVED OR THE SAME RUBIK_CUBE IS FONDED AT %d / %d. \" \n\n", c-2, numberOfMoves);
    else if ( numberOfMoves - (c-2) < 0 )
        printf(" \n\n \" SOMETHING GOES WRONG !!! (numberOfMoves done > numberOfMoves). \" \n\n");
    else
        printf(" \n\n \" X.X.X NOT SOLVED OR THE SAME RUBIK_CUBE IS NOT FONDED. \" \n\n");
    
    return 1;
}
