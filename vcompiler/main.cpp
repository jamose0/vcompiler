#include "parser.h"
#include "scanner.h"
#include "token.h"

#include <iostream>

int main()
{
    Scanner s{" var #program\n 3 >=4; 2<5; {7==2}; []!=3 [ (!3);]"};
    Token t{s.nextToken()};
    while (t.getType() != TokenType::END) {
        std::cout << t << '\n';
        t = s.nextToken();
    }
    Parser p{" var x = 7;"};
    p.parse();
    return 0;
}
