#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "RPN must take only one argument as parameter" << std::endl;
        return(1);
    }
    
    std::stack<int> stack;
    std::string     param = argv[1];

    if (parsing_incorrect(param))
        return(1);
    if (inverted_polish_calcul(param))
        return(1);
    return(0);    
}