/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:08:13 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/21 17:38:33 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./btc <input_file>\n";
		return 1;
	}
	BitcoinExchange btc;
	btc.loadDatabase("data.csv");
	btc.processInputFile(argv[1]);
	
	return 0;
}