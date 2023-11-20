#include "node.h"
#include "opcodes.h"
#include "helper.h"
#include "symtab.h"
#include <stdio.h>

#include <vector>

using namespace std;

vector<int> bytes;

void adc_imm(int immediate)
{
   bytes.push_back(0x69);
   bytes.push_back(immediate);
}

void adc_abs(int address)
{
   bytes.push_back(0x6d);
   push_address(address);
}

void adc_absx(int address)
{
   bytes.push_back(0x7d);
   push_address(address);
}  

void adc_absy(int address)
{
   bytes.push_back(0x79);
   push_address(address);
}  

void adc_indx(int address)
{
   bytes.push_back(0x61);
   bytes.push_back(low(address));
}  
void adc_indy(int address)
{
   bytes.push_back(0x71);
   bytes.push_back(low(address));
}  

void adc_z(int address)
{
   bytes.push_back(0x65);
   bytes.push_back(low(address));
}

void adc_zx(int address)
{
   bytes.push_back(0x75);
   bytes.push_back(low(address));
}

void and_imm(int immediate)
{
   bytes.push_back(0x29);
   bytes.push_back(immediate);
}

void and_abs(int address)
{
   bytes.push_back(0x2d);
   push_address(address);
}

void and_absx(int address)
{
   bytes.push_back(0x3d);
   push_address(address);
}  

void and_absy(int address)
{
   bytes.push_back(0x39);
   push_address(address);
}  

void and_indx(int address)
{
   bytes.push_back(0x21);
   bytes.push_back(low(address));
}  

void and_indy(int address)
{
   bytes.push_back(0x31);
   bytes.push_back(low(address));
}  

void and_z(int address)
{
   bytes.push_back(0x25);
   bytes.push_back(low(address));
}

void and_zx(int address)
{
   bytes.push_back(0x35);
   bytes.push_back(low(address));
}

void asl()
{
   bytes.push_back(0x0a);
}

void asl_abs(int address)
{
   bytes.push_back(0x0e);
   push_address(address);
}

void asl_absx(int address)
{
   bytes.push_back(0x1e);
   push_address(address);
}

void asl_z(int address)
{
   bytes.push_back(0x06);
   bytes.push_back(low(address));
}

void asl_zx(int address)
{
   bytes.push_back(0x16);
   bytes.push_back(low(address));
}

void bcc(int address)
{
   bytes.push_back(0x90);
   bytes.push_back(relative(address));
}

void bcs(int address)
{
   bytes.push_back(0xb0);
   bytes.push_back(relative(address));
}

void beq(int address)
{
   bytes.push_back(0xf0);
   bytes.push_back(relative(address));
}

void bit_abs(int address)
{
   bytes.push_back(0x2c);
   push_address(address);
}

void bit_zx(int address)
{
   bytes.push_back(0x24);
   bytes.push_back(low(address));
}


void bmi(int address)
{
   bytes.push_back(0x30);
   bytes.push_back(relative(address));
}

void bne(int address)
{
   bytes.push_back(0xd0);
   bytes.push_back(relative(address));
}

void bpl(int address)
{
   bytes.push_back(0x10);
   bytes.push_back(relative(address));
}

void brk()
{
   bytes.push_back(0x00);
}

void bvc(int address)
{
   bytes.push_back(0x50);
   bytes.push_back(relative(address));
}

void bvs(int address)
{
   bytes.push_back(0x70);
   bytes.push_back(relative(address));
}

void clc()
{
   bytes.push_back(0x18);
}

void cld()
{
   bytes.push_back(0xd8);
}

void cli()
{
   bytes.push_back(0x58);
}

void clv()
{
   bytes.push_back(0xb8);
}

void cmp_imm(int immediate)
{
   bytes.push_back(0xc9);
   bytes.push_back(immediate);
}

void cmp_abs(int address)
{
   bytes.push_back(0xcd);
   push_address(address);
}

void cmp_absx(int address)
{
   bytes.push_back(0xdd);
   push_address(address);
}

void cmp_absy(int address)
{
   bytes.push_back(0xd9);
   push_address(address);
}

void cmp_indx(int address)
{
   bytes.push_back(0xc1);
   bytes.push_back(low(address));
}

void cmp_indy(int address)
{
   bytes.push_back(0xd1);
   bytes.push_back(low(address));
}

void cmp_z(int address)
{
   bytes.push_back(0xc5);
   bytes.push_back(low(address));
}

void cmp_zx(int address)
{
   bytes.push_back(0xd5);
   bytes.push_back(low(address));
}

void cpx_imm(int immediate)
{
   bytes.push_back(0xe0);
   bytes.push_back(immediate);
}

void cpx_abs(int address)
{
   bytes.push_back(0xec);
   push_address(address);
}

void cpx_z(int address)
{
   bytes.push_back(0xe4);
   bytes.push_back(low(address));
}

