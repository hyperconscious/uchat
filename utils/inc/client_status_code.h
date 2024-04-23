#pragma once 

typedef enum e_client_status_code {
    NO_CONNECTION_WITH_SERVER,
    WRONG_PASSWORD,
    LOGIN_ALREADY_EXIST,
    LOGIN_DOESNT_EXIST,
    SUCCESS_REGISTRATION,
    SUCCESS_LOGIN,
    SUCCSESS
}            t_client_status_code;

