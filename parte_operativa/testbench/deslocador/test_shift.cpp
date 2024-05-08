#include "systemc.h"
#include "../../modulos/deslocador/Shift.h"

int sc_main(int argc, char* argv[]){

    //criacao dos sinais
    sc_signal <sc_uint<32>> in, out; 
    sc_signal <sc_uint<5>> shift_amount; 
    sc_signal <bool> shift_dir; 

    //instanciação do modulo deslocador_bits
    deslocador_bits deslocador("deslocador");
    deslocador.in(in);
    deslocador.shift_amount(shift_amount);
    deslocador.shift_dir(shift_dir);
    deslocador.out(out);

    //abre o arquivo vcd para gravação
    sc_trace_file *wf = sc_create_vcd_trace_file("deslocador_waveform");
    sc_trace(wf, in, "in");
    sc_trace(wf, shift_amount,"shift_amount"); 
    sc_trace(wf, shift_dir, "shift_dir");
    sc_trace(wf, out, "out");

    //inicializacao dos sinais
    in = 0b10101010101010101010101010101010;
    shift_amount = 4; 
    shift_dir= 0;

    //avança o tempo de simulação
    sc_start(10, SC_NS);

    //altera os valores dos sinais
    shift_dir = 1; 

    //avança o tempo de simulação
    sc_start(10, SC_NS);

    //fecha o arquivo vcd
    sc_close_vcd_trace_file(wf);

    return 0; 
}