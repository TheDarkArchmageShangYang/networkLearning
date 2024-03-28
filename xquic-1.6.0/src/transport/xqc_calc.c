#include <src/transport/xqc_send_ctl.h>
#include <src/transport/xqc_packet_out.h>
#include <src/transport/xqc_conn.h>
#include <src/transport/xqc_recv_record.h>
#include "src/transport/xqc_calc.h"

void xqc_calc_drop_list_init(xqc_calc_drop_rate_node_t* drop)
{
    xqc_init_list_head(&drop->list_head);
    drop->drop_range.num_of_drop = 0;
    drop->drop_range.send_pktno_range.low = 0;
    drop->drop_range.send_pktno_range.high = 0;
}

void xqc_calc_drop_list_add(xqc_calc_drop_rate_node_t* drop, xqc_packet_number_t high, xqc_packet_number_t low)
{
    xqc_calc_drop_rate_node_t* new_node = xqc_calloc(1, sizeof(xqc_calc_drop_rate_node_t));
    new_node->drop_range.send_pktno_range.high = high;
    new_node->drop_range.send_pktno_range.low = low;
    new_node->drop_range.num_of_drop = 0;
    xqc_init_list_head(&new_node->list_head);
    xqc_list_add_tail(&new_node->list_head, &drop->list_head);
}

void xqc_calc_drop_list_del(xqc_calc_drop_rate_node_t* node, xqc_list_head_t *del_pos)
{   
    xqc_list_head_t *pos = NULL, *next = NULL;
    xqc_calc_drop_rate_node_t *drop = NULL;

    xqc_list_for_each_safe(pos, next, &node->list_head) {
        if (del_pos == pos) {
            break;
        }
        drop = xqc_list_entry(pos, xqc_calc_drop_rate_node_t, list_head);
        xqc_list_del_init(pos);
        xqc_free(drop);
    }
}

void xqc_calc_drop_list_update(xqc_send_ctl_t* send_ctl, xqc_packet_number_t lost)
{
    xqc_connection_t* conn = send_ctl->ctl_conn;
    xqc_calc_drop_rate_node_t* drop_rate = send_ctl->drop_rate;
    xqc_list_head_t *del_pos = NULL;
    xqc_list_head_t *pos = NULL, *next = NULL;
    xqc_calc_drop_rate_node_t *drop = NULL;
    xqc_list_for_each_safe(pos, next, &drop_rate->list_head){
        drop = xqc_list_entry(pos, xqc_calc_drop_rate_node_t, list_head);
        xqc_packet_number_t high = drop->drop_range.send_pktno_range.high;
        xqc_packet_number_t low = drop->drop_range.send_pktno_range.low;
        
        /* 当lost包号在当前遍历的low和high之间，增加该范围的drop数量*/
        if (lost <= high && lost >= low){
            drop->drop_range.num_of_drop++;
        }
        /* 当lost包号大于high，则说明当前范围内的包号的包无更多丢失,需计算drop rate并输出*/
        else if (lost > high){
            del_pos = pos;
            xqc_log(conn->log, XQC_LOG_INFO, "|jndu_test|drop pkt_num:%d|drop rate: %.8f|", 
             lost,(float)(drop->drop_range.num_of_drop) / (float)(high - low + 1));
            continue;
        }
        /* 当lost包号小于low，则无包号对应范围可以计入*/
        else if(lost < low){
            break;
        }

        /* 删除delete_pos之前的节点*/
        if (del_pos) {
            xqc_calc_drop_list_del(drop_rate, del_pos->next);
        }
    }
}