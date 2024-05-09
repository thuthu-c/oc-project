#include "systemc.h"
#include "op_part.h"

int sc_main(int argc, char* argv[]) {
    // Instanciando o módulo OpPart
    OpPart op("OpPart");

    // Sinais para conectar ao módulo
    sc_signal<bool> clk, reset, enable, jump;
    sc_signal<sc_uint<32>> out_exmim_in_muxone, PCSrc, out_ifid_in_reg, out_memwb_in_write_register, RegWrite, out_idex_in_add, out_idex_in_alu, out_alucontrol_in_alu, out_idex_in_one_mux_two, out_idex_in_two_mux_two, ALUSrc, out_idex_in_one_mux_three, out_idex_in_two_mux_three, out_exmem_in_address_data_memory, out_exmem_in_writedata_data_memory, MemWrite, MemRead, out_memwb_in_one_mux_four, out_memwb_in_two_mux_four, MemtoReg;
    sc_signal<sc_uint<16>> instruction;

    // Conectando os sinais
    op.clk(clk);
    op.reset(reset);
    op.enable(enable);
    op.jump(jump);
    op.out_exmim_in_muxone(out_exmim_in_muxone);
    op.PCSrc(PCSrc);
    op.out_ifid_in_reg(out_ifid_in_reg);
    op.out_memwb_in_write_register(out_memwb_in_write_register);
    op.RegWrite(RegWrite);
    op.out_idex_in_add(out_idex_in_add);
    op.out_idex_in_alu(out_idex_in_alu);
    op.out_alucontrol_in_alu(out_alucontrol_in_alu);
    op.out_idex_in_one_mux_two(out_idex_in_one_mux_two);
    op.out_idex_in_two_mux_two(out_idex_in_two_mux_two);
    op.ALUSrc(ALUSrc);
    op.out_idex_in_one_mux_three(out_idex_in_one_mux_three);
    op.out_idex_in_two_mux_three(out_idex_in_two_mux_three);
    op.out_exmem_in_address_data_memory(out_exmem_in_address_data_memory);
    op.out_exmem_in_writedata_data_memory(out_exmem_in_writedata_data_memory);
    op.MemWrite(MemWrite);
    op.MemRead(MemRead);
    op.out_memwb_in_one_mux_four(out_memwb_in_one_mux_four);
    op.out_memwb_in_two_mux_four(out_memwb_in_two_mux_four);
    op.MemtoReg(MemtoReg);
    op.instruction(instruction);

    // Inicializando o VCD Trace
    sc_trace_file *wf = sc_create_vcd_trace_file("OpPart_waveform");
    wf->set_time_unit(1, SC_NS);

    // Adicionando sinais ao VCD Trace
    // Adicione os sinais que você deseja rastrear

    // Simulando por 100 ns
    for (int i = 0; i < 100; i++) {
        // Atualize os sinais de entrada conforme necessário
        sc_start(1, SC_NS);
    }

    // Fechando o VCD Trace
    sc_close_vcd_trace_file(wf);

    return 0;
}
