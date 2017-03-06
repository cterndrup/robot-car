/* Implementation of utility functions */

/* ------------------------ INCLUDES ---------------------------------------- */
#include "common/utils.h"

/* ------------------------ FUNCTION DEFINITIONS ---------------------------- */

/*!
 * @ref utils.h for function documentation
 */
void
stringcpy
(
    char       *dst,
    const char *src
)
{
    if (dst == NULL || src == NULL)
        return;

    while (*src != '\0')
    {
        *dst = *src;
        ++dst;
        ++src;
    }
    *dst = '\0';
}

/*!
 * @ref utils.h for function documentation
 */
bool
stringcmp
(
    const char *str1,
    const char *str2
)
{
    if (str1 == NULL || str2 == NULL)
        return false;

    const char *s1 = &str1[0];
    const char *s2 = &str2[0];

    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
            return false;

        ++s1;
        ++s2;
    }

    return *s1 == *s2; 
}

/*!
 * @ref utils.h for function documentation
 */
char * stringcat
(
    char       *dst,
    const char *src1,
    const char *src2
)
{
    while (*src1 != '\0')
    {
        *dst = *src1;
        ++dst;
        ++src1;
    }

    while (*src2 != '\0')
    {
        *dst = *src2;
        ++dst;
        ++src2;
    }
    *dst = '\0';

    return dst;
}

/*!
 * @ref utils.h for function documentation
 */
uint16_t
string2int(const char *str)
{
    uint16_t result = 0;
    while (*str != '\0')
    {
        result = result*10 + (uint16_t)(*str - '0');
        ++str;
    }

    return result;
}
