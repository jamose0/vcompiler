#include "parser.h"
#include "scanner.h"
#include "token.h"

#include <iostream>

int main()
{
    Scanner s{"   #djfelsj\n +{ x = 7 + 3;"};
    Token t{s.nextToken()};
    std::cout << t << '\n';
    return 0;
}
