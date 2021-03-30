#ifndef LAMBDA_H
#define LAMBDA_H

#include <cassert>

#define MAX(a,b) ((a) > (b) ? a : b)

extern int NB_LAMBDA ;
extern int MAX_LAMBDA ;
extern int SIZE_LAMBDA ;
extern int MAX_SIZE_LAMBDA ;

// Lambda contains most of the lambda management code and can be used
// directly in external code.
template <typename T> class Lambda {};
template <typename Out, typename ...In> class Lambda<Out(In...)> {
  public:
    Lambda() : lambda(nullptr), deleteLambda(nullptr), copyLambda(nullptr), executeLambda(nullptr), helper(nullptr){
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += sizeof(*this) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    Lambda(Lambda<Out(In...)> const &other) : 
        lambda(other.copyLambda ? other.copyLambda(other.lambda) : nullptr),
        deleteLambda(other.deleteLambda), copyLambda(other.copyLambda), executeLambda(other.executeLambda), helper(other.helper){
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += (sizeof(*this) + (long)(helper(this->lambda, 's'))) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    template<typename T> Lambda(T const &lambda) : lambda(nullptr){
      // Copy should set all variables
      copy(lambda);
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += (sizeof(*this) + (long)(helper(this->lambda, 's'))) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    ~Lambda(){
      NB_LAMBDA-- ;
      SIZE_LAMBDA -= sizeof(*this) ;
      if (this->lambda != nullptr){
        SIZE_LAMBDA -= (long)(helper(this->lambda, 's')) ;      
      }
      if (deleteLambda != nullptr) deleteLambda(lambda);
    }

    Lambda<Out(In...)> &operator =(Lambda<Out(In...)> const &other){
      if (this->lambda != nullptr) deleteLambda(this->lambda);
      this->lambda = other.copyLambda ? other.copyLambda(other.lambda) : nullptr;
      this->deleteLambda = other.deleteLambda;
      this->copyLambda = other.copyLambda;
      this->helper = other.helper;
      this->executeLambda = other.executeLambda;
      return *this;
    }

    template<typename T> Lambda<Out(In...)> &operator =(T const &lambda){
      copy(lambda);
      return *this;
    }

    Out operator()(In ... in){
      assert(lambda != nullptr);
      return executeLambda(lambda, in...);
    }

    operator bool(){
      return lambda != nullptr;
    }

  private:
    template<typename T> void copy(T const &lambda){
      if (this->lambda != nullptr) deleteLambda(this->lambda);
      this->lambda = new T(lambda);
      deleteLambda = [](void *lambda){
        delete (T *)lambda;
      };

      copyLambda = [](void *lambda) -> void * {
        return lambda ? new T(*(T *)lambda) : nullptr;
      };

      executeLambda = [](void *lambda, In... arguments) -> Out {
        return ((T *)lambda)->operator()(arguments...);
      };
      
      helper = [](void *lambda, char h) -> void * {
        switch (h){
          case 's' :
            return (void *)(lambda ? sizeof(*(T *)lambda) : 0) ;
        }
      };
    }

    void *lambda;
    void (*deleteLambda)(void *);
    void *(*copyLambda)(void *);
    void *(*helper)(void *, char);
    Out (*executeLambda)(void *, In...);
};

#endif