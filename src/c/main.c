	
#include <pebble.h>

#include "pokedex.h"
#include "constants.h"
	

static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
	int lang = LANG_ENGLISH;
	int h = FOOT_UNIT;
	int w = POUNDS_UNIT;
	
  /*Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_BackgroundColor);
  if(bg_color_t) {
    GColor bg_color = GColorFromHEX(bg_color_t->value->int32);
  }*/
	
	
  Tuple *language_t = dict_find(iter, MESSAGE_KEY_Language);
  if(language_t) {
	  if (strcmp( language_t->value->cstring, "en") == 0){
		  lang = LANG_ENGLISH;
	  }
	  if (strcmp( language_t->value->cstring, "de") == 0){
		  lang = LANG_GERMAN;
	  }
	  if (strcmp( language_t->value->cstring, "fr") == 0){
		  lang = LANG_FRENCH;
	  }
  }

	
  Tuple *height_unit_t = dict_find(iter, MESSAGE_KEY_HeightUnit);
  if(height_unit_t) {
	  if (strcmp( height_unit_t->value->cstring, "ft") == 0){
		  h = FOOT_UNIT;
	  }
	  if (strcmp( height_unit_t->value->cstring, "m") == 0){
		  h = METER_UNIT;
	  }
  }

	
  Tuple *weight_unit_t = dict_find(iter, MESSAGE_KEY_WeightUnit);
  if(weight_unit_t) {
	  if (strcmp( weight_unit_t->value->cstring, "lbs") == 0){
		  w = POUNDS_UNIT;
	  }
	  if (strcmp( weight_unit_t->value->cstring, "g") == 0){
		  w =  GRAM_UNIT;
	  }
  }
	
  persist_write_int( PKEY_LANGUAGE, lang );
  persist_write_int( PKEY_HEIGHT, h );
  persist_write_int( PKEY_WEIGHT, w );
	
  settings_updated( lang,  h,  w);
}



int main(void) 
{
	
	pokedex_init();

	pokedex_show();
	
	// Open AppMessage connection
  	app_message_register_inbox_received(prv_inbox_received_handler);
  	app_message_open( dict_calc_buffer_size(4, 4, 4, 4, 4), 0);
	
	// Main Loop
	app_event_loop();

	pokedex_deinit();
	
	return 0;
}




