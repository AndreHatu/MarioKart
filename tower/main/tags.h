#ifndef TAGS_H
#define TAGS_H
#include <string.h>
#include <stdint.h>

#define TAGLEN 6
#define NTAGS_CP 9
#define NTAGS_MOD 6




uint8_t is_cp(char* val, int CP);
uint8_t is_mod(char* val);


#endif