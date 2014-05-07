
#include <pebble.h>
#include "menu.h"
#include "settings.h"
#include "pokedex.h"
////#include "game1.h"
#include "localization.h"
#include "constants.h"
	
static Window *window;
static SimpleMenuLayer *simple_menu_layer;

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 2 //Pokémon, Settings

static int settings_language;
	
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem menu_items[NUM_MENU_ITEMS];


static void menu_select_callback(int index, void *ctx) 
{
	switch( index ) {
		case 0:   pokedex_show();  break;
		case 1:  settings_show();  break;
	}

	layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
}

void window_appear(Window *win){
	settings_language = persist_exists(PKEY_LANGUAGE) ? persist_read_int(PKEY_LANGUAGE) : 0;
	menu_items[1].title = localized_string[settings_language][ls_Settings];
}
	
void menu_init(void) {
	
	menu_items[0] = (SimpleMenuItem){
		.title = "Pokédex",
		.callback = menu_select_callback,
	};
  	menu_items[1] = (SimpleMenuItem){
		.title = "Settings",
    	.callback = menu_select_callback, 
	};

	menu_sections[0] = (SimpleMenuSection){
		.num_items = NUM_MENU_ITEMS,
		.items = menu_items,
	};
	
	window = window_create();
	Layer *window_layer = window_get_root_layer( window );
	GRect bounds = layer_get_frame(window_layer);

	window_set_window_handlers( window, (WindowHandlers ) { .appear = window_appear });
	
  	simple_menu_layer = simple_menu_layer_create( bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);
  	layer_add_child(window_layer, simple_menu_layer_get_layer( simple_menu_layer ));
}

void menu_deinit(void){
	simple_menu_layer_destroy(simple_menu_layer);	
  	window_destroy( window );
}

void menu_show(void) 
{
	window_stack_push( window, true);
}




