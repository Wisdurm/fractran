#include <forward_list>
#include <iostream>
#include <string>
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>
#include <list>

void interpret(std::forward_list<mpq_class>& fs, mpq_class n);
bool is_integer(float k);

int main()
{
	std::string input;
	std::getline(std::cin, input);
	const std::list<std::pair<int,int>> xs = {
		{17, 91},
		{78, 85},
		{19, 51},
		{23, 38},
		{29, 33},
		{77, 29},
		{95, 23},
		{77, 19},
		{1, 17},
		{11, 13},
		{13, 11},
		{15, 2},
		{1, 7},
		{55, 1}
	};
	std::forward_list<mpq_class> fs;
	for (auto it = xs.crbegin(); it != xs.rend(); ++it) {
		mpq_class f(it->first, it->second);
		fs.push_front(f);
	}
	interpret(fs, 2);
	return 0;
}

bool is_integer(float k)
{
	return std::floor(k) == k;
}

void interpret(std::forward_list<mpq_class>& fs, mpq_class n)
{
	std::string moi;
	for (auto it = fs.begin(); it != fs.end();) {
		mpq_class nf;
		nf = (*it) * n;
		if (nf.get_den().get_d() == 1) {
			n = nf;
			std::cout << n << std::endl;
			it = fs.begin();
		} else
			++it;
	}
}
