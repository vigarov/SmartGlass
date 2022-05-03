#pragma once

#include "glasses_globals_manager.h"

#define LOCATION_DATA_FLAGS_INST_SPEED_PRESENT 1
#define LOCATION_DATA_FLAGS_TOTAL_DIST_PRESENT (1<<1)
#define LOCATION_DATA_FLAGS_LOCATION_PRESENT (1<<2)
#define LOCATION_DATA_FLAGS_ELEV_PRESENT (1<<3)
#define LOCATION_DATA_FLAGS_HEADING_PRESENT (1<<4)
#define LOCATION_DATA_FLAGS_ROLL_TIME_PRESENT (1<<5)
#define LOCATION_DATA_FLAGS_UTC_TIME_PRESENT (1<<6)
#define LOCATION_DATA_FLAGS_POS_STATUS_NO_POS (0<<7)
#define LOCATION_DATA_FLAGS_POS_STATUS_POS_OK (1<<7)
#define LOCATION_DATA_FLAGS_POS_STATUS_EST_POS (2<<7)
#define LOCATION_DATA_FLAGS_POS_STATUS_LAST_KNOWN_POS (3<<7)
#define LOCATION_DATA_FLAGS_SPEED_DIST_FORM_2D (0<<9)
#define LOCATION_DATA_FLAGS_SPEED_DIST_FORM_3D (1<<9)
#define LOCATION_DATA_FLAGS_ELEV_POS (1<<10)
#define LOCATION_DATA_FLAGS_ELEV_BAROM (1<<10)
#define LOCATION_DATA_FLAGS_ELEV_DB (2<<10)
#define LOCATION_DATA_FLAGS_ELEV_OTHER (3<<10)
#define LOCATION_DATA_FLAGS_HEADING_MOVE (0<<11)
#define LOCATION_DATA_FLAGS_HEADING_COMPASS (1<<11)

#define LN_FEATURE_INST_SPEED_SUPPORTED (1<<0)
#define LN_FEATURE_TOTAL_DIST_SUPPORTED (1<<1)
#define LN_FEATURE_LOCATION_SUPPORTED (1<<2)
#define LN_FEATURE_ELEV_SUPPORTED (1<<3)
#define LN_FEATURE_HEADING_SUPPORTED (1<<4)
#define LN_FEATURE_ROLL_TIME_SUPPORTED (1<<5)
#define LN_FEATURE_UTC_TIME_SUPPORTED (1<<6)
#define LN_FEATURE_REMAIN_DIST_SUPPORTED (1<<7)
#define LN_FEATURE_REMAIN_VDIST_SUPPORTED (1<<8)
#define LN_FEATURE_ETA_SUPPORTED (1<<9)
#define LN_FEATURE_BEACON_SOL_SUPPORTED (1<<10)
#define LN_FEATURE_BEACON_VIEW_SUPPORTED (1<<11)
#define LN_FEATURE_T_TO_FIX_SUPPORTED (1<<12)
#define LN_FEATURE_EST_HORIZ_POS_ERR_SUPPORTED (1<<13)
#define LN_FEATURE_EST_VERT_POS_ERR_SUPPORTED (1<<14)
#define LN_FEATURE_HORIZ_DILUTION_SUPPORTED (1<<15)
#define LN_FEATURE_VERT_DILUTION_SUPPORTED (1<<16)
#define LN_FEATURE_LOC_SPEED_MASK_SUPPORTED (1<<17)
#define LN_FEATURE_FIX_RATE_SUPPORTED (1<<18)
#define LN_FEATURE_ELEV_SET_SUPPORTED (1<<19)
#define LN_FEATURE_POS_STATUS_SUPPORTED (1<<20)

void add_gnss_characteristics(GlobalsManager* const glob_mgr);