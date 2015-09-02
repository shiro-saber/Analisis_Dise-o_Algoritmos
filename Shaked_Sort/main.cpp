#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

using namespace std;
 
template <typename RandomAccessIterator>
void cocktail_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  bool swapped = true;
  while (begin != end-- && swapped) {
    swapped = false;
    for (auto i = begin; i != end; ++i) {
      if (*(i + 1) < *i) {
        std::iter_swap(i, i + 1);
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
    swapped = false;
    for (auto i = end - 1; i != begin; --i) {
      if (*i < *(i - 1)) {
        std::iter_swap(i, i - 1);
        swapped = true;
      }
    }
    ++begin;
  }
}
 
int main() {
  //time_t begin, end;
    const int n = 100;
    time_t inicio, final;
    int a[n];
    
    srand((unsigned int) time(nullptr));
    std::generate(a, a + n, []() { return rand() % 100000; });
    std::copy(a, a + n, ostream_iterator<int>(cout, " "));
    cout << endl << endl;
    cocktail_sort(std::begin(a), std::end(a));
    copy(begin(a), end(a), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}