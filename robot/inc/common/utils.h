/* Common set of utilities for all of project */

#ifndef _COMMON_UTILS_
#define _COMMON_UTILS_

/* ------------------------ MACROS AND DEFINES ------------------------------ */
#define INPUT_PORT      0x00
#define OUTPUT_PORT     0xFF

/*!
 * Sets a bit high for a given byte
 *
 * @param[in/out] byte  The byte whose bit to set
 * @param[in]     bit   The bit position to set in byte
 */
#define SET_BIT(byte, bit) \
        byte |= (1 << (bit))

/*!
 * Clears a bit for a given byte
 *
 * @param[in/out] byte  The byte whose bit is cleared
 * @param[in]     bit   The bit position to clear in byte
 */
#define CLEAR_BIT(byte, bit) \
        byte &= ~(1 << (bit))

/*!
 * Toggles a bit for a given byte
 *
 * @param[in/out] byte  The byte whose bit is toggled
 * @param[in]     bit   The bit position to toggle in byte
 */
#define TOGGLE_BIT(byte, bit) \
        byte ^= (1 << (bit))

/*!
 * Helper macro to set an I/O port's mode to either input or output
 *
 * @param[in/out] port  The I/O port whose mode is to be set
 * @param[in]     mode  The data direction mode of the port: either INPUT or 
 *                      OUTPUT
 * 
 * @note port in this macro does not refer to PORT register, but rather to data
 *       direction register (DDR)
 */
#define SET_PORT_MODE(port, mode) \
        port = mode

/*!
 * Helper macro to set the data direction mode of a given I/O port's bit to
 * INPUT
 *
 * @param[in/out] port  The I/O port whose bit's mode is to be set
 * @param[in]     bit   The bit position in the I/O port register whose mode to
 *                      set
 *
 * @note port in this macro does not refer to PORT register, but rather to data
 *       direction register (DDR)
 */
#define SET_PORT_BIT_INPUT(port, bit) \
        CLEAR_BIT(port, bit)

/*!
 * Helper macro to set the data direction mode of a given I/O port's bit to
 * OUTPUT
 *
 * @param[in/out] port  The I/O port whose bit's mode is to be set
 * @param[in]     bit   The bit position in the I/O port register whose mode to
 *                      set
 *
 * @note port in this macro does not refer to PORT register, but rather to data
 *       direction register (DDR)
 */
#define SET_PORT_BIT_OUTPUT(port, bit) \
        SET_BIT(port, bit)

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * An I/O port
 */
typedef volatile uint8_t PORT;

/*!
 * An 8-bit CPU register
 */
typedef volatile uint8_t REG8;

/*!
 * A 16-bit CPU register
 */
typedef volatile uint16_t REG16;

#endif /* _COMMON_UTILS_ */
