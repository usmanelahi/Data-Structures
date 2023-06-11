template <typename T>
class bMinHeap{

    vector<T> h;

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
        return lchild(i)>size();

    }

    void percolateUp(int i){
        //O(lgn)
        while(parent(i)>0 && h[i]<h[parent(i)]){
                swap(h[i],h[parent(i)]);
                i = parent(i);
        }
    }


    void heapify(int i){//percolate down
        //O(lgn)
        while(!isLeaf(i)){
            int mini = i;//node itself is min

            //update if lchild has smaller key
            if(h[lchild(i)]<h[mini])
                mini=lchild(i);

            //update if rchild has even smaller key
            if(rchild(i)<size() && h[rchild(i)]<h[mini])
                mini=rchild(i);

            if(i!=mini){
                swap(h[i],h[mini]);//swap ith node with the minimum of i, 2*i and 2*i+1
                i = mini;//move to one of the children
            }
            else
                break;//no violation
        }



    }



public:
    bMinHeap(){
        h.resize(1);
    }

    int size(){
        return h.size()-1;
    }

    bool empty(){
        return size()==0;
    }

    const T & getMin(){
        //O(1)
        return h[1];
    }


    void insert(const T & key){

        h.push_back(key);//key becomes the next leaf the last level

        //now percolate up
        int i = size(); //index of the newly added node
        percolateUp(i);
    }


    void deteleMin(){
        if(size()>0){
            h[1] = h[size()];//overwrite root with last leaf
            h.pop_back();//remove last leaf
            heapify(1);//percolateDown(1)
        }
    }


};