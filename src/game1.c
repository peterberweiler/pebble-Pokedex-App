/*
	Game Nr.1
	"Guess the Pokemon Name!"
*/
/*
#include <pebble.h>
#include "game1.h"
#include "pokemon.h"
#include "constants.h"

	
static Window      *window;

static GBitmap     *poke_image;
static BitmapLayer *poke_image_layer;

static GBitmap     *top_bar_image;
static BitmapLayer *top_bar_layer;
static GBitmap     *bottom_bar_image;
static BitmapLayer *bottom_bar_layer;

static GFont       *custom_font;

static long seed;
static int settings_language;

//static char num[4];
//static char text[80];

#define NUM_ANSWERS 3
#define NUM_QUESTIONS 15
	
static TextLayer * answer_layers[NUM_ANSWERS];
static int answers[NUM_ANSWERS];
static int questions[NUM_QUESTIONS];
static int selected_answer; //0, 1, 2
static int  correct_answer; //0, 1, 2
static int current_question; //0..14

int game1_random(int max) { // returns 1 ... max
	seed = (((seed * 214013L + 2531011L) >> 16) & 32767);
	return ((seed % max) + 1);
}

void game1_selection_changed() {
	if (selected_answer < 0           ){  selected_answer = NUM_ANSWERS-1;   }
	if (selected_answer >= NUM_ANSWERS){  selected_answer = 0; }

	for (int i = 0; i < NUM_ANSWERS; i++ ){
		text_layer_set_background_color( answer_layers[i], (selected_answer == i) ? GColorBlack : GColorWhite);
		text_layer_set_text_color      ( answer_layers[i], (selected_answer == i) ? GColorWhite : GColorBlack);
	}
}

void game1_new_game() {	
	bool ok;
	for (int i = 0; i < NUM_QUESTIONS; i++ ){
		do {
			ok = true;
			questions[i] = game1_random(151);	
			for (int e = 0; e < i; e++ ){
				if (questions[i] == questions[e]){	ok = false; }
			}
		} while ( ok == false);
	}
}

void game1_next_question() {
	//Generate Answers
	bool ok;
	for (int i = 0; i < NUM_ANSWERS; i++ ){
		do {
			ok = true;
			answers[i] = game1_random(151);	
			for (int e = 0; e < i; e++ ){
				if (answers[i] == answers[e]){	ok = false; }
			}
		} while ( ok == false);
	}
	
	//Choose which answer is the correct one
	correct_answer  = game1_random(3)-1; 
	selected_answer = 0;
	
	
	for (int i = 0; i < NUM_ANSWERS; i++ ){
		text_layer_set_text( answer_layers[i], poke_names [settings_language] [answers[i]-1]);
	}
	
	gbitmap_destroy( poke_image );
	poke_image = gbitmap_create_with_resource( poke_images[answers[correct_answer]-1] );
	bitmap_layer_set_bitmap( poke_image_layer, poke_image);
	
	game1_selection_changed();
}

void game1_up_click_handler(ClickRecognizerRef recognizer, void *context) {
	selected_answer = selected_answer -1;
	game1_selection_changed();
}

void game1_down_click_handler(ClickRecognizerRef recognizer, void *context) {
	selected_answer = selected_answer +1;
	game1_selection_changed();
}

void game1_select_click_handler(ClickRecognizerRef recognizer, void *context) {
	if ( selected_answer == correct_answer ) {
		if ( selected_answer == correct_answer ) {
			game1_next_question();
		}else{
			window_stack_pop( true );
		}
	}
}

void game1_click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_UP,     game1_up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN,   game1_down_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, game1_select_click_handler);
}

void game1_show(void) 
{
	settings_language = persist_exists(PKEY_LANGUAGE) ? persist_read_int(PKEY_LANGUAGE) : 0;
	
	window_stack_push( window, true);
	
	game1_new_game();
}

///////////////////////// INIT /////////////////////
void game1_init(void) {
	
	seed = time( NULL );
	
	window = window_create();
	window_set_background_color( window, GColorWhite);
	Layer *window_layer = window_get_root_layer( window );
	
	window_set_click_config_provider( window, game1_click_config_provider );
	
	/////////////  TEXT LAYER ////////////
	custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PKMN_14));
	
	
	for (int i = 0; i < NUM_ANSWERS; i++ ){
		answer_layers[i] = text_layer_create( GRect( 0,  72 + i*19, 144, 20));
		text_layer_set_font( answer_layers[i], custom_font);
		text_layer_set_text_alignment( answer_layers[i], GTextAlignmentCenter);
		layer_add_child( window_layer, text_layer_get_layer( answer_layers[i] ));
	}

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
}


///////////////////////// DE INIT /////////////////////

void game1_deinit(void) {
	bitmap_layer_destroy( poke_image_layer );
	bitmap_layer_destroy( top_bar_layer );
	bitmap_layer_destroy( bottom_bar_layer );

	gbitmap_destroy( poke_image );
	gbitmap_destroy( top_bar_image );
	gbitmap_destroy( bottom_bar_image );

	
	fonts_unload_custom_font( custom_font );
	
	for (int i = 0; i < NUM_ANSWERS; i++ ){
		text_layer_destroy( answer_layers[i] );
	}
	
	window_destroy( window );
}
*/



