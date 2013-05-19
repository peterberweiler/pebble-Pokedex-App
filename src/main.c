

#include "small_functions.h"
	
#define MY_UUID { 0x0A, 0x0D, 0xB9, 0x17, 0x9A, 0xFD, 0x4F, 0x5E, 0xAF, 0x0F, 0xDA, 0x89, 0x70, 0x4F, 0x64, 0x14 }


PBL_APP_INFO(MY_UUID,
             "Pip-Boy 2013", "Peter-Berweiler.de",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);


Window window;
TextLayer timeLayer;
Layer line_layer;
BmpContainer image_container;

int health = 0; 


void line_layer_update_callback(Layer *layer, GContext *ctx) {

  	graphics_context_set_stroke_color(ctx, GColorWhite);

  	graphics_draw_line(ctx, GPoint(0,  0), GPoint(143, 0));
  	graphics_draw_line(ctx, GPoint(0,  1), GPoint(143, 1));
  	graphics_draw_line(ctx, GPoint(0,  2), GPoint(143, 2));

  	graphics_draw_line(ctx, GPoint(0,  3), GPoint(0, 18));
  	graphics_draw_line(ctx, GPoint(1,  3), GPoint(1, 18));

  	graphics_draw_line(ctx, GPoint(143,  3), GPoint(143, 18));
  	graphics_draw_line(ctx, GPoint(142,  3), GPoint(142, 18));


  	graphics_draw_line(ctx, GPoint(2,  164), GPoint(141, 164));
  	graphics_draw_line(ctx, GPoint(2,  165), GPoint(141, 165));

  	graphics_draw_line(ctx, GPoint(2,  150), GPoint(2, 163));
  	graphics_draw_line(ctx, GPoint(3,  150), GPoint(3, 163));

	graphics_draw_line(ctx, GPoint(140,  150), GPoint(140, 163));
 	graphics_draw_line(ctx, GPoint(141,  150), GPoint(141, 163));
	
	
	
	//graphics_fill_rect(ctx, GRect(0, 28, 21, 4), 0, GCornerNone)
	seed = get_seconds(); // Seed the random numbers
	
	/*** Left Arm    14 ,39***/
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(14, 28+39+1, 21, 4), 0, GCornerNone); 
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(14, 28+39+1, random(21), 4), 0, GCornerNone);
	/*** Right Arm   112, 39***/
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(112, 28+39+1, 21, 4), 0, GCornerNone); 
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(112, 28+39+1, random(21), 4), 0, GCornerNone);
	/*** Head        63, 6 ***/
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(63, 28+6+1, 21, 4), 0, GCornerNone); 
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(63, 28+6+1, random(21), 4), 0, GCornerNone);
	/*** Body        63, 62 ***/
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(63, 28+62+1, 21, 4), 0, GCornerNone); 
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(63, 28+62+1, random(21), 4), 0, GCornerNone);
	/*** Left Leg    14, 106 ***/
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(14, 28+106+1, 21, 4), 0, GCornerNone); 
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(14, 28+106+1, random(21), 4), 0, GCornerNone);
	/*** Right Leg  108, 106 ***/
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(108, 28+106+1, 21, 4), 0, GCornerNone); 
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(108, 28+106+1, random(21), 4), 0, GCornerNone);
		
	/*health = health+1;
	
	if (health > 21){
		health = 0;
	}*/
}

/*** Called once per second ***************************/
void handle_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;

  static char timeText[] = "00:00"; // Needs to be static because it's used by the system later.

  PblTm currentTime;
  get_time(&currentTime);

  char *time_format; // "%b %d"
  if (clock_is_24h_style()) {
    time_format = "%H:%M"; 
  } else {
    time_format = "%I:%M";
  }

  string_format_time(timeText, sizeof(timeText), time_format, &currentTime);
  text_layer_set_text(&timeLayer, timeText);

  layer_mark_dirty( &line_layer );
}


void handle_init_app(AppContextRef app_ctx) {

  window_init(&window, "Lol");
  window_stack_push(&window, true);
  window_set_background_color(&window, GColorBlack);

  resource_init_current_app(&FEATURE_DEMO_IMAGE_RESOURCES);

  seed = get_seconds(); // Seed the random numbers

  /*** Vault Boy Image ****************************************************/
  bmp_init_container(RESOURCE_ID_IMAGE_VAULTBOY, &image_container);
  layer_set_frame(&image_container.layer.layer, GRect(0, 28, 144, 140));

  /*** Line Layer */
  layer_init(&line_layer, window.layer.frame);
  line_layer.update_proc = &line_layer_update_callback;
  
  /*** Time Layer old:GRect(5, 5, 100, 28)****************************************/
  GFont custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_FALLOUT_26));

  text_layer_init(&timeLayer, GRect(3, 1, 135 /* width */, 50 /* height */));
  text_layer_set_text_color(&timeLayer, GColorWhite);
  text_layer_set_background_color(&timeLayer, GColorClear);
  text_layer_set_text_alignment(&timeLayer, GTextAlignmentRight);
  text_layer_set_font(&timeLayer, custom_font);
  
  /*** Place Layers  *****************************************************/
  layer_add_child(&window.layer, &image_container.layer.layer);
  
  layer_add_child(&window.layer, &line_layer);
  layer_add_child(&window.layer, &timeLayer.layer);

  handle_tick(app_ctx, NULL);

}

/*** De Init **********************************/
void handle_deinit(AppContextRef ctx) { 
  (void)ctx;
  bmp_deinit_container(&image_container);
}

/*** The main event/run loop for our app **************/
void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init_app,
    .deinit_handler = &handle_deinit,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = MINUTE_UNIT
    }

  };
  app_event_loop(params, &handlers);
}