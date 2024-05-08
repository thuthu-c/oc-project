#ifndef EXMEM_H
#define EXMEM_H

#include "systemc.h"

SC_MODULE(EXMEM){

    //entradas
    sc_in<sc_uint<32>> out_adder,out_alu_result, out_idex; 
    sc_in<sc_uint<5>>out_mux;
    sc_in<bool> zero; 
    sc_in<bool> aluSrc;
    sc_in<bool> regDst;
    sc_in<bool> regWrite;
    sc_in<bool> memRead;
    sc_in<bool> memWrite;
    sc_in<bool> memToReg;
    sc_in<bool> branch;

    //saída
    sc_out<sc_uint<32>> in_address, in_write_data, in_mux;
    sc_out<sc_uint<5>>in_memwb; 
    sc_out<bool> zero;
    sc_out<bool> aluSrc;
    sc_out<bool> regDst;
    sc_out<bool> regWrite;
    sc_out<bool> memRead;
    sc_out<bool> memWrite;
    sc_out<bool> memToReg;
    sc_out<bool> branch;

    //comportamento
    void process(){
        out_adder.write(in_address);
        out_alu_result.write(in_write_data);
        out_idex.write(in_mux);
        out_mux.write(in_memwb);
        zero.write(zero);
        aluOp.write(aluOp);
        aluSrc.write(aluSrc);
        regWrite.write(regWrite);
        memRead.write(memRead);
        memWrite.write(memWrite);
        memToReg.write(memToReg);
        branch.write(branch);
    }



    SC_CTOR(IFID){
        SC_METHOD(process);
        sensitive << out_adder << out_alu_result << out_mux << out_idex << aluSrc <<  regDst <<  regWrite <<  memRead << memWrite << memToReg << branch;  
    }
};


#endif