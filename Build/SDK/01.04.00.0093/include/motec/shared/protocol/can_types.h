#ifndef __CAN_TYPES_H_INCLUDE__
#define __CAN_TYPES_H_INCLUDE__

/* If we're not using GNU C, elide __attribute__ and use pragma 
   M16C compiler packs by default */
#if !defined __GNUC__ && !defined __attribute__
#  define  __attribute__(x)		/* NOTHING */
#endif

/*
 * PC code requires can_msg struct to be packed.
 * (As there are assumptions that can_msg and can_msg_p are the same size.)
 * Should fix the code one day.
 */
#if defined(__BORLANDC__) || defined(_MSC_VER) || defined(INCORRECTLY_PACK_CAN_TYPES)
#  pragma pack(push, 1)
#  define __CAN_TYPES_H_PRAGMA_PACK_POP__
#  include "mtc_comm.h"                  /* bases, halts and error codes */
#endif

/* can_id: this is defined as a union of bit-fields to help enforce the
 * can id packing. This helps abstract the user slightly:) Note that a
 * std id is aligned to the top of the extended id. This is deliberate
 * as the CAN protocol treats IDs in this manner, ie standard id 0x01
 * has similar priority to extended id 0x01<<18. Packing the IDs in
 * this way makes this more apparent and also allows filters to be
 * defined that can match both standard and extended ids. */
typedef union can_id {
#if defined(__LITTLE_ENDIAN_BITFIELD)
	struct can_std_id {
		uint32_t unused :18; 
		uint32_t id :11; /* b18..28 */
		uint32_t :3; /* access via flags */
	} std;
	struct can_ext_id {
		uint32_t id :29; /* b0..28 */
		uint32_t :3; /* access via flags */
	} ext;
	struct can_flags {
		uint32_t :29; /* access via std or ext */
		uint32_t rr :1;	/* remote request */
		uint32_t type :2;
	} flags;
#elif defined(__BIG_ENDIAN_BITFIELD)
	struct can_std_id {
		uint32_t :3;
		uint32_t id :11; /* b18..28 */
		uint32_t unused :18; 
	} std;
	struct can_ext_id {
		uint32_t :3;
		uint32_t id :29; /* b0..28 */
	} ext;
	struct can_flags {
		uint32_t type :2;
		uint32_t rr :1;
		uint32_t :29;
	} flags;
#else
#error "Bitfield endianness not defined! Check your byteorder.h"
#endif

#if defined(__LITTLE_ENDIAN)
	struct {
		uint8_t id07_00;
		uint8_t id15_08;
		uint8_t id23_16;
		uint8_t id28_24;	/* shared with flags */
	} ext_b;
	struct {
		uint16_t unused;
		uint8_t id05_00;	/* top aligned */
		uint8_t id10_06;	/* shared with flags */
	} std_b;
	struct {
		uint8_t unused[3];
		uint8_t flags;		/* top aligned */
	}flags_b;

#elif defined(__BIG_ENDIAN)
	struct {
		uint8_t id28_24;	/* shared with flags */
		uint8_t id23_16;
		uint8_t id15_08;
		uint8_t id07_00;
	} ext_b;
	struct {
		uint8_t id10_06;	/* shared with flags */
		uint8_t id05_00;	/* top aligned */
	} std_b;
	struct {
		uint8_t flags;		/* top aligned */
	}flags_b;

#else
#error "Endianness not defined! Check your byteorder.h"
#endif
	uint32_t val;
} CAN_ID;

#if !defined(CUSTOM_CAN_MSG)
typedef struct can_msg {
	union can_id id;
	uint8_t d[8];
	uint8_t len;
	uint32_t time_us;
} CAN_MSG;
#endif

