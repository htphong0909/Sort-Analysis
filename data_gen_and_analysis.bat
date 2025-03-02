@echo off
setlocal enabledelayedexpansion

:: Thiết lập trình biên dịch và cờ tối ưu hóa
set COMPILER=g++
set FLAGS=-std=c++17 -O3 -Wall -Wextra -pedantic -march=native -flto -funroll-loops

:: Tạo thư mục bin nếu chưa có
if not exist bin mkdir bin

:: Xóa file cũ trong bin, reports, tests
echo Cleaning old binaries...
del /Q bin\*.exe 2>nul

echo Cleaning old reports...
del /Q reports\*.txt 2>nul
del /Q reports\*.png

echo Cleaning old tests...
del /Q tests\*.txt 2>nul

timeout /t 2 /nobreak 

cls

:: Danh sách các file C++ cần build
set FILES=DataGen HeapSort MergeSort QuickSort CppStdSort

:: Biên dịch từng file
for %%F in (%FILES%) do (
    echo Building %%F.cpp...
    %COMPILER% src\%%F.cpp -o bin\%%F.exe %FLAGS%
    if errorlevel 1 (
        echo Compilation failed for %%F.cpp!
        exit /b 1
    )
)

echo All C++ files compiled successfully!

cls

:: Chạy từng chương trình C++
for %%F in (%FILES%) do (
    echo ********** Running %%F **********
    bin\%%F.exe
)

:: Kiểm tra và cài đặt numpy nếu cần
echo Checking for numpy...
python -c "import numpy" 2>nul
if %errorlevel% neq 0 (
    echo numpy not found. Installing...
    pip install numpy
)

echo ********** Running pythonSort **********

cd src
python PythonSort.py

echo All programs executed!
echo Press any key to access the chart data visualization.
pause >nul

cls

:: Kiểm tra và cài đặt pandas, matplotlib, dataframe_image nếu cần
echo Checking for pandas...
python -c "import pandas" 2>nul
if %errorlevel% neq 0 (
    echo pandas not found. Installing...
    pip install pandas
)

echo Checking for matplotlib...
python -c "import matplotlib" 2>nul
if %errorlevel% neq 0 (
    echo matplotlib not found. Installing...
    pip install matplotlib
)

echo Checking for dataframe_image...
python -c "import dataframe_image" 2>nul
if %errorlevel% neq 0 (
    echo dataframe_image not found. Installing...
    pip install dataframe_image
)

cls

echo ********** Running FinalReportGen **********
python FinalReportGen.py