#include "systemc.h"
#include "../../modulos/extensor_de_bit/SignExt.h"

int sc_main (int argc, char* argv[]){

    //criacao dos sinais
    sc_signal<sc_int<16>> in;
    sc_signal<sc_int<32>> out;

    //instanciação do módulo SignExtend

    SignExtend extensor ("extensor");
    extensor.in(in);
    extensor.out(out);

    // abre o arquivo VCD para gravação
    sc_trace_file *wf = sc_create_vcd_trace_file("extensor_waveform");
    sc_trace(wf, in, "in");
    sc_trace(wf, out, "out");

    //inicialização do sinal
    in = 0b1010101010101010; 

    //avança o tempo de simulação
    sc_start(10, SC_NS);

    //altera o valor do sinal
    in = 0b0101010101010101;

    //avança o tempo de simulação
    sc_start(10, SC_NS);

    //fecha o arquivo VCD
    sc_close_vcd_trace_file(wf);

    return 0; 

}