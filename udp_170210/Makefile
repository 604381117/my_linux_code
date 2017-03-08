udp_chat:
	gcc udp_chat_client.c -o udp_chat_client 
	gcc udp_chat_sever.c -o udp_chat_sever
	gcc tcp_chat_client_epoll.c -o tcp_chat_client_epoll
	gcc tcp_chat_sever_epoll.c -o tcp_chat_sever_epoll
clean:
	rm -rf udp_chat_sever udp_chat_client
	rm -rf tcp_chat_client_epoll tcp_chat_sever_epoll
