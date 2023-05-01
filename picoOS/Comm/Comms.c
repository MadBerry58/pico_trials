#include "Comms.h"
#define currentAdress 0b0001001

int Comms_init()
{
#if COMM_TYPE COMM_I2C
	i2c_init(i2c_default, 100 * 1000);
    i2c_set_slave_mode(i2c_default, true, currentAdress);
    
#elif COMM_TYPE COMM_CAN
    can_init();
    //check if the data frames are up to date
#else
 #error "NO COMM INTERFACE SPECIFIED"
#endif
}

int readMessage(uint8_t sourceBusAdress, uint8_t *messageBuffer, size_t messageLength)
{

#if COMM_TYPE COMM_I2C
    i2c_read_blocking(i2c_default, sourceBusAdress, messageBuffer, 6, false);  // false - finished with bus
#elif COMM_TYPE COMM_CAN
    can_read_blocking(can_default, sourceBusAdress, messageBuffer, 6, false);  // false - finished with bus
#else
 #error "NO COMM INTERFACE SPECIFIED"
#endif

}

int sendMessage(uint8_t destinationBusAdress, uint8_t *messageBuffer, size_t messageLength)
{
#if COMM_TYPE COMM_I2C
    i2c_set_slave_mode(i2c_default, false, currentAdress); 
    i2c_write_blocking(i2c_default, destinationBusAdress, messageBuffer, messageLength, false); // false - finished with bus
    i2c_set_slave_mode(i2c_default, true, currentAdress);
#elif COMM_TYPE COMM_CAN
    can_write_blocking(can_default, destinationBusAdress, messageBuffer, messageLength, false); // false - finished with bus
#else
 #error "NO COMM INTERFACE SPECIFIED"
#endif
}