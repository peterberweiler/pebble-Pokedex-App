	
#include <pebble.h>
#include "menu.h"
#include "settings.h"
#include "pokedex.h"
  ///#include "game1.h" - maybe in a future update
	
int main(void) 
{
	menu_init();
	settings_init();
	pokedex_init();
	  ///game1_init();

	menu_show();
	
	app_event_loop();
	
	menu_deinit();
	settings_deinit();
	pokedex_deinit();
	  ///game1_deinit();
	
	return 0;
}
