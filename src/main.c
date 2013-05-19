
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
	
#include "pokedex.h"
	
#define MY_UUID { 0xC2, 0x84, 0x93, 0x30, 0xE2, 0x28, 0x4A, 0x58, 0xA9, 0xE9, 0xAC, 0x37, 0x66, 0xD4, 0xFC, 0x8C }
PBL_APP_INFO(MY_UUID,
             "Pokedex App", "Peter-Berweiler.de",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);



Window window;
TextLayer textLayer;
BmpContainer image_container;
BmpContainer image_top;
BmpContainer image_bottom;
int currentID;


void update_selection() {
	if (currentID < 1){    currentID = 1;   }
	if (currentID > 152){  currentID = 152; }
	
	text_layer_set_text(&textLayer, poke_names[currentID-1]);
	
	layer_remove_from_parent(&image_container.layer.layer);
	bmp_deinit_container(&image_container);
	
	bmp_init_container(poke_images[currentID-1], &image_container);
	layer_set_frame(&image_container.layer.layer, GRect(/*43*/ 70, 10, 58, 58));
	layer_add_child(&window.layer, &image_container.layer.layer);
	
}

///////////////////////// INPUT /////////////////////

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;
	
	currentID = currentID -1;
	update_selection();
}

void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;
	
	currentID = currentID +1;
	update_selection();
}

void up_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;
	
	currentID = currentID -15;
	update_selection();
}

void down_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;
	
	currentID = currentID +15;
	update_selection();
}

void click_config_provider(ClickConfig **config, Window *window) {
  (void)window;

	config[BUTTON_ID_UP]->click.handler      = (ClickHandler) up_single_click_handler;
	config[BUTTON_ID_UP]->long_click.handler = (ClickHandler) up_long_click_handler;
	
	config[BUTTON_ID_DOWN]->click.handler      = (ClickHandler) down_single_click_handler;
	config[BUTTON_ID_DOWN]->long_click.handler = (ClickHandler) down_long_click_handler;
}


///////////////////////// INIT /////////////////////
void handle_init_app(AppContextRef app_ctx) {

	currentID = 1;
		
	window_init(&window, "Kanto Pokedex");
	window_stack_push(&window, true);
	window_set_background_color(&window, GColorWhite);
	resource_init_current_app(&APP_RESOURCES);

	/*******  TEXT LAYER ********/
	GFont custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PKMN_14));
	text_layer_init(&textLayer, GRect(-6, 44, 150 /* width */, 98 /* height */));
	text_layer_set_text_color(&textLayer, GColorBlack);
	text_layer_set_overflow_mode(&textLayer, GTextOverflowModeTrailingEllipsis);
	text_layer_set_background_color(&textLayer, GColorClear);
	text_layer_set_text_alignment(&textLayer, GTextAlignmentCenter);
	text_layer_set_font(&textLayer, custom_font);

	
	layer_add_child(&window.layer, &textLayer.layer);
	

	/*******  IMAGE ********/
	bmp_init_container(RESOURCE_ID_IMAGE_poke9, &image_container);
	                                                       // gets overwritten
	layer_set_frame(&image_container.layer.layer, GRect(/*43*/ 0, 0, 58, 58));
	layer_add_child(&window.layer, &image_container.layer.layer);
	
	/////// UI TOP ////////////
	bmp_init_container(RESOURCE_ID_UI_TOP, &image_top);
	layer_set_frame(&image_top.layer.layer, GRect( 0, 0, 144, 11));
	layer_add_child(&window.layer, &image_top.layer.layer);
	/////// UI BOTTOM ////////////
	bmp_init_container(RESOURCE_ID_UI_BOTTOM, &image_bottom);
	layer_set_frame(&image_bottom.layer.layer, GRect( 0, 168-11-16, 144, 11));
	layer_add_child(&window.layer, &image_bottom.layer.layer);

	
	window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);
	
	update_selection();
}


///////////////////////// DE INIT /////////////////////
void handle_deinit(AppContextRef ctx) { 
  (void)ctx;
  bmp_deinit_container(&image_container);
}


///////////////////////// MAIN /////////////////////
void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init_app,
    .deinit_handler = &handle_deinit
  };
  app_event_loop(params, &handlers);
}

