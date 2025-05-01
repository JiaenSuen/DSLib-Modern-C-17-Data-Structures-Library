#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include "../../dslib/heap/heaps.hpp"
using namespace std;



vector<int> generate_arr(int size){
    random_device RD;
    mt19937 gen(RD());
    uniform_int_distribution<int> dist(0,100);
    vector<int> container;
    for (int i = 0; i < size; i++) container.push_back(dist(gen)); 
    return container;
}

void show_vec(vector<int>& List){
    for (auto& x : List)
        cout<<x<<"\t";
    cout<<endl;
}

void show_vec_pointer(vector<int*>& List){
    for (auto& x : List)
        cout<<*x<<"\t";
    cout<<endl;
}

void swap_pointer(int* x , int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}



vector<int*> GetEven(vector<int>& nums) {
    vector<int*> List;
    for (auto& x : nums) 
        if (x % 2 == 0) 
            List.push_back(&x);
    return List;
}


// Heap Sort 
vector<int> Heap_Sort(vector<int>& Array , bool from_Min=true){
    unique_ptr<Heap<int>> pool;
    if(from_Min)  pool = make_unique< MinHeap<int> >();
    else pool = make_unique< MaxHeap<int> >();
    
    vector<int> result_list;
    for (auto x :  Array) pool->insert(x);
    while (!pool->isEmpty()) result_list.push_back(pool->extract_root());
    return result_list;
}


void Heap_Sort_for_Pointer(vector<int*>& Array , bool from_Min){
    unique_ptr<Heap<int>> pool;
    if(from_Min)  pool = make_unique< MinHeap<int> >();
    else pool = make_unique< MaxHeap<int> >();

    for (auto x :  Array) pool->insert(*x);
    int i = 0;
    while (!pool->isEmpty()) {
        *Array[i] = pool->extract_root();
        i++;
    }
    
}



int main()
{   
    
    
    vector<int>  random_arr = generate_arr(20);
    vector<int>  sorted_min,sorted_max;
    cout<<"Show Vec : ";show_vec(random_arr);    
    sorted_min = Heap_Sort(random_arr,true );
    sorted_max = Heap_Sort(random_arr,false);
    cout<<"From Min : ";show_vec(sorted_min);
    cout<<"From Max : ";show_vec(sorted_max);



    vector<int> Nums = generate_arr(20);
    vector<int*> Numsp = GetEven(Nums);
    
    cout<<"\n\n\n";
    show_vec(Nums);
    Heap_Sort_for_Pointer(Numsp,true);
    show_vec(Nums);
    show_vec_pointer(Numsp);
    return 0;
}