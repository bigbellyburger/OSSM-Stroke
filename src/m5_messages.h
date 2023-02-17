#ifndef _OSSM_M5_MESSAGES
#define _OSSM_M5_MESSAGES
#include <Arduino.h>
#define HEARTBEAT_INTERVAL 500

#ifdef __cplusplus
extern "C"
{
#endif

    // All OSSM M5 messages must start with this, otherwise they are discarded
    // Avoids overlapping with other esp-now based appliances
    const int M5_HEADER = 0x73DA7922;

    typedef enum m5_message_type
    {
        M5_CONNECT = 0,
        // OSSM_HOMED = 1,
        M5_SET_OSSM_STATE = 2,
        OSSM_BROADCAST_STATE = 3,
        M5_SET_CUM_STATE = 4,
        CUM_BROADCAST_STATE = 5,
        M5_SETUP_DEPTH = 6,
    };

    typedef struct
    {
        int header;
        unsigned short sender;
        unsigned short target;
        byte message_type;
    } __attribute__((packed)) m5_message_header_t;

    // M5_CONNECT: M5 -> OSSM: wants to connect
    typedef struct
    {
    } __attribute__((packed)) m5_connect_t;

    // M5_SET_OSSM_STATE: M5 -> OSSM: set the state of the OSSM
    // OSSM_BROADCAST_STATE: OSSM -> M5: inform M5 of successful state change
    typedef struct
    {
        float speed;
        float depth;
        float stroke;
        float sensation;
        int pattern;
        float torque_f;
        float torque_r;
        boolean on;
    } __attribute__((packed)) ossm_state_t;

    typedef struct
    {
        ossm_state_t state;
    } __attribute__((packed)) m5_set_ossm_state_t;

    typedef struct
    {
        float maxspeed;
        float maxdepth;
        ossm_state_t state;
    } __attribute__((packed)) ossm_broadcast_state_t;


    // // OSSM_HOMED: OSSM -> M5: response to M5_CONNECT
    // struct ossm_homed_t {

    //     ossm_state_t state;
    // } __attribute__ ((packed));

    // M5_SET_CUM_STATE: M5 -> CUM: set the state of the CUM
    // CUM_BROADCAST_STATE: CUM -> M5: inform M5 of successful state change
    typedef struct
    {
        float speed;
        float size;
        float accel;
        boolean on;
    } __attribute__((packed)) cum_state_t;

    typedef struct
    {
        bool fancy;
    } __attribute__((packed)) m5_setup_depth_t;

#ifdef __cplusplus
}
#endif

#endif