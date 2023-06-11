template <typename T>
class bMaxHeap{

    vector<T> h;
    int n;

    inline int parent(int i){
        return i/2;
    }

    inline int lchild(int i){
        return 2*i;
    }

    inline int rchild(int i){
        return 2*i+1;
    }


    inline bool isLeaf(int i){
        return lchild(i)>n;

    }

    void percolateUp(int i){
        //O(lgn)
        while(parent(i)>0 && h[i]>h[parent(i)]){
                swap(h[i],h[parent(i)]);
                i = parent(i);
        }
    }


    void heapify(int i){//percolate down
        //O(lgn)
        while(!isLeaf(i)){
            int maxi = i;//node itself is min

            //update if lchild has smaller key
            if(h[lchild(i)]>h[maxi])
                maxi=lchild(i);

            //update if rchild has even smaller key
            if(rchild(i)<=n && h[rchild(i)]>h[maxi])
                maxi=rchild(i);

            if(i!=maxi){
                swap(h[i],h[maxi]);//swap ith node with the minimum of i, 2*i and 2*i+1
                i = maxi;//move to one of the children
            }
            else
                break;//no violation
        }

    }



public:
    bMaxHeap(){
        h.resize(1);
        n=0;
    }

    int size(){
        return n;
    }

    bool empty(){
        return n==0;
    }

    const T & getMax(){
        //O(1)
        return h[1];
    }


    void insert(const T & key){
        h.push_back(key);//key becomes the next leaf the last level
        n++;
        //now percolate up
        int i = n; //index of the newly added node
        percolateUp(i);
    }

    void buildMaxHeap(vector<T> & data){
        h = data;//data should include dummy node
        n = h.size()-1;
        for(int i = n/2; i>=1; i--)
            heapify(i);
    }




    void deteleMax(){
        if(n>0){
            h[1] = h[n];//overwrite root with last leaf
            h.pop_back();//remove last leaf
            n--;
            heapify(1);//percolateDown(1)
        }
    }





};