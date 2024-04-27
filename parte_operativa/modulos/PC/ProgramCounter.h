#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include "systemc.h"


SC_MODULE(ProgramCounter){

    //entradas
    sc_in<bool> clk;  //clock
    sc_in<bool> reset; //sinal de reset
    sc_in<bool> enable;  // habilitar incremento
    sc_in<sc_uint<32>> jump_address; //endereço para o qual pular
    sc_in<bool> jump; //sinal de controle para pular para um endereço específico


    //saídas
    sc_out<sc_uint<32>> pc_out; //valor atual do contador de programa

    //contador de programa
    sc_uint<32> pc; 


    //processo
    void pc_process() {
        if(reset.read() == 1){
            pc = 0;
        } else if(clk.read() == 1){
            if(jump.read() == 1){
                pc = jump_address.read();
            } else if(enable.read() == 1){
                pc++;
            }
        }

        pc_out.write(pc);
    }

    SC_CTOR(ProgramCounter){
        SC_METHOD(pc_process);
        sensitive << clk.pos();
    }
}; 


#endif