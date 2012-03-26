#include <exception>
class InputOutputException : public std::exception {
public:
        virtual const char* what() const throw() {
                return "A general input/output error has occurred.";
        }
};

