STACK::STACK() 
{
              head = new NODE; //creating an empty node that doesn't store a number
              node = head;     //it doesn't store number, so we never have to pop it out, allowing us to always have a valid head of the list
              node->prev = NULL; 
              top = 0;  //initializing the value that counts the number of filled node
}

STACK::~STACK()   
{
               while (node != head) //until node returns to the empty head
                     pop();    //keeps poping things out = deleting thigs
               delete head;     //delete the empty head as well
               head = NULL;    //kill the pointers
               node = NULL;      
}

int STACK::ListSize()   
{
    return (top);    //transfering a private value through a public accesor;
}                                      

void STACK::push(float new_num)
{
     node->next = new NODE;   //make a new node
     node->next->prev = node;  //double linking
     node = node->next;   //move the node forward
     node->num = new_num;   //push the number in
     top++;     //list size increases by 1
}

float STACK::pop()
{
    float num;
      
    if (node == head)   //if node is at the empty head = no valid node
       return 0;
    else       //otherwise
    {
       num = node->num;      //temporarily storing the number
       node = node->prev;   //move the node back
       delete node->next;  //delete the unwanted node
       node->next = NULL;  //ending the link
       top--;           //list size decreses
       return (num);   //return the poped number
    }  
}

float STACK::FirstNum()
{
      return(node->num);   //just getting the number on the top of the list
}

int RPN::add()
{
      if (ListSize() >= 2)   //only if there are two numbers
      {      
         push(pop()+pop());   //pop two numbers out and push the result back
         return 1;          //value 1 means no error message
      }
      else
          return 3;      //value 3 will give the message "syntax error"
}

int RPN::subtract()
{
      if (ListSize() >= 2)      //same as add()
      {      
         push((pop()-pop())*-1);  //'3' '5' '-' means "3-5" so i have to make the number on the top, '5', to be subtracted form '3'
         return 1;
      }
      else
          return 3;
}

int RPN::multiply()
{
     if (ListSize() >= 2)   //same thing as previous operations 
      {      
         push(pop()*pop());
         return 1;
      }
      else
          return 3;
}

int RPN::divide()
{
      if (ListSize() >= 2)  
      {
         if (FirstNum() != 0)    //checking if the divisor isn't 0
         {
            push(1/pop()*pop()); 
            return 1;
         }
         else   //if divisor = 0
             return 2;   // value 2 will cause the message to be "math error"
      }
      else
          return 3;
}

int RPN::sine()
{
     if (ListSize() >= 1)   //there has to be at least one number
     {
        if (fmod(FirstNum(), 180) == 0)  //if degree = -180, 0, 180, 360...
        {
           pop(); push(0);     //hard coding to return 0
           return 1;           //otherwise it won't give out 0 because my PI value isn't exact. It's weird but true 
        }              
        else          //in other cases, calculate normally
        {
             push(sin(pop()*PI/180));    // conversion from degree to radian, and then do calculation and push the result back
             return 1;
        }
     }
     else
         return 3;
}

int RPN::cosine()
{
     if (ListSize() >= 1)   
     { 
        if (fmod(FirstNum(), 180) == 90)   // if degree = -90, 90, 270...
        { 
           pop(); push(0);      //hard coding to return 0, for the same reson as sin
           return 1;
        }              
        else 
        {
             push(cos(pop()*PI/180));
             return 1;
        }
     }
     else
         return 3;
     
}
int RPN::tangent()
{
     if (ListSize() >= 1)
     {
        if (fmod(FirstNum(), 180) != 90)   // tan is undefined at 90, 270, etc due to cos being 0. so only run if it isn't          
        {
           push(tan(pop()*PI/180));  
           return 1;
        }
        else 
             return 2;     //if tan is undefined, return "math error"
     }
     else
         return 3;
}

int RPN::arcsine()
{
     if (ListSize() >= 1)    
     {
        if (FirstNum() <= 1 && FirstNum() >= -1)        //arcsin is only defined when input is between -1 and 1
        {
           push(asin(pop())*180/PI); 
           return 1;
        }
        else
            return 2;   
     }
     else
         return 3;
}

int RPN::arccosine()
{
     if (ListSize() >= 1)
     {
        if (FirstNum() <= 1 && FirstNum() >= -1)   //arccos is only defined when input is between -1 and 1
        {
           push(acos(pop())*180/PI);
           return 1;
        }
        else
            return 2;   
     }
     else
         return 3;
}

int RPN::arctangent()
{
     if (ListSize() >= 1)
     {
        push(atan(pop())*180/PI);
        return 1;
     }
     else
         return 2;
}
      
int RPN::power()
{
     if (ListSize() >= 2)    //needs two numbers, or "syntax error"
     {
        float exponent = pop(), base = pop();             //storing the popped numbers      
        if (!(base < 0 && (int)exponent != exponent))   // check if base is negative AND the exponent is not a whole number 
        {                                                //EX: (-2)^1.5 = undefined
           push(pow(base, exponent));                   //if that's not the case, do the calcalation and push back
           return 1;
        }
        else
        {
            push(base); push(exponent);          //if it IS the case, push back exactly what were popped out
            return 2;                             // "math error"
        }  
     }
     else
         return 3;         
}

int RPN::sq_root()
{
     if (ListSize() >= 1)   //needs one number
     {
        if (FirstNum() >= 0)       //only square root positive numbers
        { 
           push(sqrt(pop())) ;
           return 1;
        }
        else
            return 2;   
     }
     else
         return 3; 
}

int RPN::logarithm()
{
     if (ListSize() >= 1)
     {
        if (FirstNum() >= 0)   //only log positive numbers
        { 
           push(log10(pop())) ;
           return 1;
        }
        else
            return 2;  
     }
     else
         return 3;
}

void RPN::exchange()
{
     if (ListSize() >= 2)   //needs two numbers
     {
        float num1 = pop(), num2 = pop();   //popping and pushing them in the opposite order
        push(num1); push(num2);            
     }
     else                 //if not enough number, don't do anything
          return;
}
      
void RPN::clear()
{
     while (ListSize() > 0)    //until the there is nothing left
           pop();              //keep popping things out
}

