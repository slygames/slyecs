#pragma once

#include <vector>
//#include <algorithm> // for vector.find()

/**
 * sly::array is optimized for fast lookup by key and fast iteration and all other operations are very fast, except find is at normal vector find() speed and remove() does a swapping mechanism which is much faster than vectors do.
 */

namespace sly {

template <typename T>
class array {

protected:
	std::vector<T> value;
	std::vector<uint32_t> lookup;	// keys are the indices of the values in the value array, at the same positions as the value array, a key of 5 points to the this is used to quickly look things up.
	
public:
	array() = default;

	array& operator=(const array& new_val) {
		for(uint32_t i=0; i<new_val; i++) {
			value[i] = new_val[i];
			lookup[value[i]] = i;
		}
	}
/*
	const T& operator[](uint32_t key) const & {
		return value[lookup[key]];
	}

	T& operator[](uint32_t key) & {
		return value[lookup[key]];
	}

	// this doesn't work, so can't do []= to assign values
	T&& operator[](uint32_t key) && {
        return std::move(value[lookup[key]]);
    }
*/
	// get the value array
	std::vector<T> get_data() {
		return value;
	}

	// get a value by key (or use [] operator
	T get(uint32_t key) {
		return value[lookup[key]];
	}

	// set a value by key (or use []=) operator
	virtual void set(uint32_t key, T& val) {
		value[key] = val;
	}

	virtual uint32_t insert(T& val) {
		value.push_back(val);
		uint32_t new_index = size()-1;
		lookup.push_back(new_index);
		return new_index; // return index of added element
	}

	virtual void remove(uint32_t key) {
		uint32_t lastkey = value.size()-1;
		lookup[key] = -1; // disable in lookup by setting to -1
		lookup[lastkey] = key; // swap keys
		swap(key, lastkey);	// swap value at key index with last item value
		resize(lastkey); // remove last swapped item (key value)
	}

	virtual void clear() {
		value.clear();
		value.shrink_to_fit();
		lookup.clear();
		lookup.shrink_to_fit();
	}

	/*
	// regular vector::find(), so its linear O(n) but this array class is optimized for lookup by key and fast iteration, rather than lookup by value, so that's okay.
	uint32_t find(T val) {
		uint32_t found_key = std::find(value.begin(), value.end(), val) != value.end();
		return found_key;
	}*/

	/*
	uint32_t find(T val) {
		hash(val)]
	}*/

	uint32_t size() {
		return value.size();
	}

	// using vector iterator
	explicit array(std::initializer_list<T> init) : value(init) {}

	using iterator = typename std::vector<T>::iterator;

	using const_iterator = typename std::vector<T>::const_iterator;

	iterator begin()
	{
		return value.begin();
	} 

	iterator end()
	{
		return value.end();
	} 

	const_iterator cbegin() const
	{
		return value.cbegin();
	} 

	const_iterator cend() const
	{
		return value.cend();
	}


private:

	// swaps two keys, used for removing values quickly by swapping value with the last item and setting keys the lookup table
	void swap(uint32_t a_key,uint32_t b_key) {
		T val_old = value[a_key]; // cache current value at this index
		value[a_key] = value[b_key];	// replace current value with last value
		value[a_key] = val_old; // replace last value with cached value
	}

	void resize(uint32_t new_size) {
		new_size = new_size < value.size() ? new_size : value.size();
		value.resize(new_size);
	}

};

}
