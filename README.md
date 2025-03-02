Lớp: IT003.P21.CTTN
## <center>Báo cáo kết quả thực nghiệm</center>
Sinh viên thực hiện: Hà Thanh Phong
### I.Kết quả thử nghiệm
#### 1.Mô tả thực nghiệm
- **a. Mục tiêu chính:** So sánh hiệu năng (thời gian thực thi) của các thuật toán sắp xếp khác nhau trên các bộ dữ liệu có kích thước lớn.
- **b. Phạm vi:**
    - Các thuật toán được sử dụng: Quick Sort, Merge Sort, Heap Sort, C++ `std::sort`, Python Sort (`np.sort`).
    - Dữ liệu đầu vào: khoảng $10^6$ số thực nằm trong phạm vi từ $-10^9$ đến $10^9$.
    - Các yếu tố không được xem xét: 
            - Mức sử dụng bộ nhớ.
            - Tối ưu hóa máy chạy.
- **c. Cấu trúc**
    - Ý nghĩa từng thư mục:
        - `src`: chứa các mã nguồn C++ và Python.
        - `tests`: chứa bộ dữ liệu test.
        - `bin`: chứa các file thực thi C++ sau khi build.
        - `reports`: chứa các file báo cáo thời gian chạy của từng thuật toán cùng với đó là bảng, biểu đồ tổng thể.
    - Vai trò file `data_gen_and_analysis.bat`: build và chạy các chương trình theo thứ tự:
Sinh dữ liệu $\rightarrow$ chạy các thuật toán $\rightarrow$ vẽ biểu đồ và bảng.
- **d. Các thành phần chính:**
    - **Chương trình C++:**
        `DataGen.cpp`: chương trình sinh dữ liệu test, có thể điều chỉnh số lượng test, phạm vi.
        `MergeSort.cpp`, `QuickSort.cpp`, `HeapSort.cpp`, `CppStdSort.cpp`: chương trình chạy các hàm sort tương ứng.
    - **Chương trình Python:**
        `PythonSort.py`: chương trình chạy hàm sort của numpy.
        `FinalReportGen.py`: chương trình sinh biểu đồ và bảng.
- **e. Môi trường thử nghiệm:**
    - Máy chạy thử nghiệm: Laptop ASUS Zenbook 14 OLED UX3405MA-PP588W - Intel i5 125H
    - Môi trường C++:
        - g++: phiên bản $14.2$.
        - Cờ tối ưu:
        ```-std=c++17 -O3 -Wall -Wextra -pedantic -march=native -flto -funroll-loops```
    - Môi trường Python: Python phiên bản $3.13.2$
- **F. Video demo quá trình sinh - phân tích dữ liệu:** <a href="https://drive.google.com/file/d/1VdHf1VKD2q-3ac7ZiDzRZVOhY_GGO14s/view?usp=sharing"><img src="https://cdn-icons-png.flaticon.com/512/1384/1384060.png" alt="Google Drive Folder" width="40" height="40">
</a> 


#### 2.Bảng thời gian thực hiện
![table](https://github.com/user-attachments/assets/2e43d6f3-0369-4f69-af89-69cc1e9092ca)
#### 3.Biểu đồ cột thời gian thực hiện
![chart](https://github.com/user-attachments/assets/08f1778a-9b0a-454f-93cc-f7552e924b80)
### II.Kết luận:

Dự án này đã tiến hành so sánh hiệu năng của năm thuật toán sắp xếp: Quicksort, Heapsort, Mergesort, `std::sort` (C++), và `np.sort` (Python/NumPy) trên bộ dữ liệu gồm $10$ test case, mỗi test case chứa một mảng số thực có kích thước lớn (khoảng $10^6$ phần tử). Thời gian thực thi của mỗi thuật toán trên mỗi test case đã được đo và ghi lại, sau đó tính giá trị trung bình. Kết quả được trình bày trong bảng và biểu đồ sau:

**Phân tích và Nhận xét:**

1.  **`np.sort` (Python/NumPy) vượt trội:**  `np.sort` cho thấy hiệu suất *vượt trội* so với tất cả các thuật toán còn lại trong *mọi* test case. Thời gian chạy trung bình của `np.sort` chỉ là $15.88$ ms, thấp hơn đáng kể so với các thuật toán khác. Điều này khẳng định sức mạnh của NumPy trong việc xử lý mảng số, nhờ vào việc được viết bằng C và tối ưu hóa cao.

2.  **`std::sort` (C++) hiệu quả:** `std::sort` của C++ là thuật toán *nhanh thứ hai*, với thời gian chạy trung bình là $69.66$ ms. `std::sort` thường sử dụng thuật toán Introsort (kết hợp Quicksort, Heapsort, và Insertion Sort), cho thấy sự hiệu quả của các thư viện chuẩn C++ đã được tối ưu hóa.

3.  **QuickSort, HeapSort, MergeSort**: mặc dù đều có độ phức tạp trung bình là $O(n \times log(n))$, lại cho thấy hiệu suất *kém* hơn đáng kể so với `std::sort` và `np.sort`, với thời gian trung bình lần lượt là $123.39$ ms, $108.53$ ms, $135.30$ ms.


5. **Độ ổn định:**
    - Quan sát bảng kết quả cho thấy `np.sort`, `std::sort` và heapSort có độ ổn định cao (thời gian chạy ít biến động giữa các test case).
    - QuickSort và MergeSort có sự biến động lớn (ví dụ, test case 3 có thời gian chạy lên đến $181.84$ ms và $204.73$ ms), cho thấy nó nhạy cảm với dữ liệu đầu vào hơn.

**Kết luận chung:**

*   Đối với việc sắp xếp mảng số thực kích thước lớn trong Python, **`np.sort` là lựa chọn tốt nhất** về hiệu năng.
*   Trong C++, **`std::sort` là lựa chọn tốt** và thường nhanh hơn đáng kể so với các cài đặt thủ công của QuickSort, HeapSort, và MergeSort.
*   Kết quả này *khẳng định tầm quan trọng của việc lựa chọn thuật toán và thư viện phù hợp*. Việc sử dụng các thư viện được tối ưu hóa (như NumPy và thư viện chuẩn C++) có thể mang lại hiệu suất vượt trội so với các cài đặt tự viết.

### III Thông tin chi tiết - link github
https://github.com/htphong0909/Sort-Analysis

### IV Phụ lục
- **A.Dữ liệu đầu vào:** <a href="https://drive.google.com/drive/folders/1gCGVC1Cbuhh09TLJvy3u0veBZCEXCfeT?usp=sharing"><img src="https://icons.iconarchive.com/icons/marcus-roberto/google-play/512/Google-Drive-icon.png" alt="Google Drive Folder" width="35" height="35"></a>

- **B.Kết quả thời gian chạy:** <a href="https://drive.google.com/drive/folders/1gvoDGEtTTwyBKINSt_mVGvw-kkRBlqZK?usp=sharing"><img src="https://icons.iconarchive.com/icons/marcus-roberto/google-play/512/Google-Drive-icon.png" alt="Google Drive Folder" width="35" height="35"></a>

