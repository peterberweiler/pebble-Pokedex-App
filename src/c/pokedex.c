
#include <pebble.h>
#include "pokedex.h"
#include "pokemon.h"
#include "constants.h"
	

static Window      *window;
static StatusBarLayer *s_status_bar;


static TextLayer   *text_layer;

static GBitmap     *poke_image;

static BitmapLayer *poke_image_layer;
static Layer 	   *big_image_layer;

static GBitmap     *top_left_image;
static BitmapLayer *top_left_layer;
static GBitmap     *top_right_image;
static BitmapLayer *top_right_layer;
static GBitmap     *bottom_bar_image;
static BitmapLayer *bottom_bar_layer;

static Layer 	   *mode_layer;
	
static GFont       custom_font;

#define MODE_TYPE 1
#define MODE_DATA 2
#define MODE_IMAGE 3
#define MODE_COUNT 3

static long seed;
static int currentID;
static int mode; // 1 type, 2 data 
static int settings_language;
static int height_unit;
static int weight_unit;
static char num[4];
static char text[60];
static int window_center_x = 0;



/*static bool byte_get_bit(uint8_t *byte, uint8_t bit) {
	return ((*byte) >> bit) & 1;
}

static void byte_set_bit(uint8_t *byte, uint8_t bit, uint8_t value) {
  *byte ^= (-value ^ *byte) & (1 << bit);
}

static GColor get_pixel_color(GBitmapDataRowInfo info, int x) {
#if defined(PBL_COLOR)
  // Read the single byte color pixel
	APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", info.data[x]);
  return (GColor){ .argb = info.data[x] };
#elif defined(PBL_BW)
  // Read the single bit of the correct byte
  uint8_t byte = x / 8;
  uint8_t bit = 7- (x % 8); 
  return byte_get_bit(&info.data[byte], bit) ? GColorWhite : GColorBlack;
#endif
}

static void set_pixel_color(GBitmapDataRowInfo info, GPoint point, GColor color) {
#if defined(PBL_COLOR)
  // Write the pixel's byte color
  memset(&info.data[point.x], color.argb, 1);
#elif defined(PBL_BW)
  // Find the correct byte, then set the appropriate bit
  uint8_t byte = point.x / 8;
  uint8_t bit = point.x % 8; 
  byte_set_bit(&info.data[byte], bit, gcolor_equal(color, GColorWhite) ? 1 : 0);
#endif
}

static uint8_t getNumColorsForFormat(GBitmapFormat format){
  switch (format) {
    case GBitmapFormat1BitPalette:  return 2;
#ifdef PBL_COLOR
    case GBitmapFormat2BitPalette:  return 4;
    case GBitmapFormat4BitPalette:  return 16;
#endif
    default: return 0;
  }
}*/

static uint8_t getNumBitsPerPixelForFormat(GBitmapFormat format){
  switch (format) {
    case GBitmapFormat1Bit: 
    case GBitmapFormat1BitPalette: return 1;
#ifdef PBL_COLOR
    case GBitmapFormat2BitPalette: return 2;
    case GBitmapFormat4BitPalette: return 4;
    case GBitmapFormat8Bit:        return 8;
#endif
    default: return 0;
  }
}

uint8_t bitMaskForNumBits( uint8_t numBits){
	uint8_t mask = 1;
	for (short i = 0; i<numBits; i++)
		mask *=2; 
	return mask - 1;
}


