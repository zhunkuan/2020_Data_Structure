#include "class.h"
#include <fstream>
////////////////////////////////////////////////////////////////////
/*
    start of the definition of playing_space
*/
////////////////////////////////////////////////////////////////////
playing_space::playing_space(int ROW, int COL):row(ROW + 4), col(COL){
    space = new bool*[row];
    for (int i = 0; i < row; ++i)
        space[i] = new bool[COL];
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < COL; ++j)
            space[i][j] = 0;
}

playing_space::~playing_space(){
    for (int i = 0; i < row; ++i)
        delete space[i];
    delete space;
}

void playing_space::drop(block &d_b){
    bool stop = false;
    for (int i = d_b.now_row; (i < row - 1) && (!stop); i++)
    { 
        for (int j = 0; (j < d_b.stop_size) && (!stop); ++j)
        {
            if (space[i - d_b.lowest_block_position[j] + 1][d_b.initial_position + j])
                stop = true;
        }
        if (!stop) d_b.now_row++;
    }
    for (int i = 0; i < 4; ++i)
        space[d_b.now_row - d_b.block_position[i][0]][d_b.initial_position + d_b.block_position[i][1]] = true;

}

bool playing_space::check_over(){
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < col; ++j)
            if (space[i][j]) return true;
    return false;
}

bool playing_space::delete_check(int read_row){
    int sum = 0;
    for (int i = 0; i < col; ++i)
    {
        sum += space[read_row][i];
    }
    if (sum == col) return true;
    else return false;
}

bool playing_space::delete_row(int row_deleted){
    bool delete_done = false;
    if (delete_done = delete_check(row_deleted))
    {
        for (int i  = row_deleted; i >= 1; --i)
            for (int j = 0; j < col; ++j)
                space[i][j] = space[i - 1][j];
    }
    for (int i = 0; i < col; ++i)
        space[0][i] = false;
    return delete_done;
}

void playing_space::print(){

    fstream file;
    char *arr;
    arr = new char[col + 1];
    file.open("Tetris.final",  ios::out | ios::trunc);

    if (!file.is_open()) 
    {
        cout << "close file fails!\n";
        return;
    }

    for (int i = 4; i < row; ++i)
    {        
        for (int j = 0; j < col; ++j)
        {   
            if (space[i][j])       
                arr[j] = '1';
            else arr[j] = '0';
        }
            arr[col] = '\n';
            file.write(arr, col + 1);
    }
    
    file.close();
    if (file.is_open()) cout << "close file fails!\n";

}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of playing_space
*/
////////////////////////////////////////////////////////////////////

int block::get_now_row(){
    return now_row;
}

////////////////////////////////////////////////////////////////////
/*
    start of the definition of T_block
*/
////////////////////////////////////////////////////////////////////

T_block::T_block(int initial_place, int type){
    
    now_row = 3;
    initial_position= initial_place;
    
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
    else cout << "invalid input!!" << endl;

}
T_block::~T_block(){delete lowest_block_position;}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of T_block
*/
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
/*
    start of the definition of L_block
*/
////////////////////////////////////////////////////////////////////

L_block::L_block(int initial_place, int type){
    
    now_row = 3;
    initial_position= initial_place;
    
    if (type == 1)
    {        
        stop_size = 2;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 0;
        block_position[1][1] = 1;
        block_position[2][0] = 1;
        block_position[2][1] = 0;
        block_position[3][0] = 2; 
        block_position[3][1] = 0;
    }
    else if (type == 2)
    {
        stop_size = 3;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 1;
        lowest_block_position[2] = 1;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 1;
        block_position[1][1] = 0;
        block_position[2][0] = 1;
        block_position[2][1] = 1;
        block_position[3][0] = 1; 
        block_position[3][1] = 2;
    }
    else if (type == 3)
    {
        stop_size = 2;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 2;
        lowest_block_position[1] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 1;
        block_position[1][0] = 1;
        block_position[1][1] = 1;
        block_position[2][0] = 2;
        block_position[2][1] = 0;
        block_position[3][0] = 2; 
        block_position[3][1] = 1;
    }
    else if (type == 4)
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
        block_position[3][1] = 2;
    }
    else cout << "invalid input!!" << endl;

}
L_block::~L_block(){delete lowest_block_position;}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of L_block
*/
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
/*
    start of the definition of J_block
*/
////////////////////////////////////////////////////////////////////

