class Expression {

  virtual ~Expression () {}
  
  virtual Expression *clone () = 0;
  
  virtual int value () = 0;

}; 


// code for Plus class goes here




//code for Subt class goes here









class Times : public Expression {










};





class Number : public Expression {



};


class Ident : public Expression {





};


