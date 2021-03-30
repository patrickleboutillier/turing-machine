#ifndef TAPE_H
#define TAPE_H


#define TAPE_LEN 128


class MCONFIG ;


class TAPE {
  private:
    char _squares[TAPE_LEN] ;
    int _pos ;
  public:
    TAPE() ;
    TAPE(const char *tape) ;
    bool apply_ops(const char *ops) ;
    char scan() ;
    void print(MCONFIG mc) ;
} ;

#endif