J_block::J_block(int initial_place, int type){
    
    now_row = 3;
    initial_position= initial_place;
    
    if (type == 1)
    {        
        stop_size = 2;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 0;
        block_position[1][1] = 1;
        block_position[2][0] = 1;
        block_position[2][1] = 1;
        block_position[3][0] = 2; 
        block_position[3][1] = 1;
    }
    else if (type == 2)
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
        block_position[3][1] = 0;
    }
    else if (type == 3)
    {
        stop_size = 2;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 2;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 1;
        block_position[1][1] = 0;
        block_position[2][0] = 2;
        block_position[2][1] = 0;
        block_position[3][0] = 2; 
        block_position[3][1] = 1;
    }
    else if (type == 4)
    {
        stop_size = 3;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 1;
        lowest_block_position[1] = 1;
        lowest_block_position[2] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 2;
        block_position[1][0] = 1;
        block_position[1][1] = 0;
        block_position[2][0] = 1;
        block_position[2][1] = 1;
        block_position[3][0] = 1; 
        block_position[3][1] = 2;
    }
    else cout << "invalid input!!" << endl;

}
J_block::~J_block(){delete lowest_block_position;}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of J_block
*/
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
/*
    start of the definition of S_block
*/
////////////////////////////////////////////////////////////////////

S_block::S_block(int initial_place, int type){
    
    now_row = 3;
    initial_position= initial_place;
    
    if (type == 1)
    {        
        stop_size = 3;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 0;
        lowest_block_position[2] = 1;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 0;
        block_position[1][1] = 1;
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
        block_position[3][1] = 0;
    }
    else cout << "invalid input!!" << endl;

}
S_block::~S_block(){delete lowest_block_position;}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of S_block
*/
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
/*
    start of the definition of Z_block
*/
////////////////////////////////////////////////////////////////////

Z_block::Z_block(int initial_place, int type){
    
    now_row = 3;
    initial_position= initial_place;
    
    if (type == 1)
    {        
        stop_size = 3;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 1;
        lowest_block_position[1] = 0;
        lowest_block_position[2] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 1;
        block_position[1][0] = 0;
        block_position[1][1] = 2;
        block_position[2][0] = 1;
        block_position[2][1] = 0;
        block_position[3][0] = 1; 
        block_position[3][1] = 1;
    }
    else if (type == 2)
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
        block_position[3][1] = 1;
    }
    else cout << "invalid input!!" << endl;

}
Z_block::~Z_block(){delete lowest_block_position;}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of Z_block
*/
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
/*
    start of the definition of I_block
*/
////////////////////////////////////////////////////////////////////

I_block::I_block(int initial_place, int type){
    
    now_row = 3;
    initial_position= initial_place;
    
    if (type == 1)
    {        
        stop_size = 1;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 1;
        block_position[1][1] = 0;
        block_position[2][0] = 2;
        block_position[2][1] = 0;
        block_position[3][0] = 3; 
        block_position[3][1] = 0;
    }
    else if (type == 2)
    {
        stop_size = 4;
        lowest_block_position = new int[stop_size];
        lowest_block_position[0] = 0;
        lowest_block_position[1] = 0;
        lowest_block_position[2] = 0;
        lowest_block_position[3] = 0;

        block_position[0][0] = 0;
        block_position[0][1] = 0;
        block_position[1][0] = 0;
        block_position[1][1] = 1;
        block_position[2][0] = 0;
        block_position[2][1] = 2;
        block_position[3][0] = 0; 
        block_position[3][1] = 3;
    }
    else cout << "invalid input!!" << endl;

}
I_block::~I_block(){delete lowest_block_position;}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of I_block
*/
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
/*
    start of the definition of O_block
*/
////////////////////////////////////////////////////////////////////

O_block::O_block(int initial_place){
    
    now_row = 3;
    initial_position= initial_place;

    stop_size = 2;
    lowest_block_position = new int[stop_size];
    lowest_block_position[0] = 0;
    lowest_block_position[1] = 0;

    block_position[0][0] = 0;
    block_position[0][1] = 0;
    block_position[1][0] = 0;
    block_position[1][1] = 1;
    block_position[2][0] = 1;
    block_position[2][1] = 0;
    block_position[3][0] = 1; 
    block_position[3][1] = 1;

}
O_block::~O_block(){delete lowest_block_position;}
////////////////////////////////////////////////////////////////////
/*
    end of the definition of O_block
*/
////////////////////////////////////////////////////////////////////
