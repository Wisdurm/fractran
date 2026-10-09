#include <vector>
#include <fstream>
#include <print>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

#include <array>
#include <chrono>

void interpret(const std::vector<mpq_class>& fs, mpq_class n);
mpq_class parse(std::string line);

std::chrono::time_point<std::chrono::high_resolution_clock> st;

int main(int argv, char* argc[])
{
	std::vector<mpq_class> fs;
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

	constexpr int amount = 1000;
	std::array<double, amount> results;
	for (int i = 0; i < amount; i++) {
		st = std::chrono::high_resolution_clock::now();
		interpret(fs, 2);
		results.at(i) = (std::chrono::high_resolution_clock::now() - st).count();
	}

	// Print results
	double avg;
	for (auto r : results) {
		std::println("Time: {}", r);
		avg += r;
	}
	std::println("Average: {}", avg/amount);

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

void interpret(const std::vector<mpq_class>& fs, mpq_class n)
{
	constexpr auto comp = 227384373333196800;

	// Buffer string rendering for performance
	std::string buffer;
	uint buffered = 0;

	mpq_class nf;
	for (size_t i = 0; i < fs.size();) { [[likely]]
		nf = fs[i] * n;
		if (nf.get_den() == 1) { [[unlikely]]
			n.swap(nf);
			i = 0;

			// Number should be small enough to still preserver the
			// illusion of no buffer existing. That is: it should
			// look smooth because that's cool and good
			if (buffered > 500) {
				std::print("{}", buffer);
				buffered = 0;
				buffer.clear();
			} else {
				buffer += n.get_str();
				buffer += '\n';
				buffered++;
			}


			if (n > comp)
				break;
		} else [[likely]]
			i++;
	}
}
