#include "tokens.hpp"
#include "output.hpp"

#include <cstring>
#include <iostream>

int main()
{
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex())))
    {
        if(token == tokentype::STRING){
            int hexVal;
            int size = strlen(yytext);
            std::string buff;
            std::string hexBuffer;

            for(int i = 0; i < size; i++){
                if(yytext[i] == '\\'){
                    if(i == size - 1){
                        // What should we do if it ends in \ ?
                    }
                    i++;
                    switch(yytext[i]){
                        case 'n':
                                buff += '\n';
                                break;
                        case 'r':
                                buff += '\r';
                                break;
                        case 't':
                                buff += '\t';
                                break;
                        case '\\':
                                buff += '\\';
                                break;
                        case '\"':
                                buff += '"';
                                break;
                        case 'x':
                                if(i + 2 >= size){
                                    // Return error value
                                }
                                hexBuffer += yytext[i+1];
                                hexBuffer += yytext[i+2];
                                hexVal = std::stoi(hexBuffer, nullptr, 16);
                                if(){
                                    
                                }
                                buff += static_cast<char>(hexVal);
                                i += 2;
                                break;
                        default:
                                errorUndefinedEscape(yytext[i]);
                    }
                    
                }
                else{
                    buff += yytext[i];
                }
            }

            output::printToken(yylineno, token, buff.c_str());
        }
        else{
            output::printToken(yylineno, token, yytext);
        }
    }
    return 0;
}
