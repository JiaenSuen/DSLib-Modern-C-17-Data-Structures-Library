#pragma once
#ifndef DS_LIB_HASHING_HASH_MAP_HPP
#define DS_LIB_HASHING_HASH_MAP_HPP

#include "hasher.hpp"
#include "../../utils/ds_outputs.hpp"
#include <vector>   
#include <ostream>


namespace dslib {
namespace hashing {


    // Hash Table for Different Type
    template <typename Key, typename Value, typename Hash_Function = Hash_Transform<Key>>
    class Hash_Map {

        private :

            struct Hash_Node {
                Key   key;
                Value value;
                Hash_Node* next = nullptr;
            };

            std::vector<Hash_Node*> buckets;
            size_t bucket_count;
            size_t size = 0;        
            Hash_Function hasher;
        
        public :

            Hash_Map(size_t bucket_count = 10)
            : bucket_count(bucket_count), buckets(bucket_count, nullptr) {}

            ~Hash_Map() {
                clear();
            }


            void insert(const Key& key, const Value& value) {
                size_t idx = hasher(key) % bucket_count;
                for (Hash_Node* p = buckets[idx]; p; p = p->next) {
                    if (p->key == key) {
                        p->value = value;   
                        return;
                    }
                }
                Hash_Node* node = new Hash_Node{ key, value, buckets[idx] };
                buckets[idx] = node;
                ++size;
            }


            Value* find(const Key& key) {
                size_t idx = hasher(key) % bucket_count;
                for (Hash_Node* p = buckets[idx]; p; p = p->next) {
                    if (p->key == key) return &p->value;
                }
                return nullptr;
            }
    

            Value& operator[](const Key& key) {
                size_t idx = hasher(key) % bucket_count;
                for (Hash_Node* p = buckets[idx]; p; p = p->next) {
                    if (p->key == key) return p->value;
                }
                Hash_Node* node = new Hash_Node{ key, Value{}, buckets[idx] };
                buckets[idx] = node;
                ++size;
                return node->value;
            }

            void remove(const Key& key) {
                size_t idx = hasher(key) % bucket_count;
                Hash_Node* prev = nullptr;
                for (Hash_Node* p = buckets[idx]; p; prev = p, p = p->next) {
                    if (p->key == key) {
                        if (prev) prev->next = p->next;
                        else      buckets[idx] = p->next;
                        delete p;
                        --size;
                        return;
                    }
                }
            }

            bool contains(const Key& key) const {
                size_t idx = hasher(key) % bucket_count;
                for (Hash_Node* p = buckets[idx]; p; p = p->next) {
                    if (p->key == key) return true;
                }
                return false;
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
                                            const Hash_Map<Key, Value, Hash_Function>& ht) {
                os << "\nHash_Map Contents :\n";
                for (size_t i = 0; i < ht.bucket_count; ++i) {
                    os << "  Bucket " << i << " : ";
                    for (auto p = ht.buckets[i]; p; p = p->next)
                        os << "{" << p->key << " : " << p->value << "} ";
                    os << "\n";
                }
                return os;
            }
    };

}}  // dslib :: Hash Namespace End





#endif // DS_LIB_HASHING_HASH_LIST_HPP