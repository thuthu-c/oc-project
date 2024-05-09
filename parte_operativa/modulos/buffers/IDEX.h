#ifndef IDEX_H
#define IDEX_H

#include "systemc.h"

SC_MODULE(IDEX){

    //entradas
    sc_in<sc_uint<32>> out_ifid, out_reg_data_one, out_reg_data_two, out_ext; 
    sc_in<sc_uint<32>> instruction_one, instruction_two;
    sc_in<sc_uint<3>> aluOp;
    sc_in<bool> aluSrc;
    sc_in<bool> regDst;
    sc_in<bool> regWrite;
    sc_in<bool> memRead;
    sc_in<bool> memWrite;
    sc_in<bool> memToReg;
    sc_in<bool> branch;

    //saída
    sc_out<sc_uint<32>> in_add, in_ula, in_mux, in_instruction; 
    sc_out<sc_uint<5>> in_mux_one, in_mux_two; 
    sc_out<sc_uint<3>> aluOp;
    sc_out<bool> aluSrc;
    sc_out<bool> regDst;
    sc_out<bool> regWrite;
    sc_out<bool> memRead;
    sc_out<bool> memWrite;
    sc_out<bool> memToReg;
    sc_out<bool> branch;

    //comportamento
    void process(){
        in_add.write(out_ifid);
        in_ula.write(out_reg_data_one);
        in_mux.write(out_reg_data_two);
        in_instruction.write(out_ext);
        in_mux_one.write(instruction_one.read().range(20,16));
        in_mux_two.write(instruction_two.read().range(15,11));
        aluOp.write(aluOp);
        aluSrc.write(aluSrc);
        regDst.write(regDst);
        regWrite.write(regWrite);
        memRead.write(memRead);
        memWrite.write(memWrite);
        memToReg.write(memToReg);
        branch.write(branch);
    }



    SC_CTOR(IFID){
        SC_METHOD(process);
        sensitive << out_ifid << out_reg_data_one << out_reg_data_two << out_ext << instruction_one << instruction_two << aluOp << aluSrc <<  regDst <<  regWrite <<  memRead << memWrite << memToReg << branch;  
    }
};


#endif