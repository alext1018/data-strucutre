#include <iostream>
#include <cmath>

using namespace std;

int octalToDecimal(int octal) {
    int decimal = 0, i = 0;

    while (octal != 0) {
        int rem = octal % 10;
        decimal += rem * pow(8, i);
        ++i;
        octal /= 10;
    }

    return decimal;
}

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int octal;

    
    cin >> octal;

    int decimal = octalToDecimal(octal);
    while(cin>>octal){
    if (isPrime(decimal)) {
        cout << decimal << endl;
    } else {
        cout << "0" << endl;
    }
    }

    return 0;
}
