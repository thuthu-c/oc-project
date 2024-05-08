#include "systemc.h"
#include "../Control.h"

int sc_main(int argc, char* argv[]){

    //instanciando o modulo de controle
    Control controle("Control");

    //sinais para conectar o módulo
    sc_signal<sc_uint<6>>opcode;
    sc_signal<sc_uint<3>> aluOp;
    sc_signal<bool> aluSrc, regDst, regWrite, memRead, memWrite, memToReg, branch;

    //conectando os sinais
    controle.opcode(opcode);
    controle.aluOp(aluOp);
    controle.aluSrc(aluSrc);
    controle.regDst(regDst);
    controle.regWrite(regWrite);
    controle.memRead(memRead);
    controle.memWrite(memWrite);
    controle.memToReg(memToReg);
    controle.branch(branch);

    //inicializando o vcd trace
    sc_trace_file *wf = sc_create_vcd_trace_file("Control_waveform");
    wf->set_time_unit(1, SC_NS);

    //adicionando sinais ao vcd trace
    sc_trace(wf, opcode, "opcode");
    sc_trace(wf, aluOp, "aluOp");
    sc_trace(wf, aluSrc, "aluSrc");
    sc_trace(wf, regDst, "regDst");
    sc_trace(wf, regWrite, "regWrite");
    sc_trace(wf, memRead, "memRead");
    sc_trace(wf, memWrite, "memWrite");
    sc_trace(wf, memToReg, "memToReg");
    sc_trace(wf, branch, "branch");

    //simulando por 100 ns

    for(auto i{0}; i < 100; ++i){
        opcode = i%64; //calculando a operacao
        sc_start(1, SC_NS);
    }

    //fechando o VCD trace
    sc_close_vcd_trace_file(wf);

    return 0; 
}