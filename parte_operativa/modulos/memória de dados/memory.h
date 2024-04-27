#ifndef MEMORY_H
#define MEMORY_H

#include "systemc.h"

#define MEM_SIZE 1024 // Tamanho da memória em palavras de 32 bits

SC_MODULE(Memory) {
    // Entradas
    sc_in<bool> clk;        // Clock
    sc_in<bool> mem_write;  // Sinal de controle para escrita na memória
    sc_in<sc_uint<32>> address; //endereço da memória
    sc_in<sc_uint<32>> write_data; // dados para escrever na memória


    // saídas
    sc_out<sc_uint<32>> read_data; //dados lidos da memória

    //memória 
    sc_uint<32> memory[MEM_SIZE]; 

    //processo
    void mem_process(){
        if(mem_write.read() == 1){
            memory[address.read()] = write_data.read();
        } else{
            read_data.write(memory[address.read()]);
        }
    }

    SC_CTOR(Memory){
        SC_METHOD(mem_process);
        sensitive << clk.pos(); 
    }
};

#endif //MEMORY_H