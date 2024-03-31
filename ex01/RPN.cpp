#include "RPN.hpp"

int isoperand(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*')
        return(1);
    return(0);
}

int parsing_incorrect(std::string param)
{
    int i = 0;
    int number = 0;
    int operand = 0;

    while (param[i])
    {
        if (isdigit(param[i]))
            number++;
        else if (isoperand(param[i]) && (number - operand) < 2)
        {
            std::cout << "operand must be placed after the numbers of the operation" << std::endl;
            return(1);
        }
        else if (isoperand(param[i]))
            operand++;
        else if (!isspace(param[i]))
        {
            std::cout << "character '" << param[i] << "' is not accepted in RPM" << std::endl;
            return(1);
        }
        i++;
    }
    if (number < 2)
    {
        std::cout << "Not enough numbers" << std::endl;
        return(1);
    }
    if (number > operand + 1)
    {
        std::cout << "Too many numbers" << std::endl;
        return(1);
    }
    return(0);
}

int inverted_polish_calcul(std::string param)
{
    std::stack<int> number;
    int             i = 0;
    long int        result = 0;
    long int        temp = 0;

    while (param[i])
    {
        if (isdigit(param[i]))
            number.push(param[i] - 48);
        else if (isoperand(param[i]))
        {
            temp = number.top();
            number.pop();
            if (param[i] == '+')
                result = number.top() + temp;
            else if (param[i] == '-')
                result = number.top() - temp;
            else if (param[i] == '*')
                result = number.top() * temp;
            else if (param[i] == '/' && temp == 0)
            {
                std::cout << "Cannot divide by 0" << std::endl;
                return(1);
            }
            else if (param[i] == '/')
                result = number.top() / temp;
            number.pop();
            number.push(result);
            if (verif_limit(result))
                return(1);
        }
        i++;
    }
    std::cout << result << std::endl;
    return(0);
}

int verif_limit(long int result)
{
    if (result > 2147483647)
    {
        std::cout << "Error : result exceed MAX_INT during calculation" << std::endl;
        return(1); 
    }
    if (result < -2147483648)
    {
        std::cout << "Error : result passed below MIN_INT during calculation" << std::endl;
        return(1); 
    }
    return(0);
}