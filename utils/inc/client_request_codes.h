#pragma once

typedef enum e_client_rq {
	AUTH_SIGN_UP,
	AUTH_LOGIN,
    RQ_SEARCH_CHAT,
    RQ_ADD_CHAT,
    RQ_GET_CHATS,
    RQ_ADD_USER_TO_CHAT,
    RQ_GET_LOGIN_BY_ID,
    RQ_DISCOVER,
    RQ_CHANGE_USERNAME,
    RQ_ADD_MESSAGE,
    RQ_GET_LAST_MESSAGES
} t_client_rq;
