#include "Exception_InputOutputException.h"
#include <iostream>

class FileNotFoundException : public InputOutputException {
       static const char* MESSAGE = "The file '%s' could not be found.";
       char* completeMessage;

public:
        FileNotFoundException(char* filename) {
            sprintf(completeMessage, MESSAGE, filename);
        }

        ~FileNotFoundException() {
                delete[] completeMessage;
        }

        virtual const char* what() const throw() {
                return this->completeMessage;
        }
};
