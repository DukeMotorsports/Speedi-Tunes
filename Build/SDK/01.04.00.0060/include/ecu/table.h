#ifndef __ECU_TABLE_H__
#define __ECU_TABLE_H__
#include <ecu/types.h>
#include <ecu/util.h>

/**
 * @addtogroup Table
 * @{
 */

/*
 * A table axis _must_ have a slope > 0.
 *
 * NOTE:
 * 1) The axis search is truncated when slope <= 0, so this can be
 * used to mark unused sites in tuning software
 *
 * 2) If there are no valid points on an axis the value of the first
 * site is returned from the interpolation. This allows tables to be
 * collapsed from 3 axis => 2 axis => 1 axis => point
 */

typedef const struct {
	const u32 num;		/* max axis size */
	f32 volatile const *const data;	/* axis data */
	u32 flags;
} axis_f32_cfg;

#define AXIS_F32_FLAG_MANDATORY 0x01
#define AXIS_F32_FLAG_EXTRAPOLATE_MIN 0x02
#define AXIS_F32_FLAG_EXTRAPOLATE_MAX 0x04
#define AXIS_F32_FLAG_EXTRAPOLATE_BOTH (AXIS_F32_FLAG_EXTRAPOLATE_MIN|AXIS_F32_FLAG_EXTRAPOLATE_MAX)

typedef struct {
	struct axis_current {		/* functions can return 64 bits */
		u32 index;
		f32 ratio;
	} position;
	u32 index_last;
} axis_f32_state;

#define INIT_AXIS_F32_CFG(name, _num, _flags)	\
	{ .num = _num, .data = name, .flags = _flags }
#define CHECK_AXIS_F32_CFG(_num)		\
	ctassert(_num >= 2);

typedef const struct {
	const u32 num;		/* number of sites */
	const s32 min;		/* first site */
} lookup_s32_cfg;

typedef struct {
	struct axis_s32_position {
		s32 index;
	} position;
} axis_s32_state;

#define INIT_LOOKUP_S32_CFG(_num, _min)		\
	{ .num = _num, .min = _min }
#define CHECK_LOOKUP_S32_CFG(_num, _min)	\
	ctassert(_num >= 1);			\
	ctassert(_min <= 0);

/*****************************************************************************
 * returns the lower limit of an interpolated axis
 * ScriptName [XYZ]Minimum(void)
 */
extern f32 axis_min_f32(axis_f32_state *state, axis_f32_cfg *cfg)
 __warn_unused_result;

/*****************************************************************************
 * returns the upper limit of an interpolated axis
 * ScriptName [XYZ]Maximum(void)
 */
extern f32 axis_max_f32(axis_f32_state *state, axis_f32_cfg *cfg)
 __warn_unused_result;

/*****************************************************************************
 * returns the lower limit of an integer (lookup) axis
 * ScriptName [XYZ]Minimum(void)
 */
s32 axis_min_s32(lookup_s32_cfg *cfg) __warn_unused_result;

/*****************************************************************************
 * returns the lower limit of an integer (lookup) axis
 * ScriptName [XYZ]Maximum(void)
 */
s32 axis_max_s32(lookup_s32_cfg *cfg) __warn_unused_result;

/*****************************************************************************
 * table with no interpolated axis */
typedef const struct {
	lookup_s32_cfg x, y, z;
	f32 volatile const *const data;	/* table data */
} interp_0a_f32_cfg;

typedef struct {
	axis_s32_state x, y, z;
} interp_0a_f32_state;

/**
 * @fn f32 interp_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg, s32 x, s32 y, s32 z)
 * @arg ScriptName __Interpolate0A
 * @brief 0 axis table interpolation.
 * @param state [provide]
 * @param cfg table to interpolate
 * @param x [provide]
 * @param y [provide]
 * @param z [provide]
 * @return interpolated value
*/
extern f32 interp_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg,
			 s32 x, s32 y, s32 z) __warn_unused_result;

extern void interp_0a_f32_init(interp_0a_f32_state *state,
			       interp_0a_f32_cfg *cfg, s32 x, s32 y, s32 z);

/*****************************************************************************
 * 0 interpolated axis table helper macros */
