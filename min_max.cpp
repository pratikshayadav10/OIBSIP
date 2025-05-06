#include <iostream>     // For input and output
#include <omp.h>        // For OpenMP parallelism
using namespace std;

// Function to find the minimum value
int minvalue(int* arr, int n) {
    int minval = arr[0];    // Initialize with first element
    #pragma omp parallel for reduction(min:minval) // Parallel reduction to find min
    for (int i = 0; i < n; i++) {
        if (arr[i] < minval)
            minval = arr[i]; // Update if smaller element found
    }
    return minval;
}

// Function to find the maximum value
int maxval(int* arr, int n) {
    int maxval = arr[0];    // Initialize with first element
    #pragma omp parallel for reduction(max:maxval) // Parallel reduction to find max
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxval)
            maxval = arr[i]; // Update if larger element found
    }
    return maxval;
}

// Function to calculate the sum
int sum(int* arr, int n) {
    int total = 0;    // Initialize sum to 0
    #pragma omp parallel for reduction(+:total) // Parallel reduction to sum values
    for (int i = 0; i < n; i++) {
        total += arr[i]; // Add each element
    }
    return total;
}

// Function to calculate the average
float average(int* arr, int n) {
    return static_cast<float>(sum(arr, n)) / n; // Call sum() and divide by number of elements
}

int main() {
    int n;  // Variable to store number of elements

    // Ask user for number of elements
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];  // Declare array of size n

    // Ask user to input array elements
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];  // Read each element from user
    }

    // Call functions and print results
    cout << "Min value: " << minvalue(arr, n) << "\n";
    cout << "Max value: " << maxval(arr, n) << "\n";
    cout << "Sum: " << sum(arr, n) << "\n";
    cout << "Average: " << average(arr, n) << "\n";

    return 0;  // End of program
}