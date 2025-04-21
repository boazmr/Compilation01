#include "tokens.hpp"
#include "output.hpp"
#include <string>

using namespace std;

void handle_string(char *s)
{
    string lexema(s);
    int len = lexema.length() - 1;
    string buff;
    for (int i = 1; i < len; i++)
    {
        if (lexema[i] == '\\')
        {
            if (i + 1 == len)
            { // '\' the last charcater in the string.
                output::errorUnclosedString();
            }

            // Check the characters after '\'
            i++;
            switch (lexema[i]) // "abc\  case doesnt exist: will be catched earlier
            {
            case '\\':
                buff += '\\';
                break;
            case '"':
                buff += '"';
                break;
            case 'n':
                buff += '\n';
                break;
            case 'r':
                buff += '\r';
                break;
            case 't':
                buff += '\t';
                break;
            case '0':
                buff += '\0';
                break;
            case 'x':
                if (i + 1 == len) // no place for hex values example: "aa\x"
                {
                    char undefined_escape[2] = {'x', '\0'};
                    output::errorUndefinedEscape(undefined_escape);
                }
                else if (i + 2 == len) // place for only 1 hex value, example: "aa\x2"
                {
                    char undefined_escape[3] = {'x', lexema[i + 1], '\0'};
                    output::errorUndefinedEscape(undefined_escape);
                }
                else
                {
                    std::string hexStr;
                    // Note:
                    // lexema[i-1] == '\'
                    // lexema[i] == x
                    // lexema[i+1] == first hex digit
                    // lexema[i+2] == second hex digit
                    hexStr += lexema[i + 1];
                    hexStr += lexema[i + 2];
                    char result;
                    try
                    {
                        result = static_cast<char>(std::stoi(hexStr, nullptr, 16));
                    }
                    catch (...)
                    {
                        // In case this function fail if the digits are not hexa digits. For example: lexema[i + 1] == 'P'
                        char undefined_escape[4] = {'x', lexema[i + 1], lexema[i + 2], '\0'};
                        output::errorUndefinedEscape(undefined_escape);
                    }
                    // Result is a hex value character which value is the value after \x..
                    if (result >= 0x20 && result <= 0x7E)
                    {
                        buff += result;
                        i += 2;
                    }
                    else
                    {
                        char undefined_escape[4] = {'x', lexema[i + 1], lexema[i + 2], '\0'};
                        output::errorUndefinedEscape(undefined_escape);
                    }
                }
                break;
            default: // there is \ and after this nothing familier
                char undefined_escape[2] = {lexema[i], '\0'};
                output::errorUndefinedEscape(undefined_escape);
                break;
            }
        }
        else
        {
            buff += lexema[i];
        }
    }
    output::printToken(yylineno, STRING, &buff[0]);
}

int main()
{
    enum tokentype token;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex())))
    {
        switch (token)
        {
        case UNKNOWN_CHAR:
            output::errorUnknownChar(*yytext);
            break;
        case UNCLOSED_STRING:
            output::errorUnclosedString();
            break;
        case STRING:
            handle_string(yytext);
            break;
        case COMMENT:
            output::printToken(yylineno - 1, token, yytext);
            break;
        default:
            output::printToken(yylineno, token, yytext);
            break;
        }
    }
    return 0;
}
