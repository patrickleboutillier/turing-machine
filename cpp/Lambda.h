#ifndef LAMBDA_H
#define LAMBDA_H

#include <stdio.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? a : b)

extern int NB_LAMBDA ;
extern int MAX_LAMBDA ;
extern int SIZE_LAMBDA ;
extern int MAX_SIZE_LAMBDA ;

class MCONFIG ;
void storeOut(MCONFIG mc) ; 


// Lambda contains most of the lambda management code and can be used
// directly in external code.
class Lambda {
  public:
    Lambda() : lambda(nullptr), helper(nullptr){
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += sizeof(*this) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    Lambda(Lambda const &other) : 
        lambda(other.helper ? other.helper(other.lambda, 'c', '\0') : nullptr),
        helper(other.helper){
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += (sizeof(*this) + (long)(helper(this->lambda, 's', '\0'))) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    template<typename T> Lambda(T const &lambda) : lambda(nullptr){
      // Copy should set all variables
      copy(lambda);
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += (sizeof(*this) + (long)(helper(this->lambda, 's', '\0'))) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    ~Lambda(){
      NB_LAMBDA-- ;
      SIZE_LAMBDA -= sizeof(*this) ;
      if (this->lambda != nullptr){
        SIZE_LAMBDA -= (long)(helper(this->lambda, 's', '\0')) ;      
        helper(this->lambda, 'd', '\0') ;
      }
    }

    Lambda &operator =(Lambda const &other){
      if (this->lambda != nullptr) helper(this->lambda, 'd', '\0') ;
      this->lambda = other.helper ? other.helper(other.lambda, 'c', '\0') : nullptr;
      this->helper = other.helper;
      return *this;
    }

    template<typename T> Lambda &operator =(T const &lambda){
      copy(lambda);
      return *this;
    }

    void operator()(char s){
      helper(this->lambda, 'e', s) ;
    }

    operator bool(){
      return lambda != nullptr;
    }

  private:
    template<typename T> void copy(T const &lambda){
      if (this->lambda != nullptr) helper(this->lambda, 'd', '\0') ;
      this->lambda = new T(lambda);
      helper = [](void *lambda, char h, char s) -> void * {
        switch (h){
          case 's' : {
            long size = (lambda ? sizeof(*(T *)lambda) : 0) ; 
            // printf("size: %ld\n", size) ;
            return (void *)size ;
          }
          case 'd' : { 
            delete (T *)lambda ; return nullptr ;
          }
          case 'c':
            return lambda ? new T(*(T *)lambda) : nullptr ;
          case 'e':
            storeOut(((T *)lambda)->operator()(s)) ;
            return nullptr ;
        }
      } ;
    }

    void *lambda;
    void *(*helper)(void *, char, char) ;
} ;


#endif