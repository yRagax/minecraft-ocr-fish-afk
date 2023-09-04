#include "screenshotter.cpp"
#include "recognizer.cpp"
#include "keypresser.cpp"

int main()
{
    INPUT buffer[1];
    MouseSetup(buffer);

    Sleep(1000);
    MouseMoveAbsolute(buffer, 390, 780);
    MouseClickLeft(buffer);

    for(int i=0;i<600;++i)
    {
        Sleep(400);
        TakeScreenshot();
        std::string outt = RecognizeString();
        std::cout << "output: " << outt << std::endl;
        if (outt.find("ber spla") != std::string::npos)
        {
            MouseClickRight(buffer);
            Sleep(100);
            MouseClickRight(buffer);
            Sleep(3000);
        }
    }

    return 0;
}