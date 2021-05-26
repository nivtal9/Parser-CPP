//
// Created by nivtal9 on 24/05/2021.
//

#include "symbol.h"
#include "strings.h"

Type Symbol::getType() {
    return type;
}

int Symbol::getSymbol() {
    return symbol;
}

void Symbol::printSymbol() {
    switch(this->type){
        case Type::TERM: {
            cout << terminalStrings[symbol] << ' ';
            break;
        }
        case Type::NONTERM:{
            cout << tokenStrings[symbol] << ' ';
        }

    }
}

