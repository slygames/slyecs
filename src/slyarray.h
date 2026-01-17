#pragma once

#include <vector>
#include <type_traits> // Required for standard type traits. For std::is_arithmetic_v, std::same and type trait checking for overloaded operators to see if godot variable types support an operator before doing any operations like + or - on attributes.
#include <experimental/type_traits> // Required for std::experimental::is_detected (if C++17 is not fully adopted)
#include "util.h"
#include <any> //todo:debugging only
//#include <algorithm> // for vector.find(), not using this anymore, //todo:remove

/**
 * sly::array is optimized for fast lookup by key and fast iteration and all other operations are very fast, except find is at normal vector find() speed and remove() does a swapping mechanism which is much faster than vectors do.
 */

namespace sly {

//todo: should this use int64_t for keys as godot uid is 64 bit int64_t?

enum class OPERATOR : unsigned char {
	PLUS,
	PLUS_EQUAL,
	MINUS,
	MINUS_EQUAL,
	MULTIPLY,
	MULTIPLY_EQUAL,
	DIVIDE,
	DIVIDE_EQUAL,
};

#if 0
/* Attributes use this Bool Enum to store booleans in sly::array because the C++ booleans are bitpacked which is a bit dodgy ('cos can't assign bool values in sly::array easily) so using char instead and this Enum provides an easy way to cast from godot bool to this enum char. */
enum class BOOL : unsigned char {
	TRUE,
	FALSE,
};
#endif


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

	/* returns std::vector<T>::reference instead of T& because booleans return by value otherwise so they can't be assigned values using [] but this returns the correct bool proxy object from the vector and still works like T& for regular types. */
	typename std::vector<T>::reference operator[](int key) & {
		return value[lookup[key]];
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
		return std::vector<T>(value); // need to cast this
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
		//print("INSERT 1 val type ", val.get_type(), " value ", val);
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
		print("value size1 : ", value.size());
		print("size 1 : ", size());
		
		print("+++++INSERT 2 : ", val, " index ", size());

		print("value size2 : ", value.size());
		print("size 2 : ", size());
		
		int new_index = size();
		value.emplace_back(val);

		print("value size3 : ", value.size());
		print("size 3 : ", size());

	/*
		print("value size3 ", value.size());
		print("size 3", size());
*/

		//godot::Variant var(val);
		print("val : ", val);
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
	friend array<U>& operator+ (array<U> lhs,  const V& rhs);

	template <typename U, typename V>
	friend array<U>& operator-= (array<U>& lhs,  const V& rhs);

	template <typename U, typename V>
	friend array<U>& operator- (array<U> lhs,  const V& rhs);

	template <typename U, typename V>
	friend array<U>& operator*= (array<U>& lhs,  const V& rhs);

	template <typename U, typename V>
	friend array<U>& operator* (array<U> lhs,  const V& rhs);

	template <typename U, typename V>
	friend array<U>& operator/= (array<U>& lhs,  const V& rhs);

	template <typename U, typename V>
	friend array<U>& operator/ (array<U> lhs,  const V& rhs);
};

/* Traits checking to see if a variable supports an operator before doing an Attribute operation like add()*/

#if 0
// Detector implementation
namespace detail {
    template <typename AlwaysVoid, typename, typename... Args>
    struct detector : std::false_type {};

    template <typename Op, typename... Args>
    struct detector<std::void_t<Op>, Op, Args...> : std::true_type {};
}

// Define a general utility for checking an operation (provided in the prompt)
// The 'Op' template argument needs to be a template itself (like op_has_plus_t)
template <template <typename...> class Op, typename... Args>
using is_detected = typename detail::detector<void, Op<Args...>, Args...>::type;

// Macro Definition
#define DEFINE_OPERATOR_TRAIT(op_symbol, trait_name) \
    template <typename U, typename V> \
    using op_##trait_name##_t = decltype(std::declval<U>() op_symbol std::declval<V>()); \
    \
    template <typename U, typename V> \
	constexpr bool trait_name##_v = is_detected<op_##trait_name##_t, U, V>::value;
#endif

/* This uses a detector to find the defined operators. Some operators like [] are done seperately using templates because this method doesn't work for those */

namespace detail {
    // You can use a local implementation if std::experimental is not available
    template <typename AlwaysVoid, typename, typename... Args>
    struct detector : std::false_type {};

