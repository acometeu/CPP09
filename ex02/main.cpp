#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "not enough argument" << std::endl;
        return(1);
    }
    if (parsing_vector(argv))
        return(1);
    display_arg(argv);

    clock_t time;

    time = clock();
    if (algo_vector(argv, time))
        return(1);
    time = clock() - time;
    if (algo_deque(argv, time))
        return(1);
    return(0);
}