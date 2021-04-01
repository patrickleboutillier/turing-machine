#ifndef TAPE_H
#define TAPE_H


#define TAPE_LEN 512


class TAPE {
  private:
    static TAPE *instance ;
    char _squares[TAPE_LEN] ;
    int _pos ;
    int _max_pos ;
    TAPE() ;
  public:
    static TAPE *get_tape() ;
    void blank() ;
    void init(const char *tape) ;
    bool apply_ops(const char *ops) ;
    char scan() ;
    void print(const char *mc) ;
} ;


extern TAPE gTAPE ;


#endif