typedef struct can_filter {
    union {
        struct {
            union can_id match; /* can id to match against message ID */
            union can_id mask;  /* bits to ignore in message ID (1 == ignore) */
        };
        struct {
#if defined(__BIG_ENDIAN_BITFIELD)
            unsigned type : 2;      /* CAN_ID_TYPE_ADVANCED_FILTER */
            unsigned protocol : 6;  /* CAN_FILTER_ADVANCED_PROTOCOL_* */
            uint32_t data0 : 24;
            uint32_t data1 : 32;
#elif defined(__LITTLE_ENDIAN_BITFIELD)
            uint32_t data1 : 32;
            uint32_t data0 : 24;
            unsigned protocol : 6;  /* CAN_FILTER_ADVANCED_PROTOCOL_* */
            unsigned type : 2;      /* CAN_ID_TYPE_ADVANCED_FILTER */
#endif
        } advanced;
        struct {
#if defined(__BIG_ENDIAN_BITFIELD)
            unsigned type : 2;      /* CAN_ID_TYPE_ADVANCED_FILTER */
            unsigned protocol : 6;  /* CAN_FILTER_ADVANCED_PROTOCOL_J1939 */
            unsigned sa : 8;            /* j1939 source address */
            unsigned reserved0 : 16;    /* set to 0 */
            uint32_t reserved1 : 32;    /* set to 0 */
#elif defined(__LITTLE_ENDIAN_BITFIELD)
            uint32_t reserved1 : 32;    /* set to 0 */
            unsigned reserved0 : 16;    /* set to 0 */
            unsigned sa : 8;            /* j1939 source address */
            unsigned protocol : 6;  /* CAN_FILTER_ADVANCED_PROTOCOL_J1939 */
            unsigned type : 2;      /* CAN_ID_TYPE_ADVANCED_FILTER */
#endif
        } advanced_j1939;
    };
} CAN_FILTER;
		
#define CAN_ID_EXT_MAX 0x1FFFFFFF
#define CAN_ID_STD_MAX 0x7FF

/* defined so that STD and EXT have their own flag. Makes filter hit
 * testing nice and clean as we always treat it as a 32bit ID */
#define CAN_ID_TYPE_UNUSED 0			  
#define CAN_ID_TYPE_STD 1
#define CAN_ID_TYPE_EXT 2
#define CAN_ID_TYPE_MASK 3	/* valid bits for type */

/* for a filter match we define an advanced filter type if both the STD an EXT
 * bits are set */
#define CAN_ID_TYPE_ADVANCED_FILTER 3

/* for a filter mask, we can either match or ignore the message type
 * and rr flag */
#define CAN_ID_TYPE_MATCH 0
#define CAN_ID_TYPE_IGNORE 3
#define CAN_ID_RR_MATCH 0
#define CAN_ID_RR_IGNORE 1

/*
 * Advanced filter protocols
 */
#define CAN_FILTER_ADVANCED_PROTOCOL_J1939 0

/* 
 * Helper macros to manipulate CAN_ID and CAN_FILTER
 */
#if 0                           /* reference inplementations using bitfield */
/* set a can_id as either std, ext or unused (useful for filters, etc) */
#define CAN_ID_SET_STD(can_id, v) \
(can_id).flags.type = CAN_ID_TYPE_STD, (can_id).std.id = v
#define CAN_ID_SET_EXT(can_id, v) \
(can_id).flags.type = CAN_ID_TYPE_EXT, (can_id).ext.id = v
#define CAN_ID_SET_UNUSED(can_id) can_id.flags.type = CAN_ID_TYPE_UNUSED

/* set a can filter mask. Possible to match both STD _and_ EXT with
   one mask but most can hardware doesn't support this, so we only
   provide helper macros for STD _or_ EXT. Note that this also
   requires the rr flag to match  */
#define CAN_FILTER_MASK_STD(can_filter, v) (can_filter).mask.std.id = v, \
        (can_filter).mask.flags.type = CAN_ID_TYPE_MASK_MATCH,          \
        (can_filter).mask.flags.rr = CAN_ID_RR_MASK_MATCH
#define CAN_FILTER_MASK_EXT(can_filter, v) (can_filter).mask.ext.id = v, \
        (can_filter).mask.flags.type = CAN_ID_TYPE_MASK_MATCH,          \
        (can_filter).mask.flags.rr = CAN_ID_RR_MASK_MATCH

/* boolean tests */
#define CAN_ID_UNUSED(can_id)    (can_id.flags.type == CAN_ID_TYPE_UNUSED)
#define CAN_ID_STD(can_id)       (can_id.flags.type == CAN_ID_TYPE_STD)
#define CAN_ID_EXT(can_id)       (can_id.flags.type == CAN_ID_TYPE_EXT)

#else  /* optimised implementations */
#define CAN_ID_SET_STD(can_id, v) can_id.val =    \
        (uint32_t)CAN_ID_TYPE_STD<<30 | ((uint32_t)v)<<18
#define CAN_ID_SET_EXT(can_id, v) can_id.val =        \
        (uint32_t)CAN_ID_TYPE_EXT<<30 | ((uint32_t)v)
#define CAN_ID_SET_UNUSED(can_id) can_id.val = 0

#define CAN_FILTER_MASK_STD(can_filter, v) (can_filter).mask.val =  \
        ((uint32_t)v)<<18
