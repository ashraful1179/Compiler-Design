#include<bits/stdc++.h>
using namespace std;

bool isKeyword(string s)
{
    return s=="int" || s== "char" || s== "float" || s== "if" || s== "else";
}

bool isNumber(string s)
{
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

bool isChar(string s)
{
    return s.size() == 3 && s[0] == '\'' && s[2] == '\'';   // single quotation use as \'
}                                                           //like 'a','b'.

int main()
{
    ifstream in("input.c");
    ofstream out("output.txt");

    if (!in)
    {
        cout << "File not found!" << endl;
        return 0;
    }

    string line;
    while (getline(in, line))
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            if ((i + 1 < line.size()) && (
                        (line[i] == '=' && line[i+1] == '=') ||
                        (line[i] == '<' && line[i+1] == '=') ||
                        (line[i] == '>' && line[i+1] == '=') ||
                        (line[i] == '!' && line[i+1] == '=')))
            {
                line.insert(i, " ");
                i += 3;
                line.insert(i, " ");
            }
            else if (line[i] == ',' || line[i] == ';' || line[i] == '+' || line[i] == '-' ||
                     line[i] == '*' || line[i] == '/' || line[i] == '=' || line[i] == '<' ||
                     line[i] == '>' || line[i] == '(' || line[i] == ')')
            {
                line.insert(i, " ");
                i += 2;
                line.insert(i, " ");
            }
        }

        stringstream ss(line);
        string tkn;
        while (ss >> tkn)
        {
            if (isKeyword(tkn)) out << "[kw " << tkn<< "] ";             //int,char etc
            else if (isChar(tkn)) out << "[char " << tkn<< "] ";          //'a' character recongnige
            else if (isNumber(tkn)) out << "[num " << tkn<< "] ";            //numner
            else if (tkn== "+" || tkn== "-" ||tkn== "*" || tkn== "/" ||        // all oparation
                     tkn== "=" || tkn== "==" || tkn== "<" || tkn== ">" ||
                     tkn== "<=" || tkn== ">=" || tkn== "!=")
                out << "[op " << tkn << "] ";
            else if (tkn == "," || tkn == ";")                 //separetor
                out << "[sep " << tkn << "] ";
            else if (tkn == "(" || tkn == ")")         //bracet
                out << "[par " << tkn << "] ";
            else if (isalpha(tkn[0]) || tkn[0] == '_')    //use for check is that a variable,like ( x_3 )start with x , so its a identifier
                out << "[id " << tkn << "] ";
            else
                out << "[unkn " << tkn << "] ";
        }
    }

    in.close();
    out.close();
    cout << "Done!" << endl;
    return 0;
}
