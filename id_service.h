 
#ifndef FPID_SERVICE_H__
#define FPID_SERVICE_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"

#define BLE_UUID_FPID_BASE_UUID              {0x23, 0xD1, 0x13, 0xEF, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00} // 128-bit base UUID
#define BLE_UUID_FPID_SERVICE                0xABCD // Just a random, but recognizable value
#define BLE_UUID_FPID_CHARACTERISTC          0xDEED

/**
 * @brief This structure contains various status information for our service. 
 * It only holds one entry now, but will be populated with more items as we go.
 * The name is based on the naming convention used in Nordic's SDKs. 
 * 'ble indicates that it is a Bluetooth Low Energy relevant structure and 
 * os is short for Our Service). 
 */
typedef struct
{
    uint16_t    conn_handle;        /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection).*/
    uint16_t    service_handle;     /**< Handle of ID Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t    char_handles;
    uint32_t    fpid_values[8];

}ble_fpid_t;




/**@brief Function for initializing our new service.
 *
 * @param[in]   p_id_service       Pointer to ID Service structure.
 */
void fpid_service_init(ble_fpid_t *p_fpid_service);



/**@brief Function for handling BLE Stack events related to our service and characteristic.
 *
 * @details Handles all events from the BLE stack of interest to fpid Service.
 *
 * @param[in]   p_our_service       Our Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_fpid_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for updating and sending new characteristic values
 *
 * @details The application calls this function whenever our timer_timeout_handler triggers
 *
 * @param[in]   p_our_service                     Our Service structure.
 * @param[in]   characteristic_value     New characteristic value.
 */
void our_temperature_characteristic_update(ble_fpid_t *p_fpid_service, int32_t *temperature_value);




#endif  /* _ FPID_SERVICE_H__ */
