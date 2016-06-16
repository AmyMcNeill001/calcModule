#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Calculator
{
    string type;
    int number;
    char symbol;
};//END Calculator struct definition

void readNumber(vector<Calculator> &tokens, int &index, string line)
{
    double number = 0.0;

    while ( index < line.length() && isdigit(line[index]) )
    {
        int temp = line[index] - 48;
        number = number * 10 + temp;
        index++;
    }//END while loop

    if ( index < line.length() && line[index] == '.')
    {
        index ++;
        double keta = 0.1;

        while ( index < line.length() && isdigit(line[index]))
           {
               int temp = line[index] - 48;
               number = number + temp * keta;
               keta = keta * 0.1;
               index++;
           }//END decimal while loop
    }//END if statement for decimal point
       

        Calculator newCalc;
       newCalc.type = "NUMBER";
       newCalc.number = number;
       
       tokens.push_back(newCalc);
}//END function readNumber
void readPlus (vector<Calculator> &tokens, int &index, string line)
{
    Calculator newCalc;
    newCalc.type = "PLUS";
    newCalc.symbol = '+';
    tokens.push_back(newCalc);

    index++;
}//END function readPlus
   
void readMinus (vector<Calculator> &tokens, int &index, string line)
{
    Calculator newCalc;
    newCalc.type = "MINUS";
    newCalc.symbol = '-';
    tokens.push_back(newCalc);

    index++;
}//END function readMinus
   
void readTimes (vector<Calculator> &tokens, int &index, string line)
{
    Calculator newCalc;
    newCalc.type = "TIMES";
    newCalc.symbol = '*';
    tokens.push_back(newCalc);

    index++;
}//END function readTimes
   
   
void readDivide (vector<Calculator> &tokens, int &index, string line)
{
    Calculator newCalc;
    newCalc.type = "DIVIDE";
    newCalc.symbol = '/';
    tokens.push_back(newCalc);

    index++;
}//END function readDivide
   
void readSpace (vector<Calculator> &tokens, int &index, string line)
{
    Calculator newCalc;
    newCalc.type = "SPACE";
    newCalc.symbol = '_';
    tokens.push_back(newCalc);

    index++;
}//END function readSpace
   
   
vector<Calculator> tokenize(string line)
{
    vector<Calculator> tokens;
    int index = 0;

    while (index < line.length())
    {
        if (isdigit(line[index]))
            readNumber(tokens, index, line);
        else if (line[index] == '+')
            readPlus(tokens, index, line);
        else if (line[index] == '-')
            readMinus(tokens, index, line);
        else if (line[index] == '*')
            readTimes(tokens, index, line);
        else if (line[index] == '/')
            readDivide(tokens, index, line);
        else
        {
            cout << "Invalid character found: " << line[index] << endl;
            index ++;
        }//END invalid else statement
    }//END while loop
    
    return tokens;
}//END function tokenize

void  orderOfOperations(vector<Calculator> &tokens, double &answer)
{
    int index = 0;
    while (index < tokens.size())
    {
        if ( tokens[index].symbol == '*')
        {
            answer = answer + (tokens[index - 1].number * tokens[index + 1].number);
            tokens[index -1].type = "SPACE";
            tokens[index].type = "SPACE";
            tokens[index +1].type = "SPACE";
        }//END multiplication elif
        
        else if( tokens[index].symbol == '/')
        {
            
            answer = answer + (tokens[index - 1].number / tokens[index + 1].number);
            tokens[index -1].type = tokens[index].type = tokens[index +1].type = "SPACE";
            
        }//END division elif
        index++;
    }//END while loop to iterate through vector and perform * and / first
}//END function order of operations

   
double evaluate(vector<Calculator> &tokens)
{
    double answer = 0;
    orderOfOperations(tokens, answer);
    
    if( tokens[0].type != "SPACE")
    {
        answer = answer + tokens[0].number;
    }
    
    int index = 2;

    while (index < tokens.size())
    {
        if( tokens[index].type == "NUMBER")
        {
            if( tokens[index - 1].type == "PLUS")
                answer = answer + tokens[index].number;
            else if( tokens[index - 1].type == "MINUS")
                answer = answer - tokens[index].number;
            else if( tokens[index - 1].type == "SPACE")
                cout << " ";
            else
                cout << "Invalid syntax" << endl;
        }//END if statement for numbers
        
        index++;
    }//END while loop

    return answer;    
}//END function evaluate

int main()
{
    string line;
    cout << "< ";
    getline(cin, line);

    vector<Calculator> tokens = tokenize(line);
    double answer = evaluate(tokens);

    cout << "answer = "<< answer << endl;
}//END function main


