#ifndef __HALIDE_STD_LIB
#define __HALIDE_STD_LIB

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
		char *c_ptr();
		int to_int();
		double to_double();

		bool operator==(const string &other);

		~string();
	};

	int stringCompare(char *, char *);
	int stringLength(char *);

	namespace math {
		double pow(double x, int y); // x^y
		int abs(int x);				 // |x|
	}								 // namespace math

} // namespace hldstd

#endif