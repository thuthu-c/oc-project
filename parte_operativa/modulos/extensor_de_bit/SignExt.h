#ifndef SIGNEXT_H
#define SIGNEXT_H

#include "systemc.h"


SC_MODULE(SignExtend){
    //entrada 
   sc_in<sc_dt::sc_uint<32>> in; //entrada de 16 bits

    //saída
    sc_out<sc_uint<32>> out; // saída de 32 bits

    //comportamento
    void process(){
        out.write(in.read().range(15,0));
    }

    SC_CTOR(SignExtend){
        SC_METHOD(process);
        sensitive << in; 
    }
};

#endif