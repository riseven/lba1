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

void WaitReleaseKey()
{
  while (Key OR Fire)
  {
    // Empty loop
  }
}

void ShowMenuDemo()
{
  MenuDemo();
  Load_HQR(PATH_RESSOURCE "ress.hqr", Screen, RESS_MENU_PCR);
  CopyScreen(Screen, Log);
  SetBlackPal();
  Flip();
  FadeToPal(PtrPal);
}

void SelectNewGame()
{
  if (!InputPlayerName(42, 0))
    break;

  MenuInitGame(1, 0, 1);
  WaitReleaseKey()
}

void SelectMenuLoad()
{
  if (!ChoosePlayerName(21, 1, 0))
    break;

  MenuInitGame(-1, 0, 0);
  WaitReleaseKey()
}

void SelectMenuOptions()
{
  CopyScreen(Screen, Log);
  Flip();
  GameOptionMenu[5] = 26; // retour prec
  OptionsMenu();
}

LONG MainGameMenu()
{
  WORD select;
  bool quit = false;

  HQ_StopSample();
  CopyScreen(Log, Screen);

  while (!quit)
  {
    InitDialMainMenu();
    PlayTrackMenu();
    HQ_StopSample();

    GetMultiText(49, PleaseWait);

    select = DoGameMenu(GameMainMenu);
    switch (select)
    {
    case MenuOp_Demo:
      ShowMenuDemo();
      break;

    case MenuOp_NewGame:
      SelectNewGame();
      break;

    case MenuOp_Load:
      SelectMenuLoad();
      break;

    case MenuOp_Options:
      SelectMenuOptions();
      break;

    case MenuOp_Quit:
      quit = true;
      break;
    }
  }
  return FALSE;
}