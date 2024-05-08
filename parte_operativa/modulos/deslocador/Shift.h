#ifndef SHIFT_H
#define SHIFT_H

#include "systemc.h"

SC_MODULE(deslocador_bits){

    //entrada
    sc_in<sc_uint<5>> in; // entrada de 32 bits 
    sc_in<sc_uint<5>> shift_amount; // quanridade de deslocamento
    sc_in<bool> shift_dir; // direção do deslocamento (0 para a esquerda, 1 para a direita)

    // saída
    sc_out<sc_uint<32>> out; // saida de 32 bits

    //comporamento
    void process(){
        if(shift_dir.read() == 0){
            out.write(in.read() << shift_amount.read());
        }else out.write(in.read() >> shift_amount.read());
    }

    SC_CTOR(deslocador_bits){
        SC_METHOD(process);
        sensitive << in << shift_amount << shift_dir;
    }
}; 

#endif