/*
Copyright (c) 2009 Yahoo! Inc.  All rights reserved.  The copyrights
embodied in the content of this file are licensed under the BSD
(revised) open source license
 */

#ifndef CACHE_H
#define CACHE_H

#include "parse_example.h"

const size_t int_size = 5;
const size_t char_size = 2;

char* run_len_decode(char *p, size_t& i);
char* run_len_encode(char *p, size_t i);

int read_cached_features(parser* p, example* ae);
void cache_features(parser* p, example* ae);

#endif
