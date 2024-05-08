#include "systemc.h"
#include "../../modulos/mux/Mux.h"

int sc_main(int argc, char* argv[]){

    //criação dos sinais
    sc_signal<sc_uint<4>> a, b, out;
    sc_signal<bool> sel;

    //instacianção do módulo 
    mux2bit mux ("mux");
    mux.a(a);
    mux.b(b);
    mux.sel(sel);
    mux.out(out);

    //abre o arquivo vcd para gravação
    sc_trace_file *wf = sc_create_vcd_trace_file("mux_waveform");
    sc_trace(wf, a, "a"); 
    sc_trace(wf, b, "b");
    sc_trace(wf, sel, "sel");
    sc_trace(wf, out, "out");

    // inicialização dos sinais
    a = 0b1010; 
    b = 0b0101;
    sel = 0;

    // avança o tempo de simulação
    sc_start(10, SC_NS);

    // altera os valores dos sinais
    sel = 1;

    //avança o tempo de simulação
    sc_start(10, SC_NS);

    //fecha o arquivo VCD
    sc_close_vcd_trace_file(wf);

    return 0; 
}