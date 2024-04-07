## recv packet

3543:xqc_conn_process_packet

->xqc_packet_in_init

->3564:xqc_packet_process_single





## send packet

xqc_conn.c1607:xqc_conn_send_packets组装报文头

xqc_conn.c1528:xqc_path_send_packets

xqc_conn.c:1869发送数据包

xqc_conn.c:1854发送数据包

xqc_conn.c:1779发送数据包

->xqc_send_ctl:643发送数据包

## RTT等

xqc_conn.c2683:xqc_conn_get_lastest_rtt

4732:xqc_conn_get_min_srtt

xqc_send_ctl.c829:xqc_sned_ctl_on_ack_received收到ACK后更新rtt等数据

send_ctl->ctl_srtt获取RTT

send_ctl->ctl