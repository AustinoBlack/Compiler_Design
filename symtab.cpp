#include "symtab.h" 

#include <iostream>
#include <string>

using namespace std;

extern vector<int> bytes;

SymbolTable::SymbolTable() : m_next_address{0xcc00}, m_next_id{0}
{}

int SymbolTable::add(const string name)
{
   //Make a new symbol table entry
   Symbol new_symbol;
   new_symbol.name = name;
   new_symbol.address = m_next_address;
   new_symbol.id = m_next_id;

   //Add symbol to table
   m_symbols.push_back(new_symbol);

   //Increment counters
   ++m_next_id;
   m_next_address += 2;

   //Return the id
   return new_symbol.id;
}

int SymbolTable::temporary()
{
   string name = "t" + to_string(m_next_id);
   return add(name);
}

int SymbolTable::address(const int id) const
{
   for (auto& s: m_symbols) {
      if (s.id == id) {
         return s.address;
      }
   }
   return -1;
}

int SymbolTable::address_of(const string name) const
{
   for (auto& s: m_symbols) {
      if (s.name == name) {
         return s.address;
      }
   }
   return -1;
}

int SymbolTable::id_of(const string name) const
{
   for (auto& s: m_symbols) {
      if (s.name == name) {
         return s.id;
      }
   }
   return -1;
}

string SymbolTable::name_of(const int id) const
{
   for (auto& s: m_symbols) {
      if (s.id == id) {
         return s.name;
      }
   }
   return "";
}

string SymbolTable::name_at(const int address) const
{
   for (auto& s: m_symbols) {
      if (s.address == address) {
         return s.name;
      }
   }
   return "";
}

void SymbolTable::print() const
{
   for (auto& s: m_symbols) {
      cout << s.id << " [ " << s.name << ": " << uppercase << hex << s.address << "]" << endl;
   }
}

LabelTable::LabelTable() : m_next_id{0}
{ }

int LabelTable::add(const string name, const int address)
{
   //Make a new symbol table entry
   Symbol new_symbol;
   new_symbol.name = name;
   new_symbol.address = address;
   new_symbol.id = m_next_id;

   //Add symbol to table
   m_labels.push_back(new_symbol);

   //Increment counter
   ++m_next_id;

   //Return the id
   return new_symbol.id;
}

int LabelTable::here()
{
   return there(0);
}

int LabelTable::there(int offset)
{
   string name = "t" + to_string(m_next_id);
   return add(name, 0xc000 + bytes.size() + offset);
}

int LabelTable::address_of(const string name) const
{
   for (auto& s: m_labels) {
      if (s.name == name) {
         return s.address;
      }
   }
   return -1;
}

int LabelTable::address(const int id) const
{
   for (auto& s: m_labels) {
      if (s.id == id) {
         return s.address;
      }
   }
   return -1;
}

int LabelTable::id_of(const string name) const
{
   for (auto& s: m_labels) {
      if (s.name == name) {
         return s.id;
      }
   }
   return -1;
}

string LabelTable::name_of(const int id) const
{
   for (auto& s: m_labels) {
      if (s.id == id) {
         return s.name;
      }
   }
   return "";
}

string LabelTable::name_at(const int address) const
{
   for (auto& s: m_labels) {
      if (s.address == address) {
         return s.name;
      }
   }
   return "";
}

void LabelTable::print() const
{
   for (auto& s: m_labels) {
      cout << s.id << " [ " << s.name << ": " << uppercase << hex << s.address << "]" << endl;
   }
}


