#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "MemoryPool.h"

#include <iomanip>
#include <iostream>

enum RBTColor{ RED, BLACK };
template <class T>
class RBTNode{
public:
    RBTColor color;    
    T key;            
    RBTNode *left;    
    RBTNode *right;   
    RBTNode *parent; 
    RBTNode(){}
    void init(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r){
        key = value,color=c,left=l,right=r;
    }
};
#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

template <class T>
class RBTree {  
public:
    RBTree(int max_size):mRoot(nullptr),max_deep(0),pool(max_size){   }
    ~RBTree(){ destroy(mRoot); }
    T search(T key){  return search(mRoot, key)->key; }
    RBTNode<T>* successor(RBTNode<T> *x){
        if (x->right != nullptr)return minimum(x->right);
        RBTNode<T>* y = x->parent;
        while ((y!=nullptr) && (x==y->right)){
            x = y;
            y = y->parent;
        }
        return y;
    }
    RBTNode<T>* predecessor(RBTNode<T> *x){
        if (x->left != nullptr) return maximum(x->left);
        RBTNode<T>* y = x->parent;
        while ((y!=nullptr) && (x==y->left)) {
            x = y;
            y = y->parent;
        }
        return y;
    }
    bool insert(T key){
        RBTNode<T> *z=pool.get();
        if (z== nullptr) return false;
        z->init(key,BLACK,nullptr,nullptr,nullptr);
        insert(mRoot, z);
        return true;
    }
    void remove(T key){
        RBTNode<T> *node;
        if ((node = search(mRoot, key)) != nullptr) remove(mRoot, node);
    }
    void destroy(){ destroy(mRoot); }
    int getMaxDeep(){return max_deep;}
    void print(){
        if (mRoot != NULL)
            print(mRoot, mRoot->key, 0);
    }
    void print(RBTNode<T>* tree, T key, int direction){
        if(tree != NULL){
            if(direction==0) std::cout << std::setw(2) << tree->key << "(B) is root" << std::endl;
            else std::cout << std::setw(2) << tree->key <<  (rb_is_red(tree)?"(R)":"(B)") << " is " << std::setw(2) << key << "'s "  << std::setw(12) << (direction==1?"right child" : "left child") << std::endl;
            print(tree->left, tree->key, -1);
            print(tree->right,tree->key,  1);
        }
    }
private:
    RBTNode<T>* search(RBTNode<T>* x, T key) const {
        if (x==nullptr || x->key==key) return x;
        if (key < x->key) return search(x->left, key);
        else return search(x->right, key);
    }
    void leftRotate(RBTNode<T>* &root, RBTNode<T>* x){
        RBTNode<T> *y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) {root = y;}
        else{
            if (x->parent->left == x) x->parent->left = y;  
            else x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(RBTNode<T>* &root, RBTNode<T>* y){
        RBTNode<T> *x = y->left;
        y->left = x->right;
        if (x->right != nullptr) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)  {root = x; }
        else {
            if (y == y->parent->right) y->parent->right = x;
            else y->parent->left = x;   
        }  
        x->right = y;
        y->parent = x;
    }
    void insert(RBTNode<T>* &root, RBTNode<T>* node){
        RBTNode<T> *y = nullptr;
        RBTNode<T> *x = root;
        int now = 0;
        while (x != nullptr){
            y = x;
            now++;
            if (node->key < x->key) x = x->left;
            else x = x->right;
        }
        if(max_deep<now)max_deep = now;
        node->parent = y;
        if (y!=nullptr){
            if (node->key < y->key) y->left = node;
            else y->right = node;
        }
        else root = node;
        node->color = RED;
        insertFixUp(root, node);
    }
    void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node){
        RBTNode<T> *parent, *gparent;
        while ((parent = rb_parent(node)) && rb_is_red(parent)){
            gparent = rb_parent(parent);
            if (parent == gparent->left){ {
                    RBTNode<T> *uncle = gparent->right;
                    if (uncle && rb_is_red(uncle)){
                        rb_set_black(uncle);
                        rb_set_black(parent);
                        rb_set_red(gparent);
                        node = gparent;
                        continue;
                    }
                }
                if (parent->right == node){
                    RBTNode<T> *tmp;
                    leftRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                rb_set_black(parent);
                rb_set_red(gparent);
                rightRotate(root, gparent);
            }
            else {{
                    RBTNode<T> *uncle = gparent->left;
                    if (uncle && rb_is_red(uncle))
                    {
                        rb_set_black(uncle);
                        rb_set_black(parent);
                        rb_set_red(gparent);
                        node = gparent;
                        continue;
                    }
                }
                if (parent->left == node){
                    RBTNode<T> *tmp;
                    rightRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                rb_set_black(parent);
                rb_set_red(gparent);
                leftRotate(root, gparent);
            }
        }
        rb_set_black(root);
    }
    void remove(RBTNode<T>* &root, RBTNode<T> *node){
        RBTNode<T> *child, *parent;
        RBTColor color;
        if ( (node->left!=nullptr) && (node->right!=nullptr) ){
            RBTNode<T> *replace = node;
            replace = replace->right;
            while (replace->left != nullptr) replace = replace->left;
            if (rb_parent(node)){
            if (rb_parent(node)->left == node)    rb_parent(node)->left = replace;
            else    rb_parent(node)->right = replace;
            }
            else root = replace;
            child = replace->right;
            parent = rb_parent(replace);
            color = rb_color(replace);
            if (parent == node){parent = replace;}
            else
            {
                if (child)rb_set_parent(child, parent);
                parent->left = child;
                replace->right = node->right;
                rb_set_parent(node->right, replace);
            }
            replace->parent = node->parent;
            replace->color = node->color;
            replace->left = node->left;
            node->left->parent = replace;
            if (color == BLACK)removeFixUp(root, child, parent);
            pool.free(node);
            return ;
        }
        if (node->left !=nullptr)child = node->left;
        else child = node->right;
        parent = node->parent;
        color = node->color;
        if (child)child->parent = parent;
        if (parent){
            if (parent->left == node) parent->left = child;
            else    parent->right = child;
        }
        else root = child;
        if (color == BLACK)removeFixUp(root, child, parent);
        pool.free(node);
    }
    void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent){
        RBTNode<T> *other;
        while ((!node || rb_is_black(node)) && node != root){
            if (parent->left == node){
                other = parent->right;
                if (rb_is_red(other)){
                    rb_set_black(other);
                    rb_set_red(parent);
                    leftRotate(root, parent);
                    other = parent->right;
                }
                if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right))){
                    rb_set_red(other);
                    node = parent;
                    parent = rb_parent(node);
                }
                else {
                    if (!other->right || rb_is_black(other->right)){
                        rb_set_black(other->left);
                        rb_set_red(other);
                        rightRotate(root, other);
                        other = parent->right;
                    }
                    rb_set_color(other, rb_color(parent));
                    rb_set_black(parent);
                    rb_set_black(other->right);
                    leftRotate(root, parent);
                    node = root;
                    break;
                }
            }
            else{
                other = parent->left;
                if (rb_is_red(other)){
                    rb_set_black(other);
                    rb_set_red(parent);
                    rightRotate(root, parent);
                    other = parent->left;
                }
                if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right))){
                    rb_set_red(other);
                    node = parent;
                    parent = rb_parent(node);
                }
                else{
                    if (!other->left || rb_is_black(other->left)){
                        rb_set_black(other->right);
                        rb_set_red(other);
                        leftRotate(root, other);
                        other = parent->left;
                    }
                    rb_set_color(other, rb_color(parent));
                    rb_set_black(parent);
                    rb_set_black(other->left);
                    rightRotate(root, parent);
                    node = root;
                    break;
                }
            }
        }
        if (node)rb_set_black(node);
    }
    void destroy(RBTNode<T>* &tree){
        if (tree==nullptr)return ;
        if (tree->left != nullptr)  destroy(tree->left);
        if (tree->right != nullptr) destroy(tree->right);
        pool.free(tree);
        tree=nullptr;
    }
private:
    RBTNode<T> *mRoot;  
    int max_deep;
    MemoryPool<RBTNode<T>> pool;
};

/*

#include <iomanip>
#include <iostream>
    void print(){
        if (mRoot != NULL)
            print(mRoot, mRoot->key, 0);
    }
    void print(RBTNode<T>* tree, T key, int direction){
        if(tree != NULL){
            if(direction==0) std::cout << setw(2) << tree->key << "(B) is root" << std::endl;
            else std::cout << setw(2) << tree->key <<  (rb_is_red(tree)?"(R)":"(B)") << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << std::endl;
            print(tree->left, tree->key, -1);
            print(tree->right,tree->key,  1);
        }
    }
*/

#endif