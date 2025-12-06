#pragma once

#include <vector>
#include <type_traits> // For std::is_arithmetic_v
#include "util.h"
#include <any> //todo:debugging only
//#include <algorithm> // for vector.find(), not using this anymore, //todo:remove

/**
 * sly::array is optimized for fast lookup by key and fast iteration and all other operations are very fast, except find is at normal vector find() speed and remove() does a swapping mechanism which is much faster than vectors do.
 */

namespace sly {

//todo: should this use int64_t for keys as godot uid is 64 bit int64_t?

template <typename T>
class array {

protected:
	std::vector<int> lookup;	// keys are the indices of the values in the value array, at the same positions as the value array, a key of 5 points to the this is used to quickly look things up.
	
public:
	std::vector<T> value;

	array() = default;
	//~array() = default;
/*
	array& operator=(const array& new_val) const {

		for(int i=0; i<new_val.size(); i++) {
			value[i] = new_val[i];
			lookup[value[i]] = i;
		}
		return *this;
	}
*/

    array& operator=(const array& other) {
        if (this!=&other) {	// if not assigning to self
			value = other.value; // std::vector's own assignment operator handles deep copy
			lookup = other.lookup;
        }
        return *this; // enable chained assignments (e.g., obj1 = obj2 = obj3;).
    }



	/*
    MyCustomClass(std::string n, int v) : name(std::move(n)), value(v) {
        std::cout << "MyCustomClass constructor: " << name << ", " << value << std::endl;
    }

    // Copy constructor (optional, but good practice if you manage resources)
    MyCustomClass(const MyCustomClass& other) : name(other.name), value(other.value) {
        std::cout << "MyCustomClass copy constructor: " << name << ", " << value << std::endl;
    }

    // Move constructor (optional, for efficiency)
    MyCustomClass(MyCustomClass&& other) noexcept : name(std::move(other.name)), value(other.value) {
        std::cout << "MyCustomClass move constructor: " << name << ", " << value << std::endl;
    }*/




/*	
	array& operator+(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				value[i] += other.value[i];
			}
		} else {
			if(!is_arithmetic) printerr(typeid(this).name(), " Error: Can't multiply with this type.");
			else if(!is_arithmetic_other) printerr(typeid(other).name(), " Error: Can't multiply with this type.");
		}
	}

	array& operator-(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				value[i] -= other.value[i];
			}
		} else {
			if(!is_arithmetic) printerr(typeid(this).name(), " Error: Can't subtract with this type.");
			else if(!is_arithmetic_other) printerr(typeid(other).name(), " Error: Can't subtract with this type.");
		}
	}

	array& operator*(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				value[i] *= other.value[i];
			}
		} else {
			if(!is_arithmetic) printerr(typeid(this).name(), " Error: Can't multiply with this type.");
			else if(!is_arithmetic_other) printerr(typeid(other).name(), " Error: Can't multiply with this type.");
		}
	}

	array& operator/(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				if(other.value[i]!=0) value[i] /= other.value[i];
			}
		} else {
			if(!is_arithmetic) print_err(typeid(this).name(), " Error: Can't divide with this type.");
			else if(!is_arithmetic_other) print_err(typeid(other).name(), " Error: Can't divide with this type.");
		}
	}
*/

	/*
	array& operator+(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				value[i] += other.value[i];
			}
		} else {
			if(!is_arithmetic) printerr(typeid(this).name(), " Error: Can't multiply with this type.");
			else if(!is_arithmetic_other) printerr(typeid(other).name(), " Error: Can't multiply with this type.");
		}
	}*/

	/*
	array& operator-(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				value[i] -= other.value[i];
			}
		} else {
			if(!is_arithmetic) printerr(typeid(this).name(), " Error: Can't subtract with this type.");
			else if(!is_arithmetic_other) printerr(typeid(other).name(), " Error: Can't subtract with this type.");
		}
	}

	array& operator*(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				value[i] *= other.value[i];
			}
		} else {
			if(!is_arithmetic) printerr(typeid(this).name(), " Error: Can't multiply with this type.");
			else if(!is_arithmetic_other) printerr(typeid(other).name(), " Error: Can't multiply with this type.");
		}
	}

	array& operator/(const array& other) const {
		constexpr bool is_arithmetic = std::is_arithmetic_v<T>(value[0]);
		constexpr bool is_arithmetic_other = std::is_arithmetic_v<T>(other.value[0]);

		if (is_arithmetic && is_arithmetic_other) {
			for(int i=0; i<value.size() ;i++) {
				if(other.value[i]!=0) value[i] /= other.value[i];
			}
		} else {
			if(!is_arithmetic) print_err(typeid(this).name(), " Error: Can't divide with this type.");
			else if(!is_arithmetic_other) print_err(typeid(other).name(), " Error: Can't divide with this type.");
		}
	}
*/

	const T& operator[](int key) const & {
		const T& val = value[lookup[key]];
		return val;
	}

	T& operator[](int key) & {
		int index = lookup[key];
		T& val = value[index];
		return val;
	}

