#include "systemc.h"
#include "Adder.h"

int sc_main(int argc, char* argv[]){

    //instanciando o modulo de somador
    Adder adder("Adder"); 

    //sinais de controle
    sc_signal<sc_uint<32>> a, b, sum; 

    //conectando os sinais ao módulo de somador
    adder.a(a);
    adder.b(b);
    adder.sum(sum);


    //abrindo arquivo de trace
    sc_trace_file *wf = sc_create_vcd_trace_file("wavessform");
    sc_trace(wf, a, "a");
    sc_trace(wf, b, "b");
    sc_trace(wf, sum, "sum");

    //inicialindo os sinais
    a =  0;
    b = 0; 


    //simulando por 10 ciclos de clock
    for(auto i{0};  i < 10; ++i){
        //incrementando os valores de a e b

        a = a.read() + 1; 
        b = b.read() + 2; 

        //avançando o tempo de simulacao
        sc_start(1, SC_NS);

    }

    //fechando arquivo de trace
    sc_close_vcd_trace_file(wf);

    return 0; 

}