#ifndef OPPART_H
#define OPPART_H

#include "systemc.h"
#include "modulos/somador/Adder.h"
#include "modulos/PC/ProgramCounter.h"
#include "modulos/memoria_de_instr/InstructionMemory.h"
#include "modulos/mem_dados/memory.h"
#include "modulos/banco_de_registradores/RegisterBank.h"
#include "modulos/ula/alu4bit.h"
#include "modulos/deslocador/Shift.h"
#include "modulos/extensor_de_bit/SignExt.h"
#include "modulos/mux/Mux.h"
#include "modulos/mux/MuxCinco.h"

SC_MODULE(OpPart){
    //instanciando os módulos
    Adder somador_1;
    Adder somador_2;
    ProgramCounter pc; 
    InstructionMemory instr_mem; 
    Memory data_mem; 
    RegisterBank registers; 
    alu4bit ula; 
    deslocador_bits deslocador;
    SignExtend extensor;
    mux2bit mux_1;
    mux2bit mux_2;
    MuxCinco mux_3;
    mux2bit  mux_4;



    //entradas da parte operativa
    sc_in<bool> clk;
    sc_in<bool> reset, enable, jump;

    // entradas mux 1 
    sc_in<sc_uint<32>> out_exmim_in_muxone; 
    sc_in<bool> PCSrc;
    //entradas banco de registradores
    sc_in<sc_uint<32>> out_ifid_in_reg;
    sc_in<sc_uint<5>> out_memwb_in_write_register;
    sc_in<bool>  RegWrite;
    //entradas somador 2
    sc_in<sc_uint<32>> out_idex_in_add;
    //entradas ula
    sc_in<sc_uint<32>> out_idex_in_alu;
    sc_in<sc_uint<3>> out_alucontrol_in_alu;
    //entradas mux 2
    sc_in<sc_uint<32>> out_idex_in_one_mux_two, out_idex_in_two_mux_two;
    sc_in<bool> ALUSrc;
    //entradas mux 3
    sc_in<sc_uint<5>> out_idex_in_one_mux_three, out_idex_in_two_mux_three;
    sc_in<bool> RegDst;
    //entradas meória de dados
    sc_in<sc_uint<32>> out_exmem_in_address_data_memory, out_exmem_in_writedata_data_memory; 
    sc_in<bool> MemWrite, MemRead;
    //entradas mux 4 
    sc_in<sc_uint<32>> out_memwb_in_one_mux_four, out_memwb_in_two_mux_four;
    sc_in<bool> MemtoReg; 
    //entrada extensor
    sc_in<sc_uint<16>> instruction; 


    // saídas parte operativa

    //entradas buffer if/id
    sc_out<sc_uint<32>> out_instruction_memory_in_ifid, out_add_in_ifid;
    //entradas idex
    sc_out<sc_uint<32>> out_registers_rdataone_in_idex, out_registers_rdatatwo_in_idex, out_ext_in_idex;
    //entradas buffer ex/mem
    sc_out<sc_uint<32>> out_add_in_exmem, out_alu_in_exmem; 
    sc_out<bool> zero; 
    sc_out<sc_uint<5>> out_mux_three_in_exmem; 
    //entrdas buffer mem/wb
    sc_out<sc_uint<32>> out_datamemory_in_memwb;


    //sinais de conexão dos módulos

    //entrada mux 1  e saída do somador 1 
    sc_signal<sc_uint<32>> out_add_one_in_mux_one;
    //entrada pc e saida mmux 1 
    sc_signal<sc_uint<32>> out_mux_one_in_pc;
    //saída pc que serve de entrada para o somador 1 e para a memória de instruções
    sc_signal<sc_uint<32>> out_pc; 
    //write data (entrada banco de registradores)
    sc_signal<sc_uint<32>> out_mux_four_in_wd_registers;
    //entrada somador 2
    sc_signal<sc_uint<32>> out_shift_in_add_two; 
    //entrada ula 
    sc_signal<sc_uint<32>> out_mux_two_in_alu; 

    //somador 1
    sc_signal<sc_uint<32>> number;

    //deslocador
    sc_signal<sc_uint<5>> shift_amount; 
    sc_signal<bool> shift_dir; 


    //construtor
    SC_CTOR(OpPart) : somador_1("Adder_1"),
                      somador_2("Adder_2"),
                      mux_1 ("mux_1"),
                      mux_2("mux_2"),
                      mux_3("mux_3"),
                      mux_4("mux_4"),
                      pc("ProgramCounter"),
                      instr_mem("InstructionMemory"),
                      data_mem("Memory"),
                      registers("BankRegister"), 
                      ula("alu4bit"),
                      extensor("SignExtend"),
                      deslocador("deslocador_bits"){

                      //MUX1
                       mux_1.a(out_add_one_in_mux_one);
                       mux_1.b(out_exmim_in_muxone); 
                       mux_1.sel(PCSrc);
                       mux_1.out(out_mux_one_in_pc);
                       
                      //SOMADOR 1
                       somador_1.a(out_pc);
                       somador_1.b(number);
                       number = 4; 
                       somador_1.sum(out_add_in_ifid);



                      //CONTADOR DE PROGRAMA
                       pc.jump_address(out_mux_one_in_pc);
                       pc.pc_out(out_pc);
                       pc.jump(jump);
                       pc.enable(enable);
                       pc.reset(reset);
                       pc.clk(clk);

                       //MEMORIA DE INTRUÇÕES
                       instr_mem.address(out_pc);
                       instr_mem.clk(clk);
                       instr_mem.instruction(out_instruction_memory_in_ifid);

                       //BANCO DE REGISTRADORES
                       registers.read_address_1(out_ifid_in_reg);
                       registers.read_address_2(out_ifid_in_reg);
                       registers.write_address(out_memwb_in_write_register); 
                       registers.write_data(out_mux_four_in_wd_registers);
                       registers.read_data_1(out_registers_rdataone_in_idex);
                       registers.read_data_2(out_registers_rdatatwo_in_idex);
                       registers.clk(clk);
                       registers.write_enable(RegWrite);

                       //perguntar pra professora sobre os clocks e os enables
                      

                      // ULA
                       ula.a(out_idex_in_alu);
                       ula.b(out_mux_two_in_alu); 
                       ula.op(out_alucontrol_in_alu);
                       ula.result(out_alu_in_exmem); 
                       ula.carry_out(zero); 
                      //MUX 2
                       mux_2.a(out_idex_in_one_mux_two);
                       mux_2.b(out_idex_in_two_mux_two);
                       mux_2.sel(ALUSrc);
                       mux_2.out(out_mux_two_in_alu);

                      //EXTENSOR DE BITS
                      // sc_dt::sc_uint<16> temp = ;
                       extensor.in(out_ifid_in_reg);
                       extensor.out(out_ext_in_idex);

                      //DESLOCADOR
                      deslocador.in(out_idex_in_two_mux_three);
                      deslocador.out(out_shift_in_add_two);
                      deslocador.shift_amount(shift_amount);
                      shift_amount = 2;
                      deslocador.shift_dir(shift_dir);
                      shift_dir = 0; 

                      //SOMADOR 2
                      somador_2.a(out_idex_in_add);
                      somador_2.b(out_shift_in_add_two);
                      somador_2.sum(out_add_in_exmem);

                      //MEMORIA DE DADOS
                      data_mem.address(out_exmem_in_address_data_memory);
                      data_mem.write_data(out_exmem_in_writedata_data_memory);
                      data_mem.mem_read(MemRead);
                      data_mem.mem_write(MemWrite);
                      data_mem.clk(clk);
                      data_mem.read_data(out_datamemory_in_memwb);

                      //MUX 3 
                      mux_3.a(out_idex_in_one_mux_three); 
                      mux_3.b(out_idex_in_two_mux_three); 
                      mux_3.sel(RegDst);
                      mux_3.out(out_mux_three_in_exmem);
                      

                      //MUX 4 
                      mux_4.a(out_memwb_in_one_mux_four);
                      mux_4.b(out_memwb_in_two_mux_four);
                      mux_4.sel(MemtoReg);
                      mux_4.out(out_mux_four_in_wd_registers); 

                      sensitive << clk.pos();

                      }



};

#endif