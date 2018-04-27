#pragma once
#include <functional>
#include <iostream>
#include "NodeBB.hpp"
#include "Queue.hpp"


using namespace std;

template <class D, class K>
class TreeBB
{

private:

    NodeBB<D,K> * root;

private:

    void deleteTree(NodeBB<D,K> *& node) {

      if (node != nullptr) {
        deleteTree(node->getLeft());
        deleteTree(node->getRight());
        delete node;
        node = nullptr;
      }

    }

    void insertNode(NodeBB<D,K> *& node, K &clave, D &data) {

      if (node==nullptr) {

        node = new NodeBB<D,K>(data, clave);

      }
      else {

        if (clave < node->getClave()) // Left branch
          insertNode(node->getLeft(), clave, data);
        else // Right branch
          insertNode(node->getRight(), clave, data);

      }
    }

    bool searchNode(NodeBB<D,K> *& node, const K& clave) {

      if (node == nullptr)
        return false;
      if (node->getClave() == clave)
        return true;
      if (node->getClave() > clave) // Left branch
        return searchNode(node->getLeft(), clave);
      else
        return searchNode(node->getRight(), clave);

    }


    void sustituye(NodeBB<D,K> *& eliminado, NodeBB<D,K> *& sust) {

      if (sust->getRight() != nullptr)

        sustituye(eliminado, sust->getRight());

      else {

        eliminado->setDato(sust->getDato());
        eliminado->setClave(sust->getClave());
        eliminado = sust;
        sust = sust->getLeft();

      }
    }
   
    void deleteNode(NodeBB<D,K> *& node, const K& clave) {

      if (root == nullptr)
        return; // break -> no found key in tree

      if (clave < node->getClave())

        deleteNode(node->getLeft(), clave);

      else if (clave > node->getClave())

        deleteNode(node->getRight(), clave);

      else { // clave == node clave

        NodeBB<D,K> * eliminado = node;

        if (node->getRight()==nullptr)
          node = node->getLeft();
        else if (node->getLeft() == nullptr)
          node = node->getRight();
        else
          sustituye(eliminado, node->getLeft());

        delete eliminado;
        eliminado = nullptr;
      }
    }
      
public:

  TreeBB(void):
   root(nullptr) {}

  virtual ~TreeBB(void) {
    deleteTree(root);
  }

  bool isEmpty(void) {
    return (root == nullptr);
  }

  void insert(D data, K clave) {
    insertNode(root, clave, data);
  }

  bool search(K clave) {
    return searchNode(root, clave);
  }

  void eliminar(K clave) {
    deleteNode(root,clave);
  }

  void mostrar() {

    Queue<NodeBB<D,K> *> parents;
    Queue<NodeBB<D,K> *> childrens;

    auto addToChildrens = [&childrens](NodeBB<D,K> * node){

      if (node!= nullptr) {
        childrens.cons(node->getLeft());
        childrens.cons(node->getRight());
      }
    };

    parents.cons(root);
    int level = 0;

    while (!parents.isEmpty()) {

      cout << "Nivel " << level << ":";

      while (!parents.isEmpty()) {

        NodeBB<D,K> * aux = parents.pop();

        if (aux != nullptr)
          cout << "[" << aux->getClave() << "] ";
        else
          cout << "[.]";

        addToChildrens(aux);
      }

      cout << endl;
      level++;
      swap(parents, childrens);
    }

  }

};



