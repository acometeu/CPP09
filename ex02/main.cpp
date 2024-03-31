#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "not enough argument" << std::endl;
        return(1);
    }

    std::vector<int>    container;

    if (parsing_vector(container, argv))
        return(1);
    if (algo_vector(container))
        return(1);

    //test
    // binary_search_place_vector(container, 0, container.size() - 1, 0);
    size_t i = 0;
    std::cout << "value in vector " << i << " = " << container[i] << std::endl;
    i = 1;
    while (i < container.size())
    {
        std::cout << "value in vector " << i << " = " << container[i] << std::endl;
        if (container[i] < container[i - 1])
        {
            std::cout << "FAUUUUUUUUUUUUUUUUUUUUUUUUX" << std::endl;
            return(1);
        }
        i++;
    }


    return(0);
}