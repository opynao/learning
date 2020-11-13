#include <vector>
#include <iostream>

using blockNum_t = size_t;
using dens_t = size_t;

void GetBlockSizes(std::vector<std::vector<size_t>>& vBlockSizes)
{
	size_t height, width, length;
	std::cin >> height;
	std::cin >> width;
	std::cin >> length;
	vBlockSizes.push_back({height,width,length});
}

uint64_t CalculateBlockMass(const std::vector<std::vector<size_t>>& vBlockSizes, const dens_t density)
{
	uint64_t sumMass {};
	for(const auto& block : vBlockSizes)
	{
		uint64_t volume = block[0] * block[1] * block [2];
		sumMass += (volume*density);
	}
	return sumMass;
}


int main()
{
	blockNum_t numberOfBlocks {};
	dens_t density {};
	std::vector<std::vector<size_t>> vBlockSizes {};
	std::cin >> numberOfBlocks;
	std::cin >> density;
	while(numberOfBlocks--)
	{
		GetBlockSizes(vBlockSizes);
	}
	std::cout << CalculateBlockMass(vBlockSizes, density);
	return 0;
}
