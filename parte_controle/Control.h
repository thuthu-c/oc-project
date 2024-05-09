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
            //                  OP | ALU | HEX
            // AND - 0 2     -> 0000| 0001| 0x01
            // OR  - 1 3     -> 0001| 0011| 0x13
            // XOR - 2 4     -> 0010| 0100| 0x24
            // NOT - 3 6     -> 0011| 0110| 0x36
            // CMP - 4 5     -> 0100| 0101| 0x45
            // ADD - 5 0     -> 0101| 0000| 0x50
            // ADDI - 5 7    -> 0101| 0111| 0x57
            // SUB - 6 1     -> 0110| 0001| 0x61
            // LW  - 7 0     -> 0111| 0000| 0x70
            // SW  - 8 0     -> 1000| 0000| 0x80
            // J   - 9 0     -> 1001| 0000| 0x90
            // BNE - 10 0    -> 1010| 0000| 0xA0
            // BEQ - 11 0    -> 1011| 0000| 0xB0


            case 0x01: // AND
                aluOp.write(2);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x13: // OR
                aluOp.write(3);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x24: // XOR
                aluOp.write(4);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x36: // NOT
                aluOp.write(6);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x45: // CMP
                aluOp.write(5);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x50: // ADD
                aluOp.write(0);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x57: // ADDI
                aluOp.write(7);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x61: // SUB
                aluOp.write(1);
                aluSrc.write(0);
                regDst.write(1);
                regWrite.write(1);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x70: // LW
                aluOp.write(0);
                aluSrc.write(1);
                regDst.write(0);
                regWrite.write(1);
                memRead.write(1);
                memWrite.write(0);
                memToReg.write(1);
                branch.write(0);
                break;
            case 0x80: // SW
                aluOp.write(0);
                aluSrc.write(1);
                regDst.write(0);
                regWrite.write(0);
                memRead.write(0);
                memWrite.write(1);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0x90: // J
                aluOp.write(0);
                aluSrc.write(0);
                regDst.write(0);
                regWrite.write(0);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(1);
                break;
            case 0xA0: // BNE
                aluOp.write(0);
                aluSrc.write(0);
                regDst.write(0);
                regWrite.write(0);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(0);
                break;
            case 0xB0: // BEQ
                aluOp.write(0);
                aluSrc.write(0);
                regDst.write(0);
                regWrite.write(0);
                memRead.write(0);
                memWrite.write(0);
                memToReg.write(0);
                branch.write(1);
                break;
            default:
                break;
        }
    }

    SC_CTOR(Control) {
        SC_METHOD(process);
        sensitive << opcode;
    }
};