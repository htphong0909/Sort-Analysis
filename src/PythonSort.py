import os
import time
import numpy as np
import glob

def sort_and_measure_time(filepath):
    """Đọc file, sắp xếp bằng numpy.sort, và đo thời gian."""
    try:
        with open(filepath, 'r') as f:
            lines = f.readlines()
            n = int(lines[0])
            arr = np.fromstring(lines[1], dtype=float, sep=' ')
            if len(arr) != n:
                raise ValueError(f"Số lượng phần tử không khớp với n trong file {filepath}")

        start_time = time.time()
        arr_sorted = np.sort(arr)
        end_time = time.time()
        elapsed_time = end_time - start_time
        return elapsed_time, arr_sorted
    except FileNotFoundError:
        print(f"File not found: {filepath}")
        return None, None
    except ValueError as e:
        print(f"Error reading file {filepath}: {e}")
        return None, None
    except Exception as e:
        print(f"An unexpected error occurred with {filepath}: {e}")
        return None, None

def main():
    """Đọc các file test, sắp xếp, đo thời gian, và ghi báo cáo."""
    # Sử dụng đường dẫn tương đối để đến thư mục tests và reports
    tests_dir = "../tests"  # Đi ra khỏi src, vào tests
    reports_dir = "../reports" # Đi ra khỏi src, vào reports

    # Tạo thư mục reports nếu nó chưa tồn tại
    os.makedirs(reports_dir, exist_ok=True)

    report_filepath = os.path.join(reports_dir, "pythonSort_report.txt")

    with open(report_filepath, "w") as report_file:

        test_files = glob.glob(os.path.join(tests_dir, "TEST[0-9][0-9].txt"))
        test_files.sort()

        for filepath in test_files:
            elapsed_time, _ = sort_and_measure_time(filepath)
            if elapsed_time is not None:
                relative_filepath = os.path.relpath(filepath, start="..")
                print(f"{relative_filepath}")
                print(f"Runtime: {elapsed_time * 1000:.6f}ms")
                print("-" * 14)
                report_file.write(relative_filepath + "\n")
                report_file.write("{:.6f}\n".format(elapsed_time * 1000))


if __name__ == "__main__":
    main()