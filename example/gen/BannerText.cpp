#include <iostream>
#include <org/summerframework/core.h>

void ApplicationContext::showBanner() {
    std::cout << "  .    _____                                 __ _ _\n /\\\\  / ____|                                \\ \\ \\ \\          \n( ( )| (___  _   _ _ _ __  _ _ __   ___  _ __ \\ \\ \\ \\\n \\\\/  \\___ \\| | | | ' `. \\| ' `. \\ / _ \\| '__| ) ) ) )\n  '    ___) | |_| | || || | || || |  __/| |   / / / /\n     |_____/ \\__,_|_||_||_|_||_||_|\\___||_|  /_/_/_/\n :: Summer Framework ::                 (v0.0.1.DEBUG)\n" << std::endl;
}