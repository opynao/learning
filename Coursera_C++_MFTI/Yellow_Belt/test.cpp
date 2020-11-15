#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> vec;
auto vector_begin = begin(vec);
auto vector_end = end(vec);

string str;
auto string_begin = begin(str);
auto string_end = end(str);

set<int> s;
auto set_begin = begin(s);
auto set_end = end(s);

int main()
{
	next_permutation(string_begin, string_end);	
		next_permutation(string_begin, string_end);	
is_permutation(vector_begin, vector_end, vector_begin);
partial_sum(set_begin, set_end, back_inserter(vec));
//is_heap(string_begin, string_end);
	return 0;
}
