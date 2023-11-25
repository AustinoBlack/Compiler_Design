#include "node.h" 
#include "symtab.h"
#include "helper.h"
#include "opcodes.h"

#include <iostream>

//#define DEBUG(x) printf( "%ld: %s\n", bytes.size(), (x) )
#define DEBUG(x) 

using namespace std;

SymbolTable st;
LabelTable lt;

extern vector<int> bytes;
extern int lines;
const Node* current = nullptr;

int Node::eq(int left, int right) 
{
   int result = st.temporary();
   ldy_imm(0); 

   int end = (lt.address(lt.here()) - 2) + 18;

   lda_abs(left+1); //3
   cmp_abs(right+1); //3
   bne(end); //2

   lda_abs(left); //3
   cmp_abs(right); //3
   bne(end); //2

   ldy_imm(1); //2

   //End
   sty_abs(st.address(result));
   return result;
}
int Node::ne(int left, int right) 
{
   int result = st.temporary();
   ldy_imm(1); 

   int end = (lt.address(lt.here()) - 2) + 18;

   lda_abs(left+1); //3
   cmp_abs(right+1); //3
   bne(end); //2

   lda_abs(left); //3
   cmp_abs(right); //3
   bne(end); //2

   ldy_imm(0); //2

   //End
   sty_abs(st.address(result));
   return result;
}
int Node::less(int left, int right) 
{
   int result = st.temporary();
   ldy_imm(1); 

   int retTrue = (lt.address(lt.here()) - 2) + 26;
   int retFalse = retTrue - 2;

   //If leftHigh < rightHigh it's less than
   lda_abs(left+1); //3
   cmp_abs(right+1); //3
   bmi(retTrue); //2

   //If rightHigh < leftHigh it's not less than
   lda_abs(right+1); //3
   cmp_abs(left+1); //3
   bmi(retFalse); //2

   //If leftHigh == rightHigh, check if leftLow < rightLow
   lda_abs(left); //3
   cmp_abs(right); //3
   bmi(retTrue); //2

   //retFalse
   ldy_imm(0); //2

   //retTrue
   sty_abs(st.address(result));
   return result;
}
int Node::less_equal(int left, int right) 
{
   int result = st.temporary();
   ldy_imm(1); 

   int end = (lt.address(lt.here()) - 2) + 30;

   //If highLeft < highRight, return 1.
   lda_abs(left+1); //3
   cmp_abs(right+1); //3
   bmi(end); //2
   
   //If highRight < highLeft, return 0.
   ldy_imm(0); //2
   lda_abs(right+1); //3
   cmp_abs(left+1); //3
   bmi(end); //2

   //If highLeft == highRight, check low bytes.
   ldy_imm(1);//2
   //If lowA <= lowB, return true.
   lda_abs(right); //3
   cmp_abs(left); //3
   bpl(end); //2
   //Else return false
   ldy_imm(0); //2

   //End
   sty_abs(st.address(result));
   return result;
}
int Node::greater(int left, int right) 
{
   return less(right, left);
}
int Node::greater_equal(int left, int right) 
{
   return less_equal(right,left);
}

int Node::logical_or(int left, int right)
{
      int result = st.temporary();
      ldy_imm(1);  //True
      int end = (lt.address(lt.here()) - 2) + 12;
      lda_abs(left); //3      : If left is true, jump to end and return true
      bne(end); //2
      lda_abs(right);//3      : If right is true jump to end and return true
      bne(end);//2
      ldy_imm(0);//2                      : Otherwise, return false.
      sty_abs(st.address(result));

      return result;
}

int Node::logical_and(int left, int right)
{
      int result = st.temporary();
      ldy_imm(0);  //False
      int end = (lt.address(lt.here()) - 2) + 12;
      lda_abs(left); //3      : If left is false, jump to end and return false
      beq(end); //2
      lda_abs(right);//3      : If right is false jump to end and return false
      beq(end); //2
      ldy_imm(1); //2                     : Otherwise, return true.
      sty_abs(st.address(result));
      return result;
}

