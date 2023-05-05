#include "..\c_extern.h"

void main(int argc, char *argv[])
{
  DoInitialization(argv[0]);
  ShowAndWaitForLogo();
  CheckCDRom();
  AllocateMemory();

#ifndef DEBUG_TOOLS
  ShowBumper();
  ShowLogoEA();
  ShowFLAIntro();
#endif

  ShowMenu();
  TheEnd(PROGRAM_OK, "");
}
