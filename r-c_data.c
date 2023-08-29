
#include "r-c_structs.c"


void enteringData(RubikCube* myRubikCube){
    FILE *myfile;
    myfile = fopen("r-c_data.txt", "r");
    if (myfile == NULL) {
        printf("Error: Failed to open file = rdata.txt \n");
        exit(-1);
    }
    for ( int k=0; k<6; k++ ){
        for (int i=0; i<3; i++ ){
            for (int j=0; j<3; j++ ){
                fscanf(myfile, "%d", &(myRubikCube->side[k]).rubikElements[i][j]);
            }
            // getchar();
        }
        // getchar();
    }
    fclose(myfile);
} // add later: is that rubik cube entred exist or there an error.
void printingData(RubikCube myRubikCube){
    printf("\n-------------------------------\n");
    for ( int k=0; k<6; k++ ){
        for (int i=0; i<3; i++ ){
            for (int j=0; j<3; j++ ){
                printf(" %d ", myRubikCube.side[k].rubikElements[i][j] );
            }
            printf("\n");
        }
        printf("\n-------------------------------\n");
    }
}
void directionDefinition(RubikCube* myRubikCube){

    FILE *myfile;
    myfile = fopen("r-c-d_data.txt", "r"); // directions Data
    if (myfile == NULL) {
        printf("Error: Failed to open file = ddata.txt \n");
        exit(-1);
    }
    for ( int k=0; k<6; k++ ){
        for (int i=0; i<3; i++ ){
            fscanf(myfile, "%d", &(myRubikCube->side[k]).elementsD1.id[i] );
        }
        fscanf(myfile, "%d", &(myRubikCube->side[k]).elementsD1.sign );

        for (int i=0; i<3; i++ ){
            fscanf(myfile, "%d", &(myRubikCube->side[k]).sectionD1.id[i] );
        }
        fscanf(myfile, "%d", &(myRubikCube->side[k]).sectionD1.sign );

        for (int i=0; i<3; i++ ){
            fscanf(myfile, "%d", &(myRubikCube->side[k]).elementsD2.id[i] );
        }
        fscanf(myfile, "%d", &(myRubikCube->side[k]).elementsD2.sign );

        for (int i=0; i<3; i++ ){
            fscanf(myfile, "%d", &(myRubikCube->side[k]).sectionD2.id[i] );
        }
        fscanf(myfile, "%d", &(myRubikCube->side[k]).sectionD2.sign );

        (myRubikCube->side[k]).elementsD1.len = 1;
        (myRubikCube->side[k]).sectionD1.len = 1;
        (myRubikCube->side[k]).elementsD2.len = 1;
        (myRubikCube->side[k]).sectionD2.len = 1;
    }
    fclose(myfile);
    
}
