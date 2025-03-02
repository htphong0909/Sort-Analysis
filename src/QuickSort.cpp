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

const int CUTOFF = 8;

template<typename T>
bool le (T &v, T &w)
{
    return (v < w);
}

template<typename T>
bool eq (T &v, T &w)
{
    return w == v;
}

template <typename T>
void swap (T *a, T *b)
{
    T t = *a;
    *a = *b;
    *b = t;
}

template<typename T>
void insert(vector<T>& input, int lo, int hi)
{
    for (int i = lo; i <= hi; ++i)
    {
        for (int j = i; j > lo && le(input[j], input[j-1]); --j)
        {
            swap(&input[j], &input[j-1]);
        }
    }
}


template<typename T>
int median3 (vector<T>& input, int indI, int indJ, int indK)
{
    return (le(input[indI], input[indJ]) ?
            (le(input[indJ], input[indK]) ? indJ : le(input[indI], input[indK]) ? indK : indI) :
            (le(input[indK], input[indJ]) ? indJ : le(input[indK], input[indI]) ? indK : indI));
}


template <typename T>
void sort(vector<T>& input, int lo, int hi)
{
    int lenN = hi - lo + 1;

    if (lenN <= CUTOFF)
    {
        insert(input, lo, hi);
        return;
    }

    // use median-of-3 as partitioning element
    else if (lenN <= 40)
    {
        int median = median3(input, lo, lo + lenN / 2, hi);
        swap(&input[median], &input[lo]);
    }

    // use Tukey ninther as partitioning element
    else
    {
        int eps = lenN / 8;
        int mid = lo + lenN / 2;
        int mFirst = median3(input, lo, lo + eps, lo + eps + eps);
        int mMid = median3(input, mid - eps, mid, mid + eps);
        int mLast = median3(input, hi - eps - eps, hi - eps, hi);
        int ninther = median3(input, mFirst, mMid, mLast);
        swap(&input[ninther], &input[lo]);
    }

    // Bentley-McIlroy 3-way partitioning
    int iterI = lo, iterJ = hi + 1;
    int iterP = lo, iterQ = hi + 1;

    for (;; )
    {
        T v = input[lo];
        while (le(input[++iterI], v))
        {
            if (iterI == hi)
                break;
        }
        while (le(v, input[--iterJ]))
        {
            if (iterJ == lo)
                break;
        }
        if (iterI >= iterJ)
            break;
        swap(&input[iterI], &input[iterJ]);
        if (eq(input[iterI], v))
            swap(&input[++iterP], &input[iterI]);
        if (eq(input[iterJ], v))
            swap(&input[--iterQ], &input[iterJ]);
    }
    swap(&input[lo], &input[iterJ]);

    iterI = iterJ + 1;
    iterJ = iterJ - 1;
    for (int k = lo + 1; k <= iterP; ++k)
    {
        swap(&input[k], &input[iterJ--]);
    }
    for (int k = hi  ; k >= iterQ; --k)
    {
        swap(&input[k], &input[iterI++]);
    }

    sort(input, lo, iterJ);
    sort(input, iterI, hi);
}

int main() {
    string directory_path = "tests";
    string report_directory = "reports";

    // Tạo thư mục "reports" nếu nó chưa tồn tại
    fs::create_directory(report_directory);

    // Mở file báo cáo để ghi (ghi đè nếu file đã tồn tại)
    ofstream report_file(report_directory + "/quickSort_report.txt");
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
            sort(arr, 0, n - 1);
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