#include "glasses_constants.h"
#include "glasses_location.h"

void add_gnss_characteristics(GlobalsManager* const glob_mgr) {
    BLEService *pService_GNSS = glob_mgr->get_svc(GNSS_SERVICE);

    uint32_t ln_feature_val=LN_FEATURE_LOCATION_SUPPORTED|LN_FEATURE_ELEV_SUPPORTED;

    /*uint8_t gnss_value[28]; // just a test
    for (int i = 0; i<28; i++) {
    gnss_value[i]=i;
    }*/
    glob_mgr->characteristics[GNSS_CHAR] = pService_GNSS->createCharacteristic(
                                        BLEUUID((uint16_t)GNSS_CHAR_UUID),
                                        BLECharacteristic::PROPERTY_NOTIFY|BLECharacteristic::PROPERTY_READ
                                    );
    glob_mgr->characteristics[GNSS_FEATURES_CHAR] = pService_GNSS->createCharacteristic(
                                        BLEUUID((uint16_t)GNSS_FEATURES_CHAR_UUID),
                                        BLECharacteristic::PROPERTY_READ
                                    );
    glob_mgr->characteristics[GNSS_FEATURES_CHAR]->setValue((uint8_t*)&ln_feature_val,sizeof(ln_feature_val));
    // the pCharacteristic_GNSS is a notify field in that a task runs on the esp32 core 1,
    // whenever there's an updated position it sends a notify

}