#define INIT_INTERP_0A_F32_CFG(name_data, size_x, size_y, size_z, min_x, min_y, min_z) { \
	.x = INIT_LOOKUP_S32_CFG(size_x, min_x),	\
	.y = INIT_LOOKUP_S32_CFG(size_y, min_y),	\
	.z = INIT_LOOKUP_S32_CFG(size_z, min_z),	\
	.data = &name_data[0][0][0] };			\
	static inline void check_##name_data (void)	\
	{						\
		CHECK_LOOKUP_S32_CFG(size_x, min_x);	\
		CHECK_LOOKUP_S32_CFG(size_y, min_y);	\
		CHECK_LOOKUP_S32_CFG(size_z, min_z);	\
	}

#if 0
/* example of how to build a 0 interpolated axis table */
static f32 __ecu_cal(0) table_data[size_z][size_y][size_x];
interp_0a_f32_cfg table = INIT_INTERP_0A_F32_CFG(
	table_data, size_x, size_y, size_z, min_x, min_y, min_z);
interp_0a_f32_state table_state;

/* example of how to run a 0 interpolated axis table */
chan = interp_0a_f32(&table, x, y, z);
xmin = axis_min_s32(&table.x);
xmax = axis_max_s32(&table.x);
ymin = ayis_min_s32(&table.y);
ymax = ayis_max_s32(&table.y);
zmin = azis_min_s32(&table.z);
zmax = azis_max_s32(&table.z);
#endif

/*****************************************************************************
 * table with one interpolated axis */
typedef const struct {
	axis_f32_cfg x;
	lookup_s32_cfg y, z;
	f32 volatile const *const data;	/* table data */
} interp_1a_f32_cfg;

typedef struct {
	axis_f32_state x;
	axis_s32_state y, z;
} interp_1a_f32_state;

/**
 * @fn f32 interp_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg, f32 x, s32 y, s32 z)
 * @arg ScriptName __Interpolate1A
 * @arg initcall table
 * @brief 1 axis table interpolation.
 * @param state [provide]
 * @param cfg table to interpolate
 * @param x [provide]
 * @param y [provide]
 * @param z [provide]
 * @return interpolated value
*/
extern f32 interp_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg,
			 f32 x, s32 y, s32 z) __warn_unused_result;

extern void interp_1a_f32_init(interp_1a_f32_state *state,
			       interp_1a_f32_cfg *cfg, f32 x, s32 y, s32 z);

/**
 * @fn f32 reverse_x_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg, f32 value, s32 y, s32 z)
 * @arg ScriptName __ReverseLookupX
 * @arg initcall table
 * @brief 1 axis table reverse interpolation.
 * @param state [provide]
 * @param cfg table to interpolate
 * @param value [provide]
 * @param y [provide]
 * @param z [provide]
 * @return interpolated x
*/
extern f32 reverse_x_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg,
			 f32 value, s32 y, s32 z) __warn_unused_result;

/*****************************************************************************
 * 1 interpolated axis table helper macros */
#define INIT_INTERP_1A_F32_CFG(name_x, name_data, size_x, size_y, size_z, min_y, min_z, flags_x) { \
	.x = INIT_AXIS_F32_CFG(name_x, size_x, flags_x), \
	.y = INIT_LOOKUP_S32_CFG(size_y, min_y),	\
	.z = INIT_LOOKUP_S32_CFG(size_z, min_z),	\
	.data = &name_data[0][0][0] };			\
	static inline void check_##name_data (void)	\
	{						\
		CHECK_AXIS_F32_CFG(size_x);		\
		CHECK_LOOKUP_S32_CFG(size_y, min_y);	\
		CHECK_LOOKUP_S32_CFG(size_z, min_z);	\
	}

#if 0
/* example of how to build a 1 interpolated axis table */
static f32 __ecu_cal(0) table_xaxis[size_x];
static f32 __ecu_cal(0) table_data[size_z][size_y][size_x];
interp_1a_f32_cfg table = INIT_INTERP_1A_F32_CFG(
	table_xaxis, table_data, size_x, size_y, size_z, min_y, min_z);
interp_1a_f32_state table_state;

/* example of how to run a 1 interpolated axis table */
chan = interp_1a_f32(&table_state, &table, x, y, z);
xmin = axis_min_f32(&table_state.x, &table.x);
xmax = axis_max_f32(&table_state.x, &table.x);
ymin = ayis_min_s32(&table.y);
ymax = ayis_max_s32(&table.y);
zmin = azis_min_s32(&table.z);
zmax = azis_max_s32(&table.z);
#endif

/*****************************************************************************
 * table with two interpolated axis */
