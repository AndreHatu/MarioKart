#include "tags.h"

char c0[NTAGS_CP][TAGLEN] = {
    ")$7+1",
	")$<~m",
	")$u2h",
	")$6rI",
	")$%rZ",
	")$G'M",
	")$1(6",
	")$6|e",
	")$w \\"
};

char c1[NTAGS_CP][TAGLEN] = {
	")$d/h",
	")$>,=",
	")$v-t",
	")$Pl1",
	")$4^e",
	")$c*h",
	")$V0w",
	")$8e^",
	")$0yd"
};

char c2[NTAGS_CP][TAGLEN] = {
	")$OZ:",
	")$=*8",
	")$&KD",
	")$<du",
	")$>`Q",
	")$?8*",
	")$6>%",
	")$#Q ",
	")$I5Q"
};

char c3[NTAGS_CP][TAGLEN] = {
	")$28+",
	")$93\'",
	")$>2#",
	")$zW\"",
	")$h^;",
	")$&V ",
	")$Y,X",
	")$a:V",
	")$ >3"
};

char c4[NTAGS_CP][TAGLEN] = {
	")$y(R",
	")$&83",
	")$|\"Q",
	")$Lb#",
	")$Jm(",
	")$C/A",
	")$+Vt",
	")$c,d",
	")$=l^"
};

char modifiers[NTAGS_MOD][TAGLEN] = {
	"r68;E",
	")$=N\\",
	")$8lY",
	")$/$ ",
	")$x;P",
	")$ 8+"
};

uint8_t is_cp(char* val, int CP){
    switch(CP){
        case 0: for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c0[i], val) == 0)
                        return 1;
                } break;
        case 1: for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c1[i], val) == 0)
                        return 1;
                } break;
        case 2: for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c2[i], val) == 0)
                        return 1;
                } break;
        case 3: for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c3[i], val) == 0)
                        return 1;
                } break;
        case 4: for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c4[i], val) == 0)
                        return 1;
                } break;
        default:
                for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c0[i], val) == 0)
                        return 1;
                } 
                for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c1[i], val) == 0)
                        return 1;
                } 
                for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c2[i], val) == 0)
                        return 1;
                } 
                for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c3[i], val) == 0)
                        return 1;
                } 
                for(int i = 0; i < NTAGS_CP; i++){
                    if(strcmp(c4[i], val) == 0)
                        return 1;
                } 
    }
    return 0;
}


uint8_t is_mod(char* val){
     for(int i = 0; i < NTAGS_MOD; i++){
        if(strcmp(modifiers[i], val) == 0)
            return 1;
    }
    return 0;
}