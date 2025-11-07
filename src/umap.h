#pragma once

#include "slyarray.h"
#include <unordered_map>

namespace sly {

template <typename T>
class umap : public array<T> {
public:

    std::unordered_map<T, int> find;

    umap& operator=(const umap& new_val) {
		for(int i=0; i<new_val; i++) {
            set(i, new_val);
            /*
			value[i] = new_val[i];
			lookup[value[i]] = i;
            hash[value] = i;
            */
		}
	}

    virtual int insert(T& val) override {
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

};

}