typedef const struct {
	axis_f32_cfg x, y;
	lookup_s32_cfg z;
	f32 volatile const *const data;	/* table data */
} interp_2a_f32_cfg;

typedef struct {
	axis_f32_state x, y;
	axis_s32_state z;
} interp_2a_f32_state;

/**
 * @fn f32 interp_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg, f32 x, f32 y, s32 z)
 * @arg ScriptName __Interpolate2A
 * @arg initcall table
 * @brief 2 axis table interpolation.
 * @param state [provide]
 * @param cfg table to interpolate
 * @param x [provide]
 * @param y [provide]
 * @param z [provide]
 * @return interpolated value
*/
extern f32 interp_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg, f32 x, f32 y, s32 z) __warn_unused_result;

extern void interp_2a_f32_init(interp_2a_f32_state *state,
			       interp_2a_f32_cfg *cfg, f32 x, f32 y, s32 z);

/*****************************************************************************
 * 2 interpolated axis table helper macros */
#define INIT_INTERP_2A_F32_CFG(name_x, name_y, name_data, size_x, size_y, size_z, min_z, flags_x, flags_y) { \
	.x = INIT_AXIS_F32_CFG(name_x, size_x, flags_x), \
	.y = INIT_AXIS_F32_CFG(name_y, size_y, flags_y), \
	.z = INIT_LOOKUP_S32_CFG(size_z, min_z),	\
	.data = &name_data[0][0][0] };			\
	static inline void check_##name_data (void)	\
	{						\
		CHECK_AXIS_F32_CFG(size_x);		\
		CHECK_AXIS_F32_CFG(size_y);		\
		CHECK_LOOKUP_S32_CFG(size_z, min_z);	\
	}

#if 0
/* example of how to build a 2 interpolated axis table */
static f32 __ecu_cal(0) table_xaxis[size_x];
static f32 __ecu_cal(0) table_yaxis[size_y];
static f32 __ecu_cal(0) table_data[size_z][size_y][size_x];
interp_2a_f32_cfg table = INIT_INTERP_2A_F32_CFG(
	table_xaxis, table_yaxis, table_data, size_x, size_y, size_z, min_z);
interp_2a_f32_state table_state;

/* example of how to run a 2 interpolated axis table */
chan = interp_2a_f32(&table_state, &table, x, y, z);
xmin = axis_min_f32(&table_state.x, &table.x);
xmax = axis_max_f32(&table_state.x, &table.x);
ymin = ayis_min_f32(&table_state.y, &table.y);
ymax = ayis_max_f32(&table_state.y, &table.y);
zmin = azis_min_s32(&table.z);
zmax = azis_max_s32(&table.z);
#endif

/*****************************************************************************
 * table with three interpolated axis */
typedef const struct {
	axis_f32_cfg x, y, z;
	f32 volatile const *const data;	/* table data */
} interp_3a_f32_cfg;

typedef struct {
	axis_f32_state x, y, z;
} interp_3a_f32_state;

/**
 * @fn f32 interp_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg, f32 x, f32 y, f32 z)
 * @arg ScriptName __Interpolate3A
 * @arg initcall table
 * @brief 3 axis table interpolation.
 * @param state [provide]
 * @param cfg table to interpolate
 * @param x [provide]
 * @param y [provide]
 * @param z [provide]
 * @return interpolated value
*/
extern f32 interp_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg, f32 x, f32 y, f32 z) __warn_unused_result;

extern void interp_3a_f32_init(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg,
			       f32 x, f32 y, f32 z);

/*****************************************************************************
 * 3 interpolated axis table helper macros */
#define INIT_INTERP_3A_F32_CFG(name_x, name_y, name_z, name_data, size_x, size_y, size_z, flags_x, flags_y, flags_z) { \
	.x = INIT_AXIS_F32_CFG(name_x, size_x, flags_x), \
	.y = INIT_AXIS_F32_CFG(name_y, size_y, flags_y), \
	.z = INIT_AXIS_F32_CFG(name_z, size_z, flags_z), \
	.data = &name_data[0][0][0] };			\
	static inline void check_##name_data (void)	\
	{						\
		CHECK_AXIS_F32_CFG(size_x);		\
		CHECK_AXIS_F32_CFG(size_y);		\
		CHECK_AXIS_F32_CFG(size_z);		\
	}

