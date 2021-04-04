#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>


class PRINT {
  public:
    static void print(const char *str){
        printf("%s", str) ;
    }
    static void print(char c){
        printf("%c", c) ;
    }
    static void print(int i){
        printf("%d", i) ;
    }
    static void print(long l){
        printf("%ld", l) ;
    }
} ;


#endif