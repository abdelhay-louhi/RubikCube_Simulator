
typedef struct Direction{
    int id[3];
    int sign;
    int len; // length
} Direction;

typedef struct Side{
    int rubikElements[3][3];
    Direction sectionD1;
    Direction sectionD2;
    Direction elementsD1;
    Direction elementsD2;
    bool dirStatus;  // 1 normal or 0 virtual direction
    bool viewStatus; // viewed or not 
} Side;

typedef struct RubikCube{
    Side side[6];
} RubikCube;

typedef struct ElementsPot{
    int *pot;
    bool potStatus; // empty or filled 
} ElementsPot;
