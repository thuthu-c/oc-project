#ifndef ALU4BIT_H
#define ALU4BIT_H

#include "systemc.h"

SC_MODULE(alu4bit){

    //inputs 
    sc_in<sc_uint<32>> a, b; //operandos de 4 bits
    sc_in<sc_uint<3>> op; //codigo de operação 

    //outputs
    sc_out<sc_uint<32>> result; //resultado de 4 bits
    sc_out<bool> carry_out;  

    //behavior
    void process(){
        switch (op.read())
        {
            // SOMA A+ B 
        case 0:{
            sc_uint<5> tmp = a.read() + b.read(); //soma de 4 bits + carry
            result.write(tmp.range(3,0)); 
            carry_out.write(tmp[4]);
        } 
            
            break;

            // subtração A-B
        case 1:{
            sc_uint<5> tmp = a.read() - b.read(); //subtração de 4 bits
            result.write(tmp.range(3,0));
            carry_out.write(tmp[4]); 

        }
        break;

        //and a & b 
        case 2:{
            result.write(a.read() & b.read());
            carry_out.write(false);

        }
        break;

        // or a | b
        case 3:{
            result.write(a.read() | b.read());
            carry_out.write(false);
        }
        break;

        // xor a ^ b
        case 4: {
            result.write(a.read() ^ b.read());
            carry_out.write(false);
        }
        break; 

        
        // comp a == b
        case 5: {
            if(a.read() == b.read()){
                result.write(1);
                carry_out.write(true);
            }
            else if(a.read() <  b.read()){
                result.write(0);
                carry_out.write(false);
            }
            else{
                result.write(2);
                carry_out.write(false);
            }
             
        }

        // neg ~a
        case 6: {
            result.write(~(a.read()));
            carry_out.write(false);
        }

        case 7 :{
            result.write(a.read() + 0);
            carry_out.write(false);
        }
        
        default:
            result.write(0);
            break;
        }
    }

    SC_CTOR(alu4bit){
        SC_METHOD(process);
        sensitive << a << b << op; 
    }
};

#endif // ALU4BIT_H