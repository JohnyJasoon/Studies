#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <stack>

using namespace std;
using namespace std::chrono;

class DynamicArray {
private:
    int* data;
    int capacity;
    int size;

public:
    DynamicArray() : data(nullptr), capacity(0), size(0) {}

    DynamicArray(int initialCapacity) : capacity(initialCapacity), size(0) {
        if (initialCapacity <= 0) {
            throw invalid_argument("Initial capacity must be greater than zero");
        }
        data = new int[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(int value) {
        if (size >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            reserve(newCapacity);
        }
        data[size++] = value;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    int operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void reserve(int newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }
        int* newData = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
};

class SortingAlgorithms {
public:
    DynamicArray array;

    void displayArray(const DynamicArray& arr) {
        cout << "Array:\n";
        for (int i = 0; i < arr.getSize(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void displayArray(const DynamicArray& arr, const string& message) {
        cout << message << ":\n";
        displayArray(arr);
    }

    void insertionSort(DynamicArray& arr) {
        for (int j = 1; j < arr.getSize(); j++) {
            int key = arr[j];
            int i = j - 1;
            while (i >= 0 && arr[i] > key) {
                arr[i + 1] = arr[i];
                i = i - 1;
            }
            arr[i + 1] = key;
        }
    }

    void binaryInsertionSort(DynamicArray& arr) {
        for (int j = 1; j < arr.getSize(); j++) {
            int x = arr[j];
            int ip = 0;
            int ik = j;
            while (ik - ip > 1) {
                int i = (ip + ik) / 2;
                if (x <= arr[i])
                    ik = i;
                else
                    ip = i;
            }
            for (int i = j; i > ip; i--)
                arr[i] = arr[i - 1];
            arr[ip] = x;
        }
    }

    void heapify(DynamicArray& arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l] > arr[largest])
            largest = l;

        if (r < n && arr[r] > arr[largest])
            largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void heapSort(DynamicArray& arr) {
        for (int i = arr.getSize() / 2 - 1; i >= 0; i--)
            heapify(arr, arr.getSize(), i);

        for (int i = arr.getSize() - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    void quickSort(DynamicArray& arr, int low, int high) {
        stack<int> stack;
        stack.push(low);
        stack.push(high);

        while (!stack.empty()) {
            high = stack.top();
            stack.pop();
            low = stack.top();
            stack.pop();

            int pi = partition(arr, low, high);

            if (pi - 1 > low) {
                stack.push(low);
                stack.push(pi - 1);
            }

            if (pi + 1 < high) {
                stack.push(pi + 1);
                stack.push(high);
            }
        }
    }

    int partition(DynamicArray& arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

public:
    void loadArrayFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file '" << filename << "'." << endl;
            return;
        }

        int size;
        file >> size;
        array.reserve(size);
        for (int i = 0; i < size; ++i) {
            int value;
            file >> value;
            array.push_back(value);
        }

        file.close();
        displayArray(array, "Loaded array");
    }

    void generateRandomArray(int size) {
        array.reserve(size);
        srand(time(nullptr));
        for (int i = 0; i < size; ++i) {
            array.push_back(rand() % 100); // generating random numbers between 0 and 99
        }
        //displayArray(array, "Generated array");
    }

    void displayLastArray() {
        if (array.getSize() == 0)
            cout << "Array is empty." << endl;
        else
            displayArray(array, "Last array");
    }

    void sortArray(char choice) {
        if (array.getSize() == 0) {
            cout << "Array is empty. Cannot sort." << endl;
            return;
        }

        DynamicArray tempArray = array; // Create a copy of the original array
        switch (choice) {
        case 'a':
            insertionSort(tempArray);
            displayArray(tempArray, "Array after Insertion Sort");
            break;
        case 'b':
            binaryInsertionSort(tempArray);
            displayArray(tempArray, "Array after Binary Insertion Sort");
            break;
        case 'c':
            heapSort(tempArray);
            displayArray(tempArray, "Array after Heap Sort");
            break;
        case 'd':
            quickSort(tempArray, 0, tempArray.getSize() - 1);
            displayArray(tempArray, "Array after Quick Sort");
            break;
        default:
            cout << "Invalid choice. Sorting aborted." << endl;
        }
    }

    double measureSortTime(const DynamicArray& arr, char choice) {
        DynamicArray tempArray = arr; // Create a copy of the original array
        auto start = high_resolution_clock::now();

        switch (choice) {
        case 'a':
            insertionSort(tempArray);
            break;
        case 'b':
            binaryInsertionSort(tempArray);
            break;
        case 'c':
            heapSort(tempArray);
            break;
        case 'd':
            quickSort(tempArray, 0, tempArray.getSize() - 1);
            break;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count(); // return time in milliseconds
    }
};

int main() {
    SortingAlgorithms sorter;

    char choice;
    string filename;
    int size;
    int numTrials;
    ofstream outputFile("sorting_times.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file 'sorting_times.txt'." << endl;
        return 1;
    }

    cout << "Enter number of trials for each size: ";
    cin >> numTrials;

    do {
        cout << "\nMenu:\n";
        cout << "a) Load array from file\n";
        cout << "b) Generate random array\n";
        cout << "c) Display last array\n";
        cout << "d) Sort last array\n";
        cout << "e) Measure and display sort times\n";
        cout << "f) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 'a':
            cout << "Enter filename: ";
            cin >> filename;
            sorter.loadArrayFromFile(filename);
            break;
        case 'b':
            cout << "Enter size of array: ";
            cin >> size;
            sorter.generateRandomArray(size);
            break;
        case 'c':
            sorter.displayLastArray();
            break;
        case 'd':
            char sortChoice;
            cout << "Choose sorting algorithm (a: Insertion Sort, b: Binary Insertion Sort, c: Heap Sort, d: Quick Sort): ";
            cin >> sortChoice;
            sorter.sortArray(sortChoice);
            break;
        case 'e': {
            //cout << "Enter size of array: ";
            //cin >> size;

            DynamicArray sizes;
            sizes.push_back(10000);
            sizes.push_back(30000);
            sizes.push_back(50000);
            sizes.push_back(70000);
            sizes.push_back(90000);
            sizes.push_back(110000);
            sizes.push_back(130000);

            outputFile << "Array_Size;Insertion;Binary_InsertionHeap;Quick\n";

            for (int i = 0; i < sizes.getSize(); ++i) {
                double randomTime = 0, insertionTime = 0, binaryInsertionTime = 0, heapTime = 0, quickTime = 0;
                for (int j = 0; j < numTrials; ++j) {
                    sorter.generateRandomArray(sizes[i]);
                    insertionTime = sorter.measureSortTime(sorter.array, 'a');
                    binaryInsertionTime = sorter.measureSortTime(sorter.array, 'b');
                    heapTime = sorter.measureSortTime(sorter.array, 'c');
                    quickTime = sorter.measureSortTime(sorter.array, 'd');
                    outputFile << sizes[i] << ";" << insertionTime << ";" << binaryInsertionTime << ";" << heapTime << ";" << quickTime << endl;
                }
            }
            break;
        }
        case 'f':
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'f');

    outputFile.close();

    return 0;
}
