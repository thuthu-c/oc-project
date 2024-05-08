#ifndef IFID_H
#define IFID_H

#include "systemc.h"

SC_MODULE(IFID){

    //entradas
    sc_in<sc_uint<32>> out_adder, out_ins_mem;             

    //saída
    sc_out<sc_uint<32>> in_idex, instruction; 

    //comportamento
    void process(){
        in_idex.write(out_adder);
        instruction.write(out_ins_mem);
    }



    SC_CTOR(IFID){
        SC_METHOD(process);
        sensitive << out_adder << out_ins_mem; 
    }
};


#endif