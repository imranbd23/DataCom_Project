/* DataCom_Project
   Md. Abu Rayhan Imran 
   GUB, CSE dept.
   5th semester project */

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <sstream>
#include <bitset>
#define MAXSIZE 100
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

// Function prototypes
void bitStuffing();
void characterStuffing();
void crc();
void hammingCode();
void ipAddressConversion();
void manchesterEncoding();
void diffManchesterEncoding();
void nrziEncoding();

int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Bit Stuffing\n";
        cout << "2. Character Stuffing\n";
        cout << "3. CRC\n";
        cout << "4. Hamming Code\n";
        cout << "5. IP Address Conversion\n";
        cout << "6. Manchester Encoding\n";
        cout << "7. Differential Manchester Encoding\n";
        cout << "8. NRZI Encoding\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bitStuffing();
                break;
            case 2:
                characterStuffing();
                break;
            case 3:
                crc();
                break;
            case 4:
                hammingCode();
                break;
            case 5:
                ipAddressConversion();
                break;
            case 6:
                manchesterEncoding();
                break;
            case 7:
                diffManchesterEncoding();
                break;
            case 8:
                nrziEncoding();
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 9);

    return 0;
}

// Bit Stuffing and De-Stuffing
void bitStuffing() {
    char in[MAXSIZE];
    char stuff[MAXSIZE];
    char destuff[MAXSIZE];
    int count(0);

    cout << "Enter input string (0's & 1's only): ";
    cin >> in;

    // Stuffing on sender's site
    cout << "\n---- After BitStuffing ----" << endl;
    char *p = in;
    char *q = stuff;

    while (*p != '\0') {
        if (*p == '0') {
            *q = *p;
            q++;
            p++;
        } else {
            count = 0;
            while (*p == '1' && count != 5) {
                count++;
                *q = *p;
                q++;
                p++;
            }
            if (count == 5) {
                *q = '0';
                q++;
            }
            count = 0;
        }
    }
    *q = '\0';
    cout << "BitStuffed character string: " << stuff << endl;

    // Destuffing on receiver's site
    cout << "\n---- After BitDeStuffing ----" << endl;
    p = stuff;
    q = destuff;
    count = 0;

    while (*p != '\0') {
        if (*p == '0') {
            *q = *p;
            q++;
            p++;
        } else {
            count = 0;
            while (*p == '1' && count != 5) {
                count++;
                *q = *p;
                q++;
                p++;
            }
            if (count == 5) {
                p++; // skip the stuffed '0'
            }
            count = 0;
        }
    }
    *q = '\0';
    cout << "BitDeStuffed character string: " << destuff << endl;
}

// Character Stuffing and De-Stuffing
void characterStuffing() {
    char so[100], data[100];
    cout << "Enter the text: ";
    cin >> so;
    char flag;
    cout << "Enter the flag: ";
    cin >> flag;

    int size = strlen(so);
    data[0] = flag;
    int i, j;
    for (i = 0, j = 1; i < size; i++) {
        if (so[i] == 'k') {
            so[i] = 0;
            i++;
            data[j] = so[i];
            j++;
        } else {
            data[j] = so[i];
            j++;
        }
    }
    data[j] = flag;
    data[j + 1] = '\0';
    cout << data << endl;
}

// CRC
string xordiv(string m, string d) {
    string rem = "";
    if (m[0] == '0') {
        rem = m.substr(1);
    } else {
        for (int i = 0; i < d.length(); i++) {
            rem.push_back(m[i] == d[i] ? '0' : '1');
        }
        rem = rem.substr(1);
    }
    return rem;
}

void crc() {
    cout << "Input the sending data: ";
    string s;
    cin >> s;
    cout << "Input the divisor: ";
    string div;
    cin >> div;

    string gen_code = s;
    for (int i = 0; i < div.length() - 1; i++) {
        gen_code.push_back('0');
    }

    string temp = gen_code.substr(0, div.length());
    for (int i = 0; i <= gen_code.length() - div.length(); i++) {
        string rem = xordiv(temp, div);
        temp = rem;
        if (i + div.length() < gen_code.length())
            temp.push_back(gen_code[i + div.length()]);
    }

    string crc_code = s + temp;
    cout << crc_code << endl;
}

