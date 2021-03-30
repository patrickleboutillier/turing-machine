#ifndef LAMBDA_H
#define LAMBDA_H

#include <cassert>

#define MAX(a,b) ((a) > (b) ? a : b)

extern int NB_LAMBDA ;
extern int MAX_LAMBDA ;
extern int SIZE_LAMBDA ;
extern int MAX_SIZE_LAMBDA ;


// LambdaExecutor is an internal class that adds the ability to execute to
// Lambdas. This functionality is separated because it is the only thing
// that needed to be specialized (by return type).

// generateExecutor or receiveExecutor must be called after constructing,
// before use
template<typename T> class LambdaExecutor {} ;
template <typename Out, typename... In> class LambdaExecutor<Out(In...)> {
  public:
    Out operator()(In ... in){
      assert(lambdaref != nullptr);
      return executeLambda(lambdaref, in...);
    }

  protected:
    LambdaExecutor(void *&lambdaref) : lambdaref(lambdaref) {}

    ~LambdaExecutor(){
    }

    template <typename T> void generateExecutor(T const &lambda){
      executeLambda = [](void *lambda, In... arguments) -> Out {
        return ((T *)lambda)->operator()(arguments...);
      };
    }

    void receiveExecutor(LambdaExecutor<Out(In...)> const &other){
      executeLambda = other.executeLambda;
    }

  private:
    void *&lambdaref;
    Out (*executeLambda)(void *, In...);
};


// Lambda contains most of the lambda management code and can be used
// directly in external code.
template <typename T> class Lambda {};
template <typename Out, typename ...In> class Lambda<Out(In...)> : public LambdaExecutor<Out(In...)> {
  public:
    Lambda() : LambdaExecutor<Out(In...)>(lambda), lambda(nullptr), deleteLambda(nullptr), copyLambda(nullptr), executeLambda2(nullptr), helper(nullptr){
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += sizeof(*this) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    Lambda(Lambda<Out(In...)> const &other) : LambdaExecutor<Out(In...)>(lambda),
        lambda(other.copyLambda ? other.copyLambda(other.lambda) : nullptr),
        deleteLambda(other.deleteLambda), copyLambda(other.copyLambda), executeLambda2(other.executeLambda2), helper(other.helper){
      // this->receiveExecutor(other);
      NB_LAMBDA++ ;
      MAX_LAMBDA = MAX(MAX_LAMBDA, NB_LAMBDA) ;
      SIZE_LAMBDA += (sizeof(*this) + (long)(helper(this->lambda, 's'))) ;
      MAX_SIZE_LAMBDA = MAX(MAX_SIZE_LAMBDA, SIZE_LAMBDA) ;
    }

    template<typename T> Lambda(T const &lambda) : LambdaExecutor<Out(In...)>(this->lambda), lambda(nullptr){
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
      // this->receiveExecutor(other);
      this->deleteLambda = other.deleteLambda;
      this->copyLambda = other.copyLambda;
      this->helper = other.helper;
      this->executeLambda2 = other.executeLambda2;
      return *this;
    }

    template<typename T> Lambda<Out(In...)> &operator =(T const &lambda){
      copy(lambda);
      return *this;
    }

    Out operator()(In ... in){
      assert(lambda != nullptr);
      return executeLambda2(lambda, in...);
    }

    operator bool(){
      return lambda != nullptr;
    }

  private:
    template<typename T> void copy(T const &lambda){
      if (this->lambda != nullptr) deleteLambda(this->lambda);
      this->lambda = new T(lambda);
      // this->generateExecutor(lambda);
      deleteLambda = [](void *lambda){
        delete (T *)lambda;
      };

      copyLambda = [](void *lambda) -> void * {
        return lambda ? new T(*(T *)lambda) : nullptr;
      };

      executeLambda2 = [](void *lambda, In... arguments) -> Out {
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
    Out (*executeLambda2)(void *, In...);
};

#endif