#include "systemc.h"
#include "parte_operativa/op_part.h"
#include "parte_controle/Control.h"

int sc_main(int argc, char* argv[]){

    //instanciando os modulos
    OpPart op("OpPart");
    Control control("Control");

    //sinais para conectar os modulos
    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_uint<3>> aluOp;
    sc_signal<bool> aluSrc, regDst, regWrite, memRead, memWrite, memToReg, branch; 

    // conectando os sinais ao módulo de controle
    control.opcode(opcode);
    control.aluOp(aluOp);
    control.aluSrc(aluSrc);
    control.regDst(regDst);
    control.regWrite(regWrite);
    control.memRead(memRead);
    control.memWrite(memWrite);
    control.memToReg(memToReg);
    control.branch(branch);

    //conectando os sinais de controle ao módulo operativo
    op.aluOp(aluOp);
    op.aluSrc(aluSrc);
    op.regDst(regDst);
    op.regWrite(regWrite);
    op.memRead(memRead);
    op.memWrite(memWrite);
    op.memToReg(memToReg);
    op.branch(branch);

    
}