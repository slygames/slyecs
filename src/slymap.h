#pragma once

#include "slyarray.h"
#include <unordered_map>

namespace sly {

template <typename T>
class map : public array<T> {
public:

    std::unordered_map<T, int> find;

    map& operator=(const map& new_val) {
		for(uint32_t i=0; i<new_val; i++) {
            set(i, new_val);
            /*
			value[i] = new_val[i];
			lookup[value[i]] = i;
            hash[value] = i;
            */
		}
	}

    virtual uint32_t insert(T& val) override {
        uint32_t key = array<T>::insert(val);
        find[val] = key;
        return key;
    }

    virtual void set(uint32_t key, T& val) override {
        array<T>::set(key, val);
        find[val] = key;
	}

    virtual void remove(uint32_t key) override {
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

};

}
