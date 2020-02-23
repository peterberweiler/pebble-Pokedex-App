/*
	This File Contains all the Pokemon Information
	Kanto Pokedex
	001     ...		151		+	?
	Bulbasaur		Mew	 		MissingNo

*/

#pragma once

#include "constants.h"
	
#define NUM_POKEMON 152

#define T_NONE     0
#define T_BUG      1
#define T_DRAGON   2
#define T_ELECTRIC 3
#define T_FIGHTING 4
#define T_FIRE     5
#define T_FLYING   6
#define T_GHOST    7
#define T_GRASS    8
#define T_GROUND   9
#define T_ICE     10
#define T_NORMAL  11
#define T_POISON  12
#define T_PSYCHIC 13
#define T_ROCK    14
#define T_STEEL   15
#define T_WATER   16
#define NUM_TYPES 17

static const char * type_names [NUM_LANGUAGES] [NUM_TYPES] = {
{"",     "Bug", "Dragon",  "Electric", "Fighting",  "Fire", "Flying",   "Ghost",   "Grass", "Ground",   "Ice", "Normal", "Poison", "Psychic",    "Rock", "Steel",  "Water" }, //English 
{"",   "Käfer", "Drache",   "Elektro",    "Kampf", "Feuer",   "Flug",   "Geist", "Pflanze",  "Boden",   "Eis", "Normal",   "Gift",  "Psycho", "Gestein", "Stahl", "Wasser" }, //German
{"", "Insecte", "Dragon","Électrique",   "Combat",   "Feu",    "Vol", "Spectre",  "Plante",    "Sol", "Glace", "Normal", "Poison",     "Psy",   "Roche", "Acier",    "Eau" } //French
};

static const char * unit_names [NUM_HEIGHT_UNIT + NUM_WEIGHT_UNIT] = {
" m", "\"", " lbs", " kg"};