void Node::generate_point(int x, int y) const //TODO: adda color param
{
      if (x < 0) {
         abort("Point with undefined x coordinate.\n", m_lineno);
      }
      int addx = st.address(x);
      if (addx < 0) {
         abort("X coordinate with invalid address.\n", m_lineno);
      }
      if (y < 0) {
         abort("Point with undefined y coordinate.\n", m_lineno);
      }
      int addy = st.address(y);
      if (addy < 0) {
         abort("Y coordinate with invalid address.\n", m_lineno);
      }

      //Base Address of screen is 0x0400.  Store a pointer to it in $00fc-$00fd.
      //Base Address of color map is 0xd800.  Pointer goes in $00fe-$00ff.
      lda_imm(0x00);
      sta_z(0xfc);
      lda_imm(0x04);
      sta_z(0xfd);

      lda_imm(0x00);
      sta_z(0xfe);
      lda_imm(0xd8);
      sta_z(0xff);

      //Now loop y times and add 40 to the address.
      ldy_abs(addy);
      int end = lt.here(); //Gives me the memory address of the current instruction
      beq(lt.address(end)+16); //If y==0, jump sixteen bytes ahead to "end"

      //Top of loop
      int top = lt.address(lt.here());
      fprintf(stderr, "Top of point drawing loop: %x\n", top);
      fprintf(stderr, "Top should be: %lx\n", 0xc000+bytes.size());
      lda_imm(40);  //2 
      clc();	    //1
      adc_z(0xfc);  //Add 40 to the offset	//2
      sta_z(0xfc);  //2
      lda_imm(0);   //2
      adc_z(0xfd);  //2
      sta_z(0xfd);  //2

      lda_imm(40);  //2 
      clc();	    //1
      adc_z(0xfe);  //Add 40 to the offset	//2
      sta_z(0xfe);  //2
      lda_imm(0);   //2
      adc_z(0xff);  //2
      sta_z(0xff);  //2

      dey();        //Subtract one from y //1 
      bne(top-2);   //If not equal to zero, repeat (by jumping 16 bytes back to "top"). //2

      //End
      
      lda_imm(81);   //Screen code for a ball
      ldy_abs(addx);     //Load X coordinate into register Y for indexing
      sta_indy(0xfc); //Store at *0xfc

      lda_z(2);         //Load current color
      sta_indy(0xfe);   //Store at *0xfe
}

