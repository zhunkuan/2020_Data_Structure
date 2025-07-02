#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>

using namespace std;

class playing_space{
    private:
        bool **space;                       // The matrix of playing space.
        int row;
        int col;
    public:
        playing_space():row(0), col(0){}
        playing_space(int ROW, int COL);    // Initializing the playing space.
        ~playing_space();                                    
        void drop(class block &B);
        bool delete_row(int row_deleted);
        bool delete_check(int read_row);
        bool check_over();                  // Check if it is out of range.
        void print();   
        //void print_real_space();
};

playing_space::playing_space(int ROW, int COL):row(ROW + 4), col(COL){
    space = new bool*[row];                 // Row + 4 prevent the block from  
    for (int i = 0; i < row; ++i)           // out of the matrix.
        space[i] = new bool[COL];
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < COL; ++j)
            space[i][j] = 0;                // Initialize.
}

playing_space::~playing_space(){
    for (int i = 0; i < row; ++i)
        delete space[i];
    delete space;
}

void playing_space::drop(block &B){
    bool stop = false;
    for (int i = B.now_row; (i < row - 1) && (!stop); i++)
    { 
        for (int j = 0; (j < B.stop_size) && (!stop); ++j)
        {
            if (space[i - B.lowest_block_position[j] + 1][B.initial_position + j])
                stop = true;
        }
        if (!stop) B.now_row++;
    }
    for (int i = 0; i < 4; ++i)
        space[B.now_row - B.block_position[i][0]][B.initial_position + B.block_position[i][1]] = true;
}

bool playing_space::check_over(){                   // Use the first 4 row of row + 4 
    for (int i = 0; i < 4; ++i)                     // to determine whether it is out 
        for (int j = 0; j < col; ++j)               // of range or not.
            if (space[i][j]) return true;
    return false;
}

bool playing_space::delete_row(int row_deleted){
    bool delete_done = false;
    if (delete_done = delete_check(row_deleted)){
        for (int i  = row_deleted; i >= 1; --i)     // Let all the rows above the deleted row
            for (int j = 0; j < col; ++j)           // go down one row.
                space[i][j] = space[i - 1][j];
    }
    for (int i = 0; i < col; ++i)                   // We don't know what are the values of the 
        space[0][i] = false;                        // first row if we done the code above,
    return delete_done;                             // so we set it to 0.
}

bool playing_space::delete_check(int read_row){
    int sum = 0;
    for (int i = 0; i < col; ++i){                  // If the value of the read row are all 1,
        sum += space[read_row][i];                  // return true.
    }
    if (sum == col) return true;
    else return false;
}

void playing_space::print(){
    
    fstream file;
    
    file.open("108061147_proj1.final", ios::out);
    if (!file.good()){
        cout << "Output fails.\n";
        return;
    }

    char *arr;
    arr = new char[col + 1];
    
    for (int i = 4; i < row; ++i){        
        for (int j = 0; j < col; ++j){   
            if (space[i][j]) arr[j] = '1';
            else arr[j] = '0';
            file << arr[j] << " ";
        }
            arr[col] = '\n';
            file << arr[col];
    }
    file.close();
}

class block{
    friend playing_space;
    protected:
        int stop_size;
        int *lowest_block_position;  
            // when lowest_block_position[i] = 1, it means the the block itself
            // is at the second row regarding the row of reference point is row 1, and i means
            // i column far from the reference point
        int block_position[4][2];     // block exact position
                                      // arrange by {row, colume}
        int now_row;
        int initial_position;
    public:
    virtual ~block(){};
    int get_row();
};

int block::get_row(){
    return now_row;
}

class T_block:public block{
    public:
    T_block(){}
    T_block(int initial_place, int type);
    ~T_block();

};

T_block::T_block(int initial_place, int type){
    
    now_row = 3;
    initial_position = initial_place;
    
    if (type == 1)
    {        
        stop_size = 3;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 1;
        lowest_block_position[1] = 0;
        lowest_block_position[2] = 1;

        block_position[0][0] = 0;
        block_position[0][1] = 1;
        block_position[1][0] = 1;
        block_position[1][1] = 0;
        block_position[2][0] = 1;
        block_position[2][1] = 1;
        block_position[3][0] = 1; 
        block_position[3][1] = 2;
    }
    else if (type == 2)
    {
        stop_size = 2;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 1;
        lowest_block_position[1] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 1;
        block_position[1][0] = 1;
        block_position[1][1] = 0;
        block_position[2][0] = 1;
        block_position[2][1] = 1;
        block_position[3][0] = 2; 
        block_position[3][1] = 1;
    }
    else if (type == 3)
    {
        stop_size = 3;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 0;
        lowest_block_position[2] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 0;
        block_position[1][1] = 1;
        block_position[2][0] = 0;
        block_position[2][1] = 2;
        block_position[3][0] = 1; 
        block_position[3][1] = 1;
    }
    else if (type == 4)
    {
        stop_size = 2;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 1;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 1;
        block_position[1][1] = 0;
        block_position[2][0] = 1;
        block_position[2][1] = 1;
        block_position[3][0] = 2; 
        block_position[3][1] = 0;
    }
    else cout << "Invalid input." << endl;
}

T_block::~T_block(){delete lowest_block_position;}

class L_block:public block{
    public:
    L_block(){}
    L_block(int initial_place, int type);
    ~L_block();
};



class J_block:public block{
    public:
    J_block(){}
    J_block(int initial_place, int type);
    ~J_block();
};

class S_block:public block{
    public:
    S_block(){}
    S_block(int initial_place, int type);
    ~S_block();
};

class Z_block:public block{
    public:
    Z_block(){}
    Z_block(int initial_place, int type);
    ~Z_block();
};

class I_block:public block{
    public:
    I_block(){}
    I_block(int initial_place, int type);
    ~I_block();
};

class O_block:public block{
    public:
    O_block(){}
    O_block(int initial_place);
    ~O_block();
};

int main(int argc, char* argv[]){
    
    ifstream FILEIN;

    FILEIN.open(argv[1], ios::in);
    if (!FILEIN.good()){
        cout << "Open fails.\n";
        return 0;
    }

    int row, col;
    char ch[50];
    int first;
    bool gameover = false;

    FILEIN >> row >> col;
    playing_space space (row, col);
    FILEIN >> ch;
    while (strcmp(ch, "End") && !gameover)
    {    
        char type;
        int type_number;

        if (ch[0] != 'O') {                 // There are different types of blocks
            type_number = atoi(&ch[1]);     // except "O", so we separate them by
            type = ch[0];                   // using "type_number" and "type".
        }
        else type = ch[0];

        FILEIN >> first;                    // Read the initial position.
        first--;
        block *B;

        if (!gameover)
        {   
            if (type == 'T')     
                B = new T_block(first, type_number);
            else if (type == 'L')
                B = new L_block(first, type_number);
            else if (type == 'J')
                B = new J_block(first, type_number); 
            else if (type == 'S')
                B = new S_block(first, type_number); 
            else if (type == 'Z')
                B = new Z_block(first, type_number); 
            else if (type == 'I')
                B = new I_block(first, type_number); 
            else
                B = new O_block(first);
            space.drop(*B);
            for (int i = 0, k = 0; i < 4; ++i)
            {    
                if ((B->get_row() - k) >= 4 && space.delete_row(B->get_row() - k));
                else k++;
            }
            gameover = space.check_over();
            delete B;
        }
        if (!gameover) FILEIN >> ch;
    }
    space.print();
    FILEIN.close();
    return 0;
}