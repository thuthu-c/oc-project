#include "systemc.h"
#include "parte_operativa/op_part.h"
#include "parte_controle/Control.h"
#include "parte_operativa/modulos/buffers/EXMEM.h"
#include "parte_operativa/modulos/buffers/IDEX.h"
#include "parte_operativa/modulos/buffers/IFID.h"
#include "parte_operativa/modulos/buffers/MEMWB.h"


int decode(string instruction)
{
    // Faz a decodificação da entrada das instruções
    // Para instruções de ULA ela deve vir "Operação" "Registrador Um" "Registrador Dois" "Registrador Destino"
    // Para instruções de Mémoria, ela deve vir como "Operação" "Registrador Fonte" "Registrador Destino"
    // Para instruções de Jump, deve vir como "Operação" "Posição"

    // std::cout << "Inst: " << instruction << " ";

    uint decodedInstruction = 0;
    uint tmpInt;

    string tmp;
    stringstream ss(instruction);
    vector<string> words;

    while (getline(ss, tmp, ' '))
    {
        words.push_back(tmp);
    }

    if (words.size() == 4) // Ula
    {
        if (words[0] == "and")
        {
            tmpInt = 0x01;
        }
        else if (words[0] == "or")
        {
            tmpInt = 0x13;
        }
        else if (words[0] == "xor")
        {
            tmpInt = 0x24;
        }
        else if (words[0] == "not")
        {
            tmpInt = 0x36;
        }
        else if (words[0] == "cmp")
        {
            tmpInt = 0x45;
        }
        else if (words[0] == "add")
        {
            tmpInt = 0x50;
        }
        else if (words[0] == "sub")
        {
            tmpInt = 0x61;
        }
        else if (words[0] == "bne")
        {
            tmpInt = 0xA0; // 101101
        }
        else if (words[0] == "beq")
        {
            tmpInt = 0xB0; // 110101
        }
        decodedInstruction |= (tmpInt << 26);

        decodedInstruction |= (stoi(words[1]) << 21);

        decodedInstruction |= (stoi(words[2]) << 16);

        decodedInstruction |= (stoi(words[3]) << 11);
    }
    else if (words.size() == 3) // Memória
    {
        if (words[0] == "lw")
        {
            tmpInt = 0x70; // 010000
        }
        else if (words[0] == "sw")
        {
            tmpInt = 0x80; // 011000
        }

        decodedInstruction |= (tmpInt << 26);

        decodedInstruction |= (stoi(words[1]) << 21);

        decodedInstruction |= (stoi(words[2]) << 16);
    }
    else if (words.size() == 2) // Jump
    {
        if (words[0] == "j")
        {
            tmpInt = 0x90; // 100000
        }

        decodedInstruction |= (tmpInt << 26);

        decodedInstruction |= (stoi(words[1]) << 21);
    }
    // std::cout << decodedInstruction << " ";
    return decodedInstruction;
}

