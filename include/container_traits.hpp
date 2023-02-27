#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <stack>
#include <queue>
#include <deque>

// ==========Container Traits==========
template<typename T>
struct is_container_helper {
  template<typename C> static char test(typename C::iterator*);
  template<typename C> static long test(...);
public:
  static const bool value = sizeof(test<T>(0)) == sizeof(char) &&
                            std::is_same_v<decltype(*std::declval<T>().begin()), typename T::value_type&>;
};

template<typename T>
using is_container = std::integral_constant<bool, is_container_helper<T>::value>;

// checks if vector
template<typename T> 
struct is_vector : std::false_type {};

template<typename T, typename Alloc>
struct is_vector<std::vector<T, Alloc>> : std::true_type {};

// checks if set
template<typename T> 
struct is_set : std::false_type {};

template<typename... Ts>
struct is_set<std::set<Ts...>> : std::true_type {};

template<typename... Ts>
struct is_set<std::unordered_set<Ts...>> : std::true_type {};

template<typename T>
inline constexpr bool is_set_v = is_set<T>::value;

// checks if map
template<typename T> 
struct is_map : std::false_type {};

template<typename... Ts>
struct is_map<std::map<Ts...>> : std::true_type {};

template<typename... Ts>
struct is_map<std::unordered_map<Ts...>> : std::true_type {};

template<typename T>
inline constexpr bool is_map_v = is_map<T>::value;

// checks if list
template<typename T> 
struct is_list : std::false_type {};

template<typename T, typename Alloc>
struct is_list<std::list<T, Alloc>> : std::true_type {};

template<typename T>
inline constexpr bool is_list_v = is_list<T>::value;

// checks if deque
template<typename T> 
struct is_deque : std::false_type {};

template<typename... Ts>
struct is_deque<std::deque<Ts...>> : std::true_type {};

template<typename T>
inline constexpr bool is_deque_v = is_deque<T>::value;

// check if stack
template<typename T> 
struct is_stack : std::false_type {};

template<typename... Ts>
struct is_stack<std::stack<Ts...>> : std::true_type {};

template<typename T>
inline constexpr bool is_stack_v = is_stack<T>::value;

// check if queue
template<typename T>
struct is_queue : std::false_type {};

template<typename... Ts>
struct is_queue<std::queue<Ts...>> : std::true_type {};

template<typename... Ts>
struct is_queue<std::priority_queue<Ts...>> : std::true_type {};

template<typename T>
inline constexpr bool is_queue_v = is_queue<T>::value;

template<typename T>
inline constexpr bool is_container_v = is_container<T>::value || is_vector<T>::value || is_set<T>::value || is_map<T>::value || 
                                        is_list<T>::value || is_stack<T>::value || is_deque<T>::value || is_queue<T>::value;
// ==========Container Traits==========

// ==========Container Dimensions==========
template<typename T>
struct is_multidimensional : std::false_type {};

template<typename T>
struct dimensions_of {
    static constexpr int value = 0;
};

template<typename T>
struct dimensions_of<T*> {
    static constexpr int value = dimensions_of<T>::value + 1;
};

template<typename T, std::size_t N>
struct dimensions_of<T[N]> {
    static constexpr int value = dimensions_of<T>::value + 1;
};

template<typename T, typename Alloc>
struct dimensions_of<std::vector<T, Alloc>> {
    static constexpr int value = dimensions_of<T>::value + 1;
};

template<typename T, typename Alloc>
struct dimensions_of<std::set<T, Alloc>> {
    static constexpr int value = dimensions_of<T>::value + 1;
};

template<typename Key, typename Value, typename... Args>
struct dimensions_of<std::map<Key, Value, Args...>> {
static constexpr int value = dimensions_of<Value>::value + 1;
};

template<typename Key, typename Hash, typename KeyEqual, typename... Args>
struct dimensions_of<std::unordered_set<Key, Hash, KeyEqual, Args...>> {
static constexpr int value = dimensions_of<Key>::value + 1;
};

template<typename Key, typename Value, typename Hash, typename KeyEqual, typename... Args>
struct dimensions_of<std::unordered_map<Key, Value, Hash, KeyEqual, Args...>> {
static constexpr int value = dimensions_of<Value>::value + 1;
};

template<typename T, typename Alloc>
struct dimensions_of<std::list<T, Alloc>> {
    static constexpr int value = dimensions_of<T>::value + 1;
};

template<typename T, typename Container>
struct dimensions_of<std::stack<T, Container>> {
    static constexpr int value = dimensions_of<Container>::value;
};

template<typename T, typename Container>
struct dimensions_of<std::queue<T, Container>> {
    static constexpr int value = dimensions_of<Container>::value;
};

template<typename T, typename Container>
struct dimensions_of<std::deque<T, Container>> {
    static constexpr int value = dimensions_of<Container>::value + 1;
};

template<typename T>
inline constexpr int dimensions_of_v = dimensions_of<T>::value;

template<typename T>
inline constexpr bool is_multidimensional_v = is_multidimensional<T>::value || dimensions_of_v<T> > 1;
// ==========Container Dimensions==========

// ==========Type Checking==========
template<typename T>
constexpr bool isContainer(const T& container) 
{
    return is_container<T>::value;
}

template<typename T>
constexpr bool isVector(const T& vec)
{
    return is_vector<T>::value;
}

template<typename T>
constexpr bool isMap(const T& m)
{
    return is_map<T>::value;
}

template<typename T>
constexpr bool isSet(const T& s)
{
    return is_set<T>::value;
}

template<typename T>
constexpr bool isList(const T& l)
{
    return is_list<T>::value;
}

template<typename T>
constexpr bool isStack(const T& s)
{
    return is_stack<T>::value;
}

template<typename T>
constexpr bool isDeque(const T& d)
{
    return is_deque<T>::value;
}

template<typename T>
constexpr bool isQueue(const T& q)
{
    return is_queue<T>::value;
}

template<typename T>
int getDimensions(const T& container) 
{
    return dimensions_of<T>::value;
}
// ==========Type Checking==========