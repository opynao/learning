template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if(range_begin - range_end < 2)
		return;
	std::vector<int> vect (range_begin, range_end);
	
}
