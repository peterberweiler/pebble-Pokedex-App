module.exports = [
  {
    "type": "heading",
    "defaultValue": "Pokedex Configuration"
  },
  {
    "type": "section",
    "items": [
		/*Language*/
      	{
	  "type": "select",
	  "messageKey": "Language",
	  "defaultValue": "en",
	  "label": "Language",
	  "options": [
		{ 
		  "label": "English", 
		  "value": "en" 
		},
		{ 
		  "label": "Deutsch",
		  "value": "de" 
		},
		{ 
		  "label": "Francais",
		  "value": "fr" 
		}
	  ]
	}
	
    ]
  },
	
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Units"
      },
		/*HeightUnit*/
	{
	  "type": "select",
	  "messageKey": "HeightUnit",
	  "defaultValue": "ft",
	  "label": "Height Unit",
	  "options": [
		{ 
		  "label": "Foot", 
		  "value": "ft" 
		},
		{ 
		  "label": "Meter",
		  "value": "m" 
		}
	  ]
	},
		/*WeightUnit*/
	{
	  "type": "select",
	  "messageKey": "WeightUnit",
	  "defaultValue": "lbs",
	  "label": "Weight Unit",
	  "options": [
		{ 
		  "label": "Pounds", 
		  "value": "lbs" 
		},
		{ 
		  "label": "Gram",
		  "value": "g" 
		}
	  ]
	}	
    ]
  },
	/*Credits*/
		{
    "type": "section",
    "items": [
		
      	{
"type": "text",
"defaultValue": "<center>"+
"Created by <a href=\"http://www.peter-berweiler.de/pebble.html\">www.peter-berweiler.de</a>"+
"<br><br>"+
"<a href=\"mailto:support@peter-berweiler.de\">support@peter-berweiler.de</a>"+
"</center>"
	}	
    ]
  },
	/*Submit*/
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];