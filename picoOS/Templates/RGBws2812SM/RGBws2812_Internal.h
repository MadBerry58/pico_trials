#include "RGBws2812SM_Types.h"


/* Internal processes */
Error_t init_SM_internals       ();
uint8_t start_timer             ();
uint8_t pattern_checkExisting   ();
uint8_t pattern_set             ();
uint8_t pattern_stop            ();
uint8_t check_for_requests      ();

/* State transition checks */
bool timer_expired              ();
bool previous_pattern           ();

bool request_setPattern         ();
bool request_stopPattern        ();

bool request_startSM            ();
bool request_reinitSM           ();
bool request_stopSM             ();
bool request_resumeSM           ();
/* State Machine communication API */
Error_t setError();
void notifyHost();
