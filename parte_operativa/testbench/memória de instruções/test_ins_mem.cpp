#include "systemc.h"
#include "InstructionMemory.h"

int sc_main(int argc, char* argv[]){

    //instanciando o módulo de memória de instruções
    InstructionMemory instr_mem("InstructionMemory");

    //sinais de controle
    sc_signal<bool> clk; 
    sc_signal<sc_uint<32>> address;
    sc_signal<sc_uint<32>> instruction; 

    //conectando 
    instr_mem.clk(clk); 
    instr_mem.address(address);
    instr_mem.instruction(instruction);

    //abrindo arquivo de trace
    sc_trace_file *wf = sc_create_vcd_trace_file("wavesforms");
    sc_trace(wf, clk, "clock");
    sc_trace(wf, address, "address");
    sc_trace(wf, instruction, "instruction");

    //inicializando os sinais
    clk = 0;
    address = 0;

    //simulando 10 ciclio de clock

    for(auto i{0}; i < 10; ++i){

        //flanco de subida do clock
        clk = 1; 
        sc_start(1, SC_NS);

        //lendo da memória de instruções no ciclo 3;
        if(i == 3){
            address = 0; 
        }

        //flanco de descida do clock
        clk = 0;
        sc_start(1, SC_NS); 
    }

    // fechando arquivo de trace
    sc_close_vcd_trace_file(wf); 

    return 0; 
}