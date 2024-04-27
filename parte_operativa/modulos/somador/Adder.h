#ifndef ADDER_H
#define ADDER_H

#include "systemc.h"

SC_MODULE(Adder){

//entradas
sc_in<sc_uint<32>> a,b;

//saidas
sc_out<sc_uint<32>> sum;

//processo
void do_add(){
    sum.write(a.read() + b.read());
}

SC_CTOR(Adder){
    SC_METHOD(do_add);
    sensitive << a << b;
}

};



#endif