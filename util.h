#ifndef UTIL_H_INC
#define UTIL_H_INC

//need std::forward
#include <utility>
//need std::unique_ptr
#include <memory>

namespace util { //keep everything from polluting global namespace

//the motivation behind the next struct is to be able to bind a function
//to a type so that we can make a function type T such that sizeof(T)
//is 0, but we can call instances of T and have them call the correct
//function.  This is done in order to make custom deleters for
//std::unique_ptr without having to go through all of the boilerplate
//to define a deleter

//this outer struct is necessary to have a named scope for stateless,
//as we need to be able to take an instance of ref and therefore must
//know it's type beforehand.
template <class T, class ...Args>
struct func {
	typedef T(&ref)(Args...);
	typedef T(*ptr)(Args...);
	
	template <ref Func>
	struct bind {
		//can't re-use args as in this scope Args is not considered
		//a dependent type and thus doesn't follow reference collapsing
		template <class ...NewArgs>
		T operator()(NewArgs&&... args) {
			return Func(std::forward<NewArgs>(args)...);
		}
	};
};

//this is an alias of of the above Func is a deleter for a
//std::unique_ptr<T>
template <class T>
using deleter = func<void, T*>;

//hence the motivation: sizeof(deleter<T>::bind<foo>) == 0, where
//decltype(foo) == void(&)(T*).  However, sizeof(void(&)(T*)) > 0
//(on a modern amd64 computer, 8).  Therefore:
//	sizeof(std::unique_ptr<T, foo>) == 16 (on amd64)
//	sizeof(std::unique_ptr<T, deleter<T>::bind<foo>>) == sizeof(T*) == 8

} //end namespace

//here's a quick pointer class which is used so that functions can take
//either a T* or a std::unique_ptr<T, U>
template <class T>
class Pointer {
private:
	T * ptr;
public:
	Pointer() : ptr(nullptr) {}
	Pointer(T* t) : ptr(t) {}
	template <class U>
	Pointer(const std::unique_ptr<T, U>& p) : ptr(p.get()) {}
	T& operator*() {
		return *ptr;
	}
	const T& operator*() const {
		return *ptr;
	}
	T* operator->() {
		return ptr;
	}
	const T* operator->() const {
		return ptr;
	}
};

#endif
