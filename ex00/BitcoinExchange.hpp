/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 21:55:06 by acomet            #+#    #+#             */
/*   Updated: 2024/02/27 20:46:31 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

/*  mains functions */
int init_btc(std::map<std::string, float> &btc, std::string data);
int evaluate_btc_value(std::map<std::string, float> &btc, char **argv);
void    convert_bitcoin(std::map<std::string, float> &btc, const std::string &date, const float &value);

/*  utils   */
int initialize_date_and_value(const std::string &buffer, size_t &sep, std::string &date, float &value);

/*  verif   */
int verif_open_file(std::ifstream &src_file, const std::string filename);
int is_date_and_value_valid(const std::string &date, const float &value, const std::string &buffer);
int is_date_valid(const std::string &date);



#endif