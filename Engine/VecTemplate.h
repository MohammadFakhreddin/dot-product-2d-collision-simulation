#pragma once
template <typename T>
class _Vec {
private:
	T x;
	T y;
public:
	_Vec(T x, T y)
		:
		x(x),
		y(y)
	{}
	const T getX() const {
		return this->x;
	};
	const T getY() const {
		return this->y;
	};
	void setX(T x) {
		this->x = x;
	}
	void setY(T y) {
		this->y = y;
	}
	const double size() const {
		return sqrt(this->x * this->x + this->y * this->y);
	}
	_Vec<double> hat() {
		const double size = this->size();
		return _Vec<double>(double(this->x) / size, double(this->y) / size);
	}
	_Vec& operator+=(const _Vec<T>& rhs) {
		this->x += rhs.getX();
		this->y += rhs.getY();
		return *this;
	}
	_Vec<T> operator+(const _Vec<T>& rhs) {
		return _Vec<T>(this->x + rhs.getX(), this->y + rhs.getY());
	}
	_Vec<T> operator-(const _Vec<T>& rhs) const {
		return _Vec<T>(this->x - rhs.getX(), this->y - rhs.getY());
	}
	double operator*(const _Vec<T>& rhs) {
		return double(this->x) * double(rhs.getX()) + double(this->y) * double(rhs.getY());
	}
	_Vec<T> & operator*(const int value) {
		this->x *= value;
		this->y *= value;
		return *this;
	}
	_Vec<T>& operator=(const _Vec<T>& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	template <typename A>
	explicit operator _Vec<A>() const {
		return _Vec<A>(A(this->x), A(this->y));
	}
};

using VecInt = _Vec<int>;
using VecFloat = _Vec<float>;
using VecDouble = _Vec<double>;