#define CAN_FILTER_MASK_EXT(can_filter, v) (can_filter).mask.val = (v)

#define CAN_ID_UNUSED(can_id) ((can_id).val == 0)
#define CAN_ID_STD(can_id) (((can_id).val & ((uint32_t)CAN_ID_TYPE_MASK<<30)) \
                            == ((uint32_t)CAN_ID_TYPE_STD<<30))
#define CAN_ID_EXT(can_id) (((can_id).val & ((uint32_t)CAN_ID_TYPE_MASK<<30)) \
                            == ((uint32_t)CAN_ID_TYPE_EXT<<30))
#endif  /* optimised implementations */

#define CAN_FILTER_SET_UNUSED(can_filter)  CAN_ID_SET_UNUSED((can_filter).match)
#define CAN_FILTER_UNUSED(can_filter)      CAN_ID_UNUSED((can_filter).match)
#define CAN_FILTER_MATCH_STD(can_filter, v)     \
    CAN_ID_SET_STD((can_filter).match, v)
#define CAN_FILTER_MATCH_EXT(can_filter, v)     \
    CAN_ID_SET_EXT((can_filter).match, v)

/*
 * The COSMIC (6808) compiler can't handle inline functions.
 * Luckily, these functions are not currently used by products built
 * with that compiler, so just hide them on that platform.
 */
#ifndef __CSMC__
static inline int CAN_ID_FILTER_MATCH(CAN_ID id, CAN_FILTER filt)
{
	if (!((id.val ^ filt.match.val) & ~filt.mask.val))
		return 1;
	if (filt.match.flags.type != CAN_ID_TYPE_ADVANCED_FILTER)
		return 0;
	switch (filt.advanced.protocol) {
	case CAN_FILTER_ADVANCED_PROTOCOL_J1939:
		/* reject extended and remote request */
		if (id.flags.type != CAN_ID_TYPE_EXT)
			return 0;
		if (id.flags.rr)
			return 0;
		/* accept from any source address other than our own */
		if ((id.ext.id & 0xff) != filt.advanced_j1939.sa)
			return 1;
		/* accept address claim messages unconditionally */
		if ((id.ext.id & 0xff0000) == 0xee0000)
			return 1;
		/* reject everything else */
		return 0;
	default:
		return 0;
	}
}

static inline int CAN_FILTER_VALID(CAN_FILTER filt)
{
    if (filt.match.flags.type == CAN_ID_TYPE_ADVANCED_FILTER)
        return 1;
    if (filt.mask.flags.type == CAN_ID_TYPE_MATCH)
        return 1;
    if (filt.mask.flags.type == CAN_ID_TYPE_IGNORE)
        return 1;
    return 0;
}
#endif /* __CSMC__ */

#define CAN_ID_GET(can_id)       ((CAN_ID_STD(can_id)) ?            \
                                  (unsigned)(can_id).std.id :       \
                                  (unsigned long)(can_id).ext.id)

/* generic can status flags */
#define CAN_STATUS_ROVR     0x800 /* a Rx overrun has occurres since last query */
#define CAN_STATUS_TOVR     0x400 /* a Tx overrun has occurres since last query */
#define CAN_STATUS_WRONG_SPEED 0x200 /* kbaud for handle != bus speed */
#define CAN_STATUS_TIMEOUT  0x100 /* timeout */
#define CAN_STATUS_LOOP     0x80 /* interface is loopback */
#define CAN_STATUS_RWRN     0x40 /* rx warn: rx_error >= 96 */
#define CAN_STATUS_TWRN     0x20 /* tx warn: tx_error >= 96 */
#define CAN_STATUS_RERR     0x10 /* rx error passive: rx_error >= 127 */
#define CAN_STATUS_TERR     0x08 /* tx error passive: tx_error >= 127 */
#define CAN_STATUS_BOFF     0x04 /* bus off, rx or tx error >= 255 */
#define CAN_STATUS_OVR      0x02 /* a Rx overrun has occurres since last query */
#define CAN_STATUS_RXF      0x01 /* a message has been received since last query */

/* ADLCAN protocol specific stuff below */

/* adl_can* structs must always be packed. */
#if defined(__GNUC__) && !defined(__CAN_TYPES_H_PRAGMA_PACK_POP__)
#  pragma pack(push, 1)
#  define __CAN_TYPES_H_PRAGMA_PACK_POP__
#endif

/*
 * ADLCAN_VERSION
 *
 * 1: added rebase support
 *
 * 2: added erase command
 *
 * 3: added rebase timeout to examine (default 255 sec). Rebase
 * required for all other commands. Immediate discovery msg after
 * rebase
 */
