#ifndef MEMWB_H
#define MEMWB_H

#include "systemc.h"

SC_MODULE(MEMWB){

    //entradas
    sc_in<sc_uint<32>> out_data_memory, out_exmem_address; 
    sc_in<sc_uint<5>>out_exmem;
    sc_in<bool> reg_write_in;
    sc_in<bool> mem_to_reg_in;
 

    //saída
    sc_out<sc_uint<32>> in_mux_one, in_mux_two;
    sc_out<sc_uint<5>>in_registers_write_register; 
    sc_out<bool> reg_write_out;
    sc_out<bool> mem_to_reg_out;
 

    //comportamento
    void process(){
        in_mux_one.write(out_data_memory);
        in_mux_two.write(out_exmem_address);
        in_registers_write_register.write(out_exmem);
        reg_write_out.write(reg_write_in);
        mem_to_reg_out.write(mem_to_reg_in);
    }



    SC_CTOR(MEMWB){
        SC_METHOD(process);
        sensitive <<out_data_memory << out_exmem_address << out_exmem <<  reg_write_in  << mem_to_reg_in;
    }
};


#endif