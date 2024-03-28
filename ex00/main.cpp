#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error : Arguments invalids, filename to be analysed only needed" << std::endl;
        return(1);
    }

    std::map<std::string, float>    btc;

    if (init_btc(btc, "data.csv"))
        return(1);
    if (evaluate_btc_value(btc, argv))
        return(1);
    return(0);
}