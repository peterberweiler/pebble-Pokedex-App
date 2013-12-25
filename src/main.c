
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

void update_selection() {
	if (currentID < 1){    currentID = 1;   }
	if (currentID > 152){  currentID = 152; }
	
	if (mode == 1){ // 1 type, 2 data
		text_layer_set_text( text_layer, poke_names[currentID-1]);
	}else{
		text_layer_set_text( text_layer, poke_info[currentID-1]);
	}
	
	gbitmap_destroy( poke_image );
	poke_image = gbitmap_create_with_resource( poke_images[currentID-1] );
	bitmap_layer_set_bitmap( poke_image_layer, poke_image);

}

///////////////////////// INPUT /////////////////////

void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
	
	currentID = currentID -1;
	update_selection();
}

void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
	
	currentID = currentID +1;
	update_selection();
}

void up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
	
	currentID = currentID -15;
	update_selection();
}

void down_long_click_handler(ClickRecognizerRef recognizer, void *context) {
	
	currentID = currentID +15;
	update_selection();
}

void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
	
	if (mode == 1){ // 1 type, 2 data
		mode = 2;
	}else{
		mode = 1;
	}
	update_selection();
}

void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
	
	window_single_click_subscribe(BUTTON_ID_UP,  up_single_click_handler);
	window_long_click_subscribe(BUTTON_ID_UP, 0, up_long_click_handler, NULL);
	
	window_single_click_subscribe(BUTTON_ID_DOWN,  down_single_click_handler);
	window_long_click_subscribe(BUTTON_ID_DOWN, 0, down_long_click_handler, NULL);
}

///////////////////////// INIT /////////////////////
void handle_init(void) {
	
	currentID = 9;
	mode = 1;
	
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

