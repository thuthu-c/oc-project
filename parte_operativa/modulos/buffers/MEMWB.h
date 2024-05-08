#ifndef EXMEM_H
#define EXMEM_H

#include "systemc.h"

SC_MODULE(EXMEM){

    //entradas
    sc_in<sc_uint<32>> out_data_memory, out_exmem_address; 
    sc_in<sc_uint<5>>out_exmem;
    sc_in<bool> regWrite;
    sc_in<bool> memToReg;
 

    //saída
    sc_out<sc_uint<32>> in_mux_one, in_mux_two;
    sc_out<sc_uint<5>>in_registers_write_register; 
    sc_out<bool> regWrite;
    sc_out<bool> memToReg;
 

    //comportamento
    void process(){
        out_data_memory.write(in_mux_one);
        out_exmem_address.write(in_mux_two);
        out_exmem.write(in_registers_write_register);
        regWrite.write(regWrite);
        memToReg.write(memToReg);
    }



    SC_CTOR(IFID){
        SC_METHOD(process);
        sensitive <<out_data_memory << out_exmem_address << out_exmem <<  regWrite  << memToReg;  
    }
};


#endif