void Node::generate_rect(int x1, int y1, int w, int h) const //TODO: adda color param
{
   int x = st.temporary();
   int x2 = st.temporary(); 
   int y = st.temporary();
   int y2 = st.temporary();

   //x = x1 (low)
   lda_abs(st.address(x1));
   sta_abs(st.address(x));

   //x2 = x1 + w (low)
   clc();
   adc_abs(st.address(w));
   sta_abs(st.address(x2));

   //x = x1 (high)
   lda_abs(st.address(x1)+1);
   sta_abs(st.address(x)+1);

   //x2 = x1 + w (high)
   adc_abs(st.address(w)+1);
   sta_abs(st.address(x2)+1);

   //y = y1 (low)
   lda_abs(st.address(y1));
   sta_abs(st.address(y));

   //y2 = y1 + h (low)
   clc();
   adc_abs(st.address(h));
   sta_abs(st.address(y2));

   //y = y1 (high)
   lda_abs(st.address(y1)+1);
   sta_abs(st.address(y)+1);

   //y2 = y1 + h (high)
   adc_abs(st.address(h)+1);
   sta_abs(st.address(y2)+1);

   //Top of loop
   int top = lt.address(lt.here());
   int c1 = Node::less(st.address(x), st.address(x2));    // x < x2
   int c2 = Node::less(st.address(y), st.address(y2));    // OR y < y2
   int c3 = Node::logical_or(st.address(c1), st.address(c2));

   int body = lt.address(lt.here());
   bne(body+3);

   int placeholder = bytes.size();
   jmp(0); // Jump to end of loop

   //If x < x2
   int c4 = Node::less_equal(st.address(x),st.address(x2));
   ldy_abs(st.address(c4));

   int first_if = lt.address(lt.here());
   bne(first_if+3);
   int placeholder2 = bytes.size();
   jmp(0);
   generate_point(x,y1);
   generate_point(x,y2);

   //End if
   int end_if1 = lt.address(lt.here());
   bytes[placeholder2+1] = low(end_if1);
   bytes[placeholder2+2] = high(end_if1);

   //If y < y2
   int c5 = Node::less_equal(st.address(y),st.address(y2));
   ldy_abs(st.address(c5));
   int second_if = lt.address(lt.here());
   bne(second_if+3);
   int placeholder3 = bytes.size();
   jmp(0);

   generate_point(x1,y);
   generate_point(x2,y);

   //End if
   int end_if2 = lt.address(lt.here());
   bytes[placeholder3+1] = low(end_if2);
   bytes[placeholder3+2] = high(end_if2);

   // x = x + 1 (low)
   lda_imm(1);
   clc();
   adc_abs(st.address(x));
   sta_abs(st.address(x));

   // x = x + 0 (high) -- just for the carry
   lda_imm(0);
   adc_abs(st.address(x)+1);
   sta_abs(st.address(x)+1);

   // y = y + 1 (low)
   lda_imm(1);
   clc();
   adc_abs(st.address(y));
   sta_abs(st.address(y));

   // y = y + 0 (high) -- just for the carry
   lda_imm(0);
   adc_abs(st.address(y)+1);
   sta_abs(st.address(y)+1);

   //Loop
   jmp(top);
   
   //End of loop:
   int end = lt.address(lt.here());
   bytes[placeholder+1] = low(end);
   bytes[placeholder+2] = high(end);
}

Node::Node(string name) : m_token(name), m_lineno(lines)
{}

string Node::token() const
{
   return m_token;
}

void Node::set_token(const string& name)
{
   m_token = name;
}