	/*
	std::vector<bool>::reference operator[](int key) & {
		int index = lookup[key];
		T val = value[index];
		return val;
	}*/
	/*
	T operator[](int key) {
		T val = value.at(lookup.at(key));
		return val;
	}*/
/*
	// this doesn't work, so can't do []= to assign values
	T&& operator[](int key) && {
        return std::move(value[lookup[key]]);
    }
*/
	// get the value array
	std::vector<T> get_data() {
		return value;
	}
/*
	// get a value by key (or use [] operator
	T get(int key) {
		return value[lookup[key]];
	}
*/
/*
	T& get(int key) & {
		return value[lookup[key]];
	}
*/

	T get(int key) {
		if (key > 0 && key < lookup.size()) {
			return value[lookup[key]];
		}
		return T();
	}

	const T get(int key) const {
		if (key > 0 && key < lookup.size()) {
			return value[lookup[key]];
		}
		return T();
	}

/*

	T get(int key) const {
		return value[lookup[key]];
	}

	T& get(int key) & {
		return value[lookup[key]];
	}


	const T& get(int key) const & {
		return value[lookup[key]];
	}
*/
	// set a value by key (or use []=) operator
	virtual void set(int key, const T& val) {
		value[key] = val;
	}

	virtual int insert(const T& val) {
		print("INSERT 1");
		/*
		auto var0 = val;//todo: testing only
		godot::Variant var3 = var0;//todo: testing only
		auto cast_var = std::any_cast<T>(val); //todo: testing only
		godot::Variant var(cast_var);//todo: testing only
		*/
		//godot::Variant var = val;
		//print("cast_var ", var); 
		//var = (Variant)cast_var;
		//var = val; //todo: testing only
		//print("Inserting variant val ", var);
		print("value size1 ", value.size());
		print("size 1", size());
		
		print("value size2 ", value.size());
		print("size 2", size());
		print("INSERT 2");
		
		int new_index = size();
		value.emplace_back(val);

		//godot::Variant var(val);
		print("val ", val);
		//print("val ", val);

		/*
		T newval = std::any_cast<T>(value[new_index]); //todo:remove
		godot::Variant var2(newval);//todo:remove
		*/
		
		//print("newval ", Variant(val));
		
		//var = newval; //todo:remove
		//print("Inserted val2 ", var);
		//print("index ", new_index);
		print("INSERT 3");
		print("lookup size1 ", lookup.size());
		lookup.emplace_back(new_index);
		print("new index ", new_index);
		print("lookup size2 ", lookup.size());
		print("INSERT 4");
		return new_index; // return index of added element
	}

	virtual void remove_key(int key) {
		int lastkey = value.size()-1;
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

	bool empty() const {
		return value.empty();
	}

	/*
	// regular vector::find(), so its linear O(n) but this array class is optimized for lookup by key and fast iteration, rather than lookup by value, so that's okay.
	int find(T val) {
		int found_key = std::find(value.begin(), value.end(), val) != value.end();
		return found_key;
	}*/

	/*
	int find(T val) {
		hash(val)]
	}*/

	size_t size() const {
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
	void swap(int a_key,int b_key) {
		T val_old = value[a_key]; // cache current value at this index
		value[a_key] = value[b_key];	// replace current value with last value
		value[a_key] = val_old; // replace last value with cached value
	}

	void resize(int new_size) {
		new_size = new_size < value.size() ? new_size : value.size();
		value.resize(new_size);
	}

	template <typename U, typename V>
	friend array<U>& operator+= (array<U>& lhs,  const V& rhs);

	template <typename U, typename V>
	friend array<U>& operator+ (array<U>& lhs,  const V& rhs);
};

template <typename U, typename V>
array<U>& operator+= (array<U>& lhs, const V& rhs) {
    //lhs._value += rhs._value;
    //return lhs;

	array<U> result;

	//constexpr bool is_array = type_id(&lhs) == type_id(array<U>);

	constexpr bool is_arithmetic = std::is_arithmetic_v<U>(lhs.value[0]);
	constexpr bool is_arithmetic_other = std::is_arithmetic_v<U>(rhs.value[0]);

	array<U>* lhsptr = dynamic_cast<array<U>*>(&lhs);
	constexpr bool is_array = lhsptr != nullptr;

	if (is_arithmetic && is_arithmetic_other) {
		for(int i=0; i<lhs.value.size() ;i++) {
			if(is_array) result.value[i] = lhs.value[i] + rhs.value[i];
			else lhs.value[i] += rhs;
		}
	} else {
		if(!is_arithmetic) godot::UtilityFunctions::printerr(typeid(lhs).name(), " Error: Can't multiply with this type.");
		else if(!is_arithmetic_other) godot::UtilityFunctions::printerr(typeid(rhs).name(), " Error: Can't multiply with this type.");
	}

	return result;
} 

template <typename U, typename V>
array<U>& operator+ (array<U>& lhs, const V& rhs) {
	lhs += rhs; // Utilize the += operator for efficiency
	return lhs;
}

} // namespace sly