#if 0
/* example of how to build a 3 interpolated axis table */
static f32 __ecu_cal(0) table_xaxis[size_x];
static f32 __ecu_cal(0) table_yaxis[size_y];
static f32 __ecu_cal(0) table_zaxis[size_z];
static f32 __ecu_cal(0) table_data[size_z][size_y][size_x];
interp_3a_f32_cfg table = INIT_INTERP_3A_F32_CFG(
	table_xaxis, table_yaxis, table_zaxis, table_data, size_x, size_y, size_z);
interp_3a_f32_state table_state;

/* example of how to run a 3 interpolated axis table */
chan = interp_3a_f32(&table_state, &table, x, y, z);
xmin = axis_min_f32(&table_state.x, &table.x);
xmax = axis_max_f32(&table_state.x, &table.x);
ymin = ayis_min_f32(&table_state.y, &table.y);
ymax = ayis_max_f32(&table_state.y, &table.y);
zmin = azis_min_f32(&table_state.z, &table.z);
zmax = azis_max_f32(&table_state.z, &table.z);
#endif

/*****************************************************************************
 *****************************************************************************
 * 01.03.17 SDK extensions */

/*****************************************************************************
 * returns the axis site value at the supplied index
 * ScriptName [XYZ]Get(s32 index)
 */
extern f32 axis_get_f32(axis_f32_state *state, axis_f32_cfg *cfg, u32 index)
__warn_unused_result;

/*****************************************************************************
 * returns the lowest axis site used when Update() last executed
 * ScriptName [XYZ]Get(s32 index)
 */
extern f32 axis_get_cached_f32(axis_f32_state *state, axis_f32_cfg *cfg)
__warn_unused_result;

/*****************************************************************************
 * returns the index of the lowest site used when interpolating with the supplied value
 * ScriptName [XYZ]Index(f32 [xzy])
 */
extern u32 axis_index_f32(axis_f32_state *state, axis_f32_cfg *cfg, f32 val)
__warn_unused_result;

/*****************************************************************************
 * returns the index of the lowest site used when Update() last executed
 * ScriptName [XYZ]Index(void)
 */
static __inline __warn_unused_result
u32 axis_index_cached_f32(axis_f32_state *state, axis_f32_cfg *cfg)
{
	return state->position.index;
}

/*****************************************************************************
 * returns the first index of an interpolated axis
 * ScriptName [XYZ]IndexFirst(void)
 */
static __inline __warn_unused_result
u32 axis_index_first_f32(axis_f32_state *state, axis_f32_cfg *cfg)
{
	return 0;
}

/*****************************************************************************
 * returns the last enabled index of an interpolated axis
 * ScriptName [XYZ]IndexLast(void)
 */
extern u32 axis_index_last_f32(axis_f32_state *state, axis_f32_cfg *cfg)
 __warn_unused_result;

/*****************************************************************************
 * returns the position relative to the lowest site used when interpolating
 * with the supplied value.
 * < 0 if below minimum site
 * > 1.0 if above maximum site
 * ScriptName [XYZ]Position(f32 [xzy])
 */
extern f32 axis_position_f32(axis_f32_state *state, axis_f32_cfg *cfg, f32 val)
__warn_unused_result;

/*****************************************************************************
 * returns the position relative to the lowest site used in interpolation
 * when Update() last executed
 * < 0 if below minimum site
 * > 1.0 if above maximum site
 * ScriptName [XYZ]Position(void)
 */
static __inline __warn_unused_result
f32 axis_position_cached_f32(axis_f32_state *state, axis_f32_cfg *cfg)
{
	return state->position.ratio;
}

/*****************************************************************************
 * Get the indexed site
 * ScriptName Get(s32 x, s32 y, s32 z)
 */
extern f32 body_get_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg,
			    u32 xindex, u32 yindex, u32 zindex) __warn_unused_result;
extern f32 body_get_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg,
			    u32 xindex, u32 yindex, u32 zindex) __warn_unused_result;
extern f32 body_get_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg,
			    u32 xindex, u32 yindex, u32 zindex) __warn_unused_result;
extern f32 body_get_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg,
			    u32 xindex, u32 yindex, u32 zindex) __warn_unused_result;

/*****************************************************************************
 * Get the lowest site used when Update() last executed
 * ScriptName Get()
 */
static __inline __warn_unused_result
f32 body_get_cached_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg)
{
	return body_get_0a_f32(state, cfg, state->x.position.index,
			       state->y.position.index, state->z.position.index);
}

static __inline __warn_unused_result
f32 body_get_cached_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg)
{
	return body_get_1a_f32(state, cfg, state->x.position.index,
			       state->y.position.index, state->z.position.index);
}