void cpy_imm(int immediate)
{
   bytes.push_back(0xc0);
   bytes.push_back(immediate);
}

void cpy_abs(int address)
{
   bytes.push_back(0xcc);
   push_address(address);
}

void cpy_z(int address)
{
   bytes.push_back(0xc4);
   bytes.push_back(low(address));
}

void dec_abs(int address)
{
   bytes.push_back(0xce);
   push_address(address);
}

void dec_absx(int address)
{
   bytes.push_back(0xde);
   push_address(address);
}

void dec_z(int address)
{
   bytes.push_back(0xc6);
   bytes.push_back(low(address));
}

void dec_zx(int address)
{
   bytes.push_back(0xd6);
   bytes.push_back(low(address));
}

void dex()
{
   bytes.push_back(0xca);
}

void dey()
{
   bytes.push_back(0x88);
}

void eor(int immediate)
{
   bytes.push_back(0x49);
   bytes.push_back(immediate);
}

void eor_abs(int address)
{
   bytes.push_back(0x4d);
   push_address(address);
}

void eor_absx(int address)
{
   bytes.push_back(0x5d);
   push_address(address);
}

void eor_absy(int address)
{
   bytes.push_back(0x59);
   push_address(address);
}

void eor_indx(int address)
{
   bytes.push_back(0x41);
   bytes.push_back(low(address));
}

void eor_indy(int address)
{
   bytes.push_back(0x51);
   bytes.push_back(low(address));
}

void eor_z(int address)
{
   bytes.push_back(0x45);
   bytes.push_back(low(address));
}  

void eor_zx(int address)
{
   bytes.push_back(0x55);
   bytes.push_back(low(address));
}  

void inc_abs(int address)
{
   bytes.push_back(0xee);
   push_address(address);
}

void inc_absx(int address)
{
   bytes.push_back(0xfe);
   push_address(address);
}

void inc_z(int address)
{
   bytes.push_back(0xe6);
   bytes.push_back(low(address));
}  

void inc_zx(int address)
{
   bytes.push_back(0xf6);
   bytes.push_back(low(address));
}  


void inx()
{
   bytes.push_back(0xe8);
}

void iny()
{
   bytes.push_back(0xc8);
}

void jmp(int address)
{
   bytes.push_back(0x4c);
   push_address(address);
}

void jmp_ind(int address)
{
   bytes.push_back(0x6c);
   bytes.push_back(low(address));
}

void jsr_abs(int address)
{
   bytes.push_back(0x20);
   push_address(address);
}

void lda_imm(int immediate)
{
   bytes.push_back(0xa9);
   bytes.push_back(immediate);
}

void lda_abs(int address)
{
   bytes.push_back(0xad);
   push_address(address);
}

void lda_absx(int address)
{
   bytes.push_back(0xbd);
   push_address(address);
}  

void lda_absy(int address)
{
   bytes.push_back(0xb9);
   push_address(address);
}  

void lda_indx(int address)
{
   bytes.push_back(0xa1);
   bytes.push_back(low(address));
}  

void lda_indy(int address)
{
   bytes.push_back(0xb1);
   bytes.push_back(low(address));
}  

void lda_z(int address)
{
   bytes.push_back(0xa5);
   bytes.push_back(low(address));
}

void lda_zx(int address)
{
   bytes.push_back(0xb5);
   bytes.push_back(low(address));
}

void ldx_imm(int immediate)
{
   bytes.push_back(0xa2);
   bytes.push_back(immediate);
}

void ldx_abs(int address)
{
   bytes.push_back(0xae);
   push_address(address);
}

void ldx_absy(int address)
{
   bytes.push_back(0xbe);
   push_address(address);
}  

void ldx_z(int address)
{
   bytes.push_back(0xa6);
   bytes.push_back(low(address));
}

void ldx_zy(int address)
{
   bytes.push_back(0xb6);
   bytes.push_back(low(address));
}

void ldy_imm(int immediate)
{
   bytes.push_back(0xa0);
   bytes.push_back(immediate);
}

void ldy_abs(int address)
{
   bytes.push_back(0xac);
   push_address(address);
}

void ldy_absx(int address)
{
   bytes.push_back(0xbc);
   push_address(address);
}  

void ldy_z(int address)
{
   bytes.push_back(0xa4);
   bytes.push_back(low(address));
}

void ldy_zx(int address)
{
   bytes.push_back(0xb4);
   bytes.push_back(low(address));
}

void lsr()
{
   bytes.push_back(0x4a);
}

void lsr_abs(int address)
{
   bytes.push_back(0x4e);
   push_address(address);
}

void lsr_absx(int address)
{
   bytes.push_back(0x5e);
   push_address(address);
}

void lsr_z(int address)
{
   bytes.push_back(0x46);
   bytes.push_back(low(address));
}

void lsr_zx(int address)
{
   bytes.push_back(0x56);
   bytes.push_back(low(address));
}


