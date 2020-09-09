#ifndef __HALIDE_STD_LIB
#define __HALIDE_STD_LIB

#include <utils.h>
namespace hldstd {
	class string {
	private:
		char *m_data = nullptr;
		int m_size = 0;

	public:
		string(int x);
		string(double x, int digits_after_point);
		string(char *str);
		string(bool val);
		string(string &other);

		int size();
		char at(int i);
		char *c_ptr();
		int to_int();
		double to_double();

		~string();
	};

	template <typename T> class stack {
	private:
		int m_size;
		T *stack_arr = nullptr;
		int m_top = 0;

	public:
		stack(int size, T x);

		bool pop();		// false for underflow, true for successful pop
		bool push(T x); // false for overflow, true for successful push
		T top();
		bool isEmpty();
	};

	int stringCompare(char *, char *);
	int stringLength(char *);

	namespace math {
		double pow(double x, int y); // x^y
		int abs(int x);				 // |x|
	}								 // namespace math

} // namespace hldstd

// STACK ABSTRACTION
// Template declaration and definition need to be in the same translation unit,
// Don't move these to another file

template <typename T> hldstd::stack<T>::stack(int size, T x) {
	hldstd::stack<T>::m_size = size;
	stack_arr = (T*) mem_alloc(sizeof(T) * m_size);
	stack_arr[0] = x;
}

template <typename T> bool hldstd::stack<T>::pop() { // false for underflow, true for successful pop
	if (m_top == 0) return false;
	else {
		stack_arr[m_top] = 0;
		m_top--;
		return true;
	}
}

template <typename T> bool hldstd::stack<T>::push(T x) { // false for overflow, true for successful push
	if (m_top + 1 == m_size) return false;
	else {
		m_top++;
		stack_arr[m_top] = x;
		return true;
	}
}

template <typename T> T hldstd::stack<T>::top() { return stack_arr[m_top]; }

template <typename T> bool hldstd::stack<T>::isEmpty() { return m_top == 0; }

#endif