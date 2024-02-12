#include <iostream>
#include <string>
using namespace std;
template<typename T>
class GMvector {
private:
    T* data;
    int size;
    int capicity;
public:
    GMvector(int n) {
        capicity = n;
        size = n-n/2;
        data = new T[n];
    }
    GMvector(T* arr, int n) {
        size = n;
        capicity = n + n / 2;
        data = new T[capicity];
        for (int i = 0; i < n; i++) {
            data[i] = arr[i];
        }
    }
    GMvector(const GMvector& vec) {
        capicity = vec.capicity;
        size = vec.size;
        data = new T[capicity];
        for (int i = 0; i < size; i++) {
            data[i] = vec.data[i];
        }
    }
    ~GMvector() {
        delete[]data;
    }
    GMvector& operator=(const GMvector& vec) {
        if (this != &vec) {
            delete[]data;
            capicity = vec.capicity;
            size = vec.size;
            data = new T[capicity];
            for (int i = 0; i < size; i++) {
                data[i] = vec.data[i];
            }
        }
        return *this;
    }
    GMvector& operator=(GMvector&& vec) {
        size = vec.size;
        capicity = vec.capicity;
        data = vec.data;
        vec.capicity = 0;
        vec.size = 0;
        vec.data = nullptr;
        return *this;
    }
    T& operator[](int index) {
        /*if (index >= size)
            throw(index);
        else
            return data[index];*/
        return data[index];
    }
    int push_pack(T value) {
        if (size >= capicity) {
            realloc(capicity + capicity / 2);
        }
        data[size] = value;
        size++;
        return size;
    }
    void pop_back() {
        if (size > 0) {
            size--;
            data[size].~T();
        }
    }
    void clear() {
        for (int i = 0; i < size; i++) {
            data[i].~T();
        }
        size = 0;
    }
    int Size() const {
        return size;
    }
    int Capicity() const {
        return capicity;
    }
    void realloc(int cap) {
        T* new_data = new T[cap];
        capicity = cap;
        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[]data;
        data = new_data;
        //delete[]new_data;
    }
    class iterator {
    private:
        T* curr;
    public:
        iterator(T* data) {
            curr = data;
        }
        T* get_curr() {
            return curr;
        }
        bool operator!=(const iterator& iter) {
            return this->curr != iter.curr;
        }
        iterator& operator++() {
            curr++;
            return *this;
        }
        iterator operator++(int x) {
            iterator it = *this;
            curr++;
            return it;
        }
        T& operator*() {
            return *curr;
        }
        iterator& operator+(int x) {
            curr += x;
            return *this;
        }
        iterator& operator-(int x) {
            curr -= x;
            return *this;
        }
    };
    iterator begin() {
        return iterator(data);
    }
    iterator end() {
        return iterator(data + size);
    }
    void erase(iterator iter) {
        int x = 0;
        for (int i = 0; i < (size); i++) {
            if (data + i == iter.get_curr()) {
                x = i;
                break;
            }
        }
        T* new_data = new T[capicity]; 
        for (int i = 0; i < x; i++) {
            new_data[i] = data[i];
        }
        for (int i = (x + 1); i < size; i++) {
            new_data[i - 1] = data[i];
        }
        data = new_data;
        size--;
    }
    void erase(iterator iter1,iterator iter2) {
        int x = 0, y = 0, z = 0;;
        for (int i = 0; i < (size ); i++) {
            if (data + i == iter1.get_curr()) {
                x = i;
                break;
            }
        }
        for (int i = 0; i < (size ); i++) {
            if (data + i == iter2.get_curr()) {
                y = i;
                break;
            }
        }
        z = y - x;
        T* new_data = new T[capicity];
        for (int i = 0; i < x; i++) {
            new_data[i] = data[i];
        }
        for (int i = (y ); i < size; i++) {
            new_data[i - z] = data[i];
        }
        data = new_data;
        size -= z;
    }
    void insert(iterator iter,T value) {
        int x = 0;
        for (int i = 0; i < (size+1); i++) {
            if (data + i == iter.get_curr()) {
                x = i;
                break;
            }
        }
        if (size >= capicity) {
            realloc(capicity + capicity / 2);
        }
        T* new_data = new T[capicity];
        for (int i = 0; i < x; i++) {
            new_data[i] = data[i];
        }
        new_data[x] = value;
        for (int i = (x + 1); i < (size+1); i++) {
            new_data[i] = data[i-1];
        }
        data = new_data;
        size++;
    }
    bool empty() {
        return size == 0;
    }
    void resize(int sz) {
        if (sz < size) {
            T* new_data=new T[capicity];
            for (int i = 0; i < sz; i++) {
                new_data[i] = data[i];
            }
            data = new_data;
            size = sz;
        }
        else if (sz > size) {
            if (sz >= capicity) {
                realloc(sz + sz / 2);
            }
            T* new_data = new T[capicity];
            for (int i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            for (int i = size; i < sz; i++) {
                new_data[i] = 0;
            }
            data = new_data;
            size = sz;
        }
    }
};
int main()
{
    int arr[4] = { 1,2,3,4 };
    GMvector<int>v(arr, 4);
    
    v.push_pack(5);
    v.push_pack(6);
    v.push_pack(7);
    v.push_pack(8);
    v.push_pack(9);
    v.push_pack(10);
    
    
    for (int i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << v.Size()<<" ";
    cout << v.Capicity();
}

