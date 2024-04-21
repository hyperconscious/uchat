#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

char *serialize_chat(const t_chat *chat);
t_chat *deserialize_chat(const char *serialized_data);