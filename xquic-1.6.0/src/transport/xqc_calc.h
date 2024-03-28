// added by jndu

#ifndef _XQC_CALC_H_INCLUDED
#define _XQC_CALC_H_INCLUDED


#include <src/transport/xqc_send_ctl.h>
#include <src/transport/xqc_packet_out.h>
#include <src/transport/xqc_conn.h>
#include <src/transport/xqc_recv_record.h>



typedef struct
{
    float ct_cur_throughout;
    float ct_power1;
}xqc_calc_throughout_t;

typedef struct
{
    xqc_pktno_range_t send_pktno_range;
    int num_of_drop;
}xqc_calc_drop_rate_t;

typedef struct
{
    xqc_calc_drop_rate_t drop_range;
    xqc_list_head_t list_head;
}xqc_calc_drop_rate_node_t;


static inline void xqc_calc_throughout_update(xqc_calc_throughout_t* calc_throughout,float* max_throughout, float cur_throughout_sum, uint16_t cnt)
{
    float cur_throughout = cur_throughout_sum / cnt;
    float max = *max_throughout;
    if(cur_throughout > max)
    {
        max = cur_throughout;
    }

    calc_throughout->ct_cur_throughout = cur_throughout;
    *max_throughout = max;
    calc_throughout->ct_power1 = max != 0 ? cur_throughout / max : 1.0;


}

static inline void xqc_calc_throughout_reset(xqc_calc_throughout_t* p)
{
    p->ct_cur_throughout = 0;
    p->ct_power1 = 0;
}

static inline void xqc_calc_pkt_stream_size(xqc_packet_out_t* packet_out, uint64_t* size)
{
    xqc_po_stream_frame_t* stream_frame = packet_out->po_stream_frames;
    
    for (int i = 0; i < XQC_MAX_STREAM_FRAME_IN_PO; i++)
        *size += stream_frame[i].ps_length;
        
}

static inline float xqc_calc_throughout(uint64_t acked_size, xqc_usec_t time)
{
    /* 单位MB/s */
    float f_acked_size = acked_size * 1000000;
    float f_time = time;
    return f_acked_size / f_time / 1024.0 / 1024.0;
}

void xqc_calc_drop_list_init(xqc_calc_drop_rate_node_t* drop);

void xqc_calc_drop_list_add(xqc_calc_drop_rate_node_t* drop, xqc_packet_number_t high, xqc_packet_number_t low);

void xqc_calc_drop_list_del(xqc_calc_drop_rate_node_t* node, xqc_list_head_t *del_pos);

void xqc_calc_drop_list_update(xqc_send_ctl_t* send_ctl, xqc_packet_number_t lost);

#endif
