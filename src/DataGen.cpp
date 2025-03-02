#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>

namespace fs = std::filesystem;
using namespace std;

int main() {
    // Tạo thư mục tests
    fs::create_directory("tests");

    // Khởi tạo bộ sinh số ngẫu nhiên
    random_device rd;
    mt19937 gen(rd());

	// Nhập số lượng và kích thước các bộ test
	int t;
	cout << "So luong test (test 1, 2 se duoc sort tang, giam dan), max = 99:";
	cin >> t;
	t = min(t, 99);

	int N;
	cout << "Kich thuoc cac bo test N: ";
	cin >> N;
	cout << "Cac bo test se co so luong phan tu ~ 0.95N -> 1.05N\n";
    // Thiết lập phân phối
    uniform_int_distribution<> dist_n((int)(0.95 * N), (int)(1.05 * N));
    uniform_real_distribution<> dist_float(-1000000000.0, 1000000000.0);

    // Lặp qua t files
    for (int i = 1; i <= t; ++i) {

        // Tạo tên file, mở file để ghi
        string filename = "tests/TEST" + to_string(i / 10) + to_string(i % 10) + ".txt";
        ofstream outfile(filename);

        if (!outfile.is_open()) {
            cout << "Khong mo duoc file " << filename << endl;
            return 1; //Thoát nếu file không thể mở
        }

        // Sinh số ngẫu nhiên
        const int n = dist_n(gen);
        vector<double> arr(n);
        for (int j = 0; j < n; ++j) {
            arr[j] = dist_float(gen);
        }

        // Sắp xếp 2 test đầu
        if (i == 1) {
            sort(arr.begin(), arr.end());
        }
        else if (i == 2) {
            sort(arr.begin(), arr.end(), greater<double>());
        }

        // Ghi số đã sinh vào file test
        outfile << n << endl;
        for (int j = 0; j < n; ++j) {
            outfile << fixed << setprecision(10) << arr[j];
            if (j < n - 1) {
                outfile << " ";
            }
        }
        cout << "TEST " << i << " CREATED\n";

        // Đóng file
        outfile.close();

    }
    return 0;
}