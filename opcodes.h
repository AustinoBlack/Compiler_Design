void adc_imm(int immediate);
void adc_abs(int address);
void adc_absx(int address);
void adc_absy(int address);
void adc_indx(int address);
void adc_indy(int address);
void adc_z(int address);
void adc_zx(int address);

void and_imm(int immediate);
void and_abs(int address);
void and_absx(int address);
void and_absy(int address);
void and_indx(int address);
void and_indy(int address);
void and_z(int address);
void and_zx(int address);

void asl();
void asl_abs(int address);
void asl_absx(int address);
void asl_z(int address);
void asl_zx(int address);

void bcc(int address);

void bcs(int address);

void beq(int address);

void bit_abs(int address);
void bit_zx(int address);

void bmi(int address);

void bne(int address);

void bpl(int address);

void brk();

void bvc(int address);

void bvs(int address);

void clc();

void cld();

void cli();

void clv();

void cmp_imm(int immediate);
void cmp_abs(int address);
void cmp_absx(int address);
void cmp_absy(int address);
void cmp_indx(int address);
void cmp_indy(int address);
void cmp_z(int address);
void cmp_zx(int address);

void cpx_imm(int immediate);
void cpx_abs(int address);
void cpx_z(int address);

void cpy_imm(int immediate);
void cpy_abs(int address);
void cpy_z(int address);

void dec_abs(int address);
void dec_absx(int address);
void dec_z(int address);
void dec_zx(int address);

void dex();

void dey();

void eor(int immediate);
void eor_abs(int address);
void eor_absx(int address);
void eor_absy(int address);
void eor_indx(int address);
void eor_indy(int address);
void eor_z(int address);
void eor_zx(int address);

void inc_abs(int address);
void inc_absx(int address);
void inc_z(int address);
void inc_zx(int address);

void inx();

void iny();

void jmp(int address);
void jmp_ind(int address);

void jsr_abs(int address);

void lda_imm(int immediate);
void lda_abs(int address);
void lda_absx(int address);
void lda_absy(int address);
void lda_indx(int address);
void lda_indy(int address);
void lda_z(int address);
void lda_zx(int address);

void ldx_imm(int immediate);
void ldx_abs(int address);
void ldx_absy(int address);
void ldx_z(int address);
void ldx_zy(int address);

void ldy_imm(int immediate);
void ldy_abs(int address);
void ldy_absx(int address);
void ldy_z(int address);
void ldy_zx(int address);

void lsr();
void lsr_abs(int address);
void lsr_absx(int address);
void lsr_z(int address);
void lsr_zx(int address);

void nop();

void ora_imm(int immediate);
void ora_abs(int address);
void ora_absx(int address);
void ora_absy(int address);
void ora_indx(int address);
void ora_indy(int address);
void ora_z(int address);
void ora_zx(int address);

void pha();

void php();

void pla();

void plp();

void rol();
void rol_abs(int address);
void rol_absx(int address);
void rol_z(int address);
void rol_zx(int address);

void ror();
void ror_abs(int address);
void ror_absx(int address);
void ror_z(int address);
void ror_zx(int address);

void rti();

void rts();

void sbc_imm(int immediate);
void sbc_abs(int address);
void sbc_absx(int address);
void sbc_absy(int address);
void sbc_indx(int address);
void sbc_indy(int address);
void sbc_z(int address);
void sbc_zw(int address);

void sec();

void sed();

void sei();

void sta_abs(int address);
void sta_absx(int address);
void sta_absy(int address);
void sta_indx(int address);
void sta_indy(int address);
void sta_z(int address);
void sta_zx(int address);

void stx_abs(int address);
void stx_z(int address);
void stx_zy(int address);

void sty_abs(int address);
void sty_z(int address);
void sty_zx(int address);

void tax();

void tay();

void tsx();

void txa();

void txs();

void tya();

