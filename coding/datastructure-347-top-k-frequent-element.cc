typedef pair<int, int> PAIR;

struct CmpByValue{
    bool operator ()(const PAIR &lhs, const PAIR &rhs) {
        return lhs.second > rhs.second;
    }
};

template<typename T>
class Heap {
    Heap() {
        Heap(CAPACITY_SIZE);
    }

    Heap(int cap) {
        arr = new T[cap];
        size = 0;
        capacity = cap;
    }

    ~Heap() {
        size = 0;
        delete [] arr;
    }

    T pop() {
        if (size <= 0) 
            return T();

        T ret = arr[0];
        arr[0] = arr[size - 1];
        delete arr[size - 1];
        size--;
        heapify(0);

        return ret;
    }

    int heap_size() {
        return this.size;
    }

    T top() {
        return size <= 0 ? T() : arr[0];
    }

    void push(T v) {
        if (size == capacity)
            return;

        arr[size++] = v;

        int i = size - 1;
        while (i != 0 && arr[parent(i)] > arr[i]) {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }

private:

    int parent(int idx) {
        return (idx - 1) / 2;
    }

    void heapify(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && arr[left] < arr[smallest])
            smallest = left;

        if (right < size && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != idx) {
            swap(arr[smallest], arr[idx]);
            heapify(smallest);
        }
    }

    T *arr;
    int size;
    int capacity;
    const int CAPACITY_SIZE = 1024;
};

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> m;

    for (auto a: nums)
        m[a]++;

    //priority_queue<PAIR, vecotr<PAIR>, CmpByValue> q;
    Heap<pair<int, int>> q;
    for (auto &iter: m) {
        q.push_back(*iter);
        if (q.size() > k) {
            q.pop();
        }
    }

    vector<int> res;
    for (auto &p: q) {
        res.push_back(p.top().first);
        p.pop();
    }

    return res;
}


