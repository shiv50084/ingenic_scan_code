#ifndef __ROT_LPF_VEC_IF_H__
#define __ROT_LPF_VEC_IF_H__

#include "libsensors_id.h"

#ifdef RUN_ON_FRIZZ
	#define FLOAT	frizz_tie_fp
#else
	#define FLOAT	float
#endif

/**
 * @name Sensor ID
 */
//@{
/**
 * @brief Rotation Vector without Gyro
 */
#define ROTATION_LPF_VECTOR_ID	SENSOR_ID_ROTATION_LPF_VECTOR
//@}

/**
 * @name Output
 */
//@{
/**
 * @brief 回転ベクトル
 *
 * @note Continuous
 */
typedef struct {
	FLOAT		data[4];	/// quaternion 0~2:vector, 3:scaler
	FLOAT		accr;		/// accuracy [rad]
} rot_lpf_vec_data_t;
//@}

/**
 * @name Command List
 *
 * @note none
 */
//@{
//@}

#endif
