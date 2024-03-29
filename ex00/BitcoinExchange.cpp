#include "BitcoinExchange.hpp"

int verif_open_file(std::ifstream &src_file, const std::string filename)
{
    src_file.open(filename);
    if (!src_file.good())
    {
        std::cerr << "Error : while opening \"" << filename << "\" file" << std::endl;
        src_file.close();
        return(1);
    }
    return(0);
}

static int skip_title_line(std::ifstream &src_file, std::string &buffer, std::string filename)
{
    getline(src_file, buffer);
    if (buffer != "date,exchange_rate")
    {
        std::cout << "title line of \"" << filename << "\" is not conform" << std::endl;
        return(1);
    }
    return(0);
}

int init_btc(std::map<std::string, float> &btc, std::string data)
{
    std::ifstream   src_file;
    std::string     buffer;
    size_t          sep;
    std::string     date;
    float           value;

    if (verif_open_file(src_file, data))
    {
        src_file.close();
        return(1);
    }

    if (skip_title_line(src_file, buffer, data))
        return(1);
    while (src_file.good() && getline(src_file, buffer))
    {
        sep = buffer.find(",");
        if (sep == std::string::npos)
        {
            std::cerr << "Error : data file does not suit \"date | value\" format" << std::endl;
            src_file.close();
            return(1);
        }
        try
        {
            date = buffer.substr(0, sep);
            if (!is_date_valid(date))
            {
                std::cout << "date in line \"" << buffer << "\" isn't vaild" << std::endl;
                src_file.close();
                return(1);
            }
            value = std::stof(buffer.substr(sep + 1, buffer.size() - 1));
            if (value < 0)
            {
                std::cout << "value in line \"" << buffer << "\" must be positive" << std::endl;
                src_file.close();
                return(1);
            }
            btc.insert(std::pair<std::string, float>(buffer.substr(0, sep), value));
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error : \"" << buffer << "\" in data file is not a valid imput" << std::endl;
            src_file.close();
            return(1);
        }
    }
    src_file.close();
    return(0);
}

static void second_skip_title_line(std::ifstream &src_file, std::string buffer)
{
    int         i = 0;

    getline(src_file, buffer);
    while (isspace(buffer[i]))
        i++;
    try
    {
        if (buffer.compare(i, 4, "date"))
        {
            src_file.seekg(0);
            return;
        }
    }
    catch(const std::exception& e)
    {
        src_file.seekg(0);
        return;
    }
    i += 4;
    while (isspace(buffer[i]))
        i++;
    if (buffer[i] != '|' && buffer[i] != ',')
    {
        src_file.seekg(0);
        return;
    }
    i++;
    while (isspace(buffer[i]))
        i++;
    try
    {
        if (buffer.compare(i, 5, "value"))
        {
            src_file.seekg(0);
            return;
        }
    }
    catch(const std::exception& e)
    {
        src_file.seekg(0);
        return;
    }
    i += 5;
    while (isspace(buffer[i]))
        i++;
    if (buffer[i])
    {
        src_file.seekg(0);
        return;
    }
    return;
}

int evaluate_btc_value(std::map<std::string, float> &btc, char **argv)
{
    std::ifstream   src_file;
    std::string     buffer;
    size_t          sep;
    float           value;
    std::string     date;

    if (verif_open_file(src_file, argv[1]))
    {
        src_file.close();
        return(1);
    }
    second_skip_title_line(src_file, buffer);
    while(src_file.good() && getline(src_file, buffer))
    {
        sep = buffer.find(",");
        if (sep == std::string::npos)
            sep = buffer.find("|");
        if (sep == std::string::npos)
            std::cerr << "Error : line \"" << buffer << "\" does not suit \"date | value\" format" << std::endl;
        else
        {
            if (!initialize_date_and_value(buffer, sep, date, value))
            {
                if (is_date_and_value_valid(date, value, buffer))
                    convert_bitcoin(btc, date, value);
            }
        }
    }
    src_file.close();
    return(0);
}

int initialize_date_and_value(const std::string &buffer, size_t &sep, std::string &date, float &value)
{
    std::string temp;
    try
    {
        date = buffer.substr(0, sep);
        temp = buffer.substr(sep + 1, buffer.size() - 1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return(1);
    }
    try
    {
        value = std::stof(temp);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error : no valid number in \"" << buffer << "\"" << std::endl;
        return(1);
    }
    return(0);
}

int is_date_and_value_valid(const std::string &date, const float &value, const std::string &buffer)
{
    if (value < 0 || value > 1000)
    {
        std::cerr << "Error : number in \"" << buffer << "\" must be between 0 and 1000" << std::endl;
        return(0);
    }
    if (!is_date_valid(date))
    {
        std::cerr << "Error : date in \"" << buffer << "\" is invalid" << std::endl;
        return(0);
    }
    return(1);
}

void    convert_bitcoin(std::map<std::string, float> &btc, const std::string &date, const float &value)
{
    std::map<std::string, float>::iterator  it;

    it = btc.begin();
    if (date < it->first)
    {
        std::cerr << "Error : not Bitcoin value before \"" << it->first << "\"" << std::endl;
        return;
    }
    while (it != btc.end() && date >= it->first)
        it++;
    it--;
    std::cout << date << " | " << value * it->second << std::endl;
}

int is_date_valid(const std::string &date)
{
    int year;
    int month;
    int day;

    if (!is_parsing_date_valid(date))
		return(0);
    try
    {
        year = std::stof(date.substr(0, 4));
        month = std::stof(date.substr(5, 2));
        day = std::stof(date.substr(8, 2));
    }
    catch(const std::exception& e)
    {
		return(0);
    }
    if (month == 0 || month > 12 || day == 0 || day > 31)
		return (0);
    if ((month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return(0);
	if (month == 2 && (day > 29))
		return(0);
	if (month == 2 && day == 29 && ((year % 4) || (!(year % 100) && year % 400)))
		return(0);
    return(1);
}

int	is_parsing_date_valid(std::string date)
{
	int i = 0;

    while (isspace(date[i]))
        i++;
    if (!isdigit(date[i]) || !isdigit(date[i + 1]) || !isdigit(date[i + 2]) || !isdigit(date[i + 3]))
        return(0);
    if (date[i + 4] != '-')
        return(0);
    if (!isdigit(date[i + 5]) || !isdigit(date[i + 6]))
        return(0);
    if (date[i + 7] != '-')
        return(0);
    if (!isdigit(date[i + 8]) || !isdigit(date[i + 9]))
        return(0);
    i += 10;
    while (isspace(date[i]))
        i++;
    if (date[i])
        return(0);
    return(1);
}