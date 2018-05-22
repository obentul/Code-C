struct client_info;

#define IP_SERV 127.0.0.1
#define PORT_SERV 6666
#define DOMAIN_SERV "xxx"
#define DESC_SERV "Server1"
#define LINK_MAX 100
#define MQ_LEN 4096

struct server_info{
	/*network info*/
	char *ip;			//ip地址
	long port;			//端口
	char *domain_name;		//域名
	char *desc;			//描述
	
	/*connection info*/
	long link_max;			//最大连接数
	struct client_info *black_list;	//黑名单

	/*property*/
	short accept_thread_max;	//accept最大线程数
	short accept_thread_def;	//accept默认线程数
	short epoll_thread_max;		//epoll最大线程数
	short epoll_thread_def;		//eopll默认线程数
};

struct client_info{
	char *ip;
	long port;
	char *domain_name;
	char *desc;

	struct client_info *next;
};

struct msgbuf {
        long mtype;       		//使用connect socket id 作为消息类型
        char mtext[MQ_LEN];    		//消息长度
};

