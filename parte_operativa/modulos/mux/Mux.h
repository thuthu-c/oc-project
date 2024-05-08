#ifndef MUX_H
#define MUX_H

#include "systemc.h"

SC_MODULE(mux2bit){

    //entradas
    sc_in<sc_uint<32>> a,b; // entrada de 4 bits
    sc_in<bool> sel; //seletor de 1 bit                    

    //saída
    sc_out<sc_uint<32>> out; // saída de 4 bits

    //comportamento
    void process(){
        if(sel.read() == 0){
            out.write(a.read());
        }else out.write(b.read()); 
    }



    SC_CTOR(mux2bit){
        SC_METHOD(process);
        sensitive << a << b << sel; 
    }
};


#endif