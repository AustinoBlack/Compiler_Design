#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

class Node {
   protected:
      string m_token;
      vector<Node *> m_children;
   public:
      int m_lineno;

      Node(string name);
      string token() const;
      void set_token(const string& name);
      virtual void visit(int depth) const;
      virtual int generate_code() const;
      void add_child(Node* const kid);
      void generate_point(int x, int y) const;
      void generate_rect(int x1, int y1, int w, int h) const;
      void setup_sound();
      void play_sound(int pitch, int duration);
      static int eq(int left, int right);
      static int ne(int left, int right);
      static int less(int left, int right);
      static int greater(int left, int right);
      static int less_equal(int left, int right);
      static int greater_equal(int left, int right);
      static int logical_or(int left, int right);
      static int logical_and(int left, int right);
};

class Constant  : public Node {
   protected:
      int m_value;
   public:
      Constant(string name);
      int value() const;
      void set_value(const int v);
      void visit(int depth) const;
};

class StringConstant : public Node {
   protected:
      string m_value;
   public:
      StringConstant(string name);
      string value() const;
      void set_value(const string v);
      void visit(int depth) const;
};

class Identifier : public Node {
   protected:
      string m_value;
   public:
      Identifier(string name);
      string value() const;
      void set_value(const string& v);
      void visit(int depth) const;
};

extern const Node* current;

#endif //NODE_H
