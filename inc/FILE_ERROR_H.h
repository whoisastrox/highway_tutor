//Alessandro Bonato
#ifndef FILE_ERROR_H
#define FILE_ERROR_H
#include <stdexcept>
using namespace std;
class file_error : public runtime_error {
	private:
		int error_value;
	public:
		file_error(int);
		const char* what() const noexcept;
};

#endif