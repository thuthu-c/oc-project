#include "systemc.h"
#include "alu4bit.h"
#include "RegisterBank.h"

SC_MODULE(TopModule) {
    alu4bit alu;
    RegisterBank regBank;
    sc_signal<sc_uint<4>> alu_operand1, alu_operand2;
    sc_signal<sc_uint<3>> alu_opcode;
    sc_signal<sc_uint<3>> read_address1, read_address2, write_address;
    sc_signal<sc_uint<4>> write_data;
    sc_signal<bool> write_enable;
    sc_signal<bool> alu_carry_out;
    sc_clock clock;
    sc_signal<sc_uint<4>> alu_result; 

    SC_CTOR(TopModule) : alu("ALU"), regBank("RegBank"), clock("Clock", 10, SC_NS) {
        // Conectar saídas do banco de registradores às entradas da ALU
        alu.a(regBank.read_data_1);
        alu.b(regBank.read_data_2);
        alu.op(alu_opcode);
        alu.result(alu_result);

        // Conectar saída da ALU para o banco de registradores
        regBank.write_data(alu_result);
        regBank.read_address_1(read_address1);
        regBank.read_address_2(read_address2);
        regBank.write_address(write_address);
        regBank.write_enable(write_enable);

        // Conexões de clock
        regBank.clk(clock);
        alu.carry_out(alu_carry_out);
    }
};

int sc_main(int argc, char* argv[]) {
    TopModule top("TopModule");
    sc_start();
    return 0;
}
