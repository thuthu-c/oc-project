#ifndef BUFFER_H
#define BUFFER_H

#include "systemc.h"

template<class T>
SC_MODULE(Buffer){

    //entradas
    sc_in<bool> clk;  //clock
    sc_in<bool> reset; //sinal de reset
    sc_in<bool> write_enable;  // habilitar escrita no buffer
    sc_in<T> data_in; //dados para escrever no buffer

    //saidas
    sc_out<T> data_out; //dados lidos do buffer

    //buffer
    T buffer; 

    //processo
    void buffer_process(){
        if(reset.read() == 1){
            buffer = 0; 
        } else if(clk.read() == 1 && write_enable.read() == 1){
            buffer = data_in.read();
        }
        data_out.write(buffer);
    }

    SC_CTOR(Buffer){
        SC_METHOD(buffer_process);
        sensitive << clk.pos();
    }
};


#endif