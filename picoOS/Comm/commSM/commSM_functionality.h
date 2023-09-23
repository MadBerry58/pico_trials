#ifndef COMM_SM_FUNCTIONALITY_H
#define COMM_SM_FUNCTIONALITY_H

#include "../../SystemServices/ErrorHandling/ErrorCodes.h"

bool messageReceived    (void);
bool readDataAvailable  (void);
bool sendingRequested   (void);
bool readingError       (void);
bool writeDataLeft      (void);
bool writingError       (void);
bool notifyHost         (void);
bool writeData          (void);
bool readData           (void);
bool readData           (void);

bool processRequest     (uint8_t);


#endif