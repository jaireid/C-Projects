#include <iostream>
using namespace std;

// Returns true if and only if a "special" element was located in the array
bool find_special(int arr[], int n, int k);


int main() {

		// Read n, k, and the input array
		int n, k;
		cin >> n >> k;
		int* arr = new int[n];
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}

		// Print a special element if possible
		if (!find_special(arr, n, k)) {
				cout << "None" << endl;
		}

		// Clean up
		delete[] arr;
		arr = 0;

		return 0;
}

void swap_em(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
}

// Recursive helper function
bool find_special(int arr[], int &n, int k, int freq[]) {
		/*
		After the function has finished executing, n is overwritten with the number of distinct elements of arr.

		The first n elements (using the updated n-value) of arr are overwritten with the distinct elements in ascending order.

		The first n elements (using the updated n-value) of freq are overwritten with the frequencies of the corresponding elements in arr.
		*/
		
		// Base case: an array with only one element

		// Set frequencies to 1
		if (n == 1) {
				freq[0] = 1;
				return false;
		}

		// Split array into subarrays
		int rsz = n / 2;
		int lsz = n - rsz;
		int split_idx = lsz;

		/*
		Look for a special element in each of the lower and upper halves of the array. Terminate early if we get lucky.
		*/

		// Left hand side of array
		if (find_special(arr, lsz, k, freq)) {
				return true;
		}

		// Right hand side of array
		if (find_special(arr + split_idx, rsz, k, freq + split_idx)) {
				return true;
		}

		// Merge the distinct elements and frequencies together.
		int i = 0, j = split_idx, temp, merges = 0;
		rsz += split_idx;

		while (i < lsz && j < rsz) {
				// If the element at index i in the left subarray is larger than the element at index j in the right subarray then swap
				if (arr[j] < arr[i]) {
						swap_em(arr[j], arr[i]);
						swap_em(freq[j], freq[i]);
						i++;

						// If two neighboring elements are the same, merge them
						if (j + 1 < rsz && arr[j] == arr[j + 1]) {
								j++;
								freq[j] += freq[j - 1];
								merges++;

								// If the element's frequency is greater than or equal to k output the element
								if (freq[j] >= k) {
										cout << arr[j] << endl;
										return true;
								}
						}
				} else if (arr[i] < arr[j]) { // If the element at index i in the left subarray is smaller than the element at index j in the right subarray then increment i
						i++;
				} else { // If elements are equal add frequencies
						freq[i] += freq[j];
						merges++;

						// If the element's frequency is greater than or equal to k output the element
						if (freq[i] >= k) {
								cout << arr[i] << endl;
								return true;
						}

						i++;
						j++;
				}
		}

		if (i < j) {
				while (j < rsz) {
						arr[i] = arr[j];
						freq[i] = freq[j];
						i++;
						j++;
				}
		}

		// Update the length of the array to only count the number of distinct elements.
		n = lsz + (rsz - split_idx) - merges;
		return false;
}

bool find_special(int arr[], int n, int k) {
		// Check for trivial case of k == 1
		if (k == 1 && n == 1) {
				cout << arr[0] << endl;
				return true;
		}

		// Setting up frequency array
		int* freq = new int[n];

		// Setting up a bool variable that will flag true if there is a special character and false otherwise
		bool result = find_special(arr, n, k, freq);

		delete[] freq;
		freq = 0;

		return result;
}