    template <typename Op, typename... Args>
    struct detector<std::void_t<Op>, Op, Args...> : std::true_type {};
}

// Macro to define a specific operator trait (e.g., HAS_OP_PLUS, HAS_OP_MINUS)
#define DEFINE_OPERATOR_TRAIT(op_symbol, trait_name) \
    template <typename U, typename V> \
    using op_##trait_name##_t = decltype(std::declval<U>() op_symbol std::declval<V>()); \
    \
    template <typename U, typename V> \
    constexpr bool trait_name##_v = std::experimental::is_detected_v<op_##trait_name##_t, U, V>; // Use std::experimental::is_detected_v or your custom 'detail::detector'



// Use the macro to define traits for specific operators:
DEFINE_OPERATOR_TRAIT(+, has_plus)
DEFINE_OPERATOR_TRAIT(+=, has_plus_equal)
DEFINE_OPERATOR_TRAIT(-, has_minus)
DEFINE_OPERATOR_TRAIT(-=, has_minus_equal)
DEFINE_OPERATOR_TRAIT(*, has_multiply)
DEFINE_OPERATOR_TRAIT(*=, has_multiply_equal)
DEFINE_OPERATOR_TRAIT(/, has_divide)
DEFINE_OPERATOR_TRAIT(/=, has_divide_equal)
DEFINE_OPERATOR_TRAIT(==, has_equality)
DEFINE_OPERATOR_TRAIT(<, has_less_than)
DEFINE_OPERATOR_TRAIT(<=, has_less_than_equal)
DEFINE_OPERATOR_TRAIT(>, has_greater_than)
DEFINE_OPERATOR_TRAIT(>=, has_greater_than_equal)
// Add any other binary operators to check for here

/* to check if its an array when doing addition etc. */

// Primary template for the type trait, defaults to false
template <typename T>
struct is_array_specialization : std::false_type {};

// Partial specialization for any type that IS an array<T>
template <typename T>
struct is_array_specialization<array<T>> : std::true_type {};

// Helper variable template for convenience (C++14 onwards)
template <typename T>
constexpr bool is_array_specialization_v = is_array_specialization<T>::value;


/* [] operator trait checking */

// Seperate mechasnism for [] subscript operator 'cos its hard to incorporate into this trait detection

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct has_subscript_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct has_subscript_uv<U, V, std::void_t<decltype(std::declval<U>()[std::declval<V>()])>> : std::true_type {};

// Helper inline constexpr variable (C++17)
template <typename U, typename V>
inline constexpr bool has_subscript_v = has_subscript_uv<U, V>::value;


#if 0
// The detection idiom base templates (standard in C++17 as std::is_detected)
namespace detail {
    template <typename AlwaysVoid, typename, typename... Args>
    struct detector : std::false_type {};
    template <typename Op, typename... Args>
    struct detector<std::void_t<Op>, Op, Args...> : std::true_type {};
}

// Macro to define a specific operator trait (e.g., HAS_OP_PLUS, HAS_OP_MINUS)
#define DEFINE_OPERATOR_TRAIT(op_symbol, trait_name) \
    template <typename U, typename V> \
    using op_##trait_name##_t = decltype(std::declval<U>() op_symbol std::declval<V>()); \
    template <typename U, typename V> \
    constexpr bool trait_name##_v = detail::detector<void, op_##trait_name##_t<U, V>, U, V>::value;

// Use the macro to define traits for specific operators:
DEFINE_OPERATOR_TRAIT(+, has_plus)
DEFINE_OPERATOR_TRAIT(+=, has_plus_equal)
DEFINE_OPERATOR_TRAIT(-, has_minus)
DEFINE_OPERATOR_TRAIT(*, has_multiplication)
DEFINE_OPERATOR_TRAIT(/, has_division)
DEFINE_OPERATOR_TRAIT(==, has_equality)
DEFINE_OPERATOR_TRAIT(<, has_less_than)
// Add any other binary operators to check for here
#endif

#if 0
/* + Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_plus_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_plus_uv<U, V, std::void_t<decltype(std::declval<U>() + std::declval<V>())>> : std::true_type {};

// Helper inline constexpr variable (C++17)
template <typename U, typename V>
inline constexpr bool supports_plus_uv_v = supports_plus_uv<U, V>::value;

/* += Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_plus_equal_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_plus_equal_uv<U, V, std::void_t<decltype(std::declval<U&>() += std::declval<V const&>())>> : std::true_type {};

// Helper inline constexpr variable (C++17)
template <typename U, typename V>
inline constexpr bool supports_plus_equal_uv_v = supports_plus_equal_uv<U, V>::value;

/* - Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_minus_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_minus_uv<U, V, std::void_t<decltype(std::declval<U>() - std::declval<V>())>> : std::true_type {};

// Helper inline constexpr variable (C--17)
template <typename U, typename V>
inline constexpr bool supports_minus_uv_v = supports_minus_uv<U, V>::value;

/* -= Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_minus_equal_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_minus_equal_uv<U, V, std::void_t<decltype(std::declval<U&>() -= std::declval<V const&>())>> : std::true_type {};

// Helper inline constexpr variable (C--17)
template <typename U, typename V>
inline constexpr bool supports_minus_equal_uv_v = supports_minus_equal_uv<U, V>::value;

/* * Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_multiply_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_multiply_uv<U, V, std::void_t<decltype(std::declval<U>() * std::declval<V>())>> : std::true_type {};

// Helper inline constexpr variable (C**17)
template <typename U, typename V>
inline constexpr bool supports_multiply_uv_v = supports_multiply_uv<U, V>::value;

/* *= Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_multiply_equal_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_multiply_equal_uv<U, V, std::void_t<decltype(std::declval<U&>() *= std::declval<V const&>())>> : std::true_type {};

// Helper inline constexpr variable (C**17)
template <typename U, typename V>
inline constexpr bool supports_multiply_equal_uv_v = supports_multiply_equal_uv<U, V>::value;

/* / Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_divide_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_divide_uv<U, V, std::void_t<decltype(std::declval<U>() / std::declval<V>())>> : std::true_type {};

// Helper inline constexpr variable (C//17)
template <typename U, typename V>
inline constexpr bool supports_divide_uv_v = supports_divide_uv<U, V>::value;

/* /= Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_divide_equal_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_divide_equal_uv<U, V, std::void_t<decltype(std::declval<U&>() /= std::declval<V const&>())>> : std::true_type {};

// Helper inline constexpr variable (C//17)
template <typename U, typename V>
inline constexpr bool supports_divide_equal_uv_v = supports_divide_equal_uv<U, V>::value;

/* % Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_modulo_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_modulo_uv<U, V, std::void_t<decltype(std::declval<U>() % std::declval<V>())>> : std::true_type {};

// Helper inline constexpr variable (C%%17)
template <typename U, typename V>
inline constexpr bool supports_modulo_uv_v = supports_modulo_uv<U, V>::value;

/* %= Operator Traits */

// Primary template, defaults to false_type
template <typename U, typename V, typename = void>
struct supports_modulo_equal_uv : std::false_type {};

// Specialization enabled by SFINAE if the expression is valid
template <typename U, typename V>
struct supports_modulo_equal_uv<U, V, std::void_t<decltype(std::declval<U&>() %= std::declval<V const&>())>> : std::true_type {};

// Helper inline constexpr variable (C%%17)
template <typename U, typename V>
inline constexpr bool supports_modulo_equal_uv_v = supports_modulo_equal_uv<U, V>::value;
#endif


/* Operators */

#if 0
template <typename U, typename V>
array<U>& operator+= (array<U>& lhs, const V& rhs) {
	if constexpr (has_plus_equal_v<U, V>) {
		for(int i=0; i<lhs.value.size() ;i++) {
			lhs.value[i] += rhs;
			//operate(PLUS_EQUAL, lhs.value[i], rhs);
		}
	}
	return lhs;

	#if 0
    //lhs._value += rhs._value;
    //return lhs;
	print("array<U> operator+=");
	//array<U> result;

	//constexpr bool is_array = typeid(&lhs) == typeid(array<U>.value[0]);

	//constexpr bool is_arithmetic = std::is_arithmetic_v<U>(lhs.value[0]);

	constexpr bool is_arithmetic_first = std::is_arithmetic_v<U>;
	print("is_arithmetic", is_arithmetic_first);
	
	constexpr bool is_arithmetic_other = std::is_arithmetic_v<V>;
	print("is_arithmetic_other", is_arithmetic_other);

	// supports + operator, both operands are arithmetic (int or float)
	constexpr bool  is_arithmetic = is_arithmetic_first && is_arithmetic_other;

	// supports = operator
	constexpr bool is_assignable = std::is_assignable<U, V>::value;
	print("$ is_assignable", is_assignable);

	constexpr bool has_plus = has_plus_v<U, V>;
	print("$ has addition : ", has_plus);

	constexpr bool has_plus_equal = has_plus_v<U, V>;
	print("$ has_plus_equal : ", has_plus_equal);

	constexpr bool has_minus = has_minus_v<U, V>;
	print("$ has minus : ", has_minus);

	constexpr bool has_subscript = has_subscript_v<U, V>;
	print("$ has subscript : ", has_subscript);

	/*
	if constexpr (has_minus_v<U, V>) {
		print("$ has minus : ", has_minus_v<U, V>);
	}*/


	#if 0
	// supports + operator (e.g. String is not arithmetic but supports + operator, this checks the actual operator support, so its more useful than is_arithmetic to check if an operation can be performed on an attribute)
	constexpr bool has_plus = supports_plus_uv_v<U, V>;
	print("$ has addition : ", has_plus);

	// supports += operator
	constexpr bool has_plus_equal = supports_plus_equal_uv_v<U, V>;
	print("$ has_plus_assign : ", has_plus_equal);
	#endif



	/*
	constexpr bool is_array = std::is_same<decltype(lhs), array<U>>::value;
	print("is_array", is_array);
	*/
/*
	array<U>* lhsptr = dynamic_cast<array<U>*>(&lhs);
	constexpr bool is_array = lhsptr != nullptr;
*/
	if (is_arithmetic) {
		print("Doing Arithmetic..");
		for(int i=0; i<lhs.value.size() ;i++) {
/*
			if(is_array) {
				lhs.value[i] += rhs.value[i];
			} else {
				lhs.value[i] += rhs;
			}
*/
			lhs.value[i] += rhs;
		}
	} else {
		//todo: fix this error messages do not seem necessary and should be about
		if(!is_arithmetic) {
			godot::UtilityFunctions::printerr(typeid(lhs).name(), " Error: First Operand is Not an Arithmetic type.");
		} else if(!is_arithmetic_other) {
			godot::UtilityFunctions::printerr(typeid(rhs).name(), " Error: Second Operand is Not an Arithmetic type.");
		}
	}
	#endif
	return lhs;
}
#endif


/* Performs addition if U and V support this otherwise checks if V can be cast to U and performs casting before calling the same function recursively, which should be able to do the operation. This casting allows for addition of compatible types like int and float with each other. */

template <typename U, typename V>
array<U>& operate(OPERATOR operator_name, array<U>& lhs, const V& rhs) {
	for(int i=0; i<lhs.value.size() ;i++) {
		switch(operator_name) {
			case OPERATOR::PLUS_EQUAL:
				lhs.value[i] = lhs.value[i] + rhs; // using this format instead of "lhs.value[i] += rhs" because vector<bool> reference doesn't support += like a regular bool does, as it uses bitpacking but can do + then = instead of +=
				break;
		}
	}
	return lhs;
}

#if 0
template <typename U, typename V>
array<U>& operator+= (array<U>& lhs, const V& rhs) {
	if constexpr (has_plus_equal_v<U, V>) {
		print("*has_plus true ", typeid(lhs).name(), " and " , typeid(rhs).name());
	} else {
		print("*has_plus false ", typeid(lhs).name(), " and " , typeid(rhs).name());
	}
	if constexpr (has_plus_equal_v<U, V>) {
		printerr("+= operation ", typeid(lhs).name(), " and " , typeid(rhs).name());
		print("*1");
		lhs += rhs;
	} else if constexpr (std::is_constructible_v<U, V>) {
		print("*2");
		printerr("Casting += operation ", typeid(lhs).name(), " and " , typeid(rhs).name());
		lhs += static_cast<U>(rhs);	// cast and call the same operation recursively, as both types are the same so it will work the next time if the type supports the operation. If it fails that's okay too 'cos it will do nothing then just like if the operation wasn't possible to do.
	} else {
		print("*3");
		printerr("Can't perform += operation because ", typeid(lhs).name(), " and " , typeid(rhs).name() ," are incompatible");
	}
	return lhs;
}

template <typename U, typename V>
array<U>& operator+= (array<U>& lhs, const V& rhs) {
	if constexpr (std::is_constructible_v<U, V>) {
		print("&& is constructible ");
		U new_rhs = static_cast<U>(rhs);
		if constexpr (has_plus_equal_v<U, V>) {
			for(int i=0; i<lhs.value.size() ;i++) {
				print("Adding ", lhs.value[i], " + ", rhs);
				lhs.value[i] += new_rhs;
				print("Result ", lhs.value[i]);
			}
			print("&& ADDED");	
		}
	} else {
	    // Handle cases where conversion/addition is not possible (e.g., static_assert or compilation error)
        static_assert(std::is_constructible_v<U, V> || std::is_convertible_v<V, U>, "Incompatible types for operator+=: V must be convertible to U.");
	}

	
	
	if constexpr (has_plus_equal_v<U, V>) {
		for(int i=0; i<lhs.value.size() ;i++) {
			print("Adding ", lhs.value[i], " + ", rhs);
			lhs.value[i] += rhs;
			print("Result ", lhs.value[i]);
		}
		print("&& ADDED");
	} else if constexpr (std::is_convertible_v(U,V)) {
		U new_rhs = (U)rhs;
	}

	return lhs;
	
}