int sc_main(int argc, char* argv[]){

    //instanciando os modulos
    OpPart op("OpPart");
    
    Control control("Control");

    //sinais para conectar os modulos
    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_uint<3>> aluOp;
    sc_signal<bool> aluSrc, regDst, regWrite, memRead, memWrite, memToReg, branch; 

    //buffers
    EXMEM  buffer_1;
    IDEX   buffer_2;
    IFID   buffer_3;
    MEMWB  buffer_4; 

    //entradas e saidas buffers 

    // buffer_1
    sc_signal<sc_uint<32>> out_add_in_ifid, out_instruction_memory_in_ifid;
    sc_signal<sc_uint<32>> out_ifid_in_idex, out_ifid_in_reg;

    // buffer_2
    sc_signal<sc_uint<32>> out_ifid_in_idex, out_registers_rdataone_in_idex,out_registers_rdatatwo_in_idex,out_ext_in_idex, out_idex_in_add,out_idex_in_alu, out_buffer_2;  
    sc_signal<sc_uint<3>> aluOp; 
    sc_signal<bool> aluSrc;
    sc_signal<bool> regDst;
    sc_signal<bool> regWrite;
    sc_signal<bool> memRead;
    sc_signal<bool> memWrite;
    sc_signal<bool> memToReg;
    sc_signal<bool> branch;

    // saida buffer_2
    sc_signal<sc_uint<5>>  out_idex_in_one_mux_three, out_idex_in_two_mux_three;
    sc_signal<bool> aluSrc;
    sc_signal<bool> regDst;
    sc_signal<bool> regWrite;
    sc_signal<bool> memRead;
    sc_signal<bool> memWrite;
    sc_signal<bool> memToReg;
    sc_signal<bool> branch;

    // buffer_3
    sc_signal<sc_uint<32>> out_add_in_exmem, out_alu_in_exmem;
    sc_signal<sc_uint<5>> out_mux_three_in_exmem;
    sc_signal<sc_uint<32>>  out_exmem_in_address_data_memory, out_exmem_in_writedata_data_memory;
    sc_signal<sc_uint<32>> out_exmim_in_muxone;

    // buffer_4
    sc_signal<sc_uint<32>> out_datamemory_in_memwb;
    sc_signal<sc_uit<32>> out_memwb_in_one_mux_four, out_memwb_in_two_mux_four;
    sc_signal<sc_uint<5>> in_memwb;
    sc_signal<sc_uint<5>> out_memwb_in_write_register;

    // conectando os sinais ao módulo de controle
    control.opcode(opcode);
    control.aluOp(aluOp);
    control.aluSrc(aluSrc);
    control.regDst(regDst);
    control.regWrite(regWrite);
    control.memRead(memRead);
    control.memWrite(memWrite);
    control.memToReg(memToReg);
    control.branch(branch);

    //conectando os sinais de controle ao módulo operativo
    op.aluOp(aluOp);
    op.aluSrc(aluSrc);
    op.regDst(regDst);
    op.regWrite(regWrite);
    op.memRead(memRead);
    op.memWrite(memWrite);
    op.memToReg(memToReg);
    op.branch(branch);
    op.out_add_in_ifid(out_add_in_ifid);
    op.out_instruction_memory_in_ifid(out_instruction_memory_in_ifid);
    op.out_ifid_in_reg(out_ifid_in_reg);
    op.out_registers_rdataone_in_idex(out_registers_rdataone_in_idex);
    op.out_registers_rdatatwo_in_idex(out_registers_rdatatwo_in_idex);
    op.out_ext_in_idex(out_ext_in_idex);
    op.out_idex_in_one_mux_three(out_idex_in_one_mux_three);
    op.out_idex_in_two_mux_three(out_idex_in_two_mux_three);
    op.out_add_in_exmem(out_add_in_exmem);
    op.out_alu_in_exmem(out_alu_in_exmem);
    op.out_mux_three_in_exmem(out_mux_three_in_exmem);
    op.out_idex_in_add(out_idex_in_add);
    op.out_idex_in_alu(out_idex_in_alu);
    op.out_idex_in_one_mux_two(out_buffer_2);
    op.out_idex_in_one_mux_two(out_buffer_2);
    op.out_exmem_in_address_data_memory(out_exmem_in_address_data_memory);
    op.out_exmem_in_writedata_data_memory(out_exmem_in_writedata_data_memory);
    op.out_datamemory_in_memwb(out_datamemory_in_memwb);
    op.out_memwb_in_write_register(out_memwb_in_write_register);
    op.out_exmim_in_muxone(out_exmim_in_muxone);
    // conectando os sinais aos buffers
    

    //buffer IF/ID
    buffer_1.out_adder(out_add_in_ifid);
    buffer_1.out_ins_mem(out_instruction_memory_in_ifid);
    buffer_1.in_idex(out_ifid_in_idex);
    buffer_1.instruction(out_ifid_in_reg);

    //buffer ID/EX
    // IN
    buffer_2.out_ifid(out_ifid_in_idex);
    buffer_2.out_reg_data_one(out_registers_rdataone_in_idex);
    buffer_2.out_reg_data_two(out_registers_rdatatwo_in_idex);
    buffer_2.out_ext(out_ext_in_idex);
    buffer_2.instruction_one(out_ifid_in_idex);
    buffer_2.instruction_two(out_ifid_in_idex);
    buffer_2.aluOp(aluOp);
    buffer_2.aluSrc(aluSrc);
    buffer_2.regDst(regDst);
    buffer_2.regWrite(regWrite);
    buffer_2.memRead(memRead);
    buffer_2.memWrite(memWrite);
    buffer_2.memToReg(memToReg);
    buffer_2.branch(branch);
    // OUT
    buffer_2.in_mux_one(out_idex_in_one_mux_three);
    buffer_2.in_mux_two(out_idex_in_two_mux_three);
    buffer_2.in_add(out_idex_in_add);
    buffer_2.in_ula(out_idex_in_alu);
    buffer_2.in_mux(out_buffer_2);

    //buffer EX/MEM
    // IN
    buffer_3.out_adder(out_add_in_exmem);
    buffer_3.out_alu_result(out_alu_in_exmem);
    buffer_3.out_idex(out_idex_in_one_mux_three);
    buffer_3.out_mux(out_mux_three_in_exmem);
    // OUT
    buffer_3.in_address(out_exmem_in_address_data_memory); 
    buffer_3.in_write_data(out_exmem_in_writedata_data_memory); 
    buffer_3.in_mux(out_exmim_in_muxone);
    buffer_3.in_memwb(in_memwb); 
    buffer_3.zero(zero);
    buffer_3.aluSrc(aluSrc);
    buffer_3.regDst(regDst);
    buffer_3.regWrite(regWrite);
    buffer_3.memRead(memRead);
    buffer_3.memWrite(memWrite);
    buffer_3.memToReg(memToReg);
    buffer_3.branch(branch);

    // buffer MEM/WB
    // IN
    buffer_4.out_data_memory(out_datamemory_in_memwb); 
    buffer_4.out_exmem_address(out_exmem_in_address_data_memory); 
    buffer_4.out_exmem(in_memwb);
    buffer_4.regWrite(regWrite);
    buffer_4.memToReg(memToReg);

    // OUT
    buffer_4.in_mux_one(out_memwb_in_one_mux_four);
    buffer_4.in_mux_two(out_memwb_in_two_mux_four);
    buffer_4.in_registers_write_register(out_memwb_in_write_register);
    buffer_4.regWrite(regWrite);
    buffer_4.memToReg(memToReg);

    //!=== Read file ===!//
    fstream fileData;
    sc_uint<32> dataMem[32]; // Vetor com dados para entrarem na memória de dados
    int data, i{0};
    for (int i = 31; i > -1; i--)
    {
        OpPart.Memory.memory[i] = data;
    }

    fstream fileInstruction;
    sc_uint<32> instructionMem[32]; // Vetor com dados para entrarem na memória de instruções
    string fileName = argv[1];
    fileInstruction.open(fileName);
    if (!fileInstruction)
    {
        std::cout << "Erro no carregamento do arquivo de instruções";
        exit(1);
    }
    string instStr;
    int instInt;
    i = 0;
    while (getline(fileInstruction, instStr))
    {
        instInt = decode(instStr);
        InstMemory.InstructionBank[i] = instInt;
        i++;
    }
    fileInstruction.close();

    
}