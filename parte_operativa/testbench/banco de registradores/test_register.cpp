#include "systemc.h"
#include "RegisterBank.h"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 10, SC_NS);  // Clock de 10 ns
    sc_signal<bool> write_enable;
    sc_signal<sc_uint<3>> write_address, read_address_1, read_address_2;
    sc_signal<sc_uint<4>> write_data, read_data_1, read_data_2;

    RegisterBank bank("RegisterBank");
    bank.clk(clk);
    bank.write_enable(write_enable);
    bank.write_address(write_address);
    bank.write_data(write_data);
    bank.read_address_1(read_address_1);
    bank.read_address_2(read_address_2);
    bank.read_data_1(read_data_1);
    bank.read_data_2(read_data_2);

    sc_trace_file *wf = sc_create_vcd_trace_file("waves");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, write_enable, "write_enable");
    sc_trace(wf, write_address, "write_address");
    sc_trace(wf, write_data, "write_data");
    sc_trace(wf, read_address_1, "read_address_1");
    sc_trace(wf, read_address_2, "read_address_2");
    sc_trace(wf, read_data_1, "read_data_1");
    sc_trace(wf, read_data_2, "read_data_2");

    // Simulação de exemplo
    write_enable = false;
    write_address = 3;
    write_data = 15;
    read_address_1 = 3;
    read_address_2 = 2;

    sc_start(20, SC_NS);
    write_enable = true;
    sc_start(20, SC_NS);
    write_enable = false;
    sc_start(20, SC_NS);

    sc_close_vcd_trace_file(wf);
    return 0;
}