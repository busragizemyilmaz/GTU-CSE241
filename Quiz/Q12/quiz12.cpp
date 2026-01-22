#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

class AllocationExcept : public bad_alloc {
public:
    const char* what() const noexcept override {
        return "Error: Disk usage reached maximum limit.";
    } 
};

template<class T1, class T2>
class DictionaryLarge {
private:
    struct Node {
        T2 value;
        int frequency = 0;
    };

    map<T1, Node> RAM;
    string fileName;
    int RAMCapacity;
    int DiskCapacity;
    int count = 0;

    void moveToDisk() {
        if (count >= DiskCapacity)
            throw AllocationExcept();

        auto minIt = RAM.begin();
        for (auto it = RAM.begin(); it != RAM.end(); ++it) 
        {
            if (it->second.frequency < minIt->second.frequency)
                minIt = it;
        }

        ofstream file(fileName, ios::app);
        if (file.is_open()) 
        {
            file << minIt->first << " " << minIt->second.value << endl;
            file.close();

            RAM.erase(minIt);
            count++;
        }
    }

public:
    DictionaryLarge() : fileName(""), RAMCapacity(0), DiskCapacity(0) { }
    
    DictionaryLarge(int rc, int dc, string name) : RAMCapacity(rc), DiskCapacity(dc), fileName(name) { }

    DictionaryLarge(const DictionaryLarge<T1, T2>& other) {
        RAM = other.RAM;
        fileName = other.fileName;
        RAMCapacity = other.RAMCapacity;
        DiskCapacity = other.DiskCapacity;
        count = other.count;
    }

    DictionaryLarge& operator=(const DictionaryLarge<T1, T2>& other) {
        if (this != &other)
        {
            RAM = other.RAM;
            fileName = other.fileName;
            RAMCapacity = other.RAMCapacity;
            DiskCapacity = other.DiskCapacity;
            count = other.count;
        }

        return *this;
    }

    DictionaryLarge(DictionaryLarge<T1, T2>&& other) noexcept {
        RAM = move(other.RAM);
        fileName = move(other.fileName);
        RAMCapacity = other.RAMCapacity;
        DiskCapacity = other.DiskCapacity;
        count = other.count;

        other.RAMCapacity = 0;
        other.DiskCapacity = 0;
        other.count = 0;
    }

    DictionaryLarge& operator=(DictionaryLarge<T1, T2>&& other) noexcept {
        if (this != &other)
        {
            RAM = move(other.RAM);
            fileName = move(other.fileName);
            RAMCapacity = other.RAMCapacity;
            DiskCapacity = other.DiskCapacity;
            count = other.count;

            other.RAMCapacity = 0;
            other.DiskCapacity = 0;
            other.count = 0;
        }

        return *this;
    }

    ~DictionaryLarge() {
        RAM.clear();
    }

    void add(T1 key, T2 value) {
        auto it = RAM.find(key);
        if (it != RAM.end()) 
        {
            it->second.value = value;
            it->second.frequency++;

            return;
        }

        if (RAM.size() >= RAMCapacity)
            moveToDisk();

        RAM[key] = {value, 1};
    }

    T2* get(T1 key) {
        auto it = RAM.find(key);
        if (it != RAM.end()) 
        {
            it->second.frequency++;
            
            return &(it->second.value);
        }
 
        return nullptr; 
    }
};