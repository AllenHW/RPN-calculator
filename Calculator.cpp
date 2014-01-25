#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<dirent.h>
#include<windows.h>
#include<iomanip>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651



#include "RPN.h"

RPN calc;       // creating a class variable
using namespace std;

bool is_number (string input);    // a function that checks if a input is a number
bool is_operation (string input);   // checks if input is a command
void do_operation (string input, string &message);   // run operation
void gotoxy(int x, int y);    // moves cursor to a selected point
void print_screen();      // print icons
void refresh_screen();     // refresh the screen
void print_numbers();      // print the stack

int main() {

    system("mode 80, 29");     // setting window size

    bool run = true;
    string input;
    string message = "Enter a number or command to do calculation, or \"quit\" to close.";  // instruction

    print_screen();

    while (run == true)
    {
          refresh_screen();    // refresh the screen everytime

          gotoxy(1,4);
          cout << message;

          print_numbers();

          gotoxy(0,24);
          cout << "      List size = " << calc.ListSize() << endl;

          gotoxy(1,26);
          cin >> input;      // getting the input

          if (is_operation(input) == true)     // checking the input
          {
               do_operation(input, message);
          }
          else if (is_number(input) == true)
          {
             calc.push(atof(input.c_str()));   // if input is number, change the string to float
             message = " ";     // message goes off
          }
          else if (input == "quit")
               run = false;          //end the loop = end the program
          else
               message = "Syntax Error";     //show message that input is invalid
    }

}

bool is_number (string input)
{
     for (int i=0; i<input.length(); i++)     //going through every letter of the input
     {
         // if not number, period or signs
         if (!(isdigit(input[i]) || input[i] == '.' || input[i] == '-' || input[i] == '+'))
            return false;     // input is not a number

         // if signs are not at the beginning (EX: "5-4" is invalid)
         if ((input[i] == '-' || input[i] == '+') && i != 0)
            return false;

         if (input.length() > 38)  // if number is longer than float can hold
            return false;
     }
     return true;   // input is a number if it passes all the tests
}

bool is_operation (string input)
{
     if (input == "+" || input == "-" || input == "*" || input == "/" ||
         input == "sin" || input == "cos" || input == "tan" ||
         input == "asin" || input == "acos" || input == "atan" ||
         input == "pow" || input == "sqrt" || input == "log" ||
         input == "xchange" || input == "del" || input == "clear")
     {
         return true;    //if one these commands, input is a command
     }
     else
     {
          return false;   // otherwise not
     }
}

void do_operation (string input, string &message)
{
     int message_num = 0;   // a integer that determines the message

     //calling the appropriate function for each command input
     if (input == "+")
        message_num = calc.add();
     if (input == "-")
        message_num = calc.subtract();
     if (input == "*")
        message_num = calc.multiply();
     if (input == "/")
        message_num = calc.divide();
     if (input == "sin")
        message_num = calc.sine();
     if (input == "cos")
        message_num = calc.cosine();
     if (input == "tan")
        message_num = calc.tangent();
     if (input == "asin")
        message_num = calc.arcsine();
     if (input == "acos")
        message_num = calc.arccosine();
     if (input == "atan")
        message_num = calc.arctangent();
     if (input == "pow")
        message_num = calc.power();
     if (input == "sqrt")
        message_num = calc.sq_root();
     if (input == "log")
        message_num = calc.logarithm();
     if (input == "xchange")
     {
        calc.exchange();
        message_num = 1;
     }
     if (input == "del")
     {
        calc.pop();
        message_num = 1;
     }
     if (input == "clear")
     {
        calc.clear();
        message_num = 1;
     }

     //all functions return a integer that determines the message.
     if (message_num == 1)   //if command is valid
        message = " ";
     if (message_num == 2)   //if command causes a math problem, such as dividing by 0
        message = "Math Error";
     if (message_num == 3)    //if command cannot operated. EX: not enough numbers in the stack
        message = "Syntax Error";
}

void gotoxy(int x, int y)
{
     COORD coord = {x, y};
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  //moves the cursor to the selected position
}

