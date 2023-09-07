#include "tensorarray.h"

bool tarray_equals(dtype* a1, dtype* a2, uint32_t len)
{
    /* Checks whether to arrays are equal. If one or both arrays are array
     * pointers are NULL, false is returned.
     *
     * @param a1 The first array to compare
     * @param a2 The second array to compare
     * @param len The length of the arrays
     *
     * @return true if the arrays are equal, false otherwise
     */
    if (a1 == NULL || a2 == NULL) return false;
    for (uint32_t i = 0; i < len; i++) {
        if (DTYPE_NE(a1[i], a2[i])) return false;
    }
    return true;
}

bool tarray_uint32_equals(uint32_t* a1, uint32_t* a2, uint32_t len)
{
    /* Checks whether to arrays of the type uint32_t are equal. If one or both
     * arrays are array pointers are NULL, false is returned.
     *
     * @param a1 The first array to compare
     * @param a2 The second array to compare
     * @param len The length of the arrays
     *
     * @return true if the arrays are equal, false otherwise
     */
    if (a1 == NULL || a2 == NULL) return false;
    for (uint32_t i = 0; i < len; i++) {
        if (a1[i] != a2[i]) return false;
    }
    return true;
}
