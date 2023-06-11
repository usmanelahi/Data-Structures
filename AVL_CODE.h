#include <stack>
using namespace std;

template <typename T>
class avl{

    struct treeNode{
        T data;
        treeNode *lchild, *rchild;
        int h;//height of the node

        treeNode(const T& new_data, treeNode*lc=NULL, treeNode*rc=NULL, int nh=0){
            data=new_data;
            lchild=lc;
            rchild=rc;
            h=nh;
        }
    } *root;
    int n;//size of the tree

        int height(treeNode*ptr){
            if(ptr==NULL)
                return -1;
            else
                return ptr->h;
        }

        int bf(treeNode*ptr){
            return height(ptr->rchild)- height(ptr->lchild);
        }

        bool updateHeight(treeNode* ptr){
            int old_h = height(ptr);
            int new_h = max(height(ptr->lchild), height(ptr->rchild))+1;
            ptr->h=new_h;
            return (old_h!=new_h);

        }


    bool getAccess(const T& key, treeNode*& ptr, stack<treeNode*> & ancestors)
    {
        ptr=root;

        while(ptr!=NULL && ptr->data!=key){
            ancestors.push(ptr);
            if(key<ptr->data)
                ptr=ptr->lchild;
            else
                ptr=ptr->rchild;
        }

        return (ptr!=NULL);
    }

    int childCount(treeNode * ptr){
        if(ptr==NULL || (ptr->lchild==NULL && ptr->rchild==NULL))
            return 0;
         else if(ptr->lchild!=NULL && ptr->rchild!=NULL)
            return 2;
        else return 1;

    }

    void eraseCase0(treeNode* ptr, treeNode* pptr){

        if(ptr==root){
            //cout<<"Root updated..."<<endl;
            root=NULL;
        }else if(ptr==pptr->lchild){
            pptr->lchild=NULL;
        }else{
            pptr->rchild=NULL;
        }

        delete ptr;
    }

    void eraseCase1(treeNode* ptr, treeNode* pptr){
        treeNode* cptr;
        if(ptr->rchild!=NULL)
            cptr=ptr->rchild;
        else
            cptr=ptr->lchild;
        //ptr: node, pptr: parent of ptr, cptr: child of ptr
        if(ptr==root){
            //cout<<"Root updated..."<<endl;
            root=cptr;
            delete ptr;
        }else{
            if(ptr==pptr->lchild)//ptr is left child of pptr
                pptr->lchild=cptr;
            else//ptr is right child of pptr
                pptr->rchild=cptr;


            delete ptr;
        }
    }

    void eraseCase2(treeNode* ptr, treeNode*& pptr, stack<treeNode*>&ancestors){

        treeNode * nptr = ptr->rchild, *pnptr=ptr;
        ancestors.push(ptr);
        while(nptr->lchild!=NULL){
            pnptr=nptr;
            ancestors.push(nptr);
            nptr=nptr->lchild;
        }

        swap(ptr->data,nptr->data);

        if(childCount(nptr)==0){
            eraseCase0(nptr, pnptr);
        }else{
            eraseCase1(nptr, pnptr);
        }
    }


    bool rr(treeNode * ptr, treeNode * pptr){
        //right rotate around ptr
        treeNode* cptr = ptr->lchild;

        if(cptr==NULL)
            return false;
        else{
            //what is the node itself is the root
            //promote cptr
            if(pptr==NULL){
                root=cptr;
            }else{
                if(ptr==pptr->lchild)
                    pptr->lchild=cptr;
                else
                    pptr->rchild=cptr;
            }


            //adjust children
            treeNode * rc_cptr = cptr -> rchild;
            cptr->rchild = ptr;
            ptr->lchild=rc_cptr;

            //update heights of ptr and cptr
            updateHeight(ptr);
            updateHeight(cptr);

            return true;
        }
    }


    bool rl(treeNode* ptr, treeNode*pptr){
        //left rotate around ptr

        treeNode * cptr = ptr->rchild;

        if(cptr==NULL)
            return false;
        else{
            if(pptr==NULL){
                    root=cptr;
            }else{
                if(ptr==pptr->lchild)
                    pptr->lchild=cptr;
                else
                    pptr->rchild=cptr;
            }


            treeNode * lc_cptr = cptr->lchild;
            cptr->lchild=ptr;
            ptr->rchild = lc_cptr;

            //update heights of ptr and cptr
            updateHeight(ptr);
            updateHeight(cptr);
            return true;
        }
    }



public:
    avl(){
        root=NULL;
        n=0;
     }


