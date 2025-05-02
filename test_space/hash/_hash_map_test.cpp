#include <iostream>
#include <string>
#include <array>
#include "../../dslib/hash/hash_map.hpp"
#include "../../utils/random/randoms.hpp"
using namespace dslib::hashing;

// 定義 Person 結構
struct Person {
    std::string name;
    int age;
    int id;

    bool operator==(const Person& o) const {
        return name == o.name && age == o.age && id == o.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.name << "(" << p.age << "," << p.id << ")";
    }
};

// 使用宏定義 Person 的雜湊函式
DEFINE_HASH_FOR(Person, &Person::name, &Person::age, &Person::id)

Random_Generator& RG = Random_Generator::instance();

void test_int_map() {
    Hash_Map<int,int> m;
    for (size_t i = 0; i < 20; i++) {
        int key = RG.generate_int();
        m.insert(key, key*2);  // value = key * 2
    }
    std::cout << m << std::endl;
    int query = 5;
    auto pv = m.find(query);
    if (pv) std::cout << "Find key(5): value=" << *pv << std::endl;
    else    std::cout << "Key(5) not found\n";
}


void test_person_map() {
    Hash_Map<int, Person> m;
    for (int i = 0; i < 20; i++) {
        Person p {
            RG.generate_string(3, 8),
            RG.generate_int(18, 65),
            RG.generate_int(1000, 9999)
        };
        m.insert(i, p);   
    }

    std::cout << m << std::endl;

    int query = 5;
    auto pv = m.find(query);
    if (pv) std::cout << "Found key(" << query << "): " << *pv << std::endl;
    else    std::cout << "Key(" << query << ") not found\n";
}


int main() {
    std::cout<<"Test Int to Int : \n";
    test_int_map();


    std::cout<<"Test Int to Struct : \n";
    test_person_map();
    return 0;
}
