#include "PmergeMe.hpp"

int parsing_vector(std::vector<int> &number, char **argv)
{
    int i = 1;
    int temp;

    while (argv[i])
    {
        try
        {
            temp = std::stoi(argv[i]);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error : \"" << argv[i] << "\" isn't a valid value" << std::endl;
            return(1);
        }
        if (temp < 0)
        {
            std::cerr << "Error : only positive mumber are accepted" << std::endl;
            return(1);
        }
        try
        {
            number.push_back(temp);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return(1);
        }
        i++;
    }
    return(0);
}

int algo_vector(std::vector<int> &container)
{
    std::vector<int>    pair;

    sort_inside_pair_descendant_vector(container);
    split_pair(container, pair);
    if (container.size() != pair.size())
    {
        int temp = container[container.size() -1];
        container.pop_back();
        merge_sort_vector_split(container, pair);
        pair.push_back(temp);
    }
    else
        merge_sort_vector_split(container, pair);
    try
    {
        binary_search_jacobsthal_vector(container, pair);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return(0);
}

void    sort_inside_pair_descendant_vector(std::vector<int> &container)
{
    size_t  i = 0;
    int     temp;

    while (i < container.size() - 1)
    {
        if (container[i] < container[i + 1])
        {
            temp = container[i];
            container[i] = container[i + 1];
            container[i + 1] = temp;
        }
        i += 2;
    }
    return;
}

void    split_pair(std::vector<int> &container, std::vector<int> &pair)
{
    size_t  i = 1;
    
    while (i < container.size())
    {
        pair.push_back(container[i]);
        container.erase(container.begin() + i);
        i++;
    }
}

void    merge_sort_vector_split(std::vector<int> &container, std::vector<int> &pair)
{
    if (container.size() <= 1)
        return;

    size_t              length = container.size() / 2;
    std::vector<int>    copy1;
    std::vector<int>    copy2;
    std::vector<int>    copy_pair1;
    std::vector<int>    copy_pair2;
    size_t              i = 0;

    while (i < length)
    {
        copy1.push_back(container[i]);
        copy_pair1.push_back(pair[i]);
        i++;
    }
    while (i < container.size())
    {
        copy2.push_back(container[i]);
        copy_pair2.push_back(pair[i]);
        i++;
    }
    merge_sort_vector_split(copy1, copy_pair1);
    merge_sort_vector_split(copy2, copy_pair2);
    merge_sort_vector(container, copy1, copy2, length, pair, copy_pair1, copy_pair2);
    return;
}

void    merge_sort_vector(std::vector<int> &container, std::vector<int> &copy1, std::vector<int> &copy2, size_t length, std::vector<int> &pair, std::vector<int> &copy_pair1, std::vector<int> &copy_pair2)
{
    size_t  i = 0;
    size_t  j = 0;
    size_t  k = 0;


    while(j < length && k < container.size() - length)
    {
        if (copy1[j] <= copy2[k])
        {
            container[i] = copy1[j];
            pair[i] = copy_pair1[j];
            j++;
        }
        else
        {
            container[i] = copy2[k];
            pair[i] = copy_pair2[k];
            k++;
        }
        i++;
    }
    while(j < length)
    {
        container[i] = copy1[j];
        pair[i] = copy_pair1[j];
        j++;
        i++;
    }
    while(k < container.size() - length)
    {
        container[i] = copy2[k];
        pair[i] = copy_pair2[k];
        k++;
        i++;
    }
    return;
}

void    binary_search_jacobsthal_vector(std::vector<int> &container, std::vector<int> &pair)
{
    size_t  temp1 = 1;
    size_t  temp2 = 1;
    size_t  jacobsthal;
    size_t  i = 1;

    container.insert(container.begin(), pair[0]);
    jacobsthal = temp1 * 2 + temp2;
    while (jacobsthal <= pair.size())
    {
        i = jacobsthal - 1;
        while (i != temp2 - 1)
        {
            binary_search_place_vector(container, 0, jacobsthal + temp2 - 1, pair[i]);
            i--;
        }
        temp1 = temp2;
        temp2 = jacobsthal;
        jacobsthal = temp1 * 2 + temp2;
    }
    i = pair.size() - 1;
    while (i != temp2 - 1)
    {
        binary_search_place_vector(container, 0, container.size() - 1, pair[i]);
        i--;
    }
}

void    binary_search_place_vector(std::vector<int> &container, int min, int max, int value)
{
    if (min == max)
    {
        if (value <= container[min])
            container.insert(container.begin() + min, value);
        else
            container.insert(container.begin() + min + 1, value);
        return;
    }
    int middle = (min + max) / 2;
    if (value <= container[middle])
        binary_search_place_vector(container, min, middle, value);
    else
        binary_search_place_vector(container, middle + 1, max, value);
}