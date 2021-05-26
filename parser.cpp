//
// Created by nivtal9 on 24/05/2021.
//

#include "parser.h"
auto IsItTerm = [](Type t){
    return t==TERM;
};
terminal Parser::nextToken() {
    string tok;
    inputFile>>tok;
    if(tok.compare("id")==0)
        return terminal::ID;

    else if(tok.compare("+")==0)
        return terminal::PLUS;

    else if(tok.compare("*")==0)
        return terminal::ASTERISK;

    else if(tok.compare(")")==0)
        return terminal::RPAREN;

    else if(tok.compare("(")==0)
        return terminal::LPAREN;

    return END;
}

void Parser::printLM() {
    for(auto & i : accepted)
        i.printSymbol();
    cout<<"| ";
    for(auto i = stack.rbegin(); i != stack.rend() - 1; ++i)
        i->printSymbol();
    cout << endl;
}

void Parser::parse() {
    stack.emplace_back(END,TERM);
    terminal Ter = nextToken();
    stack.emplace_back(E,NONTERM);
    Symbol Sym=stack[stack.size() - 1];
    while(Sym.getSymbol() != END){
        printLM();
        if(Sym.getSymbol() == Ter && IsItTerm(Sym.getType())){
            accepted.push_back(Sym);
            stack.pop_back();
            Ter=nextToken();
        }
        else if(IsItTerm(Sym.getType()) || table[Sym.getSymbol()][Ter] == -1){
            cout << "syntax error" << endl;
            return;
        }
        else{
            stack.pop_back();
            for(auto &i : rules.at(table.at(Sym.getSymbol()).at(Ter))){
                stack.push_back(i);
                if(i.getSymbol()==EPSILON&&IsItTerm(i.getType())){
                    stack.pop_back();
                }
            }
        }
        Sym=stack[stack.size() - 1];
    }
    printLM();
}

