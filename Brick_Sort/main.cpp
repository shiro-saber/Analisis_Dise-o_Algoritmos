#include <iostream>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <ctime>

using namespace std;

void swap(int a[], int i, int j)
{
    int temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}
void BrickSort(int a[], int n)
{
    bool sorted=false;
    while(sorted!=true)
    {
        sorted=true;
        for(int i=1;i<n-1;i+=2)
        {
            if(a[i]>a[i+1])
            {
                swap(a,i,i+1);
                sorted=false;
            }
        }
        for(int i=0;i<n-1;i+=2)
        {
            if(a[i]>a[i+1])
            {
                swap(a,i,i+1);
                sorted=false;
            }
        }
    }
    cout << endl << endl;
    for(int i=0;i<n;i++) cout<<a[i] << " ";
}

int main(void) 
{
    const int n = 100;
    time_t inicio, final;
    int enteros[n];
    
    srand((unsigned int) time(nullptr));
    std::generate(enteros, enteros + n, []() { return rand() % 100000; });
    std::copy(enteros, enteros + n, ostream_iterator<int>(cout, " "));

    //printArray(enteros, n);
    BrickSort (enteros, n);
    //printArray(enteros, n);
    return 0;
}