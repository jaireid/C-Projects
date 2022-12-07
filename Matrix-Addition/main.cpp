#include <iostream>
#include <chrono>

void version1(int** a, int** b, int** c, int n) {
  for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        c[i][j] = a[i][j] + b[i][j];
      }
    }
}

void version2(int** a, int** b, int** c, int n) {
  for(int j = 0; j < n; j++) {
    for(int i = 0; i < n; i++) {
      c[i][j] = a[i][j] + b[i][j];
    }
  }
}

// in an int[51200][51200] there are total bytes 51200*51200*4 = 10485760000

int main() {
  int size[10] = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200};
  
  std::cout << "times are in microseconds" << std::endl;
  std::cout << "n\t\t\tversion1\t\t\tversion2" << std::endl;

  // Perform the experiment for each size specified
  for(int i = 0; i < 10; i++) {
    // Get the size to test (n)
    int n = size[i];

    std::cout << n << "\t\t\t";
      
    // Create the arrays
    int** a = new int*[n];
    int** b = new int*[n];
    int** c = new int*[n];

    for (int j = 0; j < n; j++) {
      a[j] = new int[n];
      b[j] = new int[n];
      c[j] = new int[n];
    }

    auto start = std::chrono::high_resolution_clock::now();
    version1(a, b, c, n);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << duration.count() << "\t\t\t\t\t";

    auto start2 = std::chrono::high_resolution_clock::now();
    version2(a, b, c, n);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2-start2);
    std::cout << duration2.count() << std::endl;

    // Free arrays
    for(int j = 0; j < n; j++) {
      delete[] a[j];
      delete[] b[j];
      delete[] c[j];
    }
    delete[] a;
    delete[] b;
    delete[] c;
  }
  return 0;
}