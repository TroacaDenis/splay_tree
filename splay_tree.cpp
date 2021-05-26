#include <iostream>
using namespace std;

class Splay_tree{
    int val;
    Splay_tree *left, *right, *parent;
public:
    Splay_tree();
    Splay_tree(int);
    Splay_tree(int, Splay_tree*);
    int get_val();

    Splay_tree* splay_predecesor(int, Splay_tree**);
    Splay_tree* splay_succesor(int, Splay_tree**);
    Splay_tree* splay_search(int, Splay_tree**);
    Splay_tree* splay_insert(int, Splay_tree**);
    Splay_tree* splay_delete(int, Splay_tree**);
    void rotate_left(Splay_tree*);
    void rotate_right(Splay_tree*);
    Splay_tree* splay(Splay_tree*);

    void tree_afisare(Splay_tree*);
    Splay_tree* tree_search(int, Splay_tree*);
    Splay_tree* predecesor_down(Splay_tree*);
    Splay_tree* predecesor_up(Splay_tree*);
    Splay_tree* succesor_down(Splay_tree*);
    Splay_tree* succesor_up(Splay_tree*);
    Splay_tree* tree_insert(int, Splay_tree*,Splay_tree**, Splay_tree*);

};

Splay_tree::Splay_tree(){
    val=0;
    parent=NULL;
    left=NULL;
    right=NULL;
}
Splay_tree::Splay_tree(int val){
    this->val=val;
    parent=NULL;
    left=NULL;
    right=NULL;
}
Splay_tree::Splay_tree(int val, Splay_tree* parent){
    this->val=val;
    this->parent=parent;
    left=NULL;
    right=NULL;
}
int Splay_tree::get_val(){
    return val;
}

///tree
Splay_tree* Splay_tree::tree_search(int val, Splay_tree* node){
    if(node==NULL)
        return NULL;
    if(node->val==val)
        return node;
    if(val<node->val)
        return tree_search(val,node->left);
    if(val>node->val)
        return tree_search(val,node->right);
}
Splay_tree* Splay_tree::predecesor_up(Splay_tree* node){
    if(node->parent==NULL)
        return NULL;
    if(node->parent->right==node)
        return node->parent;
    return predecesor_up(node->parent);
}
Splay_tree* Splay_tree::predecesor_down(Splay_tree* node){
    if(node->right==NULL)
        return node;
    return predecesor_down(node->right);
}
Splay_tree* Splay_tree::succesor_up(Splay_tree* node){
    if(node->parent==NULL)
        return NULL;
    if(node->parent->left==node)
        return node->parent;
    return predecesor_up(node->parent);
}
Splay_tree* Splay_tree::succesor_down(Splay_tree* node){
    if(node->left==NULL)
        return node;
    return predecesor_down(node->left);
}
Splay_tree* Splay_tree::tree_insert(int val, Splay_tree* node,Splay_tree** aux , Splay_tree* parent=NULL){
    if(node==NULL){
        *aux=new Splay_tree(val, parent);
        return *aux;
    }
    if(val<node->val){
        node->left=tree_insert(val, node->left,&*aux, node);
    }
    else{
       node->right=tree_insert(val, node->right,&*aux, node);
    }
    return node;
}
void Splay_tree::tree_afisare(Splay_tree* node){
    if (node==NULL)
        return ;
    tree_afisare(node->left);
    cout<<node->val<<" ";
    tree_afisare(node->right);
}