	#endif

template <typename U, typename V>
array<U>& operator+= (array<U>& lhs, const V& rhs) {
	//todo: make this work for arrays or do another function.. how to achieve this so that attribute + attribute does element wise addition for corresponding entity values.
	print("_______");	
	
	//U first_var = lhs.template get_data<U>()[0]; // Tell the compiler get_data is a template uses the template keyword followed by a space

	U first_var = lhs.get_data()[0];

	print("lhs first_var is", first_var);

	print("lhs first_var type is", (godot::String)typeid(first_var).name());

	//print("lhs first_var godot type is", first_var.get_type());

	//print("lhs first_var class is", first_var.get_class());

	//print("lhs is ", typeid(lhs.get_data<typename U>().front()));

	print("rhs is ", rhs.get_type());

	//print("lhs typeid is ", typeid(U).name(), " rhs typeid is : ", typeid(V).name());

	if(rhs.get_type()==godot::Variant::INT) {
		print("rhs is INT ", rhs.get_type());
	}

	if(rhs.get_type()==godot::Variant::FLOAT) {
		print("rhs is FLOAT ", rhs.get_type());
	}

	if(rhs.get_type()==godot::Variant::STRING) {
		print("rhs is STRING ", rhs.get_type());
	}

	if(rhs.get_type()==godot::Variant::STRING_NAME) {
		print("rhs is STRING_NAME ", rhs.get_type());
	}

	if(rhs.get_type()==godot::Variant::OBJECT) {

		godot::Object* obj = rhs.get_validated_object(); // Recommended way to get object safely

        if (obj != nullptr) {
			print("rhs is Variant::OBJECT of class ", obj->get_class());
		}
		
	}

	if constexpr (is_array_specialization_v<V>) {
		print("rhs is sly::array");
		//lhs = operate(PLUS_EQUAL, lhs, rhs);
	} else if constexpr (has_plus_v<U, V> && has_plus_equal_v<U, V>) {
		print("rhs ", rhs.get_type(), " has_plus");
		lhs = operate(OPERATOR::PLUS_EQUAL, lhs, rhs);
	} else if constexpr (std::is_constructible_v<U, V>) {
		print("rhs ", rhs.get_type(), " is_constructible");
		lhs = operate(OPERATOR::PLUS_EQUAL, lhs, static_cast<U>(rhs));
	} else {
		printerr("Can't perform += operation because ", typeid(lhs).name(), " and " , typeid(rhs).name() ," are incompatible for this operation.");
	}
	print("_______");
	return lhs;
}

template <typename U, typename V>
array<U>& operator-= (array<U>& lhs, const V& rhs) {
	if constexpr (has_minus_v<U, V> && has_minus_equal_v<U, V>) {
		lhs = operate(OPERATOR::MINUS_EQUAL, lhs, rhs);
	} else if constexpr (std::is_constructible_v<U, V>) {
		lhs = operate(OPERATOR::MINUS_EQUAL, lhs, static_cast<U>(rhs));
	} else {
		printerr("Can't perform -= operation because ", typeid(lhs).name(), " and " , typeid(rhs).name() ," are incompatible for this operation.");
	}
	return lhs;
}

template <typename U, typename V>
array<U>& operator*= (array<U>& lhs, const V& rhs) {
	if constexpr (has_multiply_v<U, V> && has_multiply_equal_v<U, V>) {
		lhs = operate(OPERATOR::MULTIPLY_EQUAL, lhs, rhs);
	} else if constexpr (std::is_constructible_v<U, V>) {
		lhs = operate(OPERATOR::MULTIPLY_EQUAL, lhs, static_cast<U>(rhs));
	} else {
		printerr("Can't perform *= operation because ", typeid(lhs).name(), " and " , typeid(rhs).name() ," are incompatible for this operation.");
	}
	return lhs;
}

template <typename U, typename V>
array<U>& operator/= (array<U>& lhs, const V& rhs) {
	if constexpr (has_divide_v<U,V> && has_divide_equal_v<U, V>) {
		lhs = operate(OPERATOR::DIVIDE_EQUAL, lhs, rhs);
	} else if constexpr (std::is_constructible_v<U, V>) {
		lhs = operate(OPERATOR::DIVIDE_EQUAL, lhs, static_cast<U>(rhs));
	} else {
		printerr("Can't perform *= operation because ", typeid(lhs).name(), " and " , typeid(rhs).name() ," are incompatible for this operation.");
	}
	return lhs;
}

// lhs is passed by value to + so that it can be modified by += as reference, to return the result without modifying the actual lhs
template <typename U, typename V>
array<U> operator+ (array<U> lhs, const V& rhs) {
	lhs+=rhs;
	return lhs;
}

template <typename U, typename V>
array<U>& operator- (array<U> lhs, const V& rhs) {
	lhs-=rhs;
	return lhs;
}

template <typename U, typename V>
array<U>& operator* (array<U> lhs, const V& rhs) {
	lhs*=rhs;
	return lhs;
}

template <typename U, typename V>
array<U>& operator/ (array<U> lhs, const V& rhs) {
	lhs/=rhs;
	return lhs;
}

#if 0
/* checks if a variable type supports an operator, this works for any godot types etc. then the operation is performed by operate() if it's valid*/
template <typename U, typename V>
bool can_operate (const OPERATOR operator_name, U &lhs, V &rhs) {
	constexpr bool has_minus = has_plus_v<U, V>;
	constexpr bool has_minus_equal = has_plus_equal_v<U, V>;

	bool is_valid = false;
	switch(operator_name) {
		case PLUS:
			is_valid = has_plus;
			break;
		case PLUS_EQUAL:
			is_valid = has_plus_equal;
			break;
		case MINUS:
			is_valid = has_minus;
			break;
		case MINUS_EQUAL:
			is_valid = has_minus_equal;
			break;
	}
	return is_valid;
}

/* Operations like += which pass lhs by reference and store the result in this.*/
template <typename U, typename V>
U& operate (const OPERATOR operator_name, U &lhs, V &rhs) {
	if(can_operate(operator_name, lhs, rhs)) {
		switch(operator_name) {
			case PLUS_EQUAL:
				lhs += rhs;
				break;
			case MINUS_EQUAL:
				lhs -= rhs;
				break;
			case MULTIPLY_EQUAL:
				lhs *= rhs;
				break;
			case DIVIDE_EQUAL:
				lhs /= rhs;
				break;
		}
	}
	return lhs;
}

/* does operations by reference but passes lhs by value so the original lhs isn't modified */
template <typename U, typename V>
U operate_val (const OPERATOR operator_name, U lhs, V &rhs) {
	switch(operator_name) {
		case PLUS:
			operate(PLUS_EQUAL, lhs, rhs);
			break;
		case MINUS:
			operate(MINUS_EQUAL, lhs, rhs);
			break;
		case MULTIPLY:
			operate(MULTIPLY_EQUAL, lhs, rhs);
			break;
		case DIVIDE:
			operate(DIVIDE_EQUAL, lhs, rhs);
			break;
	}
	return lhs;
}
#endif

} // namespace sly
