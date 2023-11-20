#include "node.h" 
#include <iostream>

using namespace std;

Node::Node(string name) : m_token(name)
{}

string Node::token() const
{
   return m_token;
}

void Node::set_token(const string& name)
{
   m_token = name;
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

