void abort(const string message, const int line_no);

int low(const int address);
int high(const int address);
int relative(int address);

void push_address(int address);
void print_program();

//Add "constant" to the two-byte value in address, handling carries
void add_constant(int constant, int address);

//Add value in address 1 to address 2, storing result at address 2.
void add_variables(int address1, int address2);

//Subtract value in "address" from "constant", storing result at "address". 
void sub_constant(int constant, int address);

//Subtract value in "address1" from "constant2", storing result at "address2". 
void sub_variables(int address1, int address2);
