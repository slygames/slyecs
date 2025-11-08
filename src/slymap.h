#pragma once

#include "slyarray.h"
#include <unordered_map>

namespace sly {

template <typename T>
class map : public array<T> {
public:


    // this stores a hash of the object in the same index as the object is stored in the object_list, so for any item
    //std::vector<int> hash;

    //std::unordered_map<int, int> find; // <hash_val, object_index> stores the hash value as a key in this table, uses hash function to find items by getting the key and then returning the object, this can be used to lookup actual objects by hash

    std::unordered_map<T, int> find;

    map& operator=(const map& new_val) {
		for(int i=0; i<new_val; i++) {
            set(i, new_val);
            /*
			value[i] = new_val[i];
			lookup[value[i]] = i;
            hash[value] = i;
            */
		}
	}

    virtual int insert(const T& val) override {
        int key = array<T>::insert(val);
        find[val] = key;
        return key;
    }

    virtual void set(int key, T& val) override {
        array<T>::set(key, val);
        find[val] = key;
	}

    virtual void remove(int key) override {
        T val;
        array<T>::remove(key);
        find.erase(val);
    }

    virtual void clear() {  
        array<T>::clear();
        find.clear();
        find.rehash(0); // similar to shrink_to_fit() in vectors, to free up memory
        /*
        // similar to shrink_to_fit() in vectors, to free up memory swapping to a temporary set. This works because the temporary array allocates the current size of original set which is empty.
        std::unordered_set<T>(find.begin(), find.end()).swap(find);
        */
    }

    /*
    virtual int hash(T& object) {
        std::hash(*object)
    }*/

};

}
