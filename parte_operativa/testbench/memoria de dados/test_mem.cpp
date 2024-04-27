#include "systemc.h"
#include "memory.h"

int sc_main(int argc, char* argv[]){

    //instanciando o módulo de memória
    Memory mem("Memory");

    //sinais de controle
    sc_signal<bool> clk;
    sc_signal<bool> mem_write;
    sc_signal<sc_uint<32>> address; 
    sc_signal<sc_uint<32>> write_data;
    sc_signal<sc_uint<32>> read_data; 

    //conectando os sinais ao módulo de memória
    mem.clk(clk);
    mem.mem_write(mem_write);
    mem.address(address);
    mem.write_data(write_data);
    mem.read_data(read_data);


    //abrindo arquivo de trace
    sc_trace_file *wf = sc_create_vcd_trace_file("waveform");
    sc_trace(wf, clk, "clock"); 
    sc_trace(wf, mem_write, "mem_write");
    sc_trace(wf, address, "address");
    sc_trace(wf, write_data, "write_data");
    sc_trace(wf, read_data, "read_data");

    //inicializando os sinais
    clk = 0; 
    mem_write = 0;
    address = 0;

    //simulando por 10 ciclos de clock
    for(auto i{0}; i < 10; ++i){
        //flanco de subida do clock
        clk = 1; 
        sc_start(1, SC_NS);

        //escrevendo na memoria no ciclo 3
        if(i == 3){
            mem_write = 1; 
            address = 0;
            write_data = 123;
        }

        //lendo da memoria no ciclo 5
        if (i == 5){
            mem_write = 0; 
            address = 0; 
        }

        //flanco de descida  do clock
        clk = 0; 
        sc_start(1, SC_NS);
    }

    //fechando o arquivo de trace
    sc_close_vcd_trace_file(wf);

    return 0; 

}