void print_screen()
{
     gotoxy(25,1);
     cout << right << "RPN Calculator by Allen Wang";

     //priting 16 small boxes using ascii characters and for loop.
     for (int x=26; x<75; x+=13)
     {
         for (int y=7; y<22; y+=4)
         {
             gotoxy(x,y); cout << char(218) << setfill(char(196)) << setw(12) << char(191) << endl;
             gotoxy(x,y+1); cout << char(179) << setfill(' ') << setw(12) << char(179)  << endl;
             gotoxy(x,y+2); cout << char(179) << setfill(' ') << setw(12) << char(179)  << endl;
             gotoxy(x,y+3); cout << char(192) << setfill(char(196)) << setw(12) << char(217) << endl;
         }
     }
     //priting letters inside the boxes
     gotoxy(31,8); cout << "\"+\""; gotoxy(31,9); cout << "a+b";
     gotoxy(44,8); cout << "\"-\""; gotoxy(44,9); cout << "a-b";
     gotoxy(57,8); cout << "\"*\""; gotoxy(57,9); cout << "axb";
     gotoxy(70,8); cout << "\"/\""; gotoxy(70,9); cout << "a/b";

     gotoxy(30,12); cout << "\"sin\""; gotoxy(30,13); cout << "sin(a)";
     gotoxy(30,16); cout << "\"cos\""; gotoxy(30,17); cout << "cos(a)";
     gotoxy(30,20); cout << "\"tan\""; gotoxy(30,21); cout << "tan(a)";

     gotoxy(42,12); cout << "\"asin\""; gotoxy(41,13); cout << "arcsin(a)";
     gotoxy(42,16); cout << "\"acos\""; gotoxy(41,17); cout << "arccos(a)";
     gotoxy(42,20); cout << "\"atan\""; gotoxy(41,21); cout << "arctan(a)";

     gotoxy(56,12); cout << "\"pow\""; gotoxy(57,13); cout << "a^b";
     gotoxy(56,16); cout << "\"sqrt\""; gotoxy(56,17); cout << "a^0.5";
     gotoxy(56,20); cout << "\"log\""; gotoxy(56,21); cout << "log(a)";

     gotoxy(67,12); cout << "\"xchange\""; gotoxy(66,13); cout << "swtich a&b";
     gotoxy(69,16); cout << "\"del\""; gotoxy(66,17); cout << "delete one";
     gotoxy(68,20); cout << "\"clear\""; gotoxy(66,21); cout << "delete all";
}

void refresh_screen()  //printing parts that need to be refreshed
{
     //printing the message box
     gotoxy(0,3);
     cout << char(218) << setfill(char(196)) << setw(78) << char(191) << endl;
     cout << char(179) << setfill(' ') << setw(78) << char(179)  << endl;
     cout << char(192) << setfill(char(196)) << setw(78) << char(217) << endl;

     //printing the box where the stack list is displayed
     gotoxy(0,6);
     cout << char(218) << setfill(char(196)) << setw(24) << char(191)<< endl;
     for(int i=0; i<16; i++)
             cout << char(179) << setfill(' ') << setw(24) << char(179) << endl;
     cout << char(192) << setfill(char(196)) << setw(24) << char(217)<< endl;
     cout << "                                     " << endl;

     //printing the typing box
     gotoxy(0,25);
     cout << char(218) << setfill(char(196)) << setw(78) << char(191) << endl;
     cout << char(179) << setfill(' ') << setw(78) << char(179)  << endl;
     cout << char(192) << setfill(char(196)) << setw(78) << char(217) << endl;
}

void print_numbers()
{
     int size = calc.ListSize();  //store the list size to a int, because list will change as we run the loop
     float list[size];   //an array that can store all numbers in the list
     int i;

     if (size<=16)
     {
        for (i=0; i<size; i++)  //getting all numbers from the stack
            list[i] = calc.pop();  //storing them to the array
        for (i=size-1; i>=0; i--)  //printing them all
        {
            gotoxy(1,22-i);
            cout << setfill(' ') << setw(23) << list[i]  << endl; //printing
            calc.push(list[i]);   //pushing them back
        }
     }
     if (size>16)  //if list size exceeds the maximum number that can be displayed
     {
        for (i=size-16; i<size; i++)  //only get 16 numbers on the top of the list
            list[i] = calc.pop();
        for (i=size-1; i>=size-16; i--)    //print them
        {
            gotoxy(1,7+((size-1)-i));   //a complex equation that determines where to print the number
            cout << setfill(' ') << setw(23) << list[i] << endl;
            calc.push(list[i]);   //pushing the number back in
         }
     }

}
