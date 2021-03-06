char simname[] = "Y86 Processor: seq-std.hcl";
#include <stdio.h>
#include "isa.h"
#include "sim.h"
int sim_main(int argc, char *argv[]);
int gen_pc(){return 0;}
int main(int argc, char *argv[])
  {plusmode=0;return sim_main(argc,argv);}
int gen_need_regids()
{
    return ((icode) == (I_RRMOVL)||(icode) == (I_ALU)||(icode) == (I_PUSHL)||(icode) == (I_POPL)||(icode) == (I_RMMOVL)||(icode) == (I_MRMOVL));
}

int gen_need_valC()
{
    return ((icode) == (I_RRMOVL)||(icode) == (I_RMMOVL)||(icode) == (I_MRMOVL)||(icode) == (I_JXX)||(icode) == (I_CALL)||(icode) == (I_ALU));
}

int gen_instr_valid()
{
    return ((icode) == (I_NOP)||(icode) == (I_HALT)||(icode) == (I_RRMOVL)||(icode) == (I_RMMOVL)||(icode) == (I_MRMOVL)||(icode) == (I_ALU)||(icode) == (I_JXX)||(icode) == (I_CALL)||(icode) == (I_RET)||(icode) == (I_PUSHL)||(icode) == (I_POPL)||(icode) == (I_ENTER));
}

int gen_instr_next_ifun()
{
    return ((((icode) == (I_ENTER)) & ((ifun) == 0)) ? 1 : 1 ? -1 : 0);
}

int gen_srcA()
{
    return (((icode) == (I_RRMOVL)||(icode) == (I_RMMOVL)||(icode) == (I_ALU)||(icode) == (I_PUSHL)) ? (ra) : ((icode) == (I_POPL)||(icode) == (I_RET)) ? (REG_ESP) : (((icode) == (I_ENTER)) & ((ifun) == 0)) ? (REG_EBP) : (((icode) == (I_ENTER)) & ((ifun) == 1)) ? (REG_ESP) : 1 ? (REG_NONE) : 0);
}

int gen_srcB()
{
    return (((icode) == (I_ALU)||(icode) == (I_RMMOVL)||(icode) == (I_MRMOVL)) ? (rb) : ((icode) == (I_PUSHL)||(icode) == (I_POPL)||(icode) == (I_CALL)||(icode) == (I_RET)) ? (REG_ESP) : (((icode) == (I_ENTER)) & ((ifun) == 0)) ? (REG_ESP) : (((icode) == (I_ENTER)) & ((ifun) == 1)) ? (REG_EBP) : 1 ? (REG_NONE) : 0);
}

int gen_dstE()
{
    return (((icode) == (I_RRMOVL)||(icode) == (I_ALU)) ? (rb) : ((icode) == (I_PUSHL)||(icode) == (I_POPL)||(icode) == (I_CALL)||(icode) == (I_RET)) ? (REG_ESP) : (((icode) == (I_ENTER)) & ((ifun) == 0)) ? (REG_ESP) : (((icode) == (I_ENTER)) & ((ifun) == 1)) ? (REG_EBP) : 1 ? (REG_NONE) : 0);
}

int gen_dstM()
{
    return (((icode) == (I_MRMOVL)||(icode) == (I_POPL)) ? (ra) : 1 ? (REG_NONE) : 0);
}

int gen_aluA()
{
    return ((((icode) == (I_ALU)) & ((ra) == (REG_NONE))) ? (valc) : ((icode) == (I_ALU)) ? (vala) : (((icode) == (I_RRMOVL)) & ((ra) == (REG_NONE))) ? (valc) : ((icode) == (I_RRMOVL)) ? (vala) : ((icode) == (I_RMMOVL)||(icode) == (I_MRMOVL)) ? (valc) : ((icode) == (I_CALL)||(icode) == (I_PUSHL)) ? -4 : ((icode) == (I_RET)||(icode) == (I_POPL)) ? 4 : (((icode) == (I_ENTER)) & ((ifun) == 0)) ? -4 : (((icode) == (I_ENTER)) & ((ifun) == 1)) ? (vala) : 0);
}

int gen_aluB()
{
    return (((icode) == (I_RMMOVL)||(icode) == (I_MRMOVL)||(icode) == (I_ALU)||(icode) == (I_CALL)||(icode) == (I_PUSHL)||(icode) == (I_RET)||(icode) == (I_POPL)) ? (valb) : ((icode) == (I_RRMOVL)) ? 0 : (((icode) == (I_ENTER)) & ((ifun) == 0)) ? (valb) : (((icode) == (I_ENTER)) & ((ifun) == 1)) ? 0 : 0);
}

int gen_alufun()
{
    return (((icode) == (I_ALU)) ? (ifun) : 1 ? (A_ADD) : 0);
}

int gen_set_cc()
{
    return ((icode) == (I_ALU));
}

int gen_mem_read()
{
    return ((icode) == (I_MRMOVL)||(icode) == (I_POPL)||(icode) == (I_RET));
}

int gen_mem_write()
{
    return (((icode) == (I_RMMOVL)||(icode) == (I_PUSHL)||(icode) == (I_CALL)) | (((icode) == (I_ENTER)) & ((ifun) == 0)));
}

int gen_mem_addr()
{
    return (((icode) == (I_RMMOVL)||(icode) == (I_PUSHL)||(icode) == (I_CALL)||(icode) == (I_MRMOVL)) ? (vale) : ((icode) == (I_POPL)||(icode) == (I_RET)) ? (vala) : (((icode) == (I_ENTER)) & ((ifun) == 0)) ? (vale) : 0);
}

int gen_mem_data()
{
    return (((icode) == (I_RMMOVL)||(icode) == (I_PUSHL)) ? (vala) : (((icode) == (I_ENTER)) & ((ifun) == 0)) ? (vala) : ((icode) == (I_CALL)) ? (valp) : 0);
}

int gen_new_pc()
{
    return (((icode) == (I_CALL)) ? (valc) : (((icode) == (I_JXX)) & (bcond)) ? (valc) : ((icode) == (I_RET)) ? (valm) : 1 ? (valp) : 0);
}

