
#include <stdint.h>
#include <string.h>
#include "id_service.h"
#include "ble_srv_common.h"
#include "app_error.h"
#include "SEGGER_RTT.h"
#include "ble_srv_common.h"


/**@brief Function for adding our new characterstic to "Fpid service"
 *
 * @param[in]   p_fpid_service        Fpid Service structure.
 *
 */
static uint32_t fpid_char_add(ble_fpid_t * p_fpid_service)
{
    uint32_t            err_code;
    ble_uuid_t          char_uuid;
    /*ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
    char_uuid.uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
    APP_ERROR_CHECK(err_code);
    */
    BLE_UUID_BLE_ASSIGN(char_uuid, BLE_UUID_FPID_CHARACTERISTC);

    
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
    char_md.char_props.read = 1;
    char_md.char_props.write = 0;



    
    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));


    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));
    attr_md.vloc        = BLE_GATTS_VLOC_STACK;

	
    
    
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid      = &char_uuid;
    attr_char_value.p_attr_md   = &attr_md;



    
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
    attr_char_value.max_len     = 8;
    attr_char_value.init_len    = 8;
    uint8_t value[8]            = {0x12,0x34,0x56,0x78,0x0a,0x0b,0x0c,0x0d};
    attr_char_value.p_value     = value;


    // OUR_JOB: Step 2.E, Add our new characteristic to the service
    err_code = sd_ble_gatts_characteristic_add(p_fpid_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_fpid_service->char_handles);
    APP_ERROR_CHECK(err_code);


    return NRF_SUCCESS;
}





/**@brief Function for initiating our new service.
 *
 * @param[in]   p_fpid_service        Our Service structure.
 *
 */
void fpid_service_init(ble_fpid_t *p_fpid_service)
{

    uint32_t   err_code;
    ble_uuid_t        service_uuid;
    
    /*ble_uuid128_t     base_uuid = BLE_UUID_FPID_BASE_UUID;
    service_uuid.uuid = BLE_UUID_FPID_SERVICE;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);
    */
    BLE_UUID_BLE_ASSIGN(service_uuid, BLE_UUID_FPID_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                    &service_uuid,
                                    &p_fpid_service->service_handle);
    APP_ERROR_CHECK(err_code);


    
    ble_add_char_params_t add_char_params;
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid            = BLE_UUID_FPID_CHARACTERISTC;
    add_char_params.max_len         = sizeof(uint32_t)*4;
    add_char_params.init_len        = sizeof(uint32_t)*4;
    add_char_params.p_init_value    = (uint8_t*)(p_fpid_service->fpid_values);
    add_char_params.char_props.read = 1;
    add_char_params.read_access     = SEC_OPEN;

    err_code = characteristic_add(p_fpid_service->service_handle, &add_char_params, &(p_fpid_service->char_handles));
    
}



