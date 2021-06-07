#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override 
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations 
#define SET_INDICATORS(hsv) \
		{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
     {35+0, 1, hsv} 
#define SET_UNDERGLOW(hsv) \
		{1, 5, hsv}, \
     {35+1, 5,hsv} 		  
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	{35+22, 3, hsv},\
	{35+27, 3, hsv}
#define SET_NUMROW(hsv) \
		{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	{35+ 10, 2, hsv}, \
	{35+ 20, 2, hsv}, \
	{35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
		{33, 4, hsv}, \
	{35+ 33, 4, hsv}	

#define SET_OUTER_COL(hsv) \
		{7, 4, hsv}, \
	{35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
		{25, 2, hsv}, \
	{35+ 25, 2, hsv}		
#define SET_LAYER_ID(hsv) 	\
		{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
     {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 5, hsv}, \
     {35+1, 5, hsv}, \
		{7, 4, hsv}, \
	{35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	{35+ 25, 2, hsv}	

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow 
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_RED)
  
);
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PINK)
);

// _NUM,
// Light on outer column and underglow 
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_TEAL)
 
);
// _SYMBOL,
// Light on inner column and underglow 
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_BLUE)
    
    );
// _COMMAND,
// Light on inner column and underglow 
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PURPLE)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_INDICATORS(HSV_ORANGE),
    SET_UNDERGLOW(HSV_ORANGE),
	SET_NUMPAD(HSV_BLUE),
    {7, 4, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {35+6, 4, HSV_ORANGE},
    {35+25, 2, HSV_ORANGE}
    );
// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS( 
	SET_LAYER_ID(HSV_GREEN), 
	SET_NUMROW(HSV_GREEN)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_qwerty_lights, 
	layer_num_lights,// overrides layer 1
	layer_symbol_lights,
    layer_command_lights,       
	layer_numpad_lights, 
	layer_switcher_lights,  // Overrides other layers
	layer_colemakdh_lights
);

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
	rgblight_set_layer_state(7, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_COLEMAKDH));

    
	rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
	rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
	rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
	rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
	rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
	
	rgblight_mode(10);// haven't found a way to set this in a more useful way 

}
#endif