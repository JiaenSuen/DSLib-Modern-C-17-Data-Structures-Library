#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include "../../dslib/heap/heaps.hpp"
using namespace std;





// tool kit
vector<int> generate_arr(int size,int min , int max);
void show_vec(vector<int>& List);
void show_vec_pointer(vector<int*>& List);
// tool kit


vector<int*> GetEven(vector<int>& nums) {
    vector<int*> List;
    for (auto& x : nums) 
        if (x % 2 == 0) 
            List.push_back(&x);
    return List;
}

// Heap Sort  
void Heap_Sort_for_Pointer(vector<int*>& Array , bool from_Min = true){
    if (Array.empty()) return;
    unique_ptr<Heap<int>> pool;
    if(from_Min)  pool = make_unique< MinHeap<int> >();
    else          pool = make_unique< MaxHeap<int> >();

    for (auto& x :  Array) pool->insert(*x);
    size_t i = 0;
    while (!pool->isEmpty()) {
        *Array[i] = pool->extract_root();
        i++;
    }
}

int main()
{   
    vector<int>  random_arr; 
    vector<int*> even_arr;
    // min , max , size of list
    vector<vector<int>> params = { 
        {0,100,10},
        {-100,100,10},
        {0,1000,50},
    };

    string frame_line(100, '-');
    for (auto p : params)    {
        cout<<frame_line<<"\n\n";

        random_arr = generate_arr(p[2],p[0],p[1]);
        even_arr   = GetEven(random_arr);
        cout<<"Test Case : "<<endl;
        show_vec(random_arr);
        cout<<"Sorted Main Array : "<<endl;
        Heap_Sort_for_Pointer(even_arr ,true); // 輸入 false 由 大排至小
        show_vec(random_arr);
        cout<<"Sorted Sub  Array : "<<endl;
        show_vec_pointer(even_arr);

        random_arr.clear();
        even_arr.clear();
        cout<<frame_line<<"\n\n";
    }
    system("pause");
    return 0;
}

// Tools :

vector<int> generate_arr(int size,int min=0 , int max=100){
    random_device RD;
    mt19937 gen(RD());
    uniform_int_distribution<int> dist(min,max);
    vector<int> container;
    for (int i = 0; i < size; i++) container.push_back(dist(gen)); 
    return container;
}


void show_vec(vector<int>& List){
    int c = 0;
    for (auto& x : List) {
        cout<<x<<"\t";
        if ((c++)%10==9) cout<<endl;
    }
    cout<<endl;
}

void show_vec_pointer(vector<int*>& List){
    int c = 0;
    for (auto& x : List) {
        cout<<*x<<"\t";
        if ((c++)%10==9) cout<<endl;
    }
    cout<<endl;
}