// Hamming Code (Using CRC for Simulation)
string xorOperation(string dividend, string divisor) {
    string result = dividend;
    for (int i = 0; i <= dividend.length() - divisor.length();) {
        for (int j = 0; j < divisor.length(); j++) {
            result[i + j] = (result[i + j] == divisor[j]) ? '0' : '1';
        }
        while (i < dividend.length() && result[i] != '1') {
            i++;
        }
    }
    return result;
}

bool checkCRC(string receivedMessage, string divisor) {
    string appendedMessage = receivedMessage + string(divisor.length() - 1, '0');
    string remainder = xorOperation(appendedMessage, divisor);
    for (char bit : remainder) {
        if (bit == '1') return false;
    }
    return true;
}

void hammingCode() {
    string receivedMessage, divisor;
    cout << "Enter the received message: ";
    cin >> receivedMessage;
    cout << "Enter the divisor: ";
    cin >> divisor;

    if (checkCRC(receivedMessage, divisor)) {
        cout << "The received message has no errors." << endl;
    } else {
        cout << "The received message is erroneous." << endl;
    }
}

// IP Address Conversion
void ipAddressConversion() {
    string ip;
    cout << "Enter IP address: ";
    cin >> ip;
    stringstream ss(ip);
    string segment;
    int octet;
    while (getline(ss, segment, '.')) {
        octet = stoi(segment);
        cout << bitset<8>(octet) << ' ';
    }
    cout << endl;
}

// Manchester Encoding
void manchesterEncoding() {
    string data;
    cout << "Enter binary data: ";
    cin >> data;
    string encoded = "";
    for (char bit : data) {
        encoded += (bit == '0') ? "01" : "10";
    }
    cout << "Manchester Encoded data: " << encoded << endl;
}

// Differential Manchester Encoding
void diffManchesterEncoding() {
    string data;
    cout << "Enter binary data: ";
    cin >> data;
    string encoded = "";
    char last_bit = '0';

    for (char bit : data) {
        if (bit == '0') {
            encoded += (last_bit == '0') ? "01" : "10";
            last_bit = (last_bit == '0') ? '1' : '0';
        } else {
            encoded += (last_bit == '0') ? "10" : "01";
        }
    }
    cout << "Differential Manchester Encoded data: " << encoded << endl;
}

// NRZI Encoding and Decoding
void nrziEncoding() {
    int numBits;
    cout << "Enter the number of bits: ";
    cin >> numBits;
    vector<int> bits(numBits);
    cout << "Enter the bits (0 or 1): ";
    for (int i = 0; i < numBits; ++i) {
        cin >> bits[i];
    }

    int bitrate;
    cout << "Enter the bitrate: ";
    cin >> bitrate;

    int n;
    cout << "Enter the number of samples per bit (n): ";
    cin >> n;

    int T = bits.size() / bitrate;
    int N = n * bits.size();
    double dt = static_cast<double>(T) / N;
    vector<double> t(N + 1);
    for (int i = 0; i <= N; ++i) {
        t[i] = i * dt;
    }

    vector<double> x(t.size(), 0);
    int lastbit = 4;
    for (size_t i = 0; i < bits.size(); ++i) {
        fill(x.begin() + i * n, x.begin() + (i + 1) * n, lastbit);
        if (bits[i] == 1) lastbit = -lastbit;
    }

    ofstream plot_data("plot_data.txt");
    if (plot_data.is_open()) {
        for (size_t i = 0; i < t.size(); ++i) {
            plot_data << t[i] << " " << x[i] << endl;
        }
        plot_data.close();
    } else {
        cout << "Unable to open file for writing plot data" << endl;
    }

    vector<int> decoded_data(bits.size(), 0);
    for (size_t i = 0; i < bits.size(); ++i) {
        decoded_data[i] = (x[i * n] == -4) ? 1 : 0;
    }

    cout << "Decoded data:" << endl;
    for (int bit : decoded_data) {
        cout << bit << " ";
    }
    cout << endl;
}
