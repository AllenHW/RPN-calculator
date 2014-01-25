#ifndef RPN_H_INCLUDED
#define RPN_H_INCLUDED


class STACK       //class
{
      private:
        struct NODE
        {
               float num;     
               NODE *next;
               NODE *prev;
        };
        NODE  *head, *node;    //declaring pointers to the node
        int top;        //a value that keeps the size of the list
      public:
        STACK();    //constructor
        ~STACK();   //destructor
        
        int ListSize();   //accessor to int top
        float FirstNum();  //accessor to the first number of the list, the one on the top.
        
        void push(float new_num);    //methods
        float pop();                
        
        
};

class RPN: public STACK    //inherited class
{
      
    public:          //all the functions. They do what they are called
      int add();       
      int subtract();
      int multiply();
      int divide();
      
      int sine();
      int cosine();
      int tangent();
      int arcsine();
      int arccosine();
      int arctangent();
      
      int power();
      int sq_root();
      int logarithm();
      
      void exchange();
      void clear();
};


#include "RPN.cpp"
#endif
