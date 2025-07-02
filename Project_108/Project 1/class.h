#ifndef CLASS_H
#define CLASS_H

#include <iostream>
using namespace  std;

class playing_space{
    private:
        bool **space;        // playing space
        int row;
        int col;
    public:
        playing_space():row(0), col(0){}
        playing_space(int ROW, int COL);      // initializing space
        ~playing_space();
        void print();
        void print_real_space();
        void drop(class block &d_b);
        bool delete_check(int read_row);
        bool delete_row(int row_deleted);
        bool check_over();
};

class block{
    friend playing_space;
    protected:
        int stop_size;
        int *lowest_block_position;  
            // when lowest_block_position[i] = 1, it means the the block itselt
            // is at the second row regarding the row of reference point is row 1, and i means
            // i colume far from the reference point
        int block_position[4][2];     // block exact position
                                      // arrange by {row, colume}
        int now_row;
        int initial_position;
    public:
    virtual ~block(){};
    int get_now_row();
};

class T_block:public block{
    public:
    T_block(){}
    T_block(int initial_place, int type);
    ~T_block();

};


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
#endif