static const char * poke_names [NUM_LANGUAGES] [NUM_POKEMON] = {{
"Bulbasaur",
"Ivysaur",
"Venusaur",
"Charmander",
"Charmeleon",
"Charizard",
"Squirtle",
"Wartortle",
"Blastoise",
"Caterpie",
"Metapod",
"Butterfree",
"Weedle",
"Kakuna",
"Beedrill",
"Pidgey",
"Pidgeotto",
"Pidgeot",
"Rattata",
"Raticate",
"Spearow",
"Fearow",
"Ekans",
"Arbok",
"Pikachu",
"Raichu",
"Sandshrew",
"Sandslash",
"Nidoran f",
"Nidorina",
"Nidoqueen",
"Nidoran m",
"Nidorino",
"Nidoking",
"Clefairy",
"Clefable",
"Vulpix",
"Ninetales",
"Jigglypuff",
"Wigglytuff",
"Zubat",
"Golbat",
"Oddish",
"Gloom",
"Vileplume",
"Paras",
"Parasect",
"Venonat",
"Venomoth",
"Diglett",
"Dugtrio",
"Meowth",
"Persian",
"Psyduck",
"Golduck",
"Mankey",
"Primeape",
"Growlithe",
"Arcanine",
"Poliwag",
"Poliwhirl",
"Poliwrath",
"Abra",
"Kadabra",
"Alakazam",
"Machop",
"Machoke",
"Machamp",
"Bellsprout",
"Weepinbell",
"Victreebel",
"Tentacool",
"Tentacruel",
"Geodude",
"Graveler",
"Golem",
"Ponyta",
"Rapidash",
"Slowpoke",
"Slowbro",
"Magnemite",
"Magneton",
"Farfetch'd",
"Doduo",
"Dodrio",
"Seel",
"Dewgong",
"Grimer",
"Muk",
"Shellder",
"Cloyster",
"Gastly",
"Haunter",
"Gengar",
"Onix",
"Drowzee",
"Hypno",
"Krabby",
"Kingler",
"Voltorb",
"Electrode",
"Exeggcute",
"Exeggutor",
"Cubone",
"Marowak",
"Hitmonlee",
"Hitmonchan",
"Lickitung",
"Koffing",
"Weezing",
"Rhyhorn",
"Rhydon",
"Chansey",
"Tangela",
"Kangaskhan",
"Horsea",
"Seadra",
"Goldeen",
"Seaking",
"Staryu",
"Starmie",
"Mr. Mime",
"Scyther",
"Jynx",
"Electabuzz",
"Magmar",
"Pinsir",
"Tauros",
"Magikarp",
"Gyarados",
"Lapras",
"Ditto",
"Eevee",
"Vaporeon",
"Jolteon",
"Flareon",
"Porygon",
"Omanyte",
"Omastar",
"Kabuto",
"Kabutops",
"Aerodactyl",
"Snorlax",
"Articuno",
"Zapdos",
"Moltres",
"Dratini",
"Dragonair",
"Dragonite",
"Mewtwo",
"Mew",
"MissingNo"
},
{
"Bisasam",
"Bisaknosp",
"Bisaflor",
"Glumanda",
"Glutexo",
"Glurak",
"Schiggy",
"Schillok",
"Turtok",
"Raupy",
"Safcon",
"Smettbo",
"Hornliu",
"Kokuna",
"Bibor",
"Taubsi",
"Tauboga",
"Tauboss",
"Rattfratz",
"Rattikarl",
"Habitak",
"Ibitak",
"Rettan",
"Arbok",
"Pikachu",
"Raichu",
"Sandan",
"Sandamer",
"Nidoran w",
"Nidorina",
"Nidoqueen",
"Nidoran m",
"Nidorino",
"Nidoking",
"Piepi",
"Pixi",
"Vulpix",
"Vulnona",
"Pummeluff",
"Knuddeluff",
"Zubat",
"Golbat",
"Myrapla",
"Duflor",
"Giflor",
"Paras",
"Parasek",
"Bluzuk",
"Omot",
"Digda",
"Digdri",
"Mauzi",
"Snobilikat",
"Enton",
"Entoron",
"Menki",
"Rasaff",
"Fukano",
"Arkani",
"Quapsel",
"Quaputzi",
"Quappo",
"Abra",
"Kadabra",
"Simsala",
"Machollo",
"Maschock",
"Machomei",
"Knofensa",
"Ultrigaria",
"Sarzenia",
"Tentacha",
"Tentoxa",
"Kleinstein",
"Georok",
"Geowaz",
"Ponita",
"Gallopa",
"Flegmon",
"Lahmus",
"Magnetilo",
"Magneton",
"Porenta",
"Dodu",
"Dodri",
"Jurob",
"Jugong",
"Sleima",
"Sleimok",
"Muschas",
"Austos",
"Nebulak",
"Alpollo",
"Gengar",
"Onix",
"Traumato",
"Hypno",
"Krabby",
"Kingler",
"Voltobal",
"Lektrobal",
"Owei",
"Kokowei",
"Tragosso",
"Knogga",
"Kicklee",
"Nockchan",
"Schlurp",
"Smogon",
"Smogmog",
"Rihorn",
"Rizeros",
"Chaneira",
"Tangela",
"Kangama",
"Seeper",
"Seemon",
"Goldini",
"Golking",
"Sterndu",
"Starmie",
"Pantimos",
"Sichlor",
"Rossana",
"Elektek",
"Magmar",
"Pinsir",
"Tauros",
"Karpador",
"Garados",
"Lapras",
"Ditto",
"Evoli",
"Aquana",
"Blitza",
"Flamara",
"Porygon",
"Amonitas",
"Amoroso",
"Kabuto",
"Kabutops",
"Aerodactyl",
"Relaxo",
"Arktos",
"Zapdos",
"Lavados",
"Dratini",
"Dragonir",
"Dragoran",
"Mewtu",
"Mew",
"MissingNo"
},
{
"Bulbizarre",
"Herbizarre",
"Florizarre",
"Salamèche",
"Reptincel",
"Dracaufeu",
"Carapuce",
"Carabaffe",
"Tortank",
"Chenipan",
"Chrysacier",
"Papilusion",
"Aspicot",
"Coconfort",
"Dardagnan",
"Roucool",
"Roucoups",
"Roucarnage",
"Rattata",
"Rattatac",
"Piafabec",
"Rapasdepic",
"Abo",
"Arbok",
"Pikachu",
"Raichu",
"Sabelette",
"Sablaireau",
"Nidoran f",
"Nidorina",
"Nidoqueen",
"Nidoran m",
"Nidorino",
"Nidoking",
"Mélofée",
"Mélodelfe",
"Goupix",
"Feunard",
"Rondoudou",
"Grodoudou",
"Nosferapti",
"Nosferalto",
"Mystherbe",
"Ortide",
"Rafflesia",
"Paras",
"Parasect",
"Mimitoss",
"Aéromite",
"Taupiqueur",
"Triopikeur",
"Miaouss",
"Persian",
"Psykokwak",
"Akwakwak",
"Férosinge",
"Colossinge",
"Caninos",
"Arcanin",
"Ptitard",
"Têtarte",
"Tartard",
"Abra",
"Kadabra",
"Alakazam",
"Machoc",
"Machopeur",
"Mackogneur",
"Chétiflor",
"Boustiflor",
"Empiflor",
"Tentacool",
"Tentacruel",
"Racaillou",
"Gravalanch",
"Grolem",
"Ponyta",
"Galopa",
"Ramoloss",
"Flagadoss",
"Magnéti",
"Magnéton",
"Canarticho",
"Doduo",
"Dodrio",
"Otaria",
"Lamantine",
"Tadmorv",
"Grotadmorv",
"Kokiyas",
"Crustabri",
"Fantominus",
"Spectrum",
"Ectoplasma",
"Onix",
"Soporifik",
"Hypnomade",
"Krabby",
"Krabboss",
"Voltorbe",
"Électrode",
"Noeunoeuf",
"Noadkoko",
"Osselait",
"Ossatueur",
"Kicklee",
"Tygnon",
"Excelangue",
"Smogo",
"Smogogo",
"Rhinocorne",
"Rhinoféros",
"Leveinard",
"Saquedeneu",
"Kangourex",
"Hypotrempe",
"Hypocéan",
"Poissirène",
"Poissoroy",
"Stari",
"Staross",
"M. Mime",
"Insécateur",
"Lippoutou",
"Élektek",
"Magmar",
"Scarabrute",
"Tauros",
"Magicarpe",
"Léviator",
"Lokhlass",
"Métamorph",
"Évoli",
"Aquali",
"Voltali",
"Pyroli",
"Porygon",
"Amonita",
"Amonistar",
"Kabuto",
"Kabutops",
"Ptéra",
"Ronflex",
"Artikodin",
"Électhor",
"Sulfura",
"Minidraco",
"Draco",
"Dracolosse",
"Mewtwo",
"Mew",
"MissingNo"
}
};



