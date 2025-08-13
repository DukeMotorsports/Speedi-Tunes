#ifndef __ECU_MDD_H__
#define __ECU_MDD_H__

#include <ecu/types.h>
#include <ecu/util.h>

/**
 * @addtogroup MDD
 * @{
 */

/**
 * @fn bool mdd_init(u32 id)
 * @arg ScriptName Init
 *
 * @brief Initialise MDD communications
 *
 * @param id standard CAN id (0x1 to 0x7FF)
 */

bool __warn_unused_result mdd_init(u32 id);

/**
 * @fn bool mdd_tx(s32 bus)
 * @arg ScriptName Transmit
 *
 * @brief Transmit MDD data
 *
 * @param bus CAN bus
 *
 * @details <p>This function should be called at 50Hz for correct MDD operation.
 * @details This will update the bar graph and shift lights at 25Hz and other
 * @details display elements at 3.5Hz. If the project is only supports colour
 * @details displays the rate may be increased to 100Hz.</p>>
 * @details <p>Additional features such as warning lights, brightness, contrast
 * @details can be managed in script by sending the appropriate data as per the
 * @details MDD product specification. To ensure the MDD detects the ADL display
 * @details protocol this additional data must <b>only</b> be transmitted when
 * @details data is being received from the MDD. There should be a maximum of
 * @details one message transmitted each time in a 5Hz script.</p>
 */

bool __warn_unused_result mdd_tx(u32 bus);

/**
 * @fn void mdd_numeric(s32 idx, s32 value, s32 dp, s32 format, s32 enunciator)
 * @arg ScriptName Numeric
 *
 * @brief Set the value for a display
 *
 * @param idx Display index (0: left, 1: right, 2: upper)
 * @param value Scaled value to display
 * @param dp location of decimal place in value
 * @param format The numeric format to use
 * @param enunciator enunciator to draw near value
 *
 * @details <p>The format should be one of these values:</p>
 * @details <table class=param>
 * @details <tr><th>Format</th><th>Description</th></tr>
 * @details <tr><td>0</td><td>Decimal</td></tr>
 * @details <tr><td>1</td><td>Decimal DP removal</td></tr>
 * @details <tr><td>2</td><td>M SS H</td></tr>
 * @details <tr><td>3</td><td>SS HH</td></tr>
 * @details <tr><td>4</td><td>MM SS</td></tr>
 * @details <tr><td>5</td><td>HH MM</td></tr>
 * @details </table>
 */

void mdd_numeric(u32 idx, s32 value, int dp, int format, int enuncuator);

/**
 * @fn void mdd_numeric_blank(s32 idx)
 * @arg ScriptName NumericBlank
 *
 * @brief Blank the numeric display
 *
 * @param idx Display index (0: left, 1: right, 2: upper)
 */

void mdd_numeric_blank(u32 idx);

/**
 * @fn void mdd_leds(u32 value)
 * @arg ScriptName Leds
 *
 * @brief Set the value for the leds display
 *
 * @param value bitmask for LEDs
 *
 * @details <p>The value will be the sum of one or more of these values:</p>
 * @details <table class=param>
 * @details <tr><th>Value</th><th>Description</th></tr>
 * @details <tr><td>0</td><td>All off</td></tr>
 * @details <tr><td>0x01</td><td>LED1</td></tr>
 * @details <tr><td>0x02</td><td>LED2</td></tr>
 * @details <tr><td>0x04</td><td>LED3</td></tr>
 * @details <tr><td>0x08</td><td>LED4</td></tr>
 * @details <tr><td>0x10</td><td>LED5</td></tr>
 * @details </table>
 */

void mdd_leds(u32 value);

/**
 * @fn void mdd_centre(s32 value)
 * @arg ScriptName Centre
 *
 * @brief Set the value for the centre display
 *
 * @param value Scaled value to display
 */

void mdd_centre(s32 value);

/**
 * @fn void mdd_centre_blank(void)
 * @arg ScriptName CentreBlank
 *
 * @brief Blank the centre display
 *
 */

void mdd_centre_blank(void);

/**
 * @fn void mdd_mode(s32 value)
 * @arg ScriptName Mode
 *
 * @brief Set the mode (race / practice / warmup)
 *
 * @param value
 */

void mdd_mode(s32 value);

/**
 * @fn void mdd_mode_blank(void)
 * @arg ScriptName ModeBlank
 *
 * @brief Blank the mode display
 *
 */

void mdd_mode_blank(void);

/**
 * @fn void mdd_bar_tick(s32 idx, f32 value, s32 indicator)
 * @arg ScriptName BarTick
 *
 * @brief Set the tick mark value for the bar graph
 *
 * @param idx Tick index (0-6)
 * @param value Actual value at tick mark
 * @param indicator value to display at tick mark (0-19)
 */

void mdd_bar_tick(u32 idx, f32 value, u32 indicator);

/**
 * @fn void mdd_bar_tick_blank(void)
 * @arg ScriptName BarTickBlank
 *
 * @brief Blank the bar tick marks
 *
 */

void mdd_bar_tick_blank(void);

/**
 * @fn void mdd_bar(f32 level, f32 limit, f32 peak)
 * @arg ScriptName Bar
 *
 * @brief Set the values for the bar graph
 *
 * @param level
 * @param limit
 * @param peak
 */

void mdd_bar(f32 level, f32 limit, f32 peak);

/**
 * @fn void mdd_bar_blank(void)
 * @arg ScriptName BarBlank
 *
 * @brief Blank the bar graph
 *
 */

void mdd_bar_blank(void);

/**
 * @fn void mdd_text_2_f32(string msg, f32 value, s32 dp, string msg2, f32 value2, s32 dp2)
 * @arg ScriptName Text
 *
 * @brief Display text and values on the Bottom line
 *
 * @param msg First string to display
 * @param value first value
 * @param dp first value decimal places
 * @param msg2 second string to display
 * @param value2 second value
 * @param dp2 second value decimal places
 */
void mdd_text_2_f32(const char *msg, f32 value, s32 dp,
		    const char *msg2, f32 value2, s32 dp2);

/**
 * @overload void mdd_text_1_f32(string msg, f32 value, s32 dp)
 */
void mdd_text_1_f32(const char *msg, f32 value, s32 dp);

/**
 * @overload void mdd_text(string msg)
 */

void mdd_text(const char *msg);

/**
 * @fn void mdd_text_blank(void)
 * @arg ScriptName TextBlank
 *
 * @brief Blank the bottom line
 *
 */

void mdd_text_blank(void);

/** @} MDD */

#endif // __ECU_MDD_H__
