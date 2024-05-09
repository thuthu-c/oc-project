#ifndef REGISTERBANK_H
#define REGISTERBANK_H 

#include "systemc.h"

SC_MODULE(RegisterBank){

    //inputs
    sc_in<bool> clk; //clock
    sc_in<bool> write_enable; //enable de escrita
    sc_in<sc_uint<5>> write_address; // endereço de escrita
    sc_in<sc_uint<32>> write_data; //dados de escrita; 
    sc_in<sc_uint<32>> read_address_1; // endereço de leitura 1
    sc_in<sc_uint<32>> read_address_2; // endereço de leitura 2

    //outputs
    sc_out<sc_uint<32>> read_data_1; // dados de leitura 1
    sc_out<sc_uint<32>> read_data_2; // dados de leitura 2

    //registers
    sc_uint<4> registers[8]; // banco com 8 registradores de 4 bits


    // metodo para escrever dados
    void write() {
        if(write_enable.read() == true){
            registers[write_address.read()] = write_data.read(); 
        }
    }

    // metodo para ler dados
    void read(){
        read_data_1.write(registers[read_address_1.read()]);
        read_data_2.write(registers[read_address_2.read()]);
    }



    SC_CTOR(RegisterBank){
        SC_METHOD(write);
        sensitive << clk.pos(); //trigger na borda positiva do clock

        SC_METHOD(read); 
        sensitive << read_address_1 << read_address_2; // atualiza mudança de endereço
    }


};

#endif // REGISTERBANK_H