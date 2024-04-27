#include "systemc.h"
#include "Buffer.h"

typedef sc_uint<32> bus_t; 


int sc_main(int argc, char* argv[] ){
    //instanciando o modulo buffer
    Buffer<bus_t> buffer("Buffer");

    //sinais de controle
    sc_signal<bool> clk;
    sc_signal<bool> reset; 
    sc_signal<bool> write_enable;
    sc_signal<bus_t> data_in; 
    sc_signal<bus_t> data_out; 

    //conectando os sinais ao módulo de buffer
    buffer.clk(clk);
    buffer.reset(reset);
    buffer.write_enable(write_enable);
    buffer.data_in(data_in);
    buffer.data_out(data_out);

    //abrindo arquivo de trace
    sc_trace_file *wf = sc_create_vcd_trace_file("buffer_waveform");
    sc_trace(wf, clk, "clock");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, write_enable, "write_enable");
    sc_trace(wf, data_in, "data_in");
    sc_trace(wf, data_out, "data_out");


    //inicializando os sinais
    clk = 0; 
    reset = 0; 
    write_enable = 0; 
    data_in = 0; 

    // simulando por 10 ciclos de clock
    for(auto i{0}; i < 10; ++i){

        //flanco de subida do clock
        clk = 1; 
        sc_start(1, SC_NS); 

        //resetando o buffer no ciclo 2
        if(i == 2){
            reset =1;
        }else{
            reset = 0;
        }
         
         //habilitando a escrita no buffer e escrevendo dados no ciclo 3

         if(i == 3){
            write_enable =1; 
            data_in = i;
         }
         else{
            write_enable = 0;
         }

         //flanco de descida do clock
         clk = 0;
         sc_start(1, SC_NS);
    }

    //fechando arquico de trace
    sc_close_vcd_trace_file(wf);



    return 0; 
}