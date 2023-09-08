#include "screenshotter.cpp"
#include "recognizer.cpp"
#include "keypresser.cpp"

int main()
{
    INPUT buffer[1];
    MouseSetup(buffer);

    MouseMoveAbsolute(buffer, 555, 836);
    MouseClickLeft(buffer);
    Sleep(1000);
    MouseMoveAbsolute(buffer, 1536/2, 864/2);
    MouseClickLeft(buffer);
    Sleep(1000);

    for(int i=0;i<6000;++i)
    {
        TakeScreenshot();
        //std::string outt = RecognizeString();
        //std::cout << "output: " << outt << std::endl;
        if(RecognizeString().find("ber spla") != std::string::npos)
        {
            MouseClickRight(buffer);
            Sleep(250);
            MouseMoveRelative(buffer, 300, 0);
            Sleep(250);
            MouseMoveRelative(buffer, 300, 0);
            Sleep(250);
            MouseMoveRelative(buffer, 300, 0);
            Sleep(250);
            MouseMoveRelative(buffer, 300, 0);
            Sleep(250);
            MouseClickRight(buffer);
            Sleep(2250);
        }
    }

    return 0;
}