#define ADLCAN_VERSION 3

#define ADLCAN_PACE    0x08
#define ADLCAN_REBASE  0x09
#define ADLCAN_ERASE   0x0A
#define ADLCAN_SET     0x0D
#define ADLCAN_EXAMINE 0x0E
#define ADLCAN_REPLY   0x0F

#define ADLCAN_FLAG_PACE 0x01

struct adlcan_rebase {
    uint8_t comms_version;      /**< comms protocol version. Should
                                   match the version the device
                                   implements (reported in discovery
                                   message) */
    uint8_t hw_id;              /**< hardware id. Identifies the
                                   type of device - this is the high
                                   byte of devices hw number, see doc IES0005 */
    uint16_t serial_num;        /**< serial number. This is the low 16
                                   bits of the device serial number */
    uint8_t request_base;       /**< adlcan request_base. request_base
                                   = request_can_id>>4 */
    uint8_t response_base;      /**< adlcan
                                   response_base. response_base =
                                   response_can_id>>4 */
    uint16_t crc16;             /**< crc16. crc16 of preceeding 6 bytes */
};

struct adlcan_set {
    uint8_t base;
    uint8_t page;
    uint16_t offset;
    uint16_t len;
    uint8_t data[2];
};

struct adlcan_erase {
    uint8_t base;
    uint8_t page;
    uint16_t offset;
    uint32_t len;
};

struct adlcan_examine {
    uint8_t base;
    uint8_t page;
    uint16_t offset;
    uint16_t len;
    uint8_t flags;
    uint8_t timeout_s;		/**< timeout for rebase */
};

struct adlcan_reply {
    uint8_t cmd;
    uint8_t sequence;           /* ignored */
    uint8_t command_status;
    uint8_t system_status;
    uint16_t len;
    uint8_t data[2];
};

#define CAN_DISCOVERY_EXT_ID 0x1CF80000L
#define CAN_DISCOVERY_EXT_MASK 0x0000FFFFL
#define CAN_DISCOVERY_LEN 7

struct can_discovery {
    uint8_t comms_version;      /**< comms protocol version. Roll this
                                   number if the device comms
                                   changes. This value is dependent on
                                   the protocol the device implements,
                                   ie ADLCAN or small device. For PC
                                   app msgs (i.e. when hw_id == 0),
                                   set to GW_VERSION */
    uint8_t hw_id;              /**< hardware id. Identifies the
                                   type of device - this is the high
                                   byte of devices hw number */
    uint16_t serial_num;        /**< serial number. This is the low 16
                                   bits of the device serial number */
    uint8_t request_base;       /**< adlcan
                                   request_base. request_can_id =
                                   request_base<<4 */
    uint8_t response_base;      /**< adlcan
                                   response_base. response_can_id =
                                   response_base<<4 */
    uint8_t sequence;           /**< rolling sequence number. Sequence
                                   starts at 0 and is incremented for
                                   every message sent (ensures CAN id
                                   changes each time) */
};

/*
 * Structure used by M800 [353M..354H2] and M84 [110P..120A]
 * Newer versions corrected to use structure above.
 */
struct can_discovery_e6 {
    uint8_t sequence;           /**< rolling sequence number. Sequence
                                   starts at 0 and is incremented for
                                   every message sent (ensures CAN id
                                   changes each time) */
    uint8_t hw_id;              /**< hardware id. Identifies the
                                   type of device - this is the high
                                   byte of devices hw number */
    uint16_t serial_num;        /**< serial number. This is the low 16
                                   bits of the device serial number */
    uint8_t comms_version;      /**< comms protocol version. Roll this
                                   number if the device comms
                                   changes. This value is dependent on
                                   the protocol the device implements,
                                   ie ADLCAN or small device */
    uint8_t request_base;       /**< adlcan
                                   request_base. request_can_id =
                                   request_base<<4 */
    uint8_t response_base;      /**< adlcan
                                   response_base. response_can_id =
                                   response_base<<4 */
};

/* known devices */
#define ADL_REQUEST     0x280
#define ADL_RESPONSE    0x200

#define ADL_REQUEST2    0x380
#define ADL_RESPONSE2   0x240

#define ACL_REQUEST     0x340
#define ACL_RESPONSE    0x210

#if defined(__CAN_TYPES_H_PRAGMA_PACK_POP__)
#  pragma pack(pop)
#  undef __CAN_TYPES_H_PRAGMA_PACK_POP__
#endif


#endif  /* !__CAN_TYPES_H_INCLUDE__ */
