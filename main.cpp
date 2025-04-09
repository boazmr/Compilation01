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
            switch (lexema[i + 1]) // "abc\  case doesnt exist: will be catched earlier
            {
            case '\\':
                buff += '\\';
                i++;
                break;
            case '"':
                buff += '"';
                i++;
                break;
            case 'n':
                buff += '\n';
                i++;
                break;
            case 'r':
                buff += '\r';
                i++;
                break;
            case 't':
                buff += '\t';
                i++;
                break;
            case '0':
                buff += '\0';
                i++;
                break;
            case 'x':
                if (i + 2 == len) // no place for hex values example: "aa\x"
                {
                    lexema[i + 2] = '\0';
                    output::errorUndefinedEscape(&lexema[i + 1]);
                }
                else if (i + 3 == len) // place for only 1 hex value, example: "aa\x2"
                {
                    lexema[i + 3] = '\0';
                    output::errorUndefinedEscape(&lexema[i + 1]);
                }
                else
                {
                    std::string hexStr;
                    hexStr += lexema[i + 2];
                    hexStr += s[i + 3];
                    char result = static_cast<char>(std::stoi(hexStr, nullptr, 16));
                    if (result >= 0x20 && result <= 0x7E)
                    {
                        buff += result;
                        i += 3;
                    }
                    else
                    {
                        lexema[i + 4] = '\0';
                        output::errorUndefinedEscape(&lexema[i + 1]);
                    }
                }
                break;
            default: // there is \ and after this nothing familier
                lexema[i + 2] = '\0';
                output::errorUndefinedEscape(&lexema[i + 1]);
                break;
            }
        }
        else
        {
            buff += lexema[i];
        }
    }
    buff += '\0';
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
