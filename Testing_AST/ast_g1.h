class Expression
{
 virtual ~Expression() {}
virtual Expression *clone () = 0;
virtual int value () = 0;
};


class Sub : public Expression {

Subt (Expression *left, Expression *right): m_left (left), m_right (right) {}

  // Copy constructor
  Subt (const Subt &other) {
    m_left = other.m_left->clone ();
    m_right = other.m_right->clone ();
  }
  
  virtual ~Subt () 
  {
    delete m_left;
    delete m_right;
  }

  Subt &operator = (const Subt &other) {
    if (&other != this) {
      delete m_left;
      delete m_right;
      
      m_left = other.m_left->clone ();
      m_right = other.m_right->clone ();
    }
  }



};


class Number :public Expression {
	int m_val;

public:
   
  Number (int val): m_val (val) {}

  // Copy constructor
  Number (const Number &other) { m_val = other.m_val; }

  Number &operator = (const Number &other) {
    if (&other != this)
      m_val = other.m_val;
  }

  virtual Expression *clone () { return new Number (*this); }

  virtual int value () { return m_val; }


};


class Ident : public Expression {

 int *m_val;

public:
   
  Ident (int *val): m_val (val) {}

  // Copy constructor
  Ident (const Ident &other) { m_val = other.m_val; }

  Ident &operator = (const Ident &other) {
    if (&other != this)
      m_val = other.m_val;
  }

  virtual Expression *clone () { return new Ident (*this); }
  

  virtual int value () { return *m_val; }




};
