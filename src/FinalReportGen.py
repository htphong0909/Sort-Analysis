import os
import pandas as pd
import matplotlib.pyplot as plt
import glob
import dataframe_image as dfi

def create_report(reports_dir, output_filepath="reports/report.png", table_output_filepath = "reports/table.png"):
    """Tạo bảng, biểu đồ và lưu."""

    data = {}

    # ... (Phần đọc dữ liệu từ file report - giữ nguyên) ...
    for report_file in glob.glob(os.path.join(reports_dir, "*_report.txt")):
        algorithm_name = os.path.basename(report_file).replace("_report.txt", "")
        data[algorithm_name] = []

        try:
            with open(report_file, 'r') as f:
                lines = f.readlines()
                for line in lines[1::2]:
                    time_ms = float(line.strip())
                    data[algorithm_name].append(time_ms)
        except FileNotFoundError:
            print(f"File not found: {report_file}")
        except ValueError:
            print(f"Error: Invalid data format in file {report_file}")
    if not data:
        print("Error: No report files found or all files are empty.")
        return


    df = pd.DataFrame(data)
    df.index = range(1, len(df) + 1)
    df.index.name = "Dữ liệu"
    df.loc["Trung bình"] = df.mean()

    # --- Tạo bảng ---
    dfi.export(df, table_output_filepath, table_conversion='matplotlib')
    print("Bảng thời gian thực hiện (ms):")
    print(df.to_string())
    print("\n")

    # --- Tạo biểu đồ cột ---
    # Bỏ cột numpy nếu không có
    plot_df = df.drop("sort (numpy)", axis=1, errors='ignore').copy()
    plot_df = plot_df.drop("Trung bình", axis=0, errors='ignore')

    ax = plot_df.plot(kind="bar", rot=0, figsize=(10, 6),
                      color=['#5DADE2', '#E67E22', '#85929E', '#F4D03F', '#58D68D', '#AF7AC5'])

    plt.title("Kết quả thử nghiệm trên bộ dữ liệu", fontsize=16)
    plt.xlabel("Dữ liệu", fontsize=12)
    plt.ylabel("Thời gian thực hiện (ms)", fontsize=12)
    plt.legend(loc="upper right", fontsize=10)

    for p in ax.patches:
        ax.annotate(f"{p.get_height():.0f}",
                    (p.get_x() + p.get_width() / 2., p.get_height()),
                    ha='center', va='center',
                    xytext=(0, 5),  # Giảm khoảng cách dọc
                    textcoords='offset points',
                    fontsize=8)    # Giảm fontsize

    plt.ylim(0, max(df.max()) * 1.3)  # Tăng giới hạn trên
    plt.tight_layout()
    plt.savefig(output_filepath)
    plt.show()



def main():
    reports_dir = "../reports" 
    os.makedirs(reports_dir, exist_ok=True)
    create_report(reports_dir, "../reports/report.png", "../reports/table.png")

if __name__ == "__main__":
    main()