static void mode_layer_update_proc(Layer *layer, GContext *ctx) {
	graphics_context_set_stroke_color( ctx,	 
			PBL_IF_COLOR_ELSE(GColorWhite, GColorBlack) );

	
	
	#if defined(PBL_ROUND)
		switch(mode) {
		case MODE_TYPE:
			graphics_draw_line( ctx, GPoint(4, 0), GPoint(14, 0));
			graphics_draw_line( ctx, GPoint(2, 1), GPoint(13, 1));
			graphics_draw_line( ctx, GPoint(0, 2), GPoint(12, 2));
			break;
		case MODE_DATA:
			graphics_draw_line( ctx, GPoint(17, 0), GPoint(28, 0));
			graphics_draw_line( ctx, GPoint(16, 1), GPoint(29, 1));
			graphics_draw_line( ctx, GPoint(15, 2), GPoint(30, 2));
			break;
		case MODE_IMAGE:
			graphics_draw_line( ctx, GPoint(31, 0), GPoint(41, 0));
			graphics_draw_line( ctx, GPoint(32, 1), GPoint(43, 1));
			graphics_draw_line( ctx, GPoint(33, 2), GPoint(45, 2));
			break;
		}
	#elif defined(PBL_BW)
		switch(mode) {
		case MODE_TYPE:
			for(int i=1; i<=27;i+=2)
				graphics_draw_line( ctx, GPoint(i, 0), GPoint(i, 2));
			break;
		case MODE_DATA:
			for(int i=29; i<=57;i+=2)
				graphics_draw_line( ctx, GPoint(i, 0), GPoint(i, 2));
			break;
		case MODE_IMAGE:
			for(int i=59; i<=85;i+=2)
				graphics_draw_line( ctx, GPoint(i, 0), GPoint(i, 2));
			break;
		}
	#else
		switch(mode) {
		case MODE_TYPE:
			graphics_draw_line( ctx, GPoint(4, 0), GPoint(27, 0));
			graphics_draw_line( ctx, GPoint(2, 1), GPoint(26, 1));
			graphics_draw_line( ctx, GPoint(0, 2), GPoint(25, 2));
			break;
		case MODE_DATA:
			graphics_draw_line( ctx, GPoint(30, 0), GPoint(55, 0));
			graphics_draw_line( ctx, GPoint(29, 1), GPoint(56, 1));
			graphics_draw_line( ctx, GPoint(28, 2), GPoint(57, 2));
			break;
		case MODE_IMAGE:
			graphics_draw_line( ctx, GPoint(58, 0), GPoint(81, 0));
			graphics_draw_line( ctx, GPoint(59, 1), GPoint(83, 1));
			graphics_draw_line( ctx, GPoint(60, 2), GPoint(85, 2));
			break;
		}
	#endif	
}

static void big_layer_update_proc(Layer *layer, GContext *ctx) {
	
	
	GRect bounds = gbitmap_get_bounds( poke_image );
	GPoint origin = GPoint(116/2 - bounds.size.w, 116/2 - bounds.size.h); //to center image
	
	
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "bytes_per_row %d", gbitmap_get_bytes_per_row(poke_image));
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "NumColorsForFormat %d", getNumColorsForFormat(format));
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "NumBitsPerPixelForFormat %d", getNumBitsPerPixelForFormat(format));
		
    GBitmapFormat format = gbitmap_get_format(poke_image);
	uint8_t bitsPerPixel = getNumBitsPerPixelForFormat( format);
	uint8_t pixelPerByte = 8 / bitsPerPixel;
	
	GColor *palette = gbitmap_get_palette( poke_image );
		
	uint8_t pixelMask = bitMaskForNumBits( bitsPerPixel );
	
	for(int y = 0; y < bounds.size.h; y++) {
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "NEW ROW %d: %d - %d", y, info.min_x, info.max_x); 
		GBitmapDataRowInfo info = gbitmap_get_data_row_info(poke_image, y);
		
		int yy =  y*2 + origin.y;
		
  		for(int i = info.min_x; i <= info.max_x; i++) {
			
			int xx =  i*2 + origin.x;
			
			#if defined(PBL_COLOR)
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", info.data[x]);
				//graphics_context_set_stroke_color( ctx, (GColor){ .argb = info.data[x] });
			
				//graphics_context_set_stroke_color( ctx, palette[ (info.data[x/2] >> 4*(1-x%2) )& 0xF] );
			
				graphics_context_set_stroke_color( ctx, palette[ (info.data[i/pixelPerByte] >> bitsPerPixel*(pixelPerByte -1 - i%pixelPerByte) )& pixelMask] );
					
			#elif defined(PBL_BW)
				//graphics_context_set_stroke_color( ctx, byte_get_bit(&info.data[x / 8], 7- (x % 8)) ? GColorWhite : GColorBlack);	   
			
				graphics_context_set_stroke_color( ctx,			
  					 ((info.data[i / 8]) >> (7- i%8) & 1  )? GColorWhite : GColorBlack );

			#endif
			//graphics_context_set_stroke_color( ctx, //get_pixel_color(info, i));
			
			
			//graphics_draw_rect( ctx, GRect(xx, yy, 2, 2));
			graphics_draw_pixel( ctx, GPoint(xx, yy));
			graphics_draw_pixel( ctx, GPoint(xx+1, yy));
			graphics_draw_pixel( ctx, GPoint(xx, yy+1));										  
			graphics_draw_pixel( ctx, GPoint(xx+1, yy+1));										  
													  
  		}
		graphics_context_set_stroke_color( ctx,	 GColorBlack );
		//graphics_draw_rect( ctx, GRect(0, 0, 116,  116));
	}
}

