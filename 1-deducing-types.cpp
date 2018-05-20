// There are three rules for type deduction: function templates, auto, and decltype.

template <typename T>
void f(ParamType param);

// To deduce T and ParamType, the compiler looks at the type of the function argument. There are
// three cases:

// 1. ParamType is a pointer or reference, but not a universal reference

// In this case, ignore the reference part (if any) and pattern-match the type against ParamType
// to determine T

template <typename T>
void f(T& param);

int x = 27;             // x is an int
const int cx = x;       // cx is a const int
const int& rx = x;      // rc is a reference to x as a const int

f(x);       // T is int, param is int&
f(cx);      // T is const int, param is const int&
f(rx);      // T is const int, param is const int&

// Note that the reference-ness of rx is ignored to deduce T

template <typename T>
void f(const T& param);

f(x);       // T is int, param is const int&
f(cx);      // T is int, param is const int&
f(rx);      // T is int, param is const int&

// As param is a reference to const, there is no need for const to be deducted as part of T

template <typename T>
void f(T* param);

const int *px = &x;     // px is a ptr to x as a const int

f(&x);      // T is int, param is int*
f(px);      // T is const int, param is const int*

// 2. ParamType is a universal reference

// If expr is an lvalue, both T and ParamType are deduced to be lvalue references. Otherwise, the
// case 1 rules apply.

template <typename T>
void f(T&& param);

f(x);       // x is lvalue, so T is int&, param is int&
f(cx);      // cx is lvalue, so T is const int&, param is const int&
f(rx);      // rx is lvalue, so T is const int&, param is const int&
f(27);      // 27 is rvalue, so T is int, param is int&&

// 3. ParamType is neither a pointer nor a reference

// In this case, param will be a copy when passing by value. If expr is a reference, ignore the
// reference. Also ignore const and volatile.

template <typename T>
void f(T param);

f(x);       // T and param are int
f(cx);      // T and param are int
f(rx);      // T and param are int

// const-ness is ignored as param is a completely new object, a copy.

const char* const ptr = "ptr is const ptr to const object";

f(ptr);     // The pointer itself will be copied. What it points to, the string, is still const.
            // param will be const char*

// Array arguments

// ...