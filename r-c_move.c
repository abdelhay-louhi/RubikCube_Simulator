

bool stop(RubikCube rc0, RubikCube temp_rc, int numberOfMoves, int c){
    bool b = false;
    int i=0, j=0, k=0;
    for ( k=0; k<6; k++ ){
        for ( i=0; i<3; i++ ){
            for ( j=0; j<3; j++){
                if ( rc0.side[k].rubikElements[i][j] != temp_rc.side[k].rubikElements[i][j] ){
                    b = true;
                    break;
                }
            }
            if ( b ) break;
        }
        if ( b ) break;
    }
    if ( (i==3 && j==3 && k==6) || (c == numberOfMoves)) return 1; // stop
    else return 0;
}
bool solved(RubikCube rc0, RubikCube temp_rc){
    bool b = false;
    int i=0, j=0, k=0;
    for ( k=0; k<6; k++ ){
        for ( i=0; i<3; i++ ){
            for ( j=0; j<3; j++){
                if ( rc0.side[k].rubikElements[0][0] != temp_rc.side[k].rubikElements[i][j] ){
                    b = true;
                    break;
                }
            }
            if ( b ) break;
        }
        if ( b ) break;
    }
    if ( (i==3 && j==3 && k==6) ) return 1; // stop
    else return 0;
}
void cursorGoto(int x, int y){
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
Direction getMove(int c, Direction myMove1, Direction myMove2){
    if ( c%2 ) return myMove1;
    else return myMove2;
}


bool equalTest(Direction dir1, Direction dir2 ){
    int i=0;
    while( dir1.id[i] == dir2.id[i] && i < 3 ){
        i++;
    }
    if ( i == 3 && (dir1.sign * dir2.sign > 0) ) return 1;
    else return 0;
}
Direction absDir(Direction myMove){
    for (int i=0; i<3; i++ ){
        if ( myMove.id[i] == 0 ) myMove.id[i] = 0;
        else myMove.id[i] = 1;
    }
    myMove.sign = 1;
    myMove.len = 1;
    return myMove;
}
int findSide( RubikCube* myRubikCube, Direction myMove, Direction nextDir, bool firstOne){
    int i = -1;
    bool repete = 1;
    Side *side = NULL;
    // Direction absMyMove = absDir(myMove); // sign may not can describe the retation direction 
    do{
        i++;
        side = myRubikCube->side+i;
        if ( equalTest(side->elementsD1, myMove) && ( equalTest(side->sectionD1, nextDir) || firstOne ) ){
            side->dirStatus = 1;
            repete = 0;
        }
        else if ( equalTest(side->elementsD2, myMove) && ( equalTest(side->sectionD2, nextDir) || firstOne ) ){
            side->dirStatus = 0;
            repete = 0;
        } /* else end(-2); */
    }while( repete && (i < 5)  ); // i + 1 < 6
    side->viewStatus = 1;
    return i;
}


Direction noLen(Direction dir){
    Direction noLenD = dir; // "passage par valeur"
    for (int i=0; i<3; i++ ){
        if ( dir.id[i] == 0 ) dir.id[i] = 0;
        else if ( dir.id[i]  > 0 ) dir.id[i] = 1;
        else dir.id[i] = -1;
    }
    dir.len = 1;
    return dir;
}
void thirdDir( Direction dir1, Direction dir2, Direction* the3Dir, Direction myMove){ 
    // vector product
    // return dir1 /\ dir2
    Direction newD1;
    if ( equalTest(dir1, myMove) ) newD1 = noLen(myMove);
    else newD1 = dir1;
    the3Dir->id[0] =  newD1.id[1] * dir2.id[2] - newD1.id[2] * dir2.id[1];
    the3Dir->id[1] = -newD1.id[0] * dir2.id[2] + newD1.id[2] * dir2.id[0];
    the3Dir->id[2] =  newD1.id[0] * dir2.id[1] - newD1.id[1] * dir2.id[0];

    the3Dir->sign = -1;
    int i = 0;
    while (the3Dir->id[i] >= 0 && i <= 2){
        i++;
    }
    if ( i == 3 ) the3Dir->sign = 1;
    the3Dir->len = 1;
}
int opposite( int len){  
    if ( len == 1 ) return 3;
    else if ( len == 3 ) return 1;
    else return 2;
}
void virtualFunction( Side* side, int len, bool visited, int* take, int* put){ 

    // taking 
    if ( side->elementsD1.sign * side->sectionD2.sign == 1 ){
        if ( side->sectionD1.sign * side->elementsD2.sign == 1 ){
            // alignment ff ll 
            for (int i=0; i<3; i++ ){
                take[i] = side->rubikElements[i][len-1]; // I have to reverse lines and columns
            }
        }else{
            // alignment fl lf 
            for (int i=0; i<3; i++ ){
                take[i] = side->rubikElements[i][opposite(len)-1];
            }
        }
    }else{
        if ( side->sectionD1.sign * side->elementsD2.sign == 1 ){
            // noAlingment ff ll 
            for (int i=0; i<3; i++ ){
                take[i] = side->rubikElements[2-i][len-1];
            }
        }else{
            // noAlingment fl lf 
            for (int i=0; i<3; i++ ){
                take[i] = side->rubikElements[2-i][opposite(len)-1];
            }
        }
    }        

    // putting 
    if ( visited ){ // if not the first time function used then enter 
        if ( side->elementsD1.sign * side->sectionD2.sign == 1 ){
            if ( side->sectionD1.sign * side->elementsD2.sign == 1 ){
                // alignment ff ll 
                for (int i=0; i<3; i++ ){
                    side->rubikElements[i][len-1] = put[i];
                }
            }else{
                // alignment fl lf 
                for (int i=0; i<3; i++ ){
                    side->rubikElements[i][opposite(len)-1] = put[i];
                }
            }
        }else{
            if ( side->sectionD1.sign * side->elementsD2.sign == 1 ){
                // noAlingment ff ll 
                for (int i=0; i<3; i++ ){
                    side->rubikElements[i][len-1] = put[2-i];
                }
            }else{
                // noAlingment fl lf 
                for (int i=0; i<3; i++ ){
                    side->rubikElements[i][opposite(len)-1] = put[2-i];
                }
            }
        }          
    }

}
void normalFunction( Side* side, int len, bool visited, int* take, int* put){ 

    // taking 
    for (int i=0; i<3; i++ ){
        *(take+i) = side->rubikElements[len-1][i];
    }

    // putting 
    if ( visited ){ // not first time 
        for (int i=0; i<3; i++ ){
            side->rubikElements[len-1][i] = put[i];
        }
    }

}


void retateSide(Side* side, int retSign){ 
    // retation process
    Side temp_side = *side;
    if ( retSign == 1 ){
        side->rubikElements[0][0] = temp_side.rubikElements[0][2];
        side->rubikElements[2][0] = temp_side.rubikElements[0][0];
        side->rubikElements[2][2] = temp_side.rubikElements[2][0];
        side->rubikElements[0][2] = temp_side.rubikElements[2][2];
        
        side->rubikElements[0][1] = temp_side.rubikElements[1][2];
        side->rubikElements[1][0] = temp_side.rubikElements[0][1];
        side->rubikElements[2][1] = temp_side.rubikElements[1][0];
        side->rubikElements[1][2] = temp_side.rubikElements[2][1];
    }else{
        side->rubikElements[0][0] = temp_side.rubikElements[2][0];
        side->rubikElements[2][0] = temp_side.rubikElements[2][2];
        side->rubikElements[2][2] = temp_side.rubikElements[0][2];
        side->rubikElements[0][2] = temp_side.rubikElements[0][0];
        
        side->rubikElements[0][1] = temp_side.rubikElements[1][0];
        side->rubikElements[1][0] = temp_side.rubikElements[2][1];
        side->rubikElements[2][1] = temp_side.rubikElements[1][2];
        side->rubikElements[1][2] = temp_side.rubikElements[0][1];
    }
}
int findEndSide(RubikCube *myRubikCube){  
    int i = -1;
    Side *side = NULL;
    do{
        i++;
        side = myRubikCube->side+i;
    }while( side->viewStatus == 1 && i < 5 ); // i+1 < 6, attention: if view==1 but i=5 !!! 
    side->viewStatus = 1;
    return i;
}
void retationTest(RubikCube* myRubikCube, Side* side, int len, int moveSign, int testDirSign, int retSign){ 
    int index = 0;
    if ( moveSign * testDirSign == 1){
        if (len == 1 ){ // this side
            retateSide(side, retSign);
        }
        else if ( len == 3 ){ // the other side 
            index = findEndSide(myRubikCube);
            retateSide(myRubikCube->side+index, retSign);
        }
    }else{
        if (len == 1 ){ // the other side 
            index = findEndSide(myRubikCube);
            retateSide(myRubikCube->side+index, retSign);
        }
        else if ( len == 3 ){ // this side
            retateSide(side, retSign);
        }
    }
}
void takeDirValues(Direction* nextDir, Direction myMove){
    Direction dir = noLen(myMove);
    for (int i=0; i<3; i++ ){
        nextDir->id[i] = dir.id[i];
    }
    nextDir->sign = 1;
    nextDir->len = 1;
}


void defaultSidePropreties(RubikCube* myRubikCube){
    for (int i=0; i<6; i++ ){
        (myRubikCube->side[i]).dirStatus = 1;
        (myRubikCube->side[i]).viewStatus = 0;
    }
}
void rubikMove(RubikCube* myRubikCube, Direction myMove){ 

    // sides stream 
    int index = 0;
    Direction *nextDir = (Direction*)malloc(sizeof(Direction));
    takeDirValues(nextDir, myMove);
    Side *side = NULL; // no malloc because I need just one side here, if my thoughts are correct.
    Direction nextSection = myMove;
    bool visited = 0;

    ElementsPot *pot1 = (ElementsPot*)malloc(sizeof(ElementsPot));  
    ElementsPot *pot2 = (ElementsPot*)malloc(sizeof(ElementsPot)); 
    pot1->pot = (int*)malloc(3*sizeof(int)); 
    pot2->pot = (int*)malloc(3*sizeof(int)); 
    pot1->potStatus = 0;
    pot2->potStatus = !(pot1->potStatus);
    int *take = (int*)malloc(3*sizeof(int)); 
    int *put = (int*)malloc(3*sizeof(int));  
    int retSign;

    int counter = 5;
    while( counter-- ){ 
        // finding 
        index = findSide(myRubikCube, myMove, *nextDir, !visited);
        side = myRubikCube->side+index;

        if (pot1->potStatus == 0){
            take = pot1->pot;
            put = pot2->pot;
            pot1->potStatus = 1;
        }else{
            take = pot2->pot;
            put = pot1->pot;
            pot1->potStatus = 0;
        }

        if ( side->dirStatus == 1 ){   // normal directions 
            normalFunction(side, myMove.len, visited, take, put);
            // next 
            nextSection = side->sectionD1;
        }else{   // virtual directions 
            virtualFunction(side, myMove.len, visited, take, put);
            // next 
            nextSection = side->sectionD2;
        }
        // next 
        thirdDir(myMove, nextSection, nextDir, myMove);
        if (  !visited ) visited = 1;
        if ( !(counter-4) ) retSign = nextDir->sign;
    }
    free(nextDir);
    free(pot1->pot); free(pot2->pot); 
    free(pot1); free(pot2);

    // end sides 
    Direction *testDir = (Direction*)malloc(sizeof(Direction));
    index = findEndSide(myRubikCube);
    side = side+index;
    if ( side->dirStatus == 1 )
        thirdDir(side->elementsD1, side->sectionD1, testDir, myMove);
    else
        thirdDir(side->elementsD2, side->sectionD2, testDir, myMove);
    retationTest(myRubikCube, side, myMove.len, myMove.sign, testDir->sign, retSign);
    free(testDir);

    // default properties 
    defaultSidePropreties(myRubikCube); 

}
