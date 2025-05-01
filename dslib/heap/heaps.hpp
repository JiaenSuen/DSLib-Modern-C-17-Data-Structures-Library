#ifndef HEAPS_HPP
#define HEAPS_HPP

#include <vector>
#include <stdexcept>   

template <typename T>
class Heap
{
protected:
    // Heap Interface
    virtual bool heap_compare(const T &a, const T &b) = 0;

protected:
    std::vector<T> Tree;
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left (int i)  { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void shiftUp(int i) {
        while (i > 0 && heap_compare(Tree[i] , Tree[parent(i)]) ) {
            std::swap(Tree[i], Tree[parent(i)]);
            i = parent(i);
        }
    }

    void shiftDown(int i) {
        int swapId = i;
        int l = left(i), r = right(i);

        if (l < size && heap_compare( Tree[l] , Tree[swapId])  )    swapId = l;
        if (r < size && heap_compare( Tree[r] , Tree[swapId])  )    swapId = r;
        
        if (swapId != i) {
            std::swap(Tree[i], Tree[swapId]);
            shiftDown(swapId);
        }
    }

public:
    Heap() : size(0) {}

    bool isEmpty() const   { return size == 0; }

    T getMax() const {
        if (isEmpty()) throw std::runtime_error("Heap is empty");
        return Tree[0];
    }

    void insert(T val)   {
        if (size >= Tree.size())
            Tree.push_back(val);
        else
            Tree[size] = val;
        
        shiftUp(size);
        size++;
    }

    T extract_root()   {
        if (isEmpty()) throw std::runtime_error("Heap is empty");

        T max = Tree[0];
        Tree[0] = Tree[size - 1];
        size--;
        shiftDown(0);

        return max;
    }    
};


template <typename T>
class MaxHeap : public Heap<T>
{
protected:
    bool heap_compare(const T &a, const T &b) override {
        return a > b;  
    }
};

template <typename T>
class MinHeap : public Heap<T>
{
protected:
    bool heap_compare(const T &a, const T &b) override {
        return a < b;  
    }
};








#endif  