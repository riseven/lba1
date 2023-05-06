#include "c_extern.h"

LONG MainGameMenu()
{
  enum
  {
    MENUOP_DEMO = 9999,
    MENUOP_NEW_GAME = 20,
    MENUOP_LOAD = 21,
    MENUOP_QUIT = 22,
    MENUOP_OPTIONS = 23
  };

  WORD select;
  WORD flag = 0;

  HQ_StopSample();

  CopyScreen(Log, Screen);

  while (!flag)
  {
    InitDial(0); //	SYS

#ifdef CDROM
    PlayCdTrack(9);
#else
    PlayMidiFile(9);
#endif
    HQ_StopSample();

    GetMultiText(49, PleaseWait);

    select = DoGameMenu(GameMainMenu);
    switch (select) // num mess
    {
    case MENUOP_DEMO:
      MenuDemo();
      Load_HQR(PATH_RESSOURCE "ress.hqr", Screen, RESS_MENU_PCR);
      CopyScreen(Screen, Log);
      SetBlackPal();
      Flip();
      FadeToPal(PtrPal);
      break;

      //			case -1: // esc
    case MENUOP_QUIT:
      flag = 1;
      break;

    case MENUOP_NEW_GAME:

      if (!InputPlayerName(42, 0))
        break;

      /**do
      {
        strcpy( GamePathname, PATH_RESSOURCE"S" ) ;
        strcat( GamePathname, Itoa( Rnd(10000) ) ) ;
        strcat( GamePathname, ".LBA" ) ;
      }
      while( FileSize( GamePathname ) != 0 ) ;*/

      MenuInitGame(1, 0, 1);
      while (Key OR Fire)
        ; // provisoire
      break;

    case MENUOP_LOAD: // load

      if (!ChoosePlayerName(21, 1, 0))
        break;

      MenuInitGame(-1, 0, 0);
      while (Key OR Fire)
        ; // provisoire
      break;

    case MENUOP_OPTIONS:
      CopyScreen(Screen, Log);
      Flip();
      GameOptionMenu[5] = 26; // retour prec
      OptionsMenu();
      break;
    }
  }
  return FALSE;
}