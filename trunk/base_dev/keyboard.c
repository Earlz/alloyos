#include <x86.h>
#include <stdlib.h>
#include <kdebug.h>
#include <base_dev/keyboard.h>
#include <idt.h>

uint8_t kbdus[128] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
 '9', '0', '-', '=', '\b', /* Backspace */
 '\t',   /* Tab */
 'q', 'w', 'e', 'r', /* 19 */
 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
 0,   /* 29   - Control */
 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,  /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',   /* 49 */
 'm', ',', '.', '/',   0,    /* Right shift */
 '*',
 0, /* Alt */
 ' ', /* Space bar */
 0, /* Caps lock */
 0, /* 59 - F1 key ... > */
 0,   0,   0,   0,   0,   0,   0,   0,
 0, /* < ... F10 */
 0, /* 69 - Num lock*/
 0, /* Scroll Lock */
 0, /* Home key */
 0, /* Up Arrow */
 0, /* Page Up */
 '-',
 0, /* Left Arrow */
 0,
 0, /* Right Arrow */
 '+',
 0, /* 79 - End key*/
 0, /* Down Arrow */
 0, /* Page Down */
 0, /* Insert Key */
 0, /* Delete Key */
 0,   0,   0,
 0, /* F11 Key */
 0, /* F12 Key */
 0, /* All other keys are undefined */
};

uint8_t kbdus_caps[128] =
{
	0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
 '(', ')', '_', '+', '\b', /* Backspace */
 '\t',   /* Tab */
 'Q', 'W', 'E', 'R', /* 19 */
 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
 0,   /* 29   - Control */
 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
 '"', '~',   0,  /* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',   /* 49 */
 'M', '<', '>', '?',   0,    /* Right shift */
 '*',
 0, /* Alt */
 ' ', /* Space bar */
 0, /* Caps lock */
 0, /* 59 - F1 key ... > */
 0,   0,   0,   0,   0,   0,   0,   0,
 0, /* < ... F10 */
 0, /* 69 - Num lock*/
 0, /* Scroll Lock */
 0, /* Home key */
 0, /* Up Arrow */
 0, /* Page Up */
 '-',
 0, /* Left Arrow */
 0,
 0, /* Right Arrow */
 '+',
 0, /* 79 - End key*/
 0, /* Down Arrow */
 0, /* Page Down */
 0, /* Insert Key */
 0, /* Delete Key */
 0,   0,   0,
 0, /* F11 Key */
 0, /* F12 Key */
 0, /* All other keys are undefined */
};

volatile shift_locks kbd_shifts;


inline uint8_t kbd_GetScanCode(){
	return inportb(0x60);
}

volatile kbd_key *keys;
volatile uint16_t current_key=0;

int kbd_Init(){
	keys=malloc(KBD_BUFFER_SIZE*sizeof(kbd_key));
	kbd_shifts.shift=0;
	kbd_shifts.caps=0;
	kbd_shifts.num=0;
	kbd_shifts.scroll=0;
	kbd_shifts.ctrl=0;
	kbd_shifts.alt=0;
	return InstallInterruptHook(IRQ_BASE_INT+1,&kbd_Irq1Handler);
	return 0;
}




int kbd_PutBuffer(uint16_t scan,uint8_t asci){
	stopints();
	if(current_key>=KBD_BUFFER_SIZE){
		return -1;
	}
	keys[current_key].scancode=scan;
	keys[current_key].asci=asci;
	current_key++;
	startints();
	return 0;
}

kbd_key kbd_PopBuffer(){
	kbd_key k;
	while(current_key==0){
	//fill in busy code here	
	}
	stopints();
	current_key--;
	k.scancode=keys[current_key].scancode;
	k.asci=keys[current_key].asci;
	startints();
	return k;
}

uint8_t kbd_GetKey(){ //this will just return the asci code
	kbd_key k;
	k.asci=0;
	while(k.asci==0){
		k=kbd_PopBuffer();
	}
	return k.asci;
}

 
int kbd_DoShifts(uint8_t scan){
	switch(scan){
		case RSHIFT_KEY:
			kbd_shifts.shift++;
			break;
		case LSHIFT_KEY:
			kbd_shifts.shift++;
			break;
		case CTRL_KEY:
			kbd_shifts.ctrl++;
			break;
		case ALT_KEY:
			kbd_shifts.alt++;
			break;
		case CAPS_KEY:
			kbd_shifts.caps^=1;
			break;
		case NUM_KEY:
			kbd_shifts.num^=1;
			break;
		case SCROLL_KEY:
			kbd_shifts.scroll^=1;
			break;
		default:
			return 0;
			break;
	}
	return 1;
}

int kbd_DoUnshifts(uint8_t scan){
	switch(scan){
		case RSHIFT_KEY:
			kbd_shifts.shift--;
			break;
		case LSHIFT_KEY:
			kbd_shifts.shift--;
			break;
		case CTRL_KEY:
			kbd_shifts.ctrl--;
			break;
		case ALT_KEY:
			kbd_shifts.alt--;
			break;
		case CAPS_KEY:
			//kbd_shifts.caps=0;
			break;
		case NUM_KEY:
			//kbd_shifts.num=0;
			break;
		case SCROLL_KEY:
			//kbd_shifts.scroll=0;
			break;
		default:
			return 0;
			break;
	}
	return 1;
}


void kbd_Irq1Handler(struct InterruptInfo *r){
	uint8_t tmp;
	tmp=kbd_GetScanCode();
	if(tmp>=0x80){ 
		//tmp=kbd_GetScanCode();
		tmp^=0x80;
		kbd_DoUnshifts(tmp);
	}else{
		if(kbd_DoShifts(tmp)==0){ //if not a shift-type key
			
			if ((kbd_shifts.caps^kbd_shifts.shift)==1) {
				kd_putc_xy(kbdus_caps[tmp],11,12);
				kbd_PutBuffer(tmp,kbdus_caps[tmp]);
			}else{
				kd_putc_xy(kbdus[tmp],10,12);
				kbd_PutBuffer(tmp,kbdus[tmp]);
			}
		}
	}
	
	
	
	
	
}







