#include <halidestdlib.h>

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

int hldstd::to_int(char *str) {
	int val = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if ((str[i] <= 57) && (str[i] >= 48)) {
			int t = str[i] - 48;
			val = val * 10 + t;
		}
	}

	return val;
}

double hldstd::to_double(char *str) {
	double int_part = 0;
	double decimal_part = 0;

	int decimal_len = 0;

	bool decimal = false;
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '.') {
			decimal = true;
			continue;
		}

		if (decimal) {
			int t = str[i] - 48;
			decimal_part = decimal_part * 10 + t;
			decimal_len++;
		} else {
			int t = str[i] - 48;
			int_part = int_part * 10 + t;
		}
	}

	decimal_part = decimal_part * hldstd::math::pow(10, -decimal_len);

	return int_part+decimal_part;
}

bool hldstd::to_bool(char *str) { return (bool)hldstd::stringCompare(str, "true"); }

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