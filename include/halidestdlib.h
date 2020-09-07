#ifndef __HALIDE_STD_LIB
#define __HALIDE_STD_LIB

namespace hldstd {
	int stringCompare(char *, char *);
	int stringLength(char *);

	int to_int(char *str);
	double to_double(char *str);
	bool to_bool(char *str);

	char* to_string(int);
	char* to_string(float);

	namespace math {
		double pow(double x, int y);
		int abs(int x);
	}

} // namespace hldstd

#endif