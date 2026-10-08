#include <forward_list>
#include <iostream>
#include <string>
#include <cmath>

struct Fraction
{
	float x;
	float y;
};

void interpret(std::forward_list<Fraction>& fs, int n);
bool is_integer(float k);

int main()
{
	std::string input;
	std::getline(std::cin, input);
	std::forward_list<Fraction> fs = {
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
	interpret(fs, 2);
	return 0;
}

bool is_integer(float k)
{
	return std::floor(k) == k;
}

void interpret(std::forward_list<Fraction>& fs, int n)
{
	for (auto it = fs.begin(); it != fs.end();) {
		if (float nf = it->x/it->y * n; is_integer(nf)) {
			n = nf;
			std::cout << n << std::endl;
			it = fs.begin();
		} else
			++it;
	}

}