static const char * poke_info_data[NUM_HEIGHT_UNIT + NUM_WEIGHT_UNIT][NUM_POKEMON] = {
{ //Meter
"0.7","1.0","2.0","0.6","1.1","1.7","0.5","1.0","1.6","0.3","0.7","1.1","0.3","0.6","1.0",
"0.3","1.1","1.5","0.3","0.7","0.3","1.2","2.0","3.5","0.4","0.8","0.6","1.0","0.4","0.8",
"1.3","0.5","0.9","1.4","0.6","1.3","0.6","1.1","0.5","1.0","0.8","1.6","0.5","0.8","1.2",
"0.3","1.0","1.0","1.5","0.2","0.7","0.4","1.0","0.8","1.7","0.5","1.0","0.7","1.9","0.6",
"1.0","1.3","0.9","1.3","1.5","0.8","1.5","1.6","0.7","1.0","1.7","0.9","1.6","0.4","1.0",
"1.4","1.0","1.7","1.2","1.6","0.3","1.0","0.8","1.4","1.8","1.1","1.7","0.9","1.2","0.3",
"1.5","1.3","1.6","1.5","8.8","1.0","1.6","0.4","1.3","0.5","1.2","0.4","2.0","0.4","1.0",
"1.5","1.4","1.2","0.6","1.2","1.0","1.9","1.1","1.0","2.2","0.4","1.2","0.6","1.3","0.8",
"1.1","1.3","1.5","1.4","1.1","1.3","1.5","1.4","0.9","6.5","2.5","0.3","0.3","1.0","0.8",
"0.9","0.8","0.4","1.0","0.5","1.3","1.8","2.1","1.7","1.6","2.0","1.8","4.0","2.2","2.0",
"0.4","???" },
{ //Foot
"2'04","3'03","6'07","2'00","3'07","5'07","1'08","3'03","5'03","1'00",
"2'04","3'07","1'00","2'00","3'03","1'00","3'07","4'11","1'00","2'04",
"1'00","3'11","6'07","11'06","1'04","2'07","2'00","3'03","1'04","2'07",
"4'03","1'08","2'11","4'07","2'00","4'03","2'00","3'07","1'08","3'03",
"2'07","5'03","1'08","2'07","3'11","1'00","3'03","3'03","4'11","0'08",
"2'04","1'04","3'03","2'07","5'07","1'08","3'03","2'04","6'03","2'00",
"3'03","4'03","2'11","4'03","4'11","2'07","4'11","5'03","2'04","3'03",
"5'07","2'11","5'03","1'04","3'03","4'07","3'03","5'07","3'11","5'03",
"1'00","3'03","2'07","4'07","5'11","3'07","5'07","2'11","3'11","1'00",
"4'11","4'03","5'03","4'11","28'10","3'03","5'03","1'04","4'03","1'08",
"3'11","1'04","6'07","1'04","3'03","4'11","4'07","3'11","2'00","3'11",
"3'03","6'03","3'07","3'03","7'03","1'04","3'11","2'00","4'03","2'07",
"3'07","4'03","4'11","4'07","3'07","4'03","4'11","4'07","2'11","21'04",
"8'02","1'00","1'00","3'03","2'07","2'11","2'07","1'04","3'03","1'08",
"4'03","5'11","6'11","5'07","5'03","6'07","5'11","13'01","7'03","6'07",
"1'04","???" },
{ //Pounds
"15.2","28.7","220.5","18.7","41.9","199.5","19.8","49.6","188.5","6.4","21.8","70.5","7.1",
"22.0","65.0","4.0","66.1","87.1","7.7","40.8","4.4","83.8","15.2","143.3","13.2","66.1",
"26.5","65.0","15.4","44.1","132.3","19.8","43.0","136.7","16.5","88.2","21.8","43.9","12.1",
"26.5","16.5","121.3","11.9","19.0","41.0","11.9","65.0","66.1","27.6","1.8","73.4","9.3",
"70.5","43.2","168.9","61.7","70.5","41.9","341.7","27.3","44.1","119.0","43.0","124.6",
"105.8","43.0","155.4","286.6","8.8","14.1","34.2","100.3","121.3","44.1","231.5","661.4",
"66.1","209.4","79.4","173.1","13.2","132.3","33.1","86.4","187.8","198.4","264.6","66.1",
"66.1","8.8","292.1","0.2","0.2","89.3","463.0","71.4","166.7","14.3","132.3","22.9","146.8",
"5.5","264.6","14.3","99.2","109.8","110.7","144.4","2.2","20.9","253.5","264.6","76.3","77.2",
"176.4","17.6","55.1","33.1","86.0","76.1","176.4","120.2","123.5","89.5","66.1","98.1",
"121.3","194.9","22.0","518.1","485.0","8.8","14.3","63.9","54.0","55.1","80.5","16.5","77.2",
"25.4","89.3","130.1","1014.1","122.1","116.0","132.3","7.3","36.4","463.0","269.0","8.8",
"???" },
{ //Gram 
"6.9","13.0","100.0","8.5","19.0","90.5","9.0","22.5","85.5","2.9","9.9","32.0","3.2","10.0",
"29.5","1.8","30.0","39.5","3.5","18.5","2.0","38.0","6.9","65.0","6.0","30.0","12.0","29.5",
"7.0","20.0","60.0","9.0","19.5","62.0","7.5","40.0","9.9","19.9","5.5","12.0","7.5","55.0",
"5.4","8.6","18.6","5.4","29.5","30.0","12.5","0.8","33.3","4.2","32.0","19.6","76.6","28.0",
"32.0","19.0","155.0","12.4","20.0","54.0","19.5","56.5","48.0","19.5","70.5","130.0","4.0",
"6.4","15.5","45.5","55.0","20.0","105.0","300.0","30.0","95.0","36.0","78.5","6.0","60.0",
"15.0","39.2","85.2","90.0","120.0","30.0","30.0","4.0","132.5","0.1","0.1","40.5","210.0",
"32.4","75.6","6.5","60.0","10.4","66.6","2.5","120.0","6.5","45.0","49.8","50.2","65.5",
"1.0","9.5","115.0","120.0","34.6","35.0","80.0","8.0","25.0","15.0","39.0","34.5","80.0",
"54.5","56.0","40.6","30.0","44.5","55.0","88.4","10.0","235.0","220.0","4.0","6.5","29.0",
"24.5","25.0","36.5","7.5","35.0","11.5","40.5","59.0","460.0","55.4","52.6","60.0","3.3",
"16.5","210.0","122.0","4.0","???" }
};

