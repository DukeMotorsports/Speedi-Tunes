#ifndef __ECU_SIMULINK_CAN_H__
#define __ECU_SIMULINK_CAN_H__

#include <ecu/types.h>

#ifndef _ECU_SOURCE
#include <byteorder.h>
#include <motec/shared/protocol/can_types.h>
#else
#define CAN_ID_TYPE_STD 1
#define CAN_ID_TYPE_EXT 2
/* for a filter match we define an advanced filter type if both the STD an EXT
 * bits are set */
#define CAN_ID_TYPE_ADVANCED_FILTER 3
#define CAN_ID_TYPE_MASK 3
#define CAN_ID_STD(can_id) (((can_id).val & ((u32)CAN_ID_TYPE_MASK<<30)) \
                            == ((u32)CAN_ID_TYPE_STD<<30))
#define CAN_ID_GET(can_id) ((CAN_ID_STD(can_id)) ?            \
			    (unsigned)(can_id).std.id :       \
			    (unsigned long)(can_id).ext.id)
#define CAN_ID_EXT(can_id) (((can_id).val & ((u32)CAN_ID_TYPE_MASK<<30)) \
                            == ((u32)CAN_ID_TYPE_EXT<<30))
#define CAN_ID_SET_STD(can_id, v) can_id.val =    \
        (u32)CAN_ID_TYPE_STD<<30 | ((u32)v)<<18
#define CAN_ID_SET_EXT(can_id, v) can_id.val =        \
        (u32)CAN_ID_TYPE_EXT<<30 | ((u32)v)
union can_id {
	struct can_std_id {
		u32 : 3;
		u32 id : 11;
		u32 : 18;
	} std;
	struct can_ext_id {
		u32 : 3;
		u32 id : 29;
	} ext;
	struct can_flags {
		u32 : 2;
		u32 rr : 1;
		u32 : 29;
	} flags;
	u32 val;
};

struct can_msg {
	union can_id id;
	u8 d[8];
	u8 len;
	u32 time_us;
};
#endif

int simulink_can_rx_init(u32 bus, u32 match, u32 mask);
int simulink_can_rx(int h, struct can_msg *, unsigned len);
int simulink_can_tx(u32 bus, struct can_msg *, unsigned len);

#endif
