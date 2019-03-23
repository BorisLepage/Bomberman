#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#ifdef __APPLE__
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

#ifndef SERVER_H_
#define SERVER_H_

#define MAP_SIZE 12
#define MAX_PLAYERS 4
extern int sock;

struct msg_struct {
	int id;
	char key[10];
};

typedef struct server_data_s server_data_t;
typedef struct s_server_game t_server_game;
typedef struct s_player_infos t_player_infos;
typedef struct s_other t_other;
typedef char t_map[MAP_SIZE];

struct server_data_s {
	int magic[5];
	int sock_fd[MAX_PLAYERS];
	int sock_id;
	struct sockaddr_in client;
	unsigned int client_addr_len;
};

struct s_player_infos {
	char connected;
	char alive;
	int x_pos;
	int y_pos;
	int current_dir;
	int current_speed;
	int max_speed;
	int bombs_left;
	int bombs_capacity;
	int frags;
};

struct s_other {
	int a;
};

t_player_infos *player1;
t_player_infos *player2;
t_player_infos *player3;
t_player_infos *player4;

struct s_server_game {
	t_player_infos player1;
	t_player_infos player2;
	t_player_infos player3;
	t_player_infos player4;
	t_map map;
	t_other infos;
};

int init_server(unsigned short port);
void *handler(void *input);

#endif