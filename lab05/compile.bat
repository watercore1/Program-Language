g++ -m64 -O2 -std=c++11 -o "process_bmp.exe" "process_bmp.cpp" "Bitmap.cpp"
process_bmp.exe 24.bmp rotate 134 24_1.bmp
process_bmp.exe 32.bmp rotate 134 32_1.bmp
process_bmp.exe 24.bmp resize 700 700 24_2.bmp
process_bmp.exe 32.bmp resize 700 700 32_2.bmp
process_bmp.exe 24.bmp h_flip 24_3.bmp
process_bmp.exe 32.bmp h_flip 32_3.bmp
process_bmp.exe 24.bmp v_flip 24_4.bmp
process_bmp.exe 32.bmp v_flip 32_4.bmp