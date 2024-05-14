#ifndef IDEX_H
#define IDEX_H

#include "systemc.h"

SC_MODULE(IDEX){

    //entradas
    sc_in<sc_uint<32>> out_ifid, out_reg_data_one, out_reg_data_two, out_ext; 
    sc_in<sc_uint<32>> instruction_one, instruction_two;
    sc_in<sc_uint<3>> alu_op_in;
    sc_in<bool> alu_src_in;
    sc_in<bool> reg_dst_in;
    sc_in<bool> reg_write_in;
    sc_in<bool> mem_read_in;
    sc_in<bool> mem_write_in;
    sc_in<bool> mem_to_reg_in;
    sc_in<bool> branch_in;

    //saída
    sc_out<sc_uint<32>> in_add, in_ula, in_mux, in_instruction; 
    sc_out<sc_uint<5>> in_mux_one, in_mux_two; 
    sc_out<sc_uint<3>> alu_op_out;
    sc_out<bool> alu_src_out;
    sc_out<bool> reg_dst_out;
    sc_out<bool> reg_write_out;
    sc_out<bool> mem_read_out;
    sc_out<bool> mem_write_out;
    sc_out<bool> mem_to_reg_out;
    sc_out<bool> branch_out;

    //comportamento
    void process(){
        in_add.write(out_ifid);
        in_ula.write(out_reg_data_one);
        in_mux.write(out_reg_data_two);
        in_instruction.write(out_ext);
        in_mux_one.write(instruction_one.read().range(20,16));
        in_mux_two.write(instruction_two.read().range(15,11));
        alu_op_out.write(alu_op_in);
        alu_src_out.write(alu_src_in);
        reg_dst_out.write(reg_dst_in);
        reg_write_out.write(reg_write_in);
        mem_read_out.write(mem_read_in);
        mem_write_out.write(mem_write_in);
        mem_to_reg_out.write(mem_to_reg_in);
        branch_out.write(branch_in);
    }



    SC_CTOR(IDEX){
        SC_METHOD(process);
        sensitive << out_ifid << out_reg_data_one << out_reg_data_two << out_ext << instruction_one << instruction_two << alu_op_in << alu_src_in <<  reg_dst_in <<  reg_write_in <<  mem_read_in << mem_write_in << mem_to_reg_in << branch_in;
    }
};


#endif