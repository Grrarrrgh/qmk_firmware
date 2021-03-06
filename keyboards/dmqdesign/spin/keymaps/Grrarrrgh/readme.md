# Keymap for Spin by DMQ Design - work in progress

* Keypad layout rotated to a vertical position (encoders at top, OLED at bottom)
* Layer selection is via the third encoder and is looped
* OLED displays layer name and RGB mode  
<br />

## Layout


### Numberpad.
* Encoders (CW, !CW, Press):
* 1 - VolUp, VolDn, Mute
* 2 - ScrollUp, ScrollDn, Reset
* 3 - Next layer, Previous layer, Photoshop layer  
![img](https://raw.githubusercontent.com/Grrarrrgh/qmk_firmware/dmqspindev/keyboards/dmqdesign/spin/keymaps/Grrarrrgh/spin_numpad.jpg)

### RGB  
![img](https://raw.githubusercontent.com/Grrarrrgh/qmk_firmware/dmqspindev/keyboards/dmqdesign/spin/keymaps/Grrarrrgh/spin_rgb.jpg)
<br />

### F keys  
![img](https://raw.githubusercontent.com/Grrarrrgh/qmk_firmware/dmqspindev/keyboards/dmqdesign/spin/keymaps/Grrarrrgh/spin_fnum.jpeg)
<br />

### Photoshop
* User specific Photoshop keys (customised keybinds included below) 
* Encoders (CW, !CW, Press):
* 1 - ], [, Escape
* 2 - Opacity/Fill/Flow (with Shift modifier) +3%, -3%, Next Document (CTRL+TAB)
* 3 - Next layer, Previous layer, Numberpad layer
* Note that the opacity/fill/flow functionality cannot read the current value from Photoshop, instead a value of 60% is chosen as the start point (when the keypad is connected)and for each detent turn cw that value is increased by 3, rememberred, and sent as a keypress. Turning anti-cw  reduces the value by 3 and sends as a keypress. ie on first use it will **always** set the opacity/fill/flow to 60% and increase/decrease form there.  
![img](https://raw.githubusercontent.com/Grrarrrgh/qmk_firmware/dmqspindev/keyboards/dmqdesign/spin/keymaps/Grrarrrgh/spin_ps.jpg)
<br />

### Arrows (aiming to merge these into another layer).  
![img](https://raw.githubusercontent.com/Grrarrrgh/qmk_firmware/dmqspindev/keyboards/dmqdesign/spin/keymaps/Grrarrrgh/spin_arrow.jpg)  
<br />

### Destiny 2
* Macros for lazy Guardians (not implimented yet becasue timed macros and burnout).  Encoders as numberpad.  
<br />
<br />
<br />

# Photoshop keybinds

KEY	|	TOOLS				|	CTRL			|	CTRL SHFT			|	CTRL ALT				|	CTRL ALT SHIFT	|	ALT SHIFT/MODE
---	|	------------------	|	--------------	|	------------------	|	---------------------	|	--------------	|	--------------
A 	|	Quick mask			|	Select all		|	Show/Hide 			|							|	High pass		|	
I 	|	Eye dropper			| 	Invert			|	Inverse selection	|	Edit image				|	File info		|
N 	|	Brush				|	New document	|	New layer			|							|					|	Normal
G 	|	Gradient			|	Group			|	Ungroup				|	Link/release clip mask	|					|
X 	|	Switch swatches 	|	Cut				|	Liquify				|	Transform				|	Puppet warp		|
C 	|	Crop				|	Copy			|	Copy visible		|	Canvas size				|	Colour range	|	Colour
V 	|	Move 				|	Paste			|	Paste in place		|	Dupe to new layer		|					|
D 	|	Reset swatches		|	Deselect		|						|							|					|
S	|	Clone, Heal, Spot 	|	Save			|	Save as				|	Smart object			|					|	Screen
E 	|	Dodge, Burn 		|	Merge Down		|	Merge visible		|	Stamp selected 			|	Stamp visible	|	Difference
P 	|	Path 				|	Curves			|	Place linked		|	Place embedded			|					|	Passthrough
K 	|	Smudge, Blur 		|	Selective col	|	Hue/Sat				|							|					|	Darken
L 	|	Lasso, Marquee 		|	Levels 			|						|							|					|	Luminosity
Z 	|	Zoom 				|	Step backward	|	Step forward 		|	Undo/Redo				|					|
TBA	|						|					|						|							|					|	Overlay
TBA	|						|					|						|							|					|	Soft light
