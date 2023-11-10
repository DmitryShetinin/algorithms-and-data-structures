 
 
 
#include <stdexcept>
#include <iostream>




using namespace std;






template <typename T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;

    bool AllowedIndex(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index is not available!" << std::endl;
            return false;
        }

        return true;
    }


public:
    DynamicArray() {
        capacity = 10;
        size = 0;
        arr = new T[capacity];
    }

    DynamicArray(int size) {
        capacity = size * 2;
        size = size;
        arr = new T[capacity];
    }

    DynamicArray(std::initializer_list<T> list) {
        size_t i = 0;
        size = list.size(); 
        capacity = size * 2;
        arr = new T[capacity];
        for (const T& elem : list) {
            arr[i++] = elem;
        }
    }

    T& operator[](int index) {
     
        if (AllowedIndex(index))
            return arr[index];

        throw std::out_of_range("Error");
         
    }

     
    

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }


    ~DynamicArray() {
        delete[] arr;
    }


    int getSize() {
        return size;
    }

    void insertAt(int index, T value) {
        if (AllowedIndex(index)) return;

        if (size == capacity) {
            resize();
        }

        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }

        arr[index] = value;
        size++;
    }

    void remove(T value) {
        int index = -1;

        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            removeAt(index);
        }
        else {
            std::cout << "Element is not found!" << std::endl;
        }
    }

    void removeAt(int index) {
        if (AllowedIndex(index)) return;

        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }

        size--;
    }

    void append(T value) {
        if (size == capacity) {
            resize();
        }

        arr[size] = value;
        size++;
    }

    T get(int index) {

        if (AllowedIndex(index)) return;
        return arr[index];
    }

    int getCapacity() {
        return capacity;
    }

private:
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];

        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
    }
};
class Exception : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};


 



const int MIN_MERGE = 32;

void insertionSort(DynamicArray<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void merge(DynamicArray<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    DynamicArray<int> left(len1), right(len2);

    for (int i = 0; i < len1; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < len2; i++) {
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l, testL = 0, testR = 0;
    

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    if (testL >= 7)  //галоп начинается тут, после того как из массива Left были взяты 7 раз элементы
    {
        int gallopStep = 1;
        bool col_mass = 1;
        for (int g = i; g < m - l + 1;)
        {
            if (left[g] <= right[j])
            {
                g += gallopStep;
                gallopStep *= 2;
            }
            else
            {
                col_mass = 0;
                testL = 0;
                testR = 0;
            }
        }
        if (col_mass)
        {
            for (int g = 0; g < m - l + 1; g++)
            {
                arr[k] = left[g];
                k++;
                i++;
                testL = 0;
                testR = 0;
            }
        }
    }
    else if (testR >= 7) //галоп начинается тут, после того как из массива Right были взяты 7 раз элементы
    {
        int gallopStep = 1;
        bool col_mass_bro = 1;
        for (int g = i; g < r - m;)
        {
            if (right[g] <= left[i])
            {
                g += gallopStep;
                gallopStep *= 2;
            }
            else
            {
                col_mass_bro = 0;
                testL = 0;
                testR = 0;
            }
        }
        if (col_mass_bro)
        {
            for (int g = 0; g < r - m; g++)
            {
                arr[k] = left[g];
                k++;
                j++;
                testL = 0;
                testR = 0;
            }
        }
    }


    while (i < len1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}
int get_minrun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}
void timsort(DynamicArray<int>& arr) {
    int n = get_minrun(arr.getSize());

    for (int i = 0; i < n; i += MIN_MERGE) {
        insertionSort(arr, i, std::min((i + MIN_MERGE - 1), (n - 1)));
    }

    for (int size = MIN_MERGE; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            merge(arr, left, mid, right);
        }
    }
}

int main() {
    DynamicArray<int> arr = { 1,2,3,4,5,3,4,9,7,6,5,4,3,2,1 };

    timsort(arr);
    for (int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    

    return 0;
}
