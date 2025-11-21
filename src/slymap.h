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

    map& operator=(const map& other) {
        array<T>::operator=(other); // parent =
        if (this!=&other) {	// if not assigning to self
            for(int i=0; i<other; i++) {
                set(i, other);
            }
        }
        return *this;
	}

    bool has(const T& val) const {
        return (bool)find.count(val); // count returns number of occurrences of a key but for a map this will be either 0 or 1
    }

    virtual int insert(const T& val) override {
        // check if val exists then do not insert, as maps can only have unique items
        if(has(val)) return -1;
        // value doesn't exist so insert into map
        int key = array<T>::insert(val);
        find[val] = key;
        return key;
    }

    virtual void set(int key, const T& val) override {
        array<T>::set(key, val);
        find[val] = key;
	}

    virtual void remove_key(int key) override {
        T val = array<T>::get(key);
        array<T>::remove_key(key);
        find.erase(val);
    }

    void remove(const T& val) {
        int key = find[val];
        remove_key(key);
    }

    /*
    findget(T& val) {

    }*/

    virtual void clear() {  
        array<T>::clear();
        find.clear();
        find.rehash(0); // similar to shrink_to_fit() in vectors, to free up memory
        /*
        // similar to shrink_to_fit() in vectors, to free up memory swapping to a temporary set. This works because the temporary array allocates the current size of original set which is empty.
        std::unordered_set<T>(find.begin(), find.end()).swap(find);
        */
    }

	// removes any entries which aren't also present in the other array
	map& intersect(map& other) {
		for(int i=0;i<array<T>::size();i++) {
			if(!other.find[array<T>::value[i]]) {
				remove_key(i);
			}
		}
        return *this;
	}

    /*
    virtual int hash(T& object) {
        std::hash(*object)
    }*/

};

}
