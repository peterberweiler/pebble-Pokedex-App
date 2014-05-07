#pragma once
	
	
#define NUM_LANGUAGES 3 
static const char *language_names [NUM_LANGUAGES] = { "English", "Deutsch", "Francais" };

///#define ls_Games     0
#define ls_Settings  1
static const char *localized_string[NUM_LANGUAGES][2] = {
{"Games",  "Settings"}, 	//English
{"Spiele", "Einstellungen"},//German
{"Jeux",   "Réglages"}  	//French
};

