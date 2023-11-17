#include <string>
#include <vector>

#ifndef SYMTAB_H
#define SYMTAB_H
class Symbol {
   public:
      std::string name;
      int address;
      int id;
};

class SymbolTable {
   private:
      std::vector<Symbol> m_symbols; 
      int m_next_address; 
      int m_next_id;
   public: 
      SymbolTable(); 
      int add(const std::string name); 
      int temporary();
      int address(const int id) const; 
      int address_of(const std::string name) const; 
      int id_of(const std::string name) const; 
      std::string name_of(const int id) const; 
      std::string name_at(const int address) const; 
      
      void print() const;
};

class LabelTable {
   private:
      std::vector<Symbol> m_labels; 
      int m_next_id;
   public: 
      LabelTable(); 
      int here();
      int there(int offset);
      int add(const std::string name, const int address); 

      int address(const int id) const; 
      int address_of(const std::string name) const; 
      int id_of(const std::string name) const; 

      std::string name_of(const int id) const; 
      std::string name_at(const int address) const; 
      
      void print() const;
};

#endif //SYMTAB_H
