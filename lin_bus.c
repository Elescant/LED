#include "lin_bus.h"
#include "r_cg_serial.h"
#include "string.h"
enum
{
    LIN_PROTOCOL_V1 = 1,
    LIN_PROTOCOL_V2 = 2,
};
enum
{
    S_SYNC = 0,
    S_PID,
    S_SEND,
    S_REV,
    S_CHECK,
};

uint8_t pid_parse(uint8_t pid, uint8_t *s_buf, uint8_t *len);
BOOL pid_check(uint8_t pid);
void hal_send_byte(uint8_t byte);

#define BIT(_data, shift) ((_data) & (1 << (shift)) >> (shift))

static uint8_t lin_data_checksum(const uint8_t *msg, uint8_t nbytes, uint16_t sum)
{
    while (nbytes-- > 0)
    {
        sum += *(msg++);
    }
    while (sum >> 8)
    {
        sum = (sum & 0xFF) + (sum >> 8);
    }
    return (~sum);
}

static uint8_t lin_add_parity(const uint8_t addr)
{
    uint8_t p0 = BIT(addr, 0) ^ BIT(addr, 1) ^ BIT(addr, 2) ^ BIT(addr, 4);
    uint8_t p1 = BIT(addr, 1) ^ BIT(addr, 3) ^ BIT(addr, 4) ^ BIT(addr, 5);
    return (p0 | (p1 << 1)) << 6;
}

static void send_msg(const uint8_t addr, uint8_t *const body, const uint8_t bodysize, const uint8_t protocol)
{
    enum
    {
        SINC_SIZE = 1,
        ADDR_SIZE = 1,
        MSG_MAX_SIZE = 8,
        CHECKSUM_SIZE = 1,
        BUFFER_MAX_SIZE = SINC_SIZE + ADDR_SIZE + MSG_MAX_SIZE + CHECKSUM_SIZE,
    };
    uint8_t tmp_body[8] = {0};
    uint8_t sync_byte = SYNC_BYTE;
    uint8_t addrbyte = (addr & 0x3f) | (lin_add_parity(addr));
    uint8_t cksum = lin_data_checksum(tmp_body, bodysize, (protocol == 1) ? 0 : addrbyte);

    memcpy(tmp_body, body, bodysize);
    //send break  hal_uart_transmit(uart,data_addr,size,overtime);
    //send sync
    //send addrbyte
    //send body
    //send cksum
}

void slave_rec_byte_cb(uint8_t byte)
{
    uint8_t state;
    static uint8_t data_buf[9] = {0};
    static uint8_t rev_state = S_SYNC;
    static uint8_t len = 0, dindex = 0;

    switch (rev_state)
    {
    case S_SYNC:
        if (SYNC_BYTE == byte)
        {
            rev_state = S_PID;
            len = 0;
            dindex = 0;
        }
        break;
    case S_PID:
        if (pid_check(byte))
        {
            state = pid_parse(byte, data_buf, &len);
            //send_byte();
            if (len > 0)
            {
                rev_state = state;
                if (S_SEND == rev_state)
                {
                    hal_send_byte(data_buf[dindex]);
                }
            }
            else
            {
                rev_state = S_SYNC;
            }
        }
        break;
    case S_SEND:
        if (data_buf[dindex] == byte)
        {
            dindex++;
            if (dindex < len)
            {
                hal_send_byte(data_buf[dindex]);
            }
            else
            {
                rev_state = S_SYNC;
            }
        }
        else
        {
            //lin_err;
        }
        break;
    case S_REV:
        if(dindex<len)
        {
            data_buf[dindex] = byte;
            dindex ++;
        }else
        {
            //data check and save
            if(lin_data_checksum(data_buf,len-1,0) == data_buf[8])
            {

            }else
            {
                //lin_err
            }
            rev_state = S_SYNC;
        }
        break;
    default:
        break;
    }
}

BOOL pid_check(uint8_t pid)
{
    return lin_add_parity(pid) == (pid & 0xC0);
}

uint8_t pid_parse(uint8_t pid, uint8_t *s_buf, uint8_t *len)
{
    uint8_t ret = 0;
    switch (pid)
    {
    case 1:
        //send msg
        break;
    }
    return ret;
}

void hal_send_byte(uint8_t byte)
{
   static uint8_t data;
   data = byte;
   R_UARTF0_Send(&data,1);
}