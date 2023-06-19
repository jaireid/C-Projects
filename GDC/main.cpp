#include <iostream>
#include <string>

using namespace std;

int gcd(int, int);
long long sum_of_multiples(long long, int, int);

int main()
{
		long long n;
		int a, b;
		cin >> n;
		cin >> a;
		cin >> b;
		cout << endl;
		cout << sum_of_multiples(n, a, b) << endl;
		return 0;
}

// Technically, this is not O(1). It is O(log min(a,b)), due to the gcd calculation.
// But since a and b are 32-bit integers, the complexity simplifies to O(32), ie, O(1).
int gcd(int a, int b)
{
		if (b == 0)
				return a;
		return gcd(b, a % b);
}

long long sum_of_multiples(long long n, int a, int b)	
{
		long long lcm = (long long)a * b / gcd(a, b);	// least common multiple of a and b.

		long long j = (n + a - 1) / a - 1;		// The # of multiples of a less than n.
		long long k = (n + b - 1) / b - 1;		// The # of multiples of b less than n.
		long long m = (n + lcm - 1) / lcm - 1;	// The # of multiples of lcm(a,b) less than n.

		//Use the formula for the sum of an arithmetic series to calculate the sums of the multiples of a, b, and lcm(a,b).
		return	((j + 1) * j / 2) * a +
				((k + 1) * k / 2) * b -
				((m + 1) * m / 2) * lcm;
}