///splay
void Splay_tree::rotate_right(Splay_tree* node){
    Splay_tree *aux=node->left;
    node->left=aux->right;
    if (aux->right!=NULL)
        aux->right->parent = node;
    aux->parent = node->parent;
    if (node->parent!=NULL){
        if (node==node->parent->left)
            node->parent->left=aux;
        else
            node->parent->right=aux;
    }
    aux->right=node;
    node->parent=aux;
}
void Splay_tree::rotate_left(Splay_tree* node){
    Splay_tree *aux=node->right;
    node->right=aux->left;
    if (aux->left!=NULL)
        aux->left->parent=node;
    aux->parent=node->parent;
    if (node->parent!=NULL){
        if (node==node->parent->right)
            node->parent->right=aux;
        else
            node->parent->left=aux;
    }
    aux->left=node;
    node->parent=aux;
}
Splay_tree* Splay_tree::splay(Splay_tree* node){
    if(node->parent==NULL)
        return node;
    while(node->parent!=NULL && node->parent->parent!=NULL){
        if(node->parent->left==node){
            if(node->parent->parent->left==node->parent){
                ///zig-zig step
                rotate_right(node->parent->parent);
                rotate_right(node->parent);
            }
            else{
                ///zig-zag step
                rotate_right(node->parent);
                rotate_left(node->parent);
            }
        }
        else{
            if(node->parent->parent->right==node->parent){
                ///zag-zag step
                rotate_left(node->parent->parent);
                rotate_left(node->parent);
            }
            else{
                ///zag-zig step
                rotate_left(node->parent);
                rotate_right(node->parent);
            }
        }
    }
    if(node->parent==NULL)
        return node;
    if(node->parent->left==node)
        rotate_right(node->parent);
    else
        rotate_left(node->parent);
    return node;
}
Splay_tree* Splay_tree::splay_insert(int val, Splay_tree** node){
    Splay_tree *aux=NULL;
    tree_insert(val,*node,&aux);
    *node=splay(aux);
    return *node;
}
Splay_tree* Splay_tree::splay_search(int val, Splay_tree** node){
    Splay_tree *aux=NULL;
    aux=tree_search(val,*node);
    if(aux==NULL)
        return NULL;
    *node=splay(aux);
    return *node;
}
Splay_tree* Splay_tree::splay_predecesor(int val, Splay_tree** node){
    Splay_tree *aux=NULL;
    aux=tree_search(val,*node);
    if(aux==NULL)
        return NULL;
    if(aux->left==NULL)
        aux=predecesor_up(aux);
    else
        aux=predecesor_down(aux->left);
    if(aux==NULL)
        return NULL;
    *node=splay(aux);
    return *node;
}
Splay_tree* Splay_tree::splay_succesor(int val, Splay_tree** node){
    Splay_tree *aux=NULL;
    aux=tree_search(val,*node);
    if(aux==NULL)
        return NULL;
    if(aux->right==NULL)
        aux=succesor_up(aux);
    else
        aux=succesor_down(aux->right);
    if(aux==NULL)
        return NULL;
    *node=splay(aux);
    return *node;
}
Splay_tree* Splay_tree::splay_delete(int val, Splay_tree** node){
    Splay_tree *aux=NULL;
    aux=splay_search(val,&*node);
    if(aux==NULL)
        return NULL;
    if(aux->left==NULL){
        aux->right->parent=NULL;
        *node=aux->right;
        return *node;
    }
    if(aux->right==NULL){
        aux->left->parent=NULL;
        *node=aux->left;
        return *node;
    }
    aux->left->parent=NULL;
    Splay_tree *left_root;
    left_root=predecesor_down(aux->left);
    left_root=splay(left_root);
    left_root->right=aux->right;
    aux->right->parent=left_root;
    *node=left_root;
    return *node;
}

///main
int main(){
    Splay_tree v;
    Splay_tree *root = NULL;

    ///inserare
    v.splay_insert(50,&root);
    v.splay_insert(30,&root);
    v.splay_insert(20,&root);
    v.splay_insert(40,&root);
    v.splay_insert(70,&root);
    v.splay_insert(60,&root);
    v.splay_insert(80,&root);
    v.splay_insert(10,&root);

    ///afisare
    v.tree_afisare(root);
    cout<<'\n';

    ///stergere
    v.splay_delete(60,&root);
    v.tree_afisare(root);
    cout<<'\n';

    ///cautare
    if(v.splay_search(40,&root)!=NULL)
        cout<<"nodul exista"<<'\n';
    else
        cout<<"nodul nu exista"<<'\n';

    ///succesor si predecesor
    cout<<v.splay_predecesor(50,&root)->get_val()<<'\n';
    cout<<v.splay_succesor(50,&root)->get_val()<<'\n';

}
