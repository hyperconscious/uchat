#pragma once

typedef enum e_client_rq {
	AUTH_SIGN_UP,
	AUTH_LOGIN,
    RQ_SEARCH_CHAT,
    RQ_ADD_CHAT,
    RQ_GET_CHATS
} t_client_rq;
