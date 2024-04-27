#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include "systemc.h"

#define INSTR_MEM_SIZE 1024 //tamanho da memória de instruções em palavras de 32 bits

SC_MODULE(InstructionMemory){
    //entradas
    sc_in<bool>clk; //clock
    sc_in<sc_uint<32>> address; //endereço de memória de instruções

    //saídas
    sc_out<sc_uint<32>> instruction; //instrução lida da memória de instruções

    //memória de instruções
    sc_uint<32> instr_memory[INSTR_MEM_SIZE];

    //processo
    void instr_mem_process(){
        instruction.write(instr_memory[address.read()]); 
    }

    SC_CTOR(InstructionMemory){
        SC_METHOD(instr_mem_process);
        sensitive << clk.pos();
    }
};

#endif