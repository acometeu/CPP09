#ifndef	RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <cctype>

/*  parsing */
int     parsing_incorrect(std::string param);

/*  algorythm   */
int     inverted_polish_calcul(std::string param);

/*  utils   */
int     isoperand(char c);

/*  errors  */
int     verif_limit(long int result);

#endif