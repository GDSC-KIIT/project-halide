#include <halidestdlib.h>
#include <utils.h>

// STRING FUNCTIONS

int hldstd::stringLength(char *str) {
	int len = 0;
	while (str[len++])
		;
	return len - 1;
}

int hldstd::stringCompare(char *s1, char *s2) {
	int result = 1;
	int size = hldstd::stringLength(s1);
	if (size != stringLength(s2)) result = 0;
	else {
		int i = 0;
		for (i; i <= size; i++) {
			if (s1[i] != s2[i]) result = 0;
		}
	}
	return result;
}

// STRING CLASS SPECIFICATION

hldstd::string::string(char *str) {
	int len = 0;
	while (str[len++])
		;

	m_size = len; // includes the \0
	m_data = (char *)mem_alloc(m_size);

	for (int i = 0; i < m_size; i++) {
		m_data[i] = str[i];
	}
}

hldstd::string::string(int x) {
	int x_len = 0;
	int t = x;

	while (t != 0) {
		x_len++;
		t = t / 10;
	}

	m_data = (char *)mem_alloc(x_len + 1);
	m_data[x_len] = '\0';

	for (int i = x_len - 1; i >= 0; i--) {
		m_data[i] = (char)48 + x % 10;
		x = x / 10;
	}
}

hldstd::string::string(double x) {}

hldstd::string::string(bool val) {
	if (val) {
		m_size = 5;
		m_data = (char *)mem_alloc(m_size);
		m_data = "true";
	} else {
		m_size = 6;
		m_data = (char *)mem_alloc(m_size);
		m_data = "false";
	}
}

hldstd::string::string(string &other) {
	m_size = other.m_size;

	for (int i = 0; i < m_size; i++) {
		m_data[i] = other.m_data[i];
	}
}

int hldstd::string::size() { return m_size; }

char *hldstd::string::c_ptr() { return m_data; }

int hldstd::string::to_int() {
	int val = 0;

	for (int i = 0; m_data[i] != '\0'; i++) {
		if ((m_data[i] <= 57) && (m_data[i] >= 48)) {
			int t = m_data[i] - 48;
			val = val * 10 + t;
		}
	}

	return val;
}

double hldstd::string::to_double() {
	double int_part = 0;
	double decimal_part = 0;

	int decimal_len = 0;

	bool decimal = false;

	for (int i = 0; m_data[i] != '\0'; i++) {
		if (m_data[i] == '.') {
			decimal = true;
			continue;
		}

		if (decimal) {
			int t = m_data[i] - 48;
			decimal_part = decimal_part * 10 + t;
			decimal_len++;
		} else {
			int t = m_data[i] - 48;
			int_part = int_part * 10 + t;
		}
	}

	decimal_part = decimal_part * hldstd::math::pow(10, -decimal_len);

	return int_part + decimal_part;
}

bool hldstd::string::operator==(const string &other) {
	if (m_size != other.m_size) return false;

	for (int i = 0; i < m_size; i++) {
		if (m_data[i] != other.m_data[i]) return false;
	}

	return true;
}

hldstd::string::~string() { delete[] m_data; }

// MATH FUNCTIONS

double hldstd::math::pow(double x, int y) {
	if (y == 0) return 1.0;

	double ans = 1.0;

	if (y < 0) {
		for (int i = 0; i < -y; i++)
			ans = ans / x;

		return ans;
	} else {
		for (int i = 0; i < y; i++)
			ans *= x;

		return ans;
	}
}

int hldstd::math::abs(int x) {
	if (x < 0) return -x;
	else
		return x;
}