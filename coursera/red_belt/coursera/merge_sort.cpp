#include <algorithm>
#include <vector>
#include <iterator>



template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) 
{
  // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
  int range_length = range_end - range_begin;
  if (range_length < 2)
    return;

  // 2. Создаем вектор, содержащий все элементы текущего диапазона
  std::vector<typename RandomIt::value_type> elements( std::make_move_iterator(range_begin), std::make_move_iterator(range_end));
  // 3. Разбиваем вектор на три равные части
  auto one_third = elements.begin() + range_length / 3;
  auto two_third = elements.begin() + range_length * 2 / 3;
  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());
  // 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
  // back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
  std::vector<typename RandomIt::value_type> interim_result;
  interim_result.reserve( std::distance( elements.begin(), two_third ) );
  std::merge( std::make_move_iterator(elements.begin()), 
			  std::make_move_iterator(one_third), 
			  std::make_move_iterator(one_third), 
			  std::make_move_iterator(two_third),
			  std::back_inserter(interim_result));
  // 6. С помощью алгоритма merge сливаем отсортированные части
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  std::merge( std::make_move_iterator(interim_result.begin()), 
		      std::make_move_iterator(interim_result.end()), 
			  std::make_move_iterator(two_third),
			  std::make_move_iterator(elements.end()),
			  range_begin);
}



int main()
{
	return 0;
}
