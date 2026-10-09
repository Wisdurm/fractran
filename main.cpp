#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <gmp.h>
#include <gmpxx.h>

void interpret(const std::list<mpq_class>& fs, mpq_class n);
mpq_class parse(std::string line);

int main(int argv, char* argc[])
{
	std::list<mpq_class> fs;
	if (argv > 1) {
		const std::string path = argc[1];
		std::ifstream input(path, std::ios::in);
		std::string line;
		if (input.is_open()) {
			while (std::getline(input, line)) {
				fs.push_back(parse(line));
			}
		}
		input.close();

	} else {
		std::string input;
		while (true) {
			std::getline(std::cin, input);
			if (input == "")
				break;
			fs.push_back(parse(input));
		}
	}

	interpret(fs, 2);
	return 0;
}

mpq_class parse(std::string line)
{
	if (auto i = line.find("/");
	    i != std::string::npos) {
		const int n = std::stoi(std::string(line.begin(),
						    line.begin() + i));
		const int d = std::stoi(std::string(line.begin() + i+1,
						    line.end()));
		return {n, d};
	}
	throw;
}

void interpret(const std::list<mpq_class>& fs, mpq_class n)
{
	for (auto it = fs.begin(); it != fs.end();) {
		if (const mpq_class nf((*it) * n);
		    nf.get_den() == 1) {
			n = nf;
			std::cout << n << std::endl;
			it = fs.begin();
		} else
			++it;
	}
}