static const uint8_t poke_info_type[NUM_POKEMON*2] = {
8,12,8,12,8,12,5,0,5,0,5,6,16,0,16,0,16,0,1,0,1,0,1,6,1,12,1,12,1,12,11,6,11,6,11,6,
11,0,11,0,11,6,11,6,12,0,12,0,3,0,3,0,9,0,9,0,12,0,12,0,12,9,12,0,12,0,12,9,11,0,
11,0,5,0,5,0,11,0,11,0,12,6,12,6,8,12,8,12,8,12,1,8,1,8,1,12,1,12,9,0,9,0,11,0,11,0,
16,0,16,0,4,0,4,0,5,0,5,0,16,0,16,0,16,4,13,0,13,0,13,0,4,0,4,0,4,0,8,12,8,12,8,12,
16,12,16,12,14,9,14,9,14,9,5,0,5,0,16,13,16,13,3,15,3,15,11,6,11,6,11,6,16,0,16,10,
12,0,12,0,16,0,16,10,7,12,7,12,7,12,14,9,13,0,13,0,16,0,16,0,3,0,3,0,8,13,8,13,9,0,
9,0,4,0,4,0,11,0,12,0,12,0,9,14,9,14,11,0,8,0,11,0,16,0,16,0,16,0,16,0,16,0,16,13,
13,0,1,6,10,13,3,0,5,0,1,0,11,0,16,0,16,6,16,10,11,0,11,0,16,0,3,0,5,0,11,0,14,16,
14,16,14,16,14,16,14,6,11,0,10,6,3,6,5,6,2,0,2,0,2,6,13,0,13,0,0,0 };


