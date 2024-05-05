#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
using namespace std;

string IntExpansion(int n, const int& base) {
	string result = "";
	string digits[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
					"A", "B", "C", "D", "E", "F" };

	while (n > 0) {
		int nextDigit = n % base;
		result.insert(0, digits[nextDigit]);
		n /= base;
	}

	if (base == 2) {
		for (int i = (int)result.size() - 4; i > 0; i -= 4) {
			result.insert(i, " ");
		}
	}

	return result;
}

vector<int> PrimeFact(int n) {
	vector<bool> nums;
	for (int i = 0; i < (n + 1); i++) {
		nums.push_back(true);
	}

	int factor = n;
	vector<int> result;

	for (int p = 2; p * p <= n; p++) {
		if (nums[p] == true) {
			for (int i = p * p; i <= n; i += p)
				nums[i] = false;
		}
	}

	for (int p = 2; p <= n; p++) {
		if (nums[p]) {
			while (factor % p == 0) {
				result.push_back(p);
				factor /= p;
			}
		}
	}

	return result;
}

int main(int argc, const char** argv) {
	try {
		// Check if there is 1 string entered
		if (argc != 2) {
			throw runtime_error("Wrong number of arguments");
		}

		// Read the filename from argument
		string filename = argv[1];

		if (filename.size() > 4 &&
			filename.substr(filename.size() - 4, filename.size()) != ".txt") {
			throw runtime_error("Invalid extension");
		}

		vector<int> integers;

		ifstream inFile;
		inFile.open(filename);

		// Read data file
		if (inFile.is_open()) {
			string currLine;

			getline(inFile, currLine);
			istringstream stream(currLine);

			string elem;
			while (getline(stream, elem, ',')) {
				integers.push_back(stoi(elem));
			}

			cout << filename << " read" << endl;
		}
		else {
			cout << "Could not open " << filename << endl;
		}
		inFile.close();

		ofstream outFile("output.txt");

		// Output results to file
		if (outFile.is_open()) {
			for (unsigned int i = 0; i < integers.size(); i++) {
				outFile << "++++++++++ n = " << integers[i];
				outFile << " ++++++++++" << endl;
				outFile << endl;
				string bin = IntExpansion(integers[i], 2);
				string oct = IntExpansion(integers[i], 8);
				string hex = IntExpansion(integers[i], 16);

				int width = (int)bin.size();
				outFile << "Binary: " << setw(width + 9) << bin << endl;

				width = (int)oct.size();
				outFile << "Octal: " << setw(width + 10) << oct << endl;

				width = (int)hex.size();
				outFile << "Hexadecimal: " << setw(width + 4) << hex << endl;
				outFile << endl;

				vector<int> primes;
				primes = PrimeFact(integers[i]);

				outFile << "Prime Factorization:   ";
				for (unsigned int i = 0; i < primes.size(); i++) {
					outFile << primes[i] << " ";
				}
				outFile << endl << endl;
			}

			cout << "Results written to output.txt" << endl;
		}
		else {
			cout << "Could not write to file" << endl;
		}
	}
	catch (runtime_error& excpt) {
		cout << "ERROR: " << excpt.what() << endl;
		cout << "Please enter a filename to read with extension .txt (ex: integers.txt)" << endl;
	}
}