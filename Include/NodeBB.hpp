#pragma once

template <class D, class K>
class NodeBB
{

private:

  K clave_;
  D data_;
  NodeBB<D,K> * left_;
  NodeBB<D,K> * right_;

public:

  NodeBB(D data, K clave):
    clave_(clave),
    data_(data),
    left_(nullptr),
    right_(nullptr) {};

  virtual ~NodeBB() {};

  K getClave() const {
    return clave_;
  }
  
  void setClave(K clave) {
    clave_ = clave;
  }

  void setDato(D a){
    data_ = a;
  }

  D getDato(void) const {
    return data_;
  }

  void setRight(NodeBB<D,K> * n) {
    right_ = n;
  }

  NodeBB<D,K> *& getRight(void) {
    return right_;
  }

  void setLeft(NodeBB<D,K> * n) {
    left_ = n;
  }

  NodeBB<D,K> *& getLeft(void) {
    return left_;
  }

};

