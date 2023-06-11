
template <typename T>
class bst{
    struct treeNode{
        T data;
        treeNode *lchild, *rchild;

        treeNode(const T& new_data, treeNode*lc=NULL, treeNode*rc=NULL){
            data=new_data;
            lchild=lc;
            rchild=rc;
        }

    } *root;
    int n;//size of the tree

    bool getAccess(const T& key, treeNode*& ptr=NULL, treeNode*& pptr=NULL)
    {
        ptr=root;
        pptr=NULL;

        while(ptr!=NULL && ptr->data!=key){
            pptr=ptr;//pptr is the parent of next ptr
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
	`
    }

    void eraseCase0(treeNode* ptr, treeNode* pptr){
        delete ptr;
        if(ptr==root){
            //cout<<"Root updated..."<<endl;
            root=NULL;
        }else if(ptr==pptr->lchild){
            pptr->lchild=NULL;
        }else{
            pptr->rchild=NULL;
        }
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

    void eraseCase2(treeNode* ptr, treeNode* pptr){

        treeNode * nptr = ptr->rchild, *pnptr=ptr;

        while(nptr->lchild!=NULL){
            pnptr=nptr;
            nptr=nptr->lchild;
        }

        swap(ptr->data,nptr->data);

        if(childCount(nptr)==0){
            eraseCase0(nptr, pnptr);
        }else{
            eraseCase1(nptr, pnptr);
        }
    }




public:
    bst(){
        root=NULL;
        n=0;
    }

    bool insert(const T & key){
        treeNode * ptr, *pptr;
        if(getAccess(key,ptr,pptr))
            return false;
        else{
            //ptr is null
            if(pptr==NULL){//empty tree, because pptr==NULL
                root=new treeNode(key,NULL, NULL);
            }else if(key<pptr->data){//new node is a left child
                    pptr->lchild=new treeNode(key, NULL, NULL);
            }else{
                    pptr->rchild=new treeNode(key, NULL, NULL);
            }
            n++;
            return true;
        }
    }

    bool find(const T & key){
        return getAccess(key);
    }


    bool erase(const T & key){

        treeNode*ptr, *pptr;


        if(!getAccess(key, ptr, pptr))
            return false;
        else{
                //case 0: ptr has 0 children
         
-		 if(childCount(ptr)==0){
                    //cout<<"case 0"<<endl;
                    eraseCase0(ptr, pptr);
                //case 1: ptr has 1 children
                }else if(childCount(ptr)==1){
                    //cout<<"case 1"<<endl;
                    eraseCase1(ptr, pptr);
                //case 2: ptr has 2 children
                  }else{
                    //cout<<"case 2"<<endl;
                    eraseCase2(ptr, pptr);
                  }

                n--;
                return true;
        }

    }

    int size(){
		return n;
	}



};

int main(){

    bst<int> tree; //add remove and find data
}