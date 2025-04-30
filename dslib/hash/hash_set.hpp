#pragma once
#ifndef DS_LIB_HASHING_HASH_LIST_HPP
#define DS_LIB_HASHING_HASH_LIST_HPP

#include "hasher.hpp"
#include "../../utils/ds_outputs.hpp"
#include <vector>   
#include <ostream>


namespace dslib {
namespace hashing {


    // Hash Table for Different Type
    template <typename Data , typename Hash_Function = Hash_Transform<Data>>
    class Hash_Set {

        private :

            struct Hash_Node {
                Data data;
                Hash_Node* next = nullptr;
            };

            std::vector<Hash_Node*> buckets;
            size_t bucket_count;
            size_t size = 0;        
            Hash_Function hasher;
        
        public :

            Hash_Set(size_t bucket_count = 10)
            : bucket_count(bucket_count), buckets(bucket_count, nullptr) {}

            ~Hash_Set() {
                for (auto head : buckets) {
                    while (head) {
                        Hash_Node* tmp = head;
                        head = head->next;
                        delete tmp;
                    }
                }
            }


            void insert(const Data& value) {
                size_t idx = hasher(value) % bucket_count;
                for (Hash_Node* p = buckets[idx]; p; p = p->next) if (p->data == value) return;
                Hash_Node* node = new Hash_Node{ value, buckets[idx] };
                buckets[idx] = node;
                size++;
            }

            bool contains(const Data&& value) const {
                size_t idx = hasher(value) % bucket_count;
                for (Hash_Node* p = buckets[idx]; p; p = p->next) if (p->data == value) return true;
                return false;
            }


            void remove(const Data& value) {
                size_t idx = hasher(value) % bucket_count;
                Hash_Node* prev = nullptr;
                for (Hash_Node* p = buckets[idx]; p; prev = p, p = p->next) {
                    if (p->data == value) {
                        if (prev) prev->next = p->next;
                        else      buckets[idx] = p->next;
                        delete p;
                        size--;
                        return;
                    }
                }
            }


            void clear() {
                for (auto& head : buckets) {
                    while (head) {
                        Hash_Node* tmp = head;
                        head = head->next;
                        delete tmp;
                    }
                    head = nullptr;
                }
                size = 0;
            }

            size_t get_size() const {
                return size;
            }

            bool empty() const {
                return size == 0;
            }

            
            friend std::ostream& operator<<(std::ostream& os, 
                                            const Hash_Set<Data, Hash_Function>& ht) {
                os << "\nHash_Set Contents :\n";
                for (size_t i = 0; i < ht.bucket_count; ++i) {
                    os << "  Bucket " << i << " : ";
                    for (auto p = ht.buckets[i]; p; p = p->next)
                        os << p->data << " ";
                    os << "\n";
                }
                return os;
            }
    };

}}  // dslib :: Hash Namespace End





#endif // DS_LIB_HASHING_HASH_LIST_HPP