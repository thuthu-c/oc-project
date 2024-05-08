#include "systemc.h"

SC_MODULE(Control) {
    sc_in<sc_uint<6>> opcode;
    sc_out<sc_uint<3>> aluOp;
    sc_out<bool> aluSrc;
    sc_out<bool> regDst;
    sc_out<bool> regWrite;
    sc_out<bool> memRead;
    sc_out<bool> memWrite;
    sc_out<bool> memToReg;
    sc_out<bool> branch;

    void process() {
        switch(opcode.read()) {
            case 0x00: // R-type instructions
                aluOp.write(2);
                aluSrc.write(false);
                regDst.write(true);
                regWrite.write(true);
                memRead.write(false);
                memWrite.write(false);
                memToReg.write(false);
                branch.write(false);
                break;
            case 0x23: // lw
                aluOp.write(0);
                aluSrc.write(true);
                regDst.write(false);
                regWrite.write(true);
                memRead.write(true);
                memWrite.write(false);
                memToReg.write(true);
                branch.write(false);
                break;
            case 0x2B: // sw
                aluOp.write(0);
                aluSrc.write(true);
                regDst.write(false);
                regWrite.write(false);
                memRead.write(false);
                memWrite.write(true);
                memToReg.write(false);
                branch.write(false);
                break;
            case 0x04: // beq
                aluOp.write(1);
                aluSrc.write(false);
                regDst.write(false);
                regWrite.write(false);
                memRead.write(false);
                memWrite.write(false);
                memToReg.write(false);
                branch.write(true);
                break;
            default:
                // Handle other opcodes...
                break;
        }
    }

    SC_CTOR(Control) {
        SC_METHOD(process);
        sensitive << opcode;
    }
};