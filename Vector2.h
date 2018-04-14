// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_VECTOR3_H
#define BUDDHABROT_SERVER_VECTOR3_H

#define VECTOR2(name, mem1, mem2, data_type)                  \
typedef struct {                                              \
    data_type mem1;                                           \
    data_type mem2;                                           \
} name;                                                       \
                                                              \
inline name generate##name(data_type mem1, data_type mem2) {  \
    name new_##name;                                          \
    new_name.##mem1 = mem1;                                   \
    new_name.##mem2 = mem2;                                   \
}                                                             \

#endif //BUDDHABROT_SERVER_VECTOR3_H