//gbitmap_destroy(  big_image );
		//GRect bounds = gbitmap_get_bounds( poke_image );
		//big_image = gbitmap_create_blank( GSize( bounds.size.w*2, bounds.size.h*2), 
		//							   gbitmap_get_format(poke_image));
		//big_image = scaleBitmap( poke_image, 200, 200);
		/*GRect bounds = //layer_get_bounds(layer);
		for(int y = 0; y < bounds.size.h; y++) {  //for(int y = 0; y < bounds.size.h; y++) {
  			GBitmapDataRowInfo info      = gbitmap_get_data_row_info(poke_image, y);
			GBitmapDataRowInfo nextInfo1 = gbitmap_get_data_row_info( big_image, y*2);
			//GBitmapDataRowInfo nextInfo2 = gbitmap_get_data_row_info( big_image, y*2+1);
  			for(int x = info.min_x; x <= info.max_x; x++) {
				GColor colr = get_pixel_color(info, x);
				set_pixel_color(nextInfo1, GPoint(x*2,   y*2), colr);
				set_pixel_color(nextInfo1, GPoint(x*2+1, y*2), colr);
				//set_pixel_color(nextInfo2, GPoint(x*2,   y*2+1), colr);
				//set_pixel_color(nextInfo2, GPoint(x*2+1, y*2+1), colr);
  			}
		}
		//bitmap_layer_set_bitmap( poke_image_layer, big_image);*/

void update_selection( bool mode_changed ) {
	if (currentID < 1){    currentID = 1;   }
	if (currentID > NUM_POKEMON){  currentID = NUM_POKEMON; }
	
	if (currentID  <  10 ){	     snprintf( num, sizeof(num), "00%d", currentID);}
	else if (currentID  < 100 ){ snprintf( num, sizeof(num), "0%d", currentID);	}
	else{	                     snprintf( num, sizeof(num), "%d", currentID);	}
	if (currentID == 152 ){ snprintf( num, sizeof(num), "?&0"); }
	
	if (mode == MODE_TYPE){ // 1 type
		snprintf( text, sizeof(text), 
			" %s      \n\n%s\n\n%s\n%s",
			num, 
			poke_names [settings_language] [currentID-1],
			type_names [settings_language] [poke_info_type[(currentID-1)*2]],
			type_names [settings_language] [poke_info_type[(currentID-1)*2 +1]]);
	}else if (mode == MODE_DATA){ // 2 data
		snprintf( text, sizeof(text), 				 
			" %s      \n\n%s\n\n%s%s\n%s%s",
			num, 
			poke_names[settings_language][currentID-1],
			poke_info_data[height_unit] [currentID-1] ,
			unit_names    [height_unit],
			poke_info_data[NUM_HEIGHT_UNIT + weight_unit][currentID-1],
			unit_names    [NUM_HEIGHT_UNIT + weight_unit]);
	}else{
		snprintf( text, sizeof(text), "%s", num);
	}  
	text_layer_set_text( text_layer, text); 
	
	gbitmap_destroy( poke_image );
	
	poke_image = gbitmap_create_with_resource( poke_images[currentID-1] );

	
		
	if (mode_changed) {
		layer_mark_dirty( mode_layer );
		
		if (mode == MODE_IMAGE) {
			layer_set_frame(  text_layer_get_layer( text_layer), GRect( window_center_x-68, 
										  3 + STATUS_BAR_LAYER_HEIGHT, 
                                          140, 98 ));
			layer_set_hidden( big_image_layer, false);
			layer_set_hidden( bitmap_layer_get_layer(poke_image_layer), true);
		}else{  
			layer_set_frame(  text_layer_get_layer( text_layer), GRect( window_center_x-68, 
										  44 + STATUS_BAR_LAYER_HEIGHT, 
                                          140, 98 ));
			layer_set_hidden( big_image_layer, true);
			layer_set_hidden( bitmap_layer_get_layer(poke_image_layer), false);
		}
	}else{
		if (mode == MODE_IMAGE) {
			layer_mark_dirty( big_image_layer);
		}else{  
			layer_mark_dirty(  bitmap_layer_get_layer( poke_image_layer));
			//bitmap_layer_set_bitmap( poke_image_layer, poke_image);
		}
	}
	
	
}


