

#include "Headers/Application.h"

int main(int argc, char *argv[])
{
    Application* application = new Application(argc, argv);
    delete application;
    return 0;
}