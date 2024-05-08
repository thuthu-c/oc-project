#ifndef MUXCINCO_H
#define MUXCINCO_H

#include "systemc.h"

SC_MODULE(MuxCinco){

    //entradas
    sc_in<sc_uint<5>> a,b; // entrada de 4 bits
    sc_in<bool> sel; //seletor de 1 bit                    

    //saída
    sc_out<sc_uint<5>> out; // saída de 4 bits

    //comportamento
    void process(){
        if(sel.read() == 0){
            out.write(a.read());
        }else out.write(b.read()); 
    }



    SC_CTOR(MuxCinco){
        SC_METHOD(process);
        sensitive << a << b << sel; 
    }
};


#endif