static __inline __warn_unused_result
f32 body_get_cached_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg)
{
	return body_get_2a_f32(state, cfg, state->x.position.index,
			       state->y.position.index, state->z.position.index);
}

static __inline __warn_unused_result
f32 body_get_cached_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg)
{
	return body_get_3a_f32(state, cfg, state->x.position.index,
			       state->y.position.index, state->z.position.index);
}

/*****************************************************************************
 * Detect if the calibrated components of the table (axis and / or
 * body) have been edited
 * ScriptName Hash()
 */
extern u32 table_hash_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg)
__warn_unused_result;
extern u32 table_hash_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg)
__warn_unused_result;
extern u32 table_hash_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg)
__warn_unused_result;
extern u32 table_hash_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg)
__warn_unused_result;

/*****************************************************************************
 *****************************************************************************
 * 01.03.17 SDK extensions for learning tables only */

/*****************************************************************************
 * Set the indexed site to value
 * ScriptName Set(f32 value, s32 x, s32 y, s32 z)
 */
extern void body_set_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg,
			    f32 val, u32 xindex, u32 yindex, u32 zindex);
extern void body_set_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg,
			    f32 val, u32 xindex, u32 yindex, u32 zindex);
extern void body_set_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg,
			    f32 val, u32 xindex, u32 yindex, u32 zindex);
extern void body_set_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg,
			    f32 val, u32 xindex, u32 yindex, u32 zindex);

/*****************************************************************************
 * Set the lowest site used when Update() last executed to value
 * ScriptName Set(f32 value)
 */
static __inline
void body_set_cached_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg, f32 val)
{
	body_set_0a_f32(state, cfg, val, state->x.position.index,
			state->y.position.index, state->z.position.index);
}

static __inline
void body_set_cached_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg, f32 val)
{
	body_set_1a_f32(state, cfg, val, state->x.position.index,
			state->y.position.index, state->z.position.index);
}

static __inline
void body_set_cached_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg, f32 val)
{
	body_set_2a_f32(state, cfg, val, state->x.position.index,
			state->y.position.index, state->z.position.index);
}

static __inline
void body_set_cached_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg, f32 val)
{
	body_set_3a_f32(state, cfg, val, state->x.position.index,
			state->y.position.index, state->z.position.index);
}

/*****************************************************************************
 * Preset all sites to value
 * ScriptName Preset(f32 value)
 */
extern void body_preset_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg,
			       f32 val);
extern void body_preset_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg,
			       f32 val);
extern void body_preset_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg,
			       f32 val);
extern void body_preset_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg,
			       f32 val);

/*****************************************************************************
 * Adjust the table sites towards value:
 * sites: sites withing this relative distance are moved towards value
 * change: adjusts the amount of influence value has on the sites
 * ScriptName Adjust(f32 value, f32 sites, f32 change, x_type x, y_type y, z_type z)
 */
extern void body_adjust_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg,
			    f32 val, f32 sites, f32 change, u32 x, u32 y, u32 z);
extern void body_adjust_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg,
			    f32 val, f32 sites, f32 change, f32 x, u32 y, u32 z);
extern void body_adjust_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg,
			    f32 val, f32 sites, f32 change, f32 x, f32 y, u32 z);
extern void body_adjust_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg,
			    f32 val, f32 sites, f32 change, f32 x, f32 y, f32 z);

/*****************************************************************************
 * Adjust the table sites when Update() last executed towards value:
 * sites: sites withing this relative distance are moved towards value
 * change: adjusts the amount of influence value has on the sites
 * ScriptName Adjust(f32 value, f32 sites, f32 change)
 */
extern void body_adjust_cached_0a_f32(interp_0a_f32_state *state, interp_0a_f32_cfg *cfg,
				      f32 val, f32 sites, f32 change);
extern void body_adjust_cached_1a_f32(interp_1a_f32_state *state, interp_1a_f32_cfg *cfg,
				      f32 val, f32 sites, f32 change);
extern void body_adjust_cached_2a_f32(interp_2a_f32_state *state, interp_2a_f32_cfg *cfg,
				      f32 val, f32 sites, f32 change);
extern void body_adjust_cached_3a_f32(interp_3a_f32_state *state, interp_3a_f32_cfg *cfg,
				      f32 val, f32 sites, f32 change);

/** @} table */
#endif /* __ECU_TABLE_H__ */
