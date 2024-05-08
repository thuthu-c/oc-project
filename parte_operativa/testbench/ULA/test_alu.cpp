#include "systemc.h"
#include "alu4bit.h"

int sc_main(int argc, char* argv[]){
    sc_signal<sc_uint<4>> sig_a, sig_b;
    sc_signal<sc_uint<3>> sig_op;
    sc_signal<sc_uint<4>> sig_result;
    sc_signal<bool> sig_carry_out; 

    alu4bit alu ("ALU"); 
    alu.a(sig_a);
    alu.b(sig_b);
    alu.op(sig_op);
    alu.result(sig_result);
    alu.carry_out(sig_carry_out);

    //simulation
    sc_start(1, SC_NS);
    sig_a.write(9);
    sig_b.write(3);
    sig_op.write(0); //sum 


    sc_start(1, SC_NS); //process 
    cout<< "Resultado: " << sig_result.read() << endl;
    cout << "Carry Out: " << (sig_carry_out.read() ? "true" : "false") << endl; 


    sc_start(1, SC_NS);
    sig_a.write(9);
    sig_b.write(3);
    sig_op.write(1); //sub


    sc_start(1, SC_NS); //process 
    cout<< "Resultado: " << sig_result.read() << endl;
    cout << "Carry Out: " << (sig_carry_out.read() ? "true" : "false") << endl;

    sig_op.write(2); // AND

    sc_start(1, SC_NS); // Processar
    cout << "Resultado AND: " << sig_result.read() << endl;

    sig_op.write(3); // OR
    sc_start(1, SC_NS); // Processar
    cout << "Resultado OR: " << sig_result.read() << endl;

    sig_op.write(4); // XOR
    sc_start(1, SC_NS); // Processar
    cout << "Resultado XOR: " << sig_result.read() << endl;
    
    return 0; 


}