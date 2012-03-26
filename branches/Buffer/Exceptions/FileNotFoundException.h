#include "InputOutputException.h"
#include <iostream>

class FileNotFoundException : public InputOutputException {
       static const char* MESSAGE_SIZE = "The file '%s' could not be found.";
       char* completeMessage;

public:
        FileNotFoundException(char* filename) {
            sprintf(completeMessage, "The file '%s' could not be found.", filename);
        }

        ~FileNotFoundException() {
                delete[] completeMessage;
        }

        virtual const char* what() const throw() {
                return this->completeMessage;
        }
};
