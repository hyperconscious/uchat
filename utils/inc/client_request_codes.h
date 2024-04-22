#pragma once

typedef enum e_client_rq {
	AUTH_SIGN_UP,
	AUTH_LOGIN,
    RQ_SEARCH_CHAT,
    RQ_ADD_CHAT,
    RQ_GET_CHATS,
    RQ_ADD_USER_TO_CHAT,
    RQ_DISCOVER
} t_client_rq;
