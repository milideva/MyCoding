#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

/*
 multimap example:
 String is “this is it” and position of each character in string is,
    t occurs at 0 , 9
    h occurs at 1
    i occurs at 2 , 5 , 8
    s occurs at 3 , 6

    Here key is ‘char’ and value is ‘int’ i.e. position of character in string.
    So, there are multiple key value pairs with duplicate keys.
*/

void test_multimap(void)
{

    multimap<char, int> mmap = {
        {'t', 1},
        {'h', 1},
        {'i', 2},
        {'s', 3},
        {'i', 5},
        {'s', 6},
        {'i', 8},
    };

    // Inserting an element in map

    pair mPair('t', 9); // auto mPair = make_pair('t', 9);
    mmap.insert(mPair);

    std::cout << "************ multimap ****************" << std::endl;

    // Iterate over the multimap using Iterator
    for (auto it = mmap.begin(); it != mmap.end(); it++)
        std::cout << it->first << " :: " << it->second << std::endl;
    std::cout << "****************************************" << std::endl;

    // Iterate over the multimap using range based for loop
    for (auto elem : mmap)
        std::cout << elem.first << " :: " << elem.second << std::endl;
    std::cout << "****************************************" << std::endl;

    // find a key and all multi elements for that key
    auto key = 'i';
    if (auto search = mmap.find(key); search != mmap.end())
    {
        std::cout << "Found " << search->first << " " << search->second << " count " << mmap.count(key) << '\n';
        for (auto it = mmap.equal_range(key).first; it != mmap.equal_range(key).second; ++it)
            std::cout << ' ' << (*it).second;

        // Using equal_range - cleaner way
        std::pair <std::multimap<char,int>::iterator, std::multimap<char,int>::iterator> ret;
        ret = mmap.equal_range(key);
        std::cout << key << " =>";
        for (std::multimap<char,int>::iterator it=ret.first; it!=ret.second; ++it)
            std::cout << ' ' << it->second;
            
        mmap.erase(search);
        std::cout << "\nErased one pair"
                  << " count " << mmap.count(key) << '\n';
    }
    else
    {
        std::cout << "Not found\n";
    }
}

void test_map(void)
{

    map<char, int> mymap = {
        {'t', 1},
        {'h', 1},
        {'i', 2},
        {'s', 3},
        {'i', 5},
        {'s', 6},
        {'i', 8},
    };

    // Inserting an element in map when it already exists
    auto k1 = 't';
    pair mPair(k1, 9); // auto mPair = make_pair('t', 9);
    auto ret = mymap.insert(mPair);
    if (ret.second==false) {
        cout << "element " << k1 << " already existed";
        cout << " with a value of " << ret.first->second << '\n';
    }

    std::cout << "************ map ****************" << std::endl;
    // Iterate over the multimap using Iterator
    for (auto it = mymap.begin(); it != mymap.end(); it++)
        std::cout << it->first << " :: " << it->second << std::endl;
    std::cout << "****************************************" << std::endl;

    // Iterate over the multimap using range based for loop
    for (auto elem : mymap)
        std::cout << elem.first << " :: " << elem.second << std::endl;
    std::cout << "****************************************" << std::endl;

    // find a key and all multi elements for that key
    auto key = 'i';
    if (auto search = mymap.find(key); search != mymap.end())
    {
        std::cout << "Found " << search->first << " " << search->second << " count " << mymap.count(key) << '\n';
        for (auto it = mymap.equal_range(key).first; it != mymap.equal_range(key).second; ++it)
            std::cout << ' ' << (*it).second;
        mymap.erase(search);
        std::cout << "\nErased one pair"
                  << " count " << mymap.count(key) << '\n';
    }
    else
    {
        std::cout << "Not found\n";
    }
}

int main(void)
{
    test_multimap();
    test_map();
    return 0;
}
