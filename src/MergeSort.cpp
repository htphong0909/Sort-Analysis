#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <filesystem>

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

template<typename T>
void mergesort(T * list, const int numElements) {
    if (numElements < 2)
        return;

    int numInBottom = numElements >> 1;
    int numInTop = numElements - numInBottom;

    mergesort<T> (list, numInBottom);
    mergesort<T> (list + numInBottom, numInTop);

    T * result = new T[numInBottom + numInTop];
    std::merge(list, list + numInBottom, list + numInBottom, list + numInBottom + numInTop, result);
    std::copy( result, result + numInBottom + numInTop, list );

    delete [] result;
}

int main() {
    string directory_path = "tests";
    string report_directory = "reports";

    // Tạo thư mục "reports" nếu nó chưa tồn tại
    fs::create_directory(report_directory);

    // Mở file báo cáo để ghi (ghi đè nếu file đã tồn tại)
    ofstream report_file(report_directory + "/mergeSort_report.txt");
    if (!report_file.is_open()) {
        cerr << "Khong mo duoc file bao cao" << endl;
        return 1;
    }

    // Duyệt qua tất cả các file trong thư mục tests
    for (const auto& entry : fs::directory_iterator(directory_path)) {
        if (fs::is_regular_file(entry)) {
            string filename = entry.path().string();
            ifstream infile(filename);

            if (!infile.is_open()) {
                cerr << "Khong mo duoc file test" << filename << endl;
                continue;
            }

            cout << filename << endl;

            int n;
            infile >> n;
            vector<double> arr(n);
            for (int i = 0; i < n; ++i) {
                infile >> arr[i];
            }
            infile.close();

            auto start = high_resolution_clock::now();
            mergesort<double>(arr.data(), n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            // Ghi kết quả vào file báo cáo, có định dạng
            report_file << filename << "\n" << fixed << setprecision(6) << duration.count() / 1000.0 << endl;
            cout << "Runtime: " << fixed << setprecision(6) << duration.count() / 1000.0 << "ms" << endl;
            cout << "--------------" << endl;
        }
    }
    report_file.close();
    return 0;
}