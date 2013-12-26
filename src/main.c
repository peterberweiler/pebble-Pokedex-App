
#include <pebble.h>
	
#include "pokedex.h"

Window      *window;
TextLayer   *text_layer;

GBitmap     *poke_image;
BitmapLayer *poke_image_layer;

GBitmap     *top_bar_image;
BitmapLayer *top_bar_layer;
GBitmap     *bottom_bar_image;
BitmapLayer *bottom_bar_layer;

GFont       *custom_font;

int currentID;
int mode; // 1 type, 2 data 
#define MODE_TYPE 1
#define MODE_DATA 2

static long seed;

void update_selection() {
	if (currentID < 1){    currentID = 1;   }
	if (currentID > NUM_POKEMON){  currentID = NUM_POKEMON; }
	
	if (mode == MODE_TYPE){ // 1 type, 2 data
		text_layer_set_text( text_layer, poke_names[currentID-1]);
	}else{
		text_layer_set_text( text_layer, poke_info[currentID-1]);
	}
	
	gbitmap_destroy( poke_image );
	poke_image = gbitmap_create_with_resource( poke_images[currentID-1] );
	bitmap_layer_set_bitmap( poke_image_layer, poke_image);

}

int random(int max) // returns 1 ... max
{
	seed = (((seed * 214013L + 2531011L) >> 16) & 32767);
	return ((seed % max) + 1);
}

///////////////////////// INPUT /////////////////////

void up_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	if (click_number_of_clicks_counted( recognizer ) >= 4)
		currentID = currentID -10;
	else if (click_number_of_clicks_counted( recognizer ) == 1)
		currentID = currentID -1;
	
	update_selection();
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	if (click_number_of_clicks_counted( recognizer ) >= 4)
		currentID = currentID +10;
	else if (click_number_of_clicks_counted( recognizer ) == 1)
		currentID = currentID +1;

	update_selection();
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) 
{	
	if (click_number_of_clicks_counted( recognizer ) <= 2)
	{
		if (mode == MODE_TYPE)
			mode = MODE_DATA;
		else
			mode = MODE_TYPE;
	}
	
	if (click_number_of_clicks_counted( recognizer ) >= 2)
	{
		currentID = random( NUM_POKEMON );	
	}
	
	update_selection();
}


void click_config_provider(void *context) {

	
	window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 500, select_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_UP,     300,     up_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_DOWN,   300,   down_click_handler);
}

///////////////////////// INIT /////////////////////
void handle_init(void) {
	
	seed = time( NULL );
	currentID = random( NUM_POKEMON ); //Random ID between 1 and 152
	
	mode = MODE_TYPE; //Type Mode
	
	window = window_create();
	window_set_background_color( window, GColorWhite);
	Layer *window_layer = window_get_root_layer( window );
	
	window_set_click_config_provider( window, click_config_provider );
	
	/*******  TEXT LAYER ********/
	
	text_layer = text_layer_create( GRect(4, 44, 140 /* width */, 98 /* height */));
	
	custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PKMN_14));
	text_layer_set_font( text_layer, custom_font);
	text_layer_set_text_color( text_layer, GColorBlack);
	text_layer_set_overflow_mode( text_layer, GTextOverflowModeWordWrap);
	text_layer_set_background_color( text_layer, GColorClear);
	text_layer_set_text_alignment( text_layer, GTextAlignmentCenter);
	
	layer_add_child( window_layer, text_layer_get_layer( text_layer ));

		
	/////// IMAGE ////////////
	poke_image       = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_poke1);
	poke_image_layer = bitmap_layer_create( GRect( 70, 10, 58, 58) );
	bitmap_layer_set_alignment( poke_image_layer, GAlignCenter);
	bitmap_layer_set_background_color( poke_image_layer, GColorClear);
	bitmap_layer_set_compositing_mode( poke_image_layer, GCompOpAnd);
	bitmap_layer_set_bitmap( poke_image_layer, poke_image);
	layer_add_child( window_layer, bitmap_layer_get_layer( poke_image_layer ));
	
	/////// UI TOP ////////////
	top_bar_image = gbitmap_create_with_resource( RESOURCE_ID_UI_TOP );
	top_bar_layer = bitmap_layer_create(GRect( 0, 0, 144, 11));
	bitmap_layer_set_bitmap( top_bar_layer, top_bar_image);
	layer_add_child( window_layer, bitmap_layer_get_layer( top_bar_layer ));
		
	/////// UI BOTTOM ////////////
	bottom_bar_image = gbitmap_create_with_resource( RESOURCE_ID_UI_BOTTOM );
	bottom_bar_layer = bitmap_layer_create( GRect( 0, 168-11-16, 144, 11) );
	bitmap_layer_set_bitmap( bottom_bar_layer, bottom_bar_image);
	layer_add_child( window_layer, bitmap_layer_get_layer( bottom_bar_layer ));

	
	
	update_selection();
	
	window_stack_push( window, true /* Animated */);
}


///////////////////////// DE INIT /////////////////////

void handle_deinit(void) {
	bitmap_layer_destroy( poke_image_layer );
	bitmap_layer_destroy( top_bar_layer );
	bitmap_layer_destroy( bottom_bar_layer );
	

	gbitmap_destroy( poke_image );
	gbitmap_destroy( top_bar_image );
	gbitmap_destroy( bottom_bar_image );
	
	text_layer_destroy( text_layer );

	window_destroy( window );
	
	fonts_unload_custom_font( custom_font );
}

///////////////////////// MAIN /////////////////////
int main(void) {
	  handle_init();
	  app_event_loop();
	  handle_deinit();
}

