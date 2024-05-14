#ifndef EXMEM_H
#define EXMEM_H

#include "systemc.h"

SC_MODULE(EXMEM){

    //entradas
    sc_in<sc_uint<32>> out_adder,out_alu_result, out_idex; 
    sc_in<sc_uint<5>>out_mux;
    sc_in<bool> zero_in;
    sc_in<bool> aluSrc_in;
    sc_in<bool> regDst_in;
    sc_in<bool> regWrite_in;
    sc_in<bool> memRead_in;
    sc_in<bool> memWrite_in;
    sc_in<bool> memToReg_in;
    sc_in<bool> branch_in;

    //saída
    sc_out<sc_uint<32>> in_address, in_write_data, in_mux;
    sc_out<sc_uint<5>>in_memwb; 
    sc_out<bool> zero_out;
    sc_out<bool> aluSrc_out;
    sc_out<bool> regDst_out;
    sc_out<bool> regWrite_out;
    sc_out<bool> memRead_out;
    sc_out<bool> memWrite_out;
    sc_out<bool> memToReg_out;
    sc_out<bool> branch_out;

    //comportamento
    void process(){
        in_mux.write(out_adder);
        in_address.write(out_alu_result);
        in_write_data.write(out_idex);
        in_memwb.write(out_mux);
        zero_out.write(zero_in);
        aluSrc_out.write(aluSrc_in);
        regWrite_out.write(regWrite_in);
        memRead_out.write(memRead_in);
        memWrite_out.write(memWrite_in);
        memToReg_out.write(memToReg_in);
        branch_out.write(branch_in);
    }



    SC_CTOR(EXMEM){
        SC_METHOD(process);
        sensitive << out_adder << out_alu_result << out_mux << out_idex << aluSrc_in <<  regDst_in <<  regWrite_in <<  memRead_in << memWrite_in << memToReg_in << branch_in;
    }
};


#endif