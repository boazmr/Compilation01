#include "tokens.hpp"
#include "output.hpp"

#include <cstring>
#include <iostream>

// The function checks if the ASCII entry in val is valid to represent a hexadecimal number.
// That is, if val is in [0-9a-zA-Z]. 
bool isHex(int val){
    return (97 <= val && val < 102) || (65 <= val && val < 70) || (48 <= val && val < 57);
}

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
            bool validHex = true;

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
                                if(i + 1 == size){ // Can not read characters after the string ends
                                    char non_valid_hex[2] = {'x'};
                                    output::errorUndefinedEscape(non_valid_hex);
                                    return 0;
                                }
                                else if(i + 2 == size){ // Can read only one character after the string ends
                                    char non_valid_hex[2] = {'x', yytext[i+1]};
                                    output::errorUndefinedEscape(non_valid_hex);
                                    return 0;
                                }

                                // Check for validity of the hexa values.
                                if(!isHex(yytext[i+1]) || !isHex(yytext[i+2])){
                                    validHex = false;
                                }
                                else{
                                    // Values are valid hexa values.
                                    hexBuffer += yytext[i+1];
                                    hexBuffer += yytext[i+2];
                                    hexVal = std::stoi(hexBuffer, nullptr, 16);
                                }
                                // Check if the hexa value of both numbers together is a "printable character".
                                if(!validHex || (hexVal < 0x20 && hexVal > 0x7E)){
                                    char non_valid_hex[3] = {'x', yytext[i+1], yytext[i+2]};
                                    output::errorUndefinedEscape(non_valid_hex);
                                    return 0;
                                }
                                buff += static_cast<char>(hexVal);
                                i += 2;
                                break;
                        default:
                                output::errorUndefinedEscape(&yytext[i]);
                                return 0;
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