void nop()
{
   bytes.push_back(0xea);
}

void ora_imm(int immediate)
{
   bytes.push_back(0x09);
   bytes.push_back(immediate);
}

void ora_abs(int address)
{
   bytes.push_back(0x0d);
   push_address(address);
}

void ora_absx(int address)
{
   bytes.push_back(0x1d);
   push_address(address);
}

void ora_absy(int address)
{
   bytes.push_back(0x19);
   push_address(address);
}

void ora_indx(int address)
{
   bytes.push_back(0x01);
   bytes.push_back(low(address));
}

void ora_indy(int address)
{
   bytes.push_back(0x11);
   bytes.push_back(low(address));
}

void ora_z(int address)
{
   bytes.push_back(0x05);
   bytes.push_back(low(address));
}

void ora_zx(int address)
{
   bytes.push_back(0x15);
   bytes.push_back(low(address));
}

void pha()
{
   bytes.push_back(0x48);
}

void php()
{
   bytes.push_back(0x08);
}

void pla()
{
   bytes.push_back(0x68);
}

void plp()
{
   bytes.push_back(0x28);
}

void rol()
{
   bytes.push_back(0x2a);
}

void rol_abs(int address)
{
   bytes.push_back(0x2e);
   push_address(address);
}

void rol_absx(int address)
{
   bytes.push_back(0x3e);
   push_address(address);
}

void rol_z(int address)
{
   bytes.push_back(0x26);
   bytes.push_back(low(address));
}

void rol_zx(int address)
{
   bytes.push_back(0x36);
   bytes.push_back(low(address));
}

void ror()
{
   bytes.push_back(0x6a);
}

void ror_abs(int address)
{
   bytes.push_back(0x6e);
   push_address(address);
}

void ror_absx(int address)
{
   bytes.push_back(0x7e);
   push_address(address);
}

void ror_z(int address)
{
   bytes.push_back(0x66);
   bytes.push_back(low(address));
}

void ror_zx(int address)
{
   bytes.push_back(0x76);
   bytes.push_back(low(address));
}

void rti()
{
   bytes.push_back(0x40);
}

void rts()
{
   bytes.push_back(0x60);
}

void sbc_imm(int immediate)
{
   bytes.push_back(0xe9);
   bytes.push_back(immediate);
}

void sbc_abs(int address)
{
   bytes.push_back(0xed);
   push_address(address);
}

void sbc_absx(int address)
{
   bytes.push_back(0xfd);
   push_address(address);
}  

void sbc_absy(int address)
{
   bytes.push_back(0xf9);
   push_address(address);
}  

void sbc_indx(int address)
{
   bytes.push_back(0xe1);
   bytes.push_back(low(address));
}  

void sbc_indy(int address)
{
   bytes.push_back(0xf1);
   bytes.push_back(low(address));
}  

void sbc_z(int address)
{
   bytes.push_back(0xe5);
   bytes.push_back(low(address));
}  

void sbc_zw(int address)
{
   bytes.push_back(0xf5);
   bytes.push_back(low(address));
}  

void sec()
{
   bytes.push_back(0x38);
}

void sed()
{
   bytes.push_back(0xf8);
}

void sei()
{
   bytes.push_back(0x78);
}

void sta_abs(int address)
{
   bytes.push_back(0x8d);
   push_address(address);
}

void sta_absx(int address)
{
   bytes.push_back(0x9d);
   push_address(address);
}  

void sta_absy(int address)
{
   bytes.push_back(0x99);
   push_address(address);
}  

void sta_indx(int address)
{
   bytes.push_back(0x81);
   bytes.push_back(low(address));
}  

void sta_indy(int address)
{
   bytes.push_back(0x91);
   bytes.push_back(low(address));
}  

void sta_z(int address)
{
   bytes.push_back(0x85);
   bytes.push_back(low(address));
}  

void sta_zx(int address)
{
   bytes.push_back(0x95);
   bytes.push_back(low(address));
}  

void stx_abs(int address)
{
   bytes.push_back(0x8e);
   push_address(address);
}

void stx_z(int address)
{
   bytes.push_back(0x86);
   bytes.push_back(low(address));
}

void stx_zy(int address)
{
   bytes.push_back(0x96);
   bytes.push_back(low(address));
}

void sty_abs(int address)
{
   bytes.push_back(0x8c);
   push_address(address);
}
void sty_z(int address)
{
   bytes.push_back(0x84);
   bytes.push_back(low(address));
}

void sty_zx(int address)
{
   bytes.push_back(0x94);
   bytes.push_back(low(address));
}


void tax()
{
   bytes.push_back(0xaa);
}

void tay()
{
   bytes.push_back(0xa8);
}

void tsx()
{
   bytes.push_back(0xba);
}

void txa()
{
   bytes.push_back(0x8a);
}

void txs()
{
   bytes.push_back(0x9a);
}

void tya()
{
   bytes.push_back(0x98);
}

