#include "systemc.h"
#include "ProgramCounter.h"

int sc_main(int argc, char* argv[]){

    //instanciando o módulo de contador de programa
    ProgramCounter pc("ProgramCounter");

    //sinais de controle
    sc_signal<bool> clk; 
    sc_signal<bool> reset;
    sc_signal<bool> enable; 
    sc_signal<sc_uint<32>> jump_address; 
    sc_signal<bool> jump; 
    sc_signal<sc_uint<32>> pc_out; 

    //conectando os sinais ao módulo de contador de programa
    pc.clk(clk);
    pc.reset(reset);
    pc.enable(enable); 
    pc.jump_address(jump_address);
    pc.jump(jump);
    pc.pc_out(pc_out);


    //abrindo o arquivo de trace
    sc_trace_file *wf = sc_create_vcd_trace_file("pc_waveform");
    sc_trace(wf, clk, "clock"); 
    sc_trace(wf, reset, "reset");
    sc_trace(wf, enable, "enable");
    sc_trace(wf, jump_address, "jump_address");
    sc_trace(wf, jump,"jump"); 
    sc_trace(wf, pc_out, "pc_out"); 

    //inicializando os sinais
    clk = 0; 
    reset = 0; 
    enable = 0; 
    jump_address = 0; 
    jump = 0; 

    //simulando por 10 ciclos de clock
    for(auto i{0}; i< 10; ++i){
        //flanco de subida do clock
        clk = 1; 
        sc_start(1, SC_NS); 

        //resetando o contador de programa no ciclo 2
        if(i == 2){
            reset = 1;
        }else{
            reset = 0;
        }

        // habilitando o contador de programa no ciclo 3
        if(i == 3){
            enable =1; 
        }

        //pulando para um endereço específico no ciclo 5
        if(i == 5){
            jump = 1; 
            jump_address = 123; 
        }else jump = 0; 


        //flanco de descida do clock
        clk = 0; 
        sc_start(1, SC_NS);


    }

    //fechando arquivo de trace
    sc_close_vcd_trace_file(wf);

    return 0; 
}