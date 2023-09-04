#include <windows.h>
#include <fstream>

// Function to save a bitmap to a file
bool SaveBitmapToFile(HBITMAP hBitmap, const char* filename) {
    BITMAP bitmap;
    if (GetObject(hBitmap, sizeof(BITMAP), &bitmap) == 0) {
        return false;
    }

    // Create a compatible device context
    HDC hdc = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, hBitmap);

    // Create a bitmap header
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bitmap.bmWidth;
    bi.biHeight = -bitmap.bmHeight; // Negative height to flip the image
    bi.biPlanes = 1;
    bi.biBitCount = 24; // 24-bit color
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // Calculate the size of the image data
    DWORD dataSize = ((bitmap.bmWidth * bi.biBitCount + 31) / 32) * 4 * bitmap.bmHeight;

    // Create a file and write the bitmap data to it
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdc);
        return false;
    }

    BITMAPFILEHEADER bmfh;
    bmfh.bfType = 0x4D42; // 'BM'
    bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dataSize;
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    file.write(reinterpret_cast<char*>(&bmfh), sizeof(BITMAPFILEHEADER));
    file.write(reinterpret_cast<char*>(&bi), sizeof(BITMAPINFOHEADER));

    BYTE* buffer = new BYTE[dataSize];
    if (!buffer) {
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdc);
        file.close();
        return false;
    }

    if (GetDIBits(hdcMem, hBitmap, 0, bitmap.bmHeight, buffer, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS)) {
        file.write(reinterpret_cast<char*>(buffer), dataSize);
        delete[] buffer;
    } else {
        delete[] buffer;
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdc);
        file.close();
        return false;
    }

    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdc);
    file.close();
    return true;
}

void TakeScreenshot()
{
    HDC hScreenDC = GetDC(nullptr); // CreateDC("DISPLAY",nullptr,nullptr,nullptr);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    int width = 1000; //GetDeviceCaps(hScreenDC,HORZRES);
    int height = 450; //GetDeviceCaps(hScreenDC,VERTRES);
    int left = 2800;
    int top = 1400;
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC,width,height);
    HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC,hBitmap));
    BitBlt(hMemoryDC,0,0,width,height,hScreenDC,left,top,SRCCOPY);
    hBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC,hOldBitmap));
    DeleteDC(hMemoryDC);
    DeleteDC(hScreenDC);
    SaveBitmapToFile(hBitmap, "screenshot.bmp");
}