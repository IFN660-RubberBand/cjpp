class Expression {

  virtual ~Expression () {}
  
  virtual Expression *clone () = 0;
  
  virtual int value () = 0;

}; 



class Times : public Expression {


Expression *m_left, *m_right;

public:
   
  Times (Expression *left, Expression *right): m_left (left), m_right (right) {}

  // Copy constructor
  Times (const Times &other) {
    m_left = other.m_left->clone ();
    m_right = other.m_right->clone ();
  }

  virtual ~Times () 
  {
    delete m_left;
    delete m_right;
  }


 Times &operator = (const Times &other) {
    if (&other != this) {
      delete m_left;
      delete m_right;
      
      m_left = other.m_left->clone ();
      m_right = other.m_right->clone ();
    }
  }


  virtual Expression *clone () { return new Times (*this); }
  
  virtual int value () { return m_left->value () * m_right->value (); }



};





class Number : public Expression {



};


class Ident : public Expression {





};


