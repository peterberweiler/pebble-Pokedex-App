#include <pebble.h>
#include "settings.h"
#include "localization.h"
#include "constants.h"
	
static Window *window;
static SimpleMenuLayer *simple_menu_layer;

#define NUM_MENU_SECTIONS 2
#define NUM_MENU_UNIT_ITEMS 2
#define NUM_MENU_LANGUAGE_ITEMS NUM_LANGUAGES

static SimpleMenuSection    menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem     unit_menu_items[NUM_MENU_UNIT_ITEMS];
static SimpleMenuItem language_menu_items[NUM_MENU_LANGUAGE_ITEMS];


static int settings_language;
static int height_unit;
static int weight_unit;

	
#define HEIGHT_CELL 0
#define WEIGHT_CELL 1

	
static void unit_select_callback(int index, void *ctx) {

	if (index == HEIGHT_CELL) {
		if ( height_unit == METER_UNIT) {   height_unit = FOOT_UNIT;
		}else{             /*FOOT_UNIT*/    height_unit = METER_UNIT; }
		persist_write_int( PKEY_HEIGHT, height_unit );
	}else{ /*WEIGHT_CELL*/
		if ( weight_unit == POUNDS_UNIT) {   weight_unit = GRAM_UNIT;
		}else{             /*GRAM_UNIT*/    weight_unit = POUNDS_UNIT;}
		persist_write_int( PKEY_WEIGHT, weight_unit );
	}
	
	
	if ( height_unit == METER_UNIT) { 
		unit_menu_items[HEIGHT_CELL].title = "Height: Meter";
	}else{             //FOOT_UNIT
		unit_menu_items[HEIGHT_CELL].title = "Height: Foot";
	}
	if ( weight_unit == POUNDS_UNIT) {
		unit_menu_items[WEIGHT_CELL].title = "Weight: Pounds";
	}else{             //GRAM_UNIT
		unit_menu_items[WEIGHT_CELL].title = "Weight: Gram";
		
	}
		
	layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
}

static void language_select_callback(int index, void *ctx) 
{	
	persist_write_int( PKEY_LANGUAGE, index );
	
	for ( int i=0; i < NUM_LANGUAGES; i++ ) 
	{
		if ( index == i ){
			language_menu_items[i].subtitle = "Selected";	
		}else{	
			language_menu_items[i].subtitle = "";	
		}
	}
	layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
}

void settings_init(void) {
	
	settings_language = persist_exists(PKEY_LANGUAGE) ? persist_read_int(PKEY_LANGUAGE) : 0;
	height_unit = persist_exists(PKEY_HEIGHT) ? persist_read_int(PKEY_HEIGHT) : METER_UNIT;
	weight_unit = persist_exists(PKEY_WEIGHT) ? persist_read_int(PKEY_WEIGHT) : GRAM_UNIT;
	
	
	unit_menu_items[HEIGHT_CELL] = (SimpleMenuItem){
		.callback = unit_select_callback,
	};
  	unit_menu_items[WEIGHT_CELL] = (SimpleMenuItem){
    	.callback = unit_select_callback,
	};
	
	if ( height_unit == METER_UNIT) { 
		unit_menu_items[HEIGHT_CELL].title = "Height: Meter";
	}else{             //FOOT_UNIT
		unit_menu_items[HEIGHT_CELL].title = "Height: Foot";
	}
	if ( weight_unit == POUNDS_UNIT) {
		unit_menu_items[WEIGHT_CELL].title = "Weight: Pounds";
	}else{             //GRAM_UNIT
		unit_menu_items[WEIGHT_CELL].title = "Weight: Gram";
	}

		
	for ( int i=0; i < NUM_LANGUAGES; i++ ) 
	{
		language_menu_items[i] = (SimpleMenuItem) {
			.title = language_names[i],
    		.callback = language_select_callback, 
		};
		
		if ( settings_language == i ){
			language_menu_items[i].subtitle = "Selected";	
		}else{	
			language_menu_items[i].subtitle = "";	
		}
	}
	
	menu_sections[0] = (SimpleMenuSection){
		.title = "Units",
		.num_items = NUM_MENU_UNIT_ITEMS,
		.items = unit_menu_items,
	};	
	menu_sections[1] = (SimpleMenuSection){
		.title = "Language",
		.num_items = NUM_MENU_LANGUAGE_ITEMS,
		.items = language_menu_items,
	};
	
	window = window_create();
	Layer *window_layer = window_get_root_layer( window );
	GRect bounds = layer_get_frame(window_layer);

  	simple_menu_layer = simple_menu_layer_create( bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);
  	layer_add_child(window_layer, simple_menu_layer_get_layer( simple_menu_layer ));

}

void settings_deinit(void){
	simple_menu_layer_destroy(simple_menu_layer);	
	layer_mark_dirty( window_get_root_layer( window ));
  	window_destroy( window );
}

void settings_show(void) 
{
	window_stack_push( window, true);
}


