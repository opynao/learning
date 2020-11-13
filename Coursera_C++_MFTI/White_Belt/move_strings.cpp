#include <vector>
#include <string>
#include <iterator>
#include <cassert>

using Words_t = std::vector<std::string>;

void MoveStrings(Words_t&,Words_t&);

void testMoveStrings()
{
	Words_t destination {"a","b","c"};
	Words_t source {"z"};
	Words_t controlDestination {"a","b","c","z"};
	Words_t emptySource {};
	MoveStrings(source,destination);
	assert(destination == controlDestination);
	assert(source == emptySource);
}

void MoveStrings(Words_t& source, Words_t& destination)
{
	std::move(source.begin(),source.end(),std::back_inserter(destination));
	source.clear();
}

int main()
{
	testMoveStrings();
}
