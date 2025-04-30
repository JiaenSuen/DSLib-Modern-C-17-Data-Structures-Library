#include <iostream>
#include <string>
#include <array>
#include "../../dslib/hash/hash_set.hpp"
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



void test_int() {
    Hash_Set<int> h;
    for (size_t i = 0; i < 20; i++) h.insert(RG.generate_int());
    std::cout << h << std::endl;
    std::cout<<"Chech Data ( 5 ) : "<<h.contains(5)<<std::endl;
}

void test_float() {
    Hash_Set<float> h;
    for (size_t i = 0; i < 20; i++) h.insert(RG.generate_float());
    std::cout << h << std::endl;
    std::cout<<"Chech Data ( 3.14 ) : "<<h.contains(3.14)<<std::endl;
}

void test_double() {
    Hash_Set<double> h;
    for (size_t i = 0; i < 20; i++) h.insert(RG.generate_double());
    std::cout << h << std::endl;
    std::cout<<"Chech Data ( 3.1415926 ) : "<<h.contains(3.1415926)<<std::endl;
}

void test_string() {
    Hash_Set<std::string> h;
    for (size_t i = 0; i < 20; i++) h.insert(RG.generate_string(3,5));
    std::cout << h << std::endl;
    std::cout<<"Chech Data ( hello ) : "<<h.contains("hello")<<std::endl;
}

void test_array() {
    using Arr = std::array<int, 3>;
    Hash_Set<Arr> h;
    for (size_t i = 0; i < 20; i++) h.insert(RG.generate_array<int,3>(1,10));
    std::cout << h << std::endl;
    std::cout<<"Chech Data ( yoQ(44,8141) ) : "<<h.contains({1,2,3})<<std::endl;
} 




void test_person() {
    Hash_Set<Person> h;
    for (size_t i = 0; i < 20; i++) {
        Person p {
            RG.generate_string(3, 8),     // Name Length is Between 3 to 8 char
            RG.generate_int(18, 65),     // Age
            RG.generate_int(1000, 9999) // ID 
        };
        h.insert(p);
    }
    std::cout << h << std::endl;
    std::cout<<"Chech Data ( yoQ(44,8141) ) : "<<h.contains({"yoQ",44,8141})<<std::endl;
}


 
int main() {
    std::cout<<std::boolalpha;

    std::cout << "=== Test int ===\n";
    test_int();

    std::cout << "\n=== Test float ===\n";
    test_float();

    std::cout << "\n=== Test double ===\n";
    test_double();

    std::cout << "\n=== Test string ===\n";
    test_string();

    std::cout << "\n=== Test array<int, 3> ===\n";
    test_array(); 

    std::cout << "\n=== Test Person ===\n";
    test_person();
    return 0;
}