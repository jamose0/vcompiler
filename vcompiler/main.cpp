#include "parser.h"
#include "scanner.h"
#include "token.h"

#include <iostream>

int main()
{
    Scanner s{" #program\n 3 ==f 2 =8 -9 * 6 <=d >= != ! < >7"};
    Token t{s.nextToken()};
    while (t.getType() != TokenType::END) {
        std::cout << t << '\n';
        t = s.nextToken();
    }
    return 0;
}