    bool insert(const T & key){

        treeNode * ptr=NULL;
        stack<treeNode*> ancestors;
        if(getAccess(key,ptr,ancestors))
            return false;
        else{
            //being here means ptr is NULL
            treeNode*pptr = ancestors.size()==0?NULL:ancestors.top();

            if(pptr==NULL){//empty tree
                root=new treeNode(key,NULL, NULL, 0);
            }else if(key<pptr->data){//new node is a left child
                    pptr->lchild=new treeNode(key, NULL, NULL,0);
            }else{
                    pptr->rchild=new treeNode(key, NULL, NULL,0);
            }

            //now update heights and check balance factors of the ancestors
            while(!ancestors.empty()){
                treeNode * anc = ancestors.top();
                ancestors.pop();

                //update the height of the next ancestor
                updateHeight(anc);

                 //is there imbalance on this ancestor?
                if(bf(anc)>1 || bf(anc)<-1){
                   //Yes there is imbalance.
                   //Identify the type of imbalance and resolve it

                   //get parent pointer, required by rotation methods
                   treeNode* panc = ancestors.empty()?NULL:ancestors.top();

                   if(bf(anc)==2 && bf(anc->rchild)==1){
                        //right-right
                        rl(anc, panc);
                   }else
                   if(bf(anc)==-2 && bf(anc->lchild)==-1){
                       //left-left
                       rr(anc,panc);
                   }else
                   if(bf(anc)==2 && bf(anc->rchild)==-1){
                       //right-left
                       rr(anc->rchild, anc);//make it a right-right imbalance
                       rl(anc, panc);
                   }else
                   if(bf(anc)==-2 && bf(anc->lchild)==1){
                       //left-right
                       rl(anc->lchild, anc);//make it a left-left imbalance
                       rr(anc, panc);
                   }
                }
            }

            n++;
            return true;
        }
    }

    bool find(const T & key){
        return getAccess(key);
    }


    bool erase(const T & key){

        treeNode*ptr;
        stack<treeNode*> ancestors;

        if(!getAccess(key, ptr, ancestors))
            return false;
        else{
                treeNode*pptr=ancestors.empty()?NULL:ancestors.top();
                //case 0: ptr has 0 children
                if(childCount(ptr)==0){
                    //cout<<"case 0"<<endl;
                    eraseCase0(ptr, pptr);
                //case 1: ptr has 1 children
                }else if(childCount(ptr)==1){
                    //cout<<"case 1"<<endl;
                    eraseCase1(ptr, pptr);
                //case 2: ptr has 2 children
                  }else{
                    //cout<<"case 2"<<endl;
                    eraseCase2(ptr, pptr, ancestors);
                  }

            //now update heights and check balance factors of the ancestors
            while(!ancestors.empty()){
                treeNode * anc = ancestors.top();
                ancestors.pop();

                //will the height of anc change?
                updateHeight(anc);
                 //height is changing: is there imbalance?
                if(bf(anc)>1 || bf(anc)<-1){
                   //Yes there is imbalance.
                   //Identify the type of imbalance and resolve it

                   //get parent pointer, required by rotation methods
                   treeNode* panc = ancestors.empty()?NULL:ancestors.top();


                   if(bf(anc)==2 && bf(anc->rchild)>=0){
                        //right-right
                        rl(anc, panc);
                   }else
                   if(bf(anc)==-2 && bf(anc->lchild)<=0){
                       //left-left
                       rr(anc,panc);
                   }else
                   if(bf(anc)==2 && bf(anc->rchild)==-1){
                       //right-left
                       rr(anc->rchild, anc);
                       rl(anc, panc);
                   }else
                   if(bf(anc)==-2 && bf(anc->lchild)==1){
                       //left right
                       rl(anc->lchild, anc);
                       rr(anc, panc);
                   }
                }
            }
                n--;
                return true;
        }

    }

    int size(){return n;}

};









bool Insert(Anode*& r, T x) {
if r == nullptr
r := new Anode; r->data = x; r->height = 0; return 1;//the links to

//children are null

else{
if(r->data == x) return 0; //Duplicate do nothing
else if(r->data > x){ Insert(r->left, x);

if ((height(r->left)- height(r->right)) == 2){
if (r->left->data > x ) //outside case

r = RotateRight (r);

else //inside case

r = DoubleRotateReft (r);}

else if (r->data < x) Insert(r->right, x);
code similar to the left case

}
r->height := max(height(r->left),height(r->right)) +1;
return 1;
}