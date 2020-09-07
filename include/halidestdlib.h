#ifndef __HALIDE_STD_LIB
#define __HALIDE_STD_LIB

namespace hldstd {
	int stringCompare(char *, char *);
	int stringLength(char *);
	char *to_string(int);
	char *to_string(double);

	int to_int(char *str);
	double to_double(char *str);
	bool to_bool(char *str);

	namespace math {
		double pow(double x, int y); // x^y
		int abs(int x); // |x|
	} // namespace math

} // namespace hldstd

#endif