int Node::generate_code() const //TODO pls
{
   current = this;
   if (m_token == "program") {
      DEBUG("program");
      if (m_children.size() < 1) {
         abort("Program is empty.\n", m_lineno);
      }
      //Set drawing color to current cursor color
      lda_abs(646);
      sta_z(2);

      m_children[0]->generate_code();
      rts(); 
   }
	 else if (m_token == "code") {
			m_children[0]->generate_code();
		  m_children[1]->generate_code();
   }

   //TODO: We have an identifier token, so keep?
   //TODO: mayhaps edit
   else if (m_token == "identifier") {
      DEBUG("identifier");
      const Identifier* id = dynamic_cast<const Identifier *>(this);
      if (!id) {
         abort("Expected identifier!\n", m_lineno);
      }

      int t = st.id_of(id->value());
      if (t < 0) {
         t = st.add(id->value());
      }
      if (t < 0) {
         abort("Could not allocate symbol for identifier\n", m_lineno);
      }
      return t;
   }
   //TODO: We have a constant token, so keep?
   //TODO: mayhaps edit
   else if (m_token == "constant") {
      DEBUG("constant");
      const Constant* cstnt = dynamic_cast<const Constant *>(this);
      if (cstnt) {
         int t = st.temporary();
         int value = cstnt->value();

         lda_imm(low(value));
         int addy = st.address(t);
         if (addy < 0) {
            abort("Constant with no address\n", m_lineno);
         }
         sta_abs(addy);
         lda_imm(high(value));
         sta_abs(addy+1);
         return t;
      }
      else {
         abort("Constant with no value1\n", m_lineno);
      }  
   }
   //TODO: We have a statement token, so keep?
   //TODO: mayhaps edit
   else if (m_token == "statements") {
         DEBUG("statements");
         if (m_children.size() < 2) {
            abort("Statements node with too few children.\n", m_lineno);
         }
         m_children[0]->generate_code(); 
         m_children[1]->generate_code(); 
   }
   else if (m_token == "number") {
         const Constant* child = dynamic_cast<const Constant *>(this);
	 int result = st.temporary();
         lda_imm(low(child->value()));
	 sta_abs(st.address(result));
         lda_imm(high(child->value()));
      	 sta_abs(st.address(result)+1);
	 return result;
   }
   //TODO: We have an assignment token, so keep?
   //TODO: mayhaps edit
   else if (m_token == "assignment") {
      DEBUG("assignment");
      if (m_children.size() < 2) {
         abort("Assignment missing either identifier or expression\n", m_lineno);
      }
      int variable = m_children[0]->generate_code();
      if (variable < 0) {
         abort("Assigning to identifier with no symbol.\n", m_lineno);
      }
      if (m_children[1]->m_token == "constant") {
         const Constant* child = dynamic_cast<const Constant *>(m_children[1]);
         lda_imm(low(child->value()));
         sta_abs(st.address(variable));
         lda_imm(high(child->value()));
         sta_abs(st.address(variable)+1);
      }
      else if (m_children[1]->m_token == "identifier") {
         const Identifier* child = dynamic_cast<const Identifier*>(m_children[1]);
         int id = st.id_of(child->value());
         if (id < 0) {
            abort("Undefined variable in assignment\n", m_lineno);
         }
         lda_abs(st.address(id));
         sta_abs(st.address(variable));
         lda_abs(st.address(id)+1);
         sta_abs(st.address(variable)+1);
      }
      else{
         int value = m_children[1]->generate_code();
         if (value < 0) {
            abort("Assignment with no temporary.\n", m_lineno);
         }
         lda_abs(st.address(value));
         sta_abs(st.address(variable));
         lda_abs(st.address(value)+1);
         sta_abs(st.address(variable)+1);
      }
   }
   //TODO: add poke to lang?
   else if (m_token == "poke") {
         DEBUG("point");
      if (m_children.size() < 2) {
         abort("Point requires two coordinates.\n", m_lineno);
      }
      int x = m_children[0]->generate_code();
      int y = m_children[1]->generate_code();

      lda_abs(st.address(x)); 
      sta_z(0xfc);
      lda_abs(st.address(x)+1); 
      sta_z(0xfd);
      lda_abs(st.address(y));
      ldx_imm(0);
      sta_indx(0xfc);
   }
   //TODO I do not think we need a move token, but idk
   else if (m_token == "move") {
         DEBUG("point");
      if (m_children.size() < 2) {
         abort("Point requires two coordinates.\n", m_lineno);
      }
      int x = m_children[0]->generate_code();
      int y = m_children[1]->generate_code();

      ldy_abs(st.address(x)); //Load X coordinate into register Y (backwards, I know, but that's how PLOT works)
      ldx_abs(st.address(y)); //Load Y coordinate into register X
      clc(); //Clear carry bit to mean "set position"
      jsr_abs(0xfff0); //Call kernal PLOT function
   }
	 //TODO: Implement "color" we generate code but do not pass it as a param. see line 161.
   else if (m_token == "pixel") {
         DEBUG("point");
      if (m_children.size() < 3) {
         abort("Point requires color, x, y.\n", m_lineno);
      }
			int color = dynamic_cast<Constant *>(m_children[0])->value();
      int x = m_children[1]->generate_code();
      int y = m_children[2]->generate_code();
      this->generate_point(x,y);
   }	
	 //TODO: Implement "color" we generate code but do not pass it as a param. see line 228
   else if (m_token == "rectangle") {
         DEBUG("rect");
      if (m_children.size() < 5) {
         abort("Rectangle requires color,x,y, width, and height.\n", m_lineno);
      }
      int color = dynamic_cast<Constant *>(m_children[0])->value();
      int x = m_children[1]->generate_code();
      int y = m_children[2]->generate_code();
      int w = m_children[3]->generate_code();
      int h = m_children[4]->generate_code();
      generate_rect(x,y,w,h);
   }
   //TODO: Keep this, we have an if
   else if (m_token == "if") {
      DEBUG("if");
      if (m_children.size() < 2) {
         abort("If statement requires both condition and body\n", m_lineno);
      }
      int cond = m_children[0]->generate_code();
      lda_abs(st.address(cond));
      cmp_imm(0);
      int top = lt.here();
      bne(lt.address(top)+3); 
      int backpatch = bytes.size();
      jmp(0xc000);//Insert placeholder
      m_children[1]->generate_code();
      int end = lt.address(lt.here());

      //Backpatch placeholder
      bytes[backpatch+1] = low(end);
      bytes[backpatch+2] = high(end);
   }
   //TODO: we have a while loop i think so keep this
   else if (m_token == "while") {
      DEBUG("while");
      if (m_children.size() < 2) {
         abort("If statement requires both condition and body\n", m_lineno);
      }

      int top = lt.here();

      int cond = m_children[0]->generate_code();
      ldy_abs(st.address(cond));

      int body = lt.here();
      bne(lt.address(body)+3);
      long int placeholder = bytes.size();
      jmp(0); //3

      m_children[1]->generate_code();
      jmp(lt.address(top));

      int end = lt.address(lt.here());
	
      //Backpatching of the jmp(0)
      bytes[placeholder+1] = low(end);
      bytes[placeholder+2] = high(end);
      fprintf(stderr, "While loop top should be: %lx\n", 0xc000+bytes.size());
      fprintf(stderr, "While loop top: %x\n", end);
   }
   //TODO: We dont have an "and" token i feel like mayhaps we will need this
   else if (m_token == "and") {
      if (m_children.size() < 2) {
         abort("AND requires a left and right condition.\n", m_lineno);
      }
      int left = m_children[0]->generate_code();
      int right = m_children[1]->generate_code();

      return logical_and(st.address(left), st.address(right));
   }
   //TODO: We dont have an "or" token i feel like mayhaps we will need this
   else if (m_token == "or") {
      if (m_children.size() < 2) {
         abort("OR requires a left and right condition.\n", m_lineno);
      }
      int left = m_children[0]->generate_code();
      int right = m_children[1]->generate_code();

      return logical_or(st.address(left), st.address(right));
   }
   else if(m_token == "condition") {
         DEBUG("condition");
      if (m_children.size() < 3) {
         abort("condition requires two coordinates.\n", m_lineno);
      }
      int left = m_children[0]->generate_code();
      int right = m_children[2]->generate_code();

      int left_addy = st.address(left);
      int right_addy = st.address(right);

      int top;
      if (m_children[1]->m_token == "LT") {
         return less(left_addy, right_addy);
      }
      else if (m_children[1]->m_token == "GT") {
         return greater(left_addy, right_addy);
      }
      else if (m_children[1]->m_token == "EQ") {
         return eq(left_addy, right_addy);
      }
      else if (m_children[1]->m_token == "NE") {
         return ne(left_addy, right_addy);
      }
      else if (m_children[1]->m_token == "LTE") {
         return less_equal(left_addy, right_addy);
      }
      else if (m_children[1]->m_token == "GTE") {
         return greater_equal(left_addy, right_addy);
      }
      abort(string("Not implemented: ") + m_children[1]->m_token, m_lineno);
      return -1;
   }
   //TODO: we have a plus token so we probs need to keep this
   else if (m_token == "plus") {
         DEBUG("plus");
      if (m_children.size() < 2) {
         abort("Addition requires two operands.\n", m_lineno);
      }
      int left = m_children[0]->generate_code();
      int right = m_children[1]->generate_code();
      int result = st.temporary();
      lda_abs(st.address(left));
      sta_abs(st.address(result));
      lda_abs(st.address(left)+1);
      sta_abs(st.address(result)+1);
      add_variables(st.address(right), st.address(result));
      return result;
   }
   //TODO: we have a minus token so we probs need to keep this
   else if (m_token == "minus")  {
      DEBUG("minus");
      if (m_children.size() < 2) {
         abort("Subtraction requires two operands.\n", m_lineno);
      }
      int left = m_children[0]->generate_code();
      int right = m_children[1]->generate_code();
      int result = st.temporary();
      lda_abs(st.address(left));
      sta_abs(st.address(result));
      lda_abs(st.address(left)+1);
      sta_abs(st.address(result)+1);
      sub_variables(st.address(right), st.address(result));
      return result;
   }
   //TODO: we have a times token so we probs need to keep this
   else if (m_token == "times") {
      int left = m_children[0]->generate_code();
      int right = m_children[1]->generate_code();
      int result = st.temporary();

      lda_imm(0);
      sta_abs(st.address(result));
      sta_abs(st.address(result)+1);

      ldy_abs(st.address(right));

      int placeholder = bytes.size();
      beq(0); //Jump to end
      
      int top = lt.address(lt.here());
      lda_abs(st.address(left));
      clc();
      adc_abs(st.address(result));
      sta_abs(st.address(result));
      lda_abs(st.address(left)+1);
      adc_abs(st.address(result)+1);
      sta_abs(st.address(result)+1);
      dey();
      bne(top);

      //Backpatch end 
      int end = lt.address(lt.here());
      bytes[placeholder + 1] = low(end);
      bytes[placeholder + 2] = high(end);

      sta_abs(st.address(result));
   }
   //TODO: we probs need to add a divide token here

   //TODO: may need to edit color token to fit with our language
   else if (m_token == "color") {
      const Constant* c = dynamic_cast<const Constant *>(this);  
      if (!c) {
         abort("Invalid color\n", m_lineno);
      }
      lda_imm(c->value());
      sta_z(2); //Store current color at $0002.
   }
   //TODO: check if we need background token... could be useful to implement for game
   else if (m_token == "background") {
      const Constant* c = dynamic_cast<const Constant *>(this);  
      if (!c) {
         abort("Invalid color\n", m_lineno);
      }
      lda_imm(c->value());
      sta_abs(53281); //Store current color at $D021.
   }
   //TODO: check if we need clear token... could be useful to implement for game
   else if (m_token == "clear") {
      lda_imm(147); //Load code for CLR/HOME (0x93) into accumulator
      jsr_abs(0xffd2); //Call kernal CHROUT function to print to screen
   }
   else {
      abort(string("Unimplemented token: ") + m_token, m_lineno);
      //Placeholder
      for (auto n: m_children) {
         n->generate_code();
      }
   }
   return -1;
}