void settings_updated(int lang, int h, int w) {
	settings_language = lang;
 	height_unit = h;
	weight_unit = w;
	
	update_selection( false);
}

int random(int max) // returns 1 ... max
{
	seed = (((seed * 214013L + 2531011L) >> 16) & 32767);
	return ((seed % max) + 1);
}


void up_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	if (click_number_of_clicks_counted( recognizer ) >= 4)
		currentID = currentID -10;
	else if (click_number_of_clicks_counted( recognizer ) == 1)
		currentID = currentID -1;
	
	update_selection( false);
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	if (click_number_of_clicks_counted( recognizer ) >= 4){
		currentID = currentID +10;
		if (currentID > NUM_POKEMON-1){  currentID = NUM_POKEMON-1; } //Dont show MissignNo during fast scrolling
	}else if (click_number_of_clicks_counted( recognizer ) == 1)
		currentID = currentID +1;

	update_selection( false);
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) 
{
	if (click_number_of_clicks_counted( recognizer ) >= 3) {
		currentID = random( NUM_POKEMON );
		
		if (click_number_of_clicks_counted( recognizer ) == 3) {
			mode -= 1;
			if (mode < 1) mode = MODE_COUNT;
		}
	}else if (click_number_of_clicks_counted( recognizer ) == 1){
		mode += 1;
		if (mode > MODE_COUNT)
			mode = 1;
	}
	
	update_selection( true);
}

void click_config_provider(void *context) {
	window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 650, select_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_UP,     300,     up_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_DOWN,   300,   down_click_handler);
}

void pokedex_show(void) 
{
	settings_language = persist_exists(PKEY_LANGUAGE) ? persist_read_int(PKEY_LANGUAGE) : 0;
	height_unit = persist_exists(PKEY_HEIGHT) ? persist_read_int(PKEY_HEIGHT) : FOOT_UNIT;
	weight_unit = persist_exists(PKEY_WEIGHT) ? persist_read_int(PKEY_WEIGHT) : POUNDS_UNIT;

	window_stack_push( window, true);
	update_selection( true);
}

