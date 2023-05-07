#include "c_extern.h"

enum
{
  MenuOp_Demo = 9999,
  MenuOp_NewGame = 20,
  MenuOp_Load = 21,
  MenuOp_Quit = 22,
  MenuOp_Options = 23
};

void InitDialMainMenu()
{
  InitDial(0);
}

void PlayTrackMenu()
{
#ifdef CDROM
  PlayCdTrack(9);
#else
  PlayMidiFile(9);
#endif
}

LONG MainGameMenu()
{
  WORD select;
  WORD flag = 0;

  HQ_StopSample();
  CopyScreen(Log, Screen);

  while (!flag)
  {
    InitDialMainMenu();
    PlayTrackMenu();
    HQ_StopSample();

    GetMultiText(49, PleaseWait);

    select = DoGameMenu(GameMainMenu);
    switch (select) // num mess
    {
    case MenuOp_Demo:
      MenuDemo();
      Load_HQR(PATH_RESSOURCE "ress.hqr", Screen, RESS_MENU_PCR);
      CopyScreen(Screen, Log);
      SetBlackPal();
      Flip();
      FadeToPal(PtrPal);
      break;

      //			case -1: // esc
    case MenuOp_Quit:
      flag = 1;
      break;

    case MenuOp_NewGame:

      if (!InputPlayerName(42, 0))
        break;

      MenuInitGame(1, 0, 1);
      while (Key OR Fire)
        ; // provisoire
      break;

    case MenuOp_Load: // load

      if (!ChoosePlayerName(21, 1, 0))
        break;

      MenuInitGame(-1, 0, 0);
      while (Key OR Fire)
        ; // provisoire
      break;

    case MenuOp_Options:
      CopyScreen(Screen, Log);
      Flip();
      GameOptionMenu[5] = 26; // retour prec
      OptionsMenu();
      break;
    }
  }
  return FALSE;
}