void Node::visit(int depth) const
{
   for (int i=0; i < depth; ++i) {
      cout << "  ";
   }
   cout << m_token << endl;
   for (auto n: m_children) {
      n->visit(depth+1);
   }
}

void Node::add_child(Node* const kid)
{
   m_children.push_back(kid);
}

Constant::Constant(string name) : Node(name)
{}

int Constant::value() const
{
   return m_value;
}

void Constant::set_value(const int v) 
{
   m_value = v;
}

void Constant::visit(int depth) const
{
   for (int i=0; i < depth; ++i) {
      cout << "  ";
   }
   cout << m_token << "(" << m_value << ")" << endl;
   for (auto n: m_children) {
      n->visit(depth+1);
   }
}

StringConstant::StringConstant(string name) : Node(name)
{}

string StringConstant::value() const
{
   return m_value;
}

void StringConstant::set_value(const string v) 
{
   m_value = v;
}

void StringConstant::visit(int depth) const
{
   for (int i=0; i < depth; ++i) {
      cout << "  ";
   }
   cout << m_token << "(" << m_value << ")" << endl;
   for (auto n: m_children) {
      n->visit(depth+1);
   }
}

Identifier::Identifier(string name) : Node(name)
{}

string Identifier::value() const
{
   return m_value;
}

void Identifier::set_value(const string& v) {
   m_value = v;
}

void Identifier::visit(int depth) const
{
   for (int i=0; i < depth; ++i) {
      cout << "  ";
   }
   cout << m_token << "(" << m_value << ")" << endl;
   for (auto n: m_children) {
      n->visit(depth+1);
   }
}
