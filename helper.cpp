#include "opcodes.h"
#include "symtab.h"
#include "node.h"
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

extern vector<int> bytes;
extern int lines;
extern LabelTable lt;

/* Generate a parsing error message and quit. */
void abort(const string msg, const int line) {
   printf("Syntax Error on line %d: %s\n", current->m_lineno, msg.c_str());
   printf("\n");
   printf("Partial Program output:");
   for (int i=0; i < bytes.size(); ++i) {
      printf("%d ", bytes[i]);
   }
   printf("\n");
   exit(-1);
}

//Return the low byte of an address
int low(const int address) {
   return address%256;
}

//Return the high byte of an address
int high(const int address) {
   return address/256;
}

int twos_complement(int byte)
{
         if (byte < 0)
             return 256+byte;
         return byte;
}

//Calculate how many bytes the program counter is from an address.
unsigned char relative(int address)
{
   int current = lt.address(lt.here());
   int rel_addr = address - (current - 1);

   if (rel_addr < -128 || rel_addr > 127) {
      printf("Relative address %x (%d) out of range.  ", rel_addr, rel_addr);
      printf("Destination address: %x.  Current address: %x).\n", address, current);
      abort("Illegal relative address", -1);
   }
   return twos_complement(rel_addr);
}

//Add both bytes of a two-byte address to the program
void push_address(int address)
{
   bytes.push_back(low(address));
   bytes.push_back(high(address));
}

void add_constant(int constant, int address) {
   lda_imm(low(constant));   
   clc();
   adc_abs(address);
   sta_abs(address);

   lda_imm(high(constant));
   adc_abs(address+1);
   sta_abs(address+1);
}

void add_variables(int address1, int address2) {
   lda_abs(address1);   
   clc();
   adc_abs(address2);
   sta_abs(address2);

   lda_abs(address1+1);
   adc_abs(address2+1);
   sta_abs(address2+1);
}

void sub_constant(int constant, int address)
{
   lda_imm(low(constant));
   sec();
   sbc_abs(low(address));
   sta_abs(low(address));

   lda_imm(high(constant));
   sbc_abs(high(address));
   sta_abs(high(address));
}

void sub_variables(int address1, int address2)
{
   lda_abs(address2);
   sec();
   sbc_abs(address1);
   sta_abs(address2);

   lda_abs(address2+1);
   sbc_abs(address1+1);
   sta_abs(address2+1);
}

void print_program()
{
   printf("\n"); //Start with a blank line to separate debugging output
   //Read and poke each byte of the program into memory at address $C000
   printf("5 print \"{clr}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}\"\n");
   printf("10 for i = 0 to %ld\n", bytes.size()-1);
   printf("20 read b\n");
   printf("30 poke 49152+i, b\n");
   printf("40 next i\n");

   //Execute the program at address $C000 (49152 in decimal)
   printf("50 sys 49152\n");

   //Encode the assembly program as bytes in DATA statements
   int lineno=100;
   for (int i=0; i < bytes.size(); ++i)
   {
      //Check for illegal bytes
      if (bytes[i] > 255 || bytes[i] < 0)
         abort("Opcode or byte value out of range\n", lineno);

      //We support a max of 16 bytes per DATA statement
      if (i % 16 == 0) {
         printf("\n%d data %d", lineno, bytes[i]);
         lineno += 10;

      }
      else {
         printf(",%d", bytes[i]); 
      }
   }
   printf("\n");
}

