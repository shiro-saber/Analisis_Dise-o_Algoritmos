#include<iostream>
#include<cstdlib>
#include <algorithm>
#include <iterator>
#include<time.h>
#include<vector>
#define N 10000
 
using namespace std;
 
template <typename RandomAccessIterator>
void bubble_sort(RandomAccessIterator begin, RandomAccessIterator end) {
    bool swapped = true;
    while (begin != end-- && swapped) {
        swapped = false;
        for (auto i = begin; i != end; ++i) {
            if (*(i + 1) < *i) {
                std::iter_swap(i, i + 1);
                swapped = true;
            }
        }
    }
}
 
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
 
 
template <typename RandomAccessIterator, typename Predicate>
void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end,
    Predicate p) {
    for (auto i = begin; i != end; ++i) {
        std::rotate(std::upper_bound(begin, i, *i, p), i, i + 1);
    }
}
 
template <typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end) {
    insertion_sort(
        begin, end,
        std::less<
        typename std::iterator_traits<RandomAccessIterator>::value_type>());
}
 
//bucket sort
 
void Bucket_Sort(int array[], int n)
{
    int i, j;
    int count[N];
    for (i = 0; i < n; i++)
    {
        count[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        (count[array[i]])++;
    }
    for (i = 0, j = 0; i < n; i++)
    {
        for (; count[i]>0; (count[i])--)
        {
            array[j++] = i;
        }
    }
}
 
 
void BucketSort(int arr[], int n)
{
    int buckets[N];
 
    for (int j = 0; j < N; ++j)
    {
        buckets[j] = 0;
    }
    for (int i = 0; i < (N); ++i)
    {
        ++buckets[arr[i]];
    }
    for (int i = 0, j = 0; j < N; ++j)
    {
        for (int k = buckets[j]; k>0; --k)
        {
            arr[i++] = j;
        }
    }
}
 
 
 
//fin bucket
 
 
template<typename ForwardIterator>
void counting_sort(ForwardIterator begin, ForwardIterator end) {
    auto min_max = std::minmax_element(begin, end);
    if (min_max.first == min_max.second) {  // empty range
        return;
    }
    auto min = *min_max.first;
    auto max = *min_max.second;
    std::vector<unsigned> count((max - min) + 1, 0u);
    for (auto i = begin; i != end; ++i) {
        ++count[*i - min];
    }
    for (auto i = min; i <= max; ++i) {
        for (auto j = 0; j < count[i - min]; ++j) {
            *begin++ = i;
        }
    }
}

template<typename RandomAccessIterator, typename Order>
void mergesort(RandomAccessIterator first, RandomAccessIterator last, Order order)
{
    if (last - first > 1)
    {
        RandomAccessIterator middle = first + (last - first) / 2;
        mergesort(first, middle, order);
        mergesort(middle, last, order);
        std::inplace_merge(first, middle, last, order);
    }
}
 
template<typename RandomAccessIterator>
void mergesort(RandomAccessIterator first, RandomAccessIterator last)
{
    mergesort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template <class RandomAccessIterator>
void tree_sort(RandomAccessIterator first, RandomAccessIterator last);
 
namespace
{
 
    template <class RandomAccessIterator>
    class treenode
    {
    public:
        friend void tree_sort<RandomAccessIterator>(RandomAccessIterator, RandomAccessIterator);
        typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
        treenode(const T& value)
            : value_(value), left_(NULL), right_(NULL)
        {
        }
        static treenode<RandomAccessIterator>* build(RandomAccessIterator first, RandomAccessIterator last)
        {
            treenode<RandomAccessIterator>* root = NULL;
            for (RandomAccessIterator it = first; it < last; ++it) {
                treenode<RandomAccessIterator>* node = new treenode<RandomAccessIterator>(*it);
                if (root == NULL) {
                    root = node;
                }
                else {
                    treenode<RandomAccessIterator>* current = root, *previous = NULL;
                    bool less;
                    while (current != NULL) {
                        less = node->value_ < current->value_;
                        previous = current;
                        current = less ? current->left_ : current->right_;
                    }
                    if (less) {
                        previous->left_ = node;
                    }
                    else {
                        previous->right_ = node;
                    }
                }
            }
            return root;
        }
        void write(RandomAccessIterator* it) const
        {
            if (left_) {
                left_->write(it);
            }
            **it = value_;
            ++(*it);
            if (right_) {
                right_->write(it);
            }
        }
        void destroy()
        {
            if (left_) {
                left_->destroy();
            }
            if (right_) {
                right_->destroy();
            }
            delete this;
        }
        T value_;
        treenode<RandomAccessIterator>* left_;
        treenode<RandomAccessIterator>* right_;
    };
 
};
 
template <class RandomAccessIterator>
void tree_sort(RandomAccessIterator first, RandomAccessIterator last)
{
    treenode<RandomAccessIterator>* tree = treenode<RandomAccessIterator>::build(first, last);
    tree->write(&first);
    tree->destroy();
}
 
class radix_test
{
    const int bit; // bit position [0..31] to examine
public:
    radix_test(int offset) : bit(offset) {} // constructor
 
    bool operator()(int value) const // function call operator
    {
        if (bit == 31) // sign bit
            return value < 0; // negative int to left partition
        else
            return !(value & (1 << bit)); // 0 bit to left partition
    }
};
 
void lsd_radix_sort(int *first, int *last)
{
    for (int lsb = 0; lsb < 32; ++lsb) // least-significant-bit
    {
        std::stable_partition(first, last, radix_test(lsb));
    }
}
 
 
class shell
{
public:
    shell()
    {
        _gap[0] = 1750; _gap[1] = 701; _gap[2] = 301; _gap[3] = 132; _gap[4] = 57; _gap[5] = 23; _gap[6] = 10; _gap[7] = 4; _gap[8] = 1;
    }
 
    void sort(int* a, int count)
    {
        _cnt = count;
        for (int x = 0; x < 9; x++)
            if (count > _gap[x])
            {
                _idx = x; break;
            }
 
        sortIt(a);
    }
 
private:
    void sortIt(int* arr)
    {
        bool sorted = false;
        while (true)
        {
            sorted = true;
            int st = 0;
            for (int x = _gap[_idx]; x < _cnt; x += _gap[_idx])
            {
                if (arr[st] > arr[x])
                {
                    swap(arr[st], arr[x]); sorted = false;
                }
                st = x;
            }
            if (++_idx >= 8) _idx = 8;
            if (sorted && _idx == 8) break;
        }
    }
 
    void swap(int& a, int& b) { int t = a; a = b; b = t; }
 
    int _gap[9], _idx, _cnt;
};
 
 
template<typename ForwardIterator>
void selection_sort(ForwardIterator begin, ForwardIterator end)
{
    for (auto i = begin; i != end; ++i) {
        std::iter_swap(i, std::min_element(i, end));
    }
}
 
 
template<typename RandomAccessIterator>
void heap_sort(RandomAccessIterator begin, RandomAccessIterator end) {
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
}
 
 
 
void quickSort(int v[], int primero, int ultimo)
{
    int izquierdo = primero;
    int derecho = ultimo;
    int temp;
    //Se selecciona pivote
    int pivote = v[primero];
    if (primero < ultimo) // Paso base
    {
        // particion
        while (izquierdo < derecho)
        {
            while ((izquierdo < derecho) && (v[izquierdo] <= pivote)) izquierdo++;
            while (v[derecho] > pivote) derecho--;
            if (izquierdo < derecho) // se intercambian los contenidos
            {
                temp = v[derecho];
                v[derecho] = v[izquierdo];
                v[izquierdo] = temp;
            }
        }
        temp = v[derecho];
        v[derecho] = v[primero];
        v[primero] = temp;
        // Paso recursivo
        quickSort(v, primero, derecho - 1);
        quickSort(v, izquierdo, ultimo);
    }
}
 
 
void imprime(int arreglo[], int n)
{
 
    for (int i = 0; i < N; i++){
 
        cout << arreglo[i] << "||";
        if (i % 100 == 0){
 
            cout << endl;
        }
    }
    cout << endl << endl << endl;
}
 
int main()
{
    srand((int)time(NULL));
    int arreglo[N];
    for (int i = 0; i < N; i++){
        arreglo[i] = rand() % 1000;
   
    clock_t t;
    t = clock();
    bubble_sort(begin(arreglo), end(arreglo)); 
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate BUBBLE SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
 
    t = clock();//es para poder medir el tiempo de medicion
    cocktail_sort(begin(arreglo), end(arreglo));
     t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate COCKTAIL SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
 
    t = clock();//es para poder medir el tiempo de medicion
    insertion_sort(begin(arreglo), end(arreglo));
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate INSERTION SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
 
   /* t = clock();//es para poder medir el tiempo de medicion
    counting_sort(begin(arreglo), end(arreglo));
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate COUNTING SORT \n", t, ((float)t) / CLOCKS_PER_SEC); */

    t = clock();//es para poder medir el tiempo de medicion
    mergesort(begin(arreglo), end(arreglo));
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate MERGE SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
  
    t = clock();//es para poder medir el tiempo de medicion
    lsd_radix_sort(arreglo, arreglo + N);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate RADIX \n", t, ((float)t) / CLOCKS_PER_SEC);
 
    t = clock();//es para poder medir el tiempo de medicion
    shell s; 
    s.sort(arreglo, N);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate SHELL SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
 
    t = clock();//es para poder medir el tiempo de medicion
   selection_sort(begin(arreglo), end(arreglo));
     t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate SELECTION SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
 
    t = clock();//es para poder medir el tiempo de medicion
    heap_sort(begin(arreglo), end(arreglo));
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate HEAP SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
 
   t = clock();//es para poder medir el tiempo de medicion
   quickSort(arreglo, 0, N - 1);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate QUICK SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
 
     t = clock();//es para poder medir el tiempo de medicion
     tree_sort(begin(arreglo), end(arreglo));
     t = clock() - t;
    printf("It took me %d clicks (%f seconds). To calculate TREE SORT \n", t, ((float)t) / CLOCKS_PER_SEC);
    
	printf("With an array of size %d \n", N);
       return 0;
}}

