#include <errno.h>
#include <stdint.h>

#include "usbd_cdc_if.h"

#if 0
int _read(int fd, char *ptr, int len)
{
    int i;

    for (i = 0; i < len; ++i)
    {
        int const c = CDC_GetChar();

        if (c < 0)
        {
            break;
        }

        ptr[i] = c;
    }

    if (i == 0 && len > 0)
    {
        errno = EAGAIN;

        return -1;
    }

    return i;
}
#endif

#if 0
int _write(int fd, char *ptr, int len)
{
    uint8_t result;

    do
    {
        result = CDC_Transmit_FS((uint8_t *)ptr, len);
    } while (result == USBD_BUSY);

    return result == USBD_OK ? len : -1;
}
#endif