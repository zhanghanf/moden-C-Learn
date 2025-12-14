#pragma once
#include<cstdio>
template<typename T>
class SimpleiUniquePoint
{
public:
	SimpleiUniquePoint() = default;
	explicit SimpleiUniquePoint(T* p):ptr(p){}
	~SimpleiUniquePoint() {
		if (ptr) { delete ptr; ptr = nullptr; }
	}
	SimpleiUniquePoint& operator=(const SimpleiUniquePoint&) = delete;
	SimpleiUniquePoint(const SimpleiUniquePoint&) = delete;
	SimpleiUniquePoint(SimpleiUniquePoint&& other) noexcept :ptr(other.ptr) {
		other.ptr = nullptr;
	}
	SimpleiUniquePoint& operator=(SimpleiUniquePoint&& other) noexcept {
		if (this != &other) {
			if (ptr) { delete ptr; ptr = nullptr; }
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}
	T& operator*() {
		return *ptr;
	}
	T*get() {
		return ptr;
	}
private:
	T* ptr;
};