///////////////////////// INIT /////////////////////
void pokedex_init(void) {
	
	seed = time( NULL );
	currentID = 1;
	//currentID = random( NUM_POKEMON ); //Random ID between 1 and 152

	mode = MODE_TYPE; //Type Mode
	
	window = window_create();
	window_set_background_color( window, GColorWhite);
	window_set_click_config_provider( window, click_config_provider );
	
	
	Layer *window_layer = window_get_root_layer( window );
	GRect window_bounds = layer_get_frame( window_layer );
	window_center_x = window_bounds.size.w/2;
	
	s_status_bar = status_bar_layer_create();
	
	//status_bar_layer_set_separator_mode(s_status_bar,  StatusBarLayerSeparatorModeDotted);
	//status_bar_layer_set_separator_mode(s_status_bar, StatusBarLayerSeparatorModeNone);
	// TODO
	status_bar_layer_set_colors(s_status_bar, 
								PBL_IF_COLOR_ELSE( GColorRed, GColorBlack),
								PBL_IF_COLOR_ELSE( GColorBlack, GColorWhite));
	
  	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));
	

	/////// TEXT LAYER ////////////
	text_layer = text_layer_create( GRect( window_center_x-68, 
										  44+STATUS_BAR_LAYER_HEIGHT, 
                                          140, 98 ));
	//TODO
	custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PKMN_14));
	//custom_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
	text_layer_set_font( text_layer, custom_font);
	
	text_layer_set_text_color( text_layer, GColorBlack);
	text_layer_set_overflow_mode( text_layer, GTextOverflowModeWordWrap);
	text_layer_set_text_alignment( text_layer, GTextAlignmentCenter);
	
	layer_add_child( window_layer, text_layer_get_layer( text_layer ));
	
	/////// IMAGE ////////////
	poke_image       = gbitmap_create_with_resource( poke_images[0]);
	poke_image_layer = bitmap_layer_create( GRect( window_center_x-2, 10+STATUS_BAR_LAYER_HEIGHT, 
												   58, 58) );
	bitmap_layer_set_alignment( poke_image_layer, GAlignCenter);
	
	
	bitmap_layer_set_bitmap( poke_image_layer, poke_image);
	layer_add_child( window_layer, bitmap_layer_get_layer( poke_image_layer ));
	
	/////// UI TOP////////////
	top_left_image  = gbitmap_create_with_resource( RESOURCE_ID_UI_TOP_LEFT );
	top_right_image = gbitmap_create_with_resource( RESOURCE_ID_UI_TOP_RIGHT );
	
	#if defined(PBL_ROUND)  		
		top_left_layer  = bitmap_layer_create(GRect( window_center_x-68, STATUS_BAR_LAYER_HEIGHT-12,
											   47, 18));
		top_right_layer = bitmap_layer_create(GRect( window_center_x+21, STATUS_BAR_LAYER_HEIGHT-12,
											   47, 18));
	#else
		top_left_layer  = bitmap_layer_create(GRect( window_center_x-72, STATUS_BAR_LAYER_HEIGHT-12,
											   31, 18));
		top_right_layer = bitmap_layer_create(GRect( window_center_x+41, STATUS_BAR_LAYER_HEIGHT-12,
											   31, 18));
	#endif
	
		
	bitmap_layer_set_bitmap( top_left_layer,  top_left_image);
	bitmap_layer_set_bitmap( top_right_layer, top_right_image);
	layer_add_child( window_layer, bitmap_layer_get_layer( top_left_layer ));
	layer_add_child( window_layer, bitmap_layer_get_layer( top_right_layer ));
	
	/////// UI BOTTOM ////////////
	bottom_bar_image = gbitmap_create_with_resource( RESOURCE_ID_UI_BOTTOM );

	#if defined(PBL_ROUND)
  		bottom_bar_layer = bitmap_layer_create( GRect( window_center_x-36, window_bounds.size.h-11, 
												  72, 11) );
	#else
		bottom_bar_layer = bitmap_layer_create( GRect( window_center_x-72, window_bounds.size.h-11, 
												  144, 11) );
	#endif
	
	bitmap_layer_set_bitmap( bottom_bar_layer, bottom_bar_image);
	layer_add_child( window_layer, bitmap_layer_get_layer( bottom_bar_layer ));

	
	/////// BIG IMAGE ////////////
	big_image_layer = layer_create(GRect( window_center_x-58, 
										  20+STATUS_BAR_LAYER_HEIGHT,
										  116, 116));
	layer_set_update_proc( big_image_layer, big_layer_update_proc );
	layer_set_hidden( big_image_layer, true);
	layer_add_child( window_layer, big_image_layer);
	
	/////// MODE LAYER ////////////
	#if defined(PBL_ROUND)
		mode_layer = layer_create(GRect( window_center_x-23, 
									 window_bounds.size.h-9, 
									  46, 3));
	#else
		mode_layer = layer_create(GRect( window_center_x-43, 
									 window_bounds.size.h-9, 
									  86, 3));
	#endif
	
	layer_set_update_proc( mode_layer, mode_layer_update_proc );
	layer_add_child( window_layer, mode_layer);
	
	
	
		
	#ifdef PBL_COLOR
		bitmap_layer_set_background_color( top_left_layer, GColorClear);
		bitmap_layer_set_background_color( top_right_layer, GColorClear);
		bitmap_layer_set_background_color( bottom_bar_layer, GColorClear);
		bitmap_layer_set_background_color( poke_image_layer, GColorClear);
		text_layer_set_background_color( text_layer, GColorClear);
	
  		bitmap_layer_set_compositing_mode( top_left_layer, GCompOpSet );
  		bitmap_layer_set_compositing_mode( top_right_layer, GCompOpSet );
  		bitmap_layer_set_compositing_mode( poke_image_layer, GCompOpSet );
  		bitmap_layer_set_compositing_mode( bottom_bar_layer, GCompOpSet );
	#endif
}


///////////////////////// DE INIT /////////////////////

void pokedex_deinit(void) {
	window_destroy( window );
	status_bar_layer_destroy( s_status_bar);
		
	text_layer_destroy( text_layer );
		
	gbitmap_destroy( poke_image );
		
	bitmap_layer_destroy( poke_image_layer );
	layer_destroy( big_image_layer);
		
	gbitmap_destroy( top_left_image );
	bitmap_layer_destroy( top_left_layer );
	gbitmap_destroy( top_right_image );
	bitmap_layer_destroy( top_right_layer );
	gbitmap_destroy( bottom_bar_image );
	bitmap_layer_destroy( bottom_bar_layer );
	
	layer_destroy( mode_layer);

	fonts_unload_custom_font( custom_font );
}