static const  uint8_t poke_images[] = {
RESOURCE_ID_1,
RESOURCE_ID_2,
RESOURCE_ID_3,
RESOURCE_ID_4,
RESOURCE_ID_5,
RESOURCE_ID_6,
RESOURCE_ID_7,
RESOURCE_ID_8,
RESOURCE_ID_9,
RESOURCE_ID_10,
RESOURCE_ID_11,
RESOURCE_ID_12,
RESOURCE_ID_13,
RESOURCE_ID_14,
RESOURCE_ID_15,
RESOURCE_ID_16,
RESOURCE_ID_17,
RESOURCE_ID_18,
RESOURCE_ID_19,
RESOURCE_ID_20,
RESOURCE_ID_21,
RESOURCE_ID_22,
RESOURCE_ID_23,
RESOURCE_ID_24,
RESOURCE_ID_25,
RESOURCE_ID_26,
RESOURCE_ID_27,
RESOURCE_ID_28,
RESOURCE_ID_29,
RESOURCE_ID_30,
RESOURCE_ID_31,
RESOURCE_ID_32,
RESOURCE_ID_33,
RESOURCE_ID_34,
RESOURCE_ID_35,
RESOURCE_ID_36,
RESOURCE_ID_37,
RESOURCE_ID_38,
RESOURCE_ID_39,
RESOURCE_ID_40,
RESOURCE_ID_41,
RESOURCE_ID_42,
RESOURCE_ID_43,
RESOURCE_ID_44,
RESOURCE_ID_45,
RESOURCE_ID_46,
RESOURCE_ID_47,
RESOURCE_ID_48,
RESOURCE_ID_49,
RESOURCE_ID_50,
RESOURCE_ID_51,
RESOURCE_ID_52,
RESOURCE_ID_53,
RESOURCE_ID_54,
RESOURCE_ID_55,
RESOURCE_ID_56,
RESOURCE_ID_57,
RESOURCE_ID_58,
RESOURCE_ID_59,
RESOURCE_ID_60,
RESOURCE_ID_61,
RESOURCE_ID_62,
RESOURCE_ID_63,
RESOURCE_ID_64,
RESOURCE_ID_65,
RESOURCE_ID_66,
RESOURCE_ID_67,
RESOURCE_ID_68,
RESOURCE_ID_69,
RESOURCE_ID_70,
RESOURCE_ID_71,
RESOURCE_ID_72,
RESOURCE_ID_73,
RESOURCE_ID_74,
RESOURCE_ID_75,
RESOURCE_ID_76,
RESOURCE_ID_77,
RESOURCE_ID_78,
RESOURCE_ID_79,
RESOURCE_ID_80,
RESOURCE_ID_81,
RESOURCE_ID_82,
RESOURCE_ID_83,
RESOURCE_ID_84,
RESOURCE_ID_85,
RESOURCE_ID_86,
RESOURCE_ID_87,
RESOURCE_ID_88,
RESOURCE_ID_89,
RESOURCE_ID_90,
RESOURCE_ID_91,
RESOURCE_ID_92,
RESOURCE_ID_93,
RESOURCE_ID_94,
RESOURCE_ID_95,
RESOURCE_ID_96,
RESOURCE_ID_97,
RESOURCE_ID_98,
RESOURCE_ID_99,
RESOURCE_ID_100,
RESOURCE_ID_101,
RESOURCE_ID_102,
RESOURCE_ID_103,
RESOURCE_ID_104,
RESOURCE_ID_105,
RESOURCE_ID_106,
RESOURCE_ID_107,
RESOURCE_ID_108,
RESOURCE_ID_109,
RESOURCE_ID_110,
RESOURCE_ID_111,
RESOURCE_ID_112,
RESOURCE_ID_113,
RESOURCE_ID_114,
RESOURCE_ID_115,
RESOURCE_ID_116,
RESOURCE_ID_117,
RESOURCE_ID_118,
RESOURCE_ID_119,
RESOURCE_ID_120,
RESOURCE_ID_121,
RESOURCE_ID_122,
RESOURCE_ID_123,
RESOURCE_ID_124,
RESOURCE_ID_125,
RESOURCE_ID_126,
RESOURCE_ID_127,
RESOURCE_ID_128,
RESOURCE_ID_129,
RESOURCE_ID_130,
RESOURCE_ID_131,
RESOURCE_ID_132,
RESOURCE_ID_133,
RESOURCE_ID_134,
RESOURCE_ID_135,
RESOURCE_ID_136,
RESOURCE_ID_137,
RESOURCE_ID_138,
RESOURCE_ID_139,
RESOURCE_ID_140,
RESOURCE_ID_141,
RESOURCE_ID_142,
RESOURCE_ID_143,
RESOURCE_ID_144,
RESOURCE_ID_145,
RESOURCE_ID_146,
RESOURCE_ID_147,
RESOURCE_ID_148,
RESOURCE_ID_149,
RESOURCE_ID_150,
RESOURCE_ID_151,
RESOURCE_ID_152
};


