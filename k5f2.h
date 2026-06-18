/*
 *  _  _____ ___ ___
 * | |/ / __| __|_  )
 * | ' <|__ \ _| / /
 * |_|\_\___/_| /___|
 *
 * k5f2.h - Single-Header Library Collection
 *
 * Usage:
 *   In exactly ONE .c file, before including this header:
 *     #define K5F2_IMPLEMENTATION
 *     #include "k5f2.h"
 *
 *   All other .c files just do:
 *     #include "k5f2.h"
 *
 */

#ifndef K5F2_H
#define K5F2_H

/* ========================================================================== */
/*  System Includes                                                           */
/* ========================================================================== */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <setjmp.h>
#include <signal.h>
#include <malloc.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <ctype.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>
#include <libgen.h>

/* ========================================================================== */
/*  Common Typedefs                                                           */
/* ========================================================================== */

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;
typedef unsigned long  ddword;
typedef unsigned long  doubledoubleword;

/* ========================================================================== *
 *  _    ___ ___ _    ___   ___                                               *
 * | |  |_ _| _ ) |  / _ \ / __|                                             *
 * | |__ | || _ \ |_| (_) | (_ |                                             *
 * |____|___|___/____\___/ \___|                                              *
 *                                                                            *
 * ========================================================================== */

/* Init */
void set_process_name(char *p);

/* Debug */
void set_debug();
void clr_debug();
#define debug_enable set_debug
#define debug_disable clr_debug
int   is_debug();
#define isdebug is_debug
#define toggle_debug is_debug	/* Placeholder */
void debug(char *s,...);
void ldebug(int,char *s,...);
void ddump(char *s,void *v,int n);
#define debug_dump ddump
#define ldebug_dump(a,b,c,d) ddump(b,c,d)

/* Verbose */
void set_verbose();
void clr_verbose();
int   is_verbose();
void verbose(char *s,...);
void vdump(char *s,void *v,int n);

/* Logging */
void notice(char *s,...);
void error(char *s,...);
void warning(char *s,...);
#define severe warning
#define fwarning warning
void pseudofatal(char *s,...);
void fatal(char *s,...);

/* Sys Logging (appends strerror) */
void sysnotice(char *s,...);
void syserror(char *s,...);
void syswarning(char *s,...);
#define syssevere warning
void sysfatal(char *s,...);
void syspseudofatal(char *s,...);

/* Misc */
void logmessage(char *m,char *s,...);
void syntax(char *,...);
void returnfar();
void writeln(char *s,...);
void errorln(char *s,...);
int loglevel(int);
void logsetlevel(int);
void logclrlevel(int);

/* ========================================================================== *
 *  _    ___ ___  ___ _____ _  _ ___ ___                                      *
 * | |  |_ _| _ )/ _ \_   _| || | __| _ \                                    *
 * | |__ | || _ \ (_) || | | __ | _||   /                                     *
 * |____|___|___/\___/ |_| |_||_|___|_|_\                                     *
 *                                                                            *
 * ========================================================================== */

char ebcdic_to_ascii(char);
void dump( char *title, void *x, size_t n );
void edump( char *title, void *x, size_t n );
char *sdump( void *x, size_t n );
char *number(int);
char *hnumber(int);

/* ========================================================================== *
 *  _    ___ ___ ___ ___ ___  _   _ ___ _  _  ___ ___                        *
 * | |  |_ _| _ ) __| __/ _ \| | | | __| \| |/ __| __|                       *
 * | |__ | || _ \__ \ _| (_) | |_| | _|| .` | (__| _|                        *
 * |____|___|___/___/___\__\_\\___/|___|_|\_|\___|___|                        *
 *                                                                            *
 * ========================================================================== */

typedef struct sequence {
	int      value;
	char    *name;
	char    *seq;
	void    (*function)(int);
	} sequence;

int sequence_count();
char *sequence_name(int);
sequence * sequence_get(int);
char * sequence_name_by_value( int );
void sequence_add( int value, char *name, char *seq, void (*f)(int) );
void sequence_print();

/* ========================================================================== *
 *  _    ___ ___ ___ ___ __  __                                               *
 * | |  |_ _| _ ) __/ __|  \/  |                                             *
 * | |__ | || _ \ _|\__ \ |\/| |                                             *
 * |____|___|___/_| |___/_|  |_|                                              *
 *                                                                            *
 * ========================================================================== */

int  fsm_add_sequence( char *p, int action );
void fsm_print();
void fsm_ccode();
void fsm_setcallback( void(*)(char *,int) );
void fsm_action(int c);

/* ========================================================================== *
 *  _    ___ ___ _____ _______   __                                           *
 * | |  |_ _| _ )_   _|_   _\ \ / /                                          *
 * | |__ | || _ \ | |   | |  \ V /                                            *
 * |____|___|___/ |_|   |_|   |_|                                             *
 *                                                                            *
 * ========================================================================== */

/* Init */
void terminal_init(int fd);
void terminal_alternate_screen(int enable);
int  terminal_rows();
int  terminal_cols();
int  twrite(int,void *,int);

/* Exit */
void set_exit_message(char *);

/* Basic */
void autowrap();
void noautowrap();
void bold();
void unbold();
void cls();
void clear_line();
void erase_to_end();
void home();
void reset();
void newline();
void reverse();
void scroll_down();
void scroll_up();
void underline();
void ununderline();

/* Colors */
char * colors_name(int);
int colors_fg(int);
int colors_bg(int);
int set_colors_default_bg(int);
int get_colors_default_bg();
int set_colors_default_fg(int);
int get_colors_default_fg();
int set_colors_bg(int);
int get_colors_bg();
int set_colors_fg(int);
int get_colors_fg();
void reset_colors();
void set_background( char *);
void set_foreground( char *);
int get_bg_from_fg(int c);

/* Cursor */
void restore_cursor();
void save_cursor();
void visible_cursor();
void invisible_cursor();
void move_cursor(int,int);

/* Mouse */
void mouse_events_on();
void mouse_events_off();

/* ========================================================================== *
 *  _    ___ ___ _____   _____ _  _ _____                                     *
 * | |  |_ _| _ ) __\ \ / / __| \| |_   _|                                   *
 * | |__ | || _ \ _| \ V /| _|| .` | | |                                     *
 * |____|___|___/___| \_/ |___|_|\_| |_|                                      *
 *                                                                            *
 * ========================================================================== */

typedef struct event {
	char	type;
	int	index;
	union {
		char	character;
		int	number;
		int	error;
		int	signal;
		int	fd;
	} parameter;
} event;

#define NO_EVENT	0
#define TIME_EVENT	1
#define KEY_EVENT	2
#define SIG_EVENT	3
#define ERR_EVENT	4
#define EOF_EVENT	5
#define TCP_EVENT	6	/* Place Holder */

const char *event_type(int);
void  event_init(int mouse_events);
event * event_wait();
void  event_timer(int,int);
void  event_mouse_on();
void  event_mouse_off();

/* ========================================================================== *
 *  _    ___ ___ _  __                                                        *
 * | |  |_ _| _ ) |/ /                                                       *
 * | |__ | || _ \ ' <                                                         *
 * |____|___|___/_|\_\                                                        *
 *                                                                            *
 * ========================================================================== */

typedef struct key_sequence {
	int	value;
	char	*name;
	char	*seq;
	void	(*function)(void);
} key_sequence;

#define EOT  3
#define  LF 10

typedef	enum {
		DEL = 255,
		UP_ARROW,
		DOWN_ARROW,
		RIGHT_ARROW,
		LEFT_ARROW,
		END_KEY,
		HOME_KEY,
		SHIFT_TAB,

		PAGE_DOWN,
		PAGE_UP,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		INSERT_KEY,
		DO_KEY,
		HELP_KEY,
		FIND_KEY,
		REMOVE_KEY,

		CTRL_UP_ARROW,
		CTRL_DOWN_ARROW,
		CTRL_RIGHT_ARROW,
		CTRL_LEFT_ARROW,
		CTRL_HOME_KEY,
		CTRL_PAGE_DOWN,
		CTRL_PAGE_UP,
		CTRL_F1,
		CTRL_F2,
		CTRL_F3,
		CTRL_F4,
		CTRL_F5,
		CTRL_F6,
		CTRL_F7,
		CTRL_F8,
		CTRL_F9,
		CTRL_F10,
		CTRL_F11,
		CTRL_F12,
		CTRL_F13,
		CTRL_F14,
		CTRL_F15,
		CTRL_F16,
		CTRL_F17,
		CTRL_F18,
		CTRL_F19,
		CTRL_F20,
		CTRL_INSERT_KEY,
		CTRL_END_KEY,
		CTRL_DO_KEY,
		CTRL_HELP_KEY,
		CTRL_FIND_KEY,
		CTRL_REMOVE_KEY,

		SHIFT_F1,
		SHIFT_F2,
		SHIFT_F3,
		SHIFT_F4,
		SHIFT_F5,
		SHIFT_F6,
		SHIFT_F7,
		SHIFT_F8,
		SHIFT_F9,
		SHIFT_F10,
		SHIFT_F11,
		SHIFT_F12,
		SHIFT_F13,
		SHIFT_F14,
		SHIFT_F15,
		SHIFT_F16,
		SHIFT_F17,
		SHIFT_F18,
		SHIFT_F19,
		SHIFT_F20,

		ALT_UP_ARROW,
		ALT_DOWN_ARROW,
		ALT_RIGHT_ARROW,
		ALT_LEFT_ARROW,
		ALT_HOME_KEY,
		ALT_PAGE_DOWN,
		ALT_PAGE_UP,
		ALT_F1,
		ALT_F2,
		ALT_F3,
		ALT_F4,
		ALT_F5,
		ALT_F6,
		ALT_F7,
		ALT_F8,
		ALT_F9,
		ALT_F10,
		ALT_F11,
		ALT_F12,
		ALT_F13,
		ALT_F14,
		ALT_F15,
		ALT_F16,
		ALT_F17,
		ALT_F18,
		ALT_F19,
		ALT_F20,
		ALT_INSERT_KEY,
		ALT_END_KEY,
		ALT_DO_KEY,
		ALT_HELP_KEY,
		ALT_FIND_KEY,
		ALT_REMOVE_KEY,

		MOUSE_KEY,
		TTY_KEY,

		IGNORE_KEY,
		UNDEFINED_KEY,
		LAST_KEY
	     } KEY_LIST;

int key_sequence_count();
key_sequence * key_sequence_get(int);
char *key_sequence_name(int);
char *key_sequence_name_by_value(int);
void key_sequence_print();

/* ========================================================================== *
 *  _    ___ _____   __                                                       *
 * | |  |_ _| _ ) \ / /                                                      *
 * | |__ | || _ \\ V /                                                        *
 * |____|___|___/ \_/                                                         *
 *                                                                            *
 * ========================================================================== */

typedef struct vt_sequence {
	int	value;
	char	*name;
	char	*seq;
	void	(*function)(void);
} vt_sequence;

typedef	enum {
		VT_FF = 2255,
		VT_UP,
		VT_DOWN,
		VT_RIGHT,
		VT_LEFT,
		VT_HOME,
		VT_CLS,
		VT_RESET,
		VT_BOLD,
		VT_FAINT,
		VT_ITALIC,
		VT_UNDERLINE,
		VT_BLINKING,
		VT_INVERSE,
		VT_HIDDEN,
		VT_STRIKE,
		VT_CURSAVE,
		VT_CURRESTORE,
		VT_ERASE,
		VT_ERASE2SOL,
		VT_ATTR,
		LAST_VT		//
	     } VT_LIST;

int vt_sequence_count();
vt_sequence * vt_sequence_get(int);
char *vt_sequence_name(int);
char *vt_sequence_name_by_value(int);
void vt_sequence_print();

/* ========================================================================== *
 *  _    ___ ___ __  __ ___  ___                                              *
 * | |  |_ _| _ )  \/  / __|/ __|                                             *
 * | |__ | || _ \ |\/| \__ \ (_ |                                              *
 * |____|___|___/_|  |_|___/\___|                                              *
 *                                                                            *
 * ========================================================================== */

typedef enum {
    BEFORE_MOUSE_EVENTS = 1023,
    MOUSE_LEFT_BUTTON_PRESSED,
    MOUSE_MIDDLE_BUTTON_PRESSED,
    MOUSE_RIGHT_BUTTON_PRESSED,
    MOUSE_NONE_BUTTON_PRESSED,

    SHIFTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    SHIFTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    SHIFTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    SHIFTKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    ALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    ALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    ALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    ALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    SHIFTALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    SHIFTALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    SHIFTALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    SHIFTALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    CTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    CTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    CTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    CTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    SHIFTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    SHIFTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    SHIFTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    SHIFTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    ALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    ALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    ALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    ALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    SHIFTALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    SHIFTALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    SHIFTALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    SHIFTALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_SHIFTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_SHIFTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_SHIFTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_SHIFTKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_ALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_ALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_ALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_ALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_SHIFTALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_SHIFTALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_SHIFTALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_SHIFTALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_CTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_CTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_CTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_CTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_ALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_ALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_ALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_ALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED,
    MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED,
    MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED,
    MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED,

    MOUSE_SCROLL_UP,
    MOUSE_SCROLL_DOWN,

    UNKNOWN_42_MOUSE_EVENT,
    UNKNOWN_43_MOUSE_EVENT,
    UNKNOWN_44_MOUSE_EVENT,
    UNKNOWN_45_MOUSE_EVENT,
    UNKNOWN_46_MOUSE_EVENT,
    UNKNOWN_47_MOUSE_EVENT,
    UNKNOWN_48_MOUSE_EVENT,
    UNKNOWN_49_MOUSE_EVENT,
    UNKNOWN_4A_MOUSE_EVENT,
    UNKNOWN_4B_MOUSE_EVENT,
    UNKNOWN_4C_MOUSE_EVENT,
    UNKNOWN_4D_MOUSE_EVENT,
    UNKNOWN_4E_MOUSE_EVENT,
    UNKNOWN_4F_MOUSE_EVENT,
  
    LAST_MOUSE_EVENT

} MOUSE_LIST;

#define MOUSE_ON_THE_MOVE	MOTM_AND_MOUSE_NONE_BUTTON_PRESSED

typedef struct message {
	int	type;
	int	index;				// Not Used
	int	counter;			// Not Used
	union {
		int	character;		// See libk
		int	number;
		int	error;
		int	sequence;
		int	signal;
		int	fd;
		struct {
			int	character;		
			int	button;
			int	row;
			int	column;
		} mouse;
		struct {			// Incomplete
			int	a;
			int	b;
			int	c;
		} tty;
		struct {
			char greetings[8];
		} app;
	} parameter;
	char	event_name[8];
	} message;

#define NO_MESSAGE	0
#define TIME_MESSAGE	1
#define KEY_MESSAGE	2
#define SIG_MESSAGE	3
#define ERR_MESSAGE	4
#define EOF_MESSAGE	5

#define MOUSE_MESSAGE	6
#define TTY_MESSAGE	7
#define APP_MESSAGE	8

void message_init();
message * message_get();
const char *mouse_event_name(int);
void message_mouse_on();
void message_mouse_off();
void message_display(message *pm, char *note);

/* ========================================================================== *
 *  _    ___ ___ _    _    ___ ___ _____                                      *
 * | |  |_ _| _ ) |  | |  |_ _/ __|_   _|                                    *
 * | |__ | || _ \ |__| |__ | |\__ \ | |                                      *
 * |____|___|___/____|____|___|___/ |_|                                       *
 *                                                                            *
 * ========================================================================== */

typedef struct LLIST {
	char *name;
	struct {
		int flags;
	} u;
	struct LLIST *next;
	struct LLIST *previous;
	void   *cargo;
	} LLIST;

LLIST * llinsert(LLIST **,LLIST *);		// Add Before
LLIST * llappend(LLIST **,LLIST *);		// Add After
LLIST * llend(LLIST **,LLIST *);		// Add at End
LLIST * llremove (LLIST **,LLIST *);		// Remove

LLIST * llnext    (LLIST *);
LLIST * llprevious(LLIST *);

LLIST * lllast(LLIST *);
LLIST * llfirst(LLIST *);

/* ========================================================================== *
 *  _    ___ ___ ___                                                          *
 * | |  |_ _| _ ) _ \                                                        *
 * | |__ | || _ \  _/                                                        *
 * |____|___|___/_|                                                           *
 *                                                                            *
 * ========================================================================== */

int pattern_add( char *, int );
int pattern_find( char * );
void pattern_print();

/* ========================================================================== *
 *  _    ___ ___ ___ ___ ___ ___ _____ _   _                                  *
 * | |  |_ _| _ )|   \_ _/ __|_ _|_   _/_\ | |                               *
 * | |__ | || _ \| |) | | (_ || |  | |/ _ \| |__                              *
 * |____|___|___/|___/___\___|___| |_/_/ \_\____|                              *
 *                                                                            *
 * ========================================================================== */

#define DIGITAL_LITERAL	255+1
#define DIGITAL_ANY	255+2
#define DIGITAL_MANY	255+3
#define DIGITAL_LAST	256+4
#define DIGITAL_MAX	DIGITAL_LAST

typedef void * DTREE;

typedef struct DNODE {
	word		index[DIGITAL_MAX];
	void		(*function)(void *, void *);
	void		*parameter;
	struct DNODE	*parent;
	word		c;
	int		n;
	struct DNODE	*reference[1];
} DNODE;

typedef struct DROOT {
	DNODE  *root;
	DNODE  *current;
	DNODE  *search;
	int     deleting;
	int     chain_flag;
	jmp_buf jump;
} DROOT;

#define NOT_FOUND ((DNODE *)-1)

#define DS_START      -2
#define DS_CONTINUE   -1
#define DS_NOT_FOUND   0
#define DS_FOUND       1

#ifndef BUFSIZE
#define BUFSIZE 8192
#endif

/* Digital Tree — add/delete */
int   digital_add_len(DTREE *, byte *, int, void (*)(void *, void *), void *);
int   digital_add(DTREE *, byte *, void (*)(void *, void *), void *);
int   digital_delete_len(DTREE *, byte *, int);
int   digital_delete(DTREE *, byte *);

/* Digital Tree — lookup/find */
DNODE *digital_lookup(DROOT *, DNODE *, byte);
int    digital_find(DTREE *, byte *);

/* Digital Tree — utilities */
word  *digital_fixup(byte *, int);
void   digital_print(DTREE *);
void   digital_purge(DTREE *);
void   digital_possibilities(DTREE *);
byte  *digital_finish(DTREE *, byte *);

/* Digital Tree — display helpers */
void   print_digital_character(word);
void   print_digital_tree_path(DNODE *);

/* Digital Tree — streaming search */
int    check_search_list(DTREE *, word);
void   delete_searches(DTREE *);
void   print_search_tree(void);

/* ========================================================================== *
 *  _    ___ ___  ___                                                         *
 * | |  |_ _| _ )/ _ \                                                       *
 * | |__ | || _ \ (_) |                                                      *
 * |____|___|___/\__\_\                                                      *
 *                                                                            *
 * ========================================================================== */

#define QSIG "QuEuE's FoR YoU!"
//            0123456789ABCDEF

typedef struct QH {
	char            sig[16];
	unsigned long	n;
	struct Q	*first;
	struct Q	*last;
	} QH;

typedef struct Q {
	void		*item;
	struct Q	*next;
	struct Q	*previous;
	} Q;

typedef void * QUEUE;
void test_queue( QUEUE * );
void * queue( QUEUE *, void * );
void * stack( QUEUE *, void * );
void * dequeue( QUEUE * );
void * unstack( QUEUE * );
void purge_queue( QUEUE * );
int chkqueue( QUEUE * );

/* ========================================================================== *
 *   _    ___ ___   _                                                         *
 *  | |  |_ _| _ ) /_\                                                        *
 *  | |__ | || _ \/ _ \                                                       *
 *  |____|___|___/_/ \_\                                                      *
 *                                                                            *
 * ========================================================================== */

#define APP_NO_MESSAGE		NO_MESSAGE	// 0
#define APP_TIME_MESSAGE	TIME_MESSAGE	// 1
#define APP_KEY_MESSAGE		KEY_MESSAGE	// 2
#define APP_SIG_MESSAGE		SIG_MESSAGE	// 3
#define APP_ERR_MESSAGE		ERR_MESSAGE	// 4
#define APP_EOF_MESSAGE		EOF_MESSAGE	// 5
#define APP_MOUSE_MESSAGE	MOUSE_MESSAGE	// 6
#define APP_TTY_MESSAGE		TTY_MESSAGE	// 7
#define APP_HOWDY		APP_MESSAGE	// 8

#define MAX_APPS 12

void app_init();
int  app_register( int (*)( message *) );
int  app_wait();
message *app_wait_any();
int app_message( char *text );
int app_exit();
int app_timer(int,int);

/* ========================================================================== *
 *   _    ___ ___ ___                                                         *
 *  | |  |_ _| _ )   \                                                        *
 *  | |__ | || _ \ |) |                                                       *
 *  |____|___|___/___/                                                        *
 *                                                                            *
 * ========================================================================== */

#define D_NOTHING     0x0000000000000000
//                      AABBCCDDAABBCCDD
#define D_CHAR	      0x00000000FFFFFFFF
#define D_USED	      0x0000000100000000	// How Used
#define D_LINE	      0x0000000200000000	// Empty Line
#define D_EMJI        0x0000000400000000	// Before/After Emoji
#define D_FUT1        0x0000000800000000	// Future Use
#define D_USER        0x000000F000000000	// Use by User

//                      AABBCCDDAABBCCDD
#define D_BG          0x00FF000000000000
#define D_FG          0x0000FF0000000000

#define d_fg(k) (int)( ( k & D_FG ) >> 40 )
#define d_bg(k)	(int)( ( k & D_BG ) >> 48 )

// Column 0
#define R_COLUMNS     0x0000000000000FFF

#define D_MAXROWS	256
#define D_MAXCOLS	256

#define U_NBSP 0xc2a0

typedef unsigned long long DATASTORE_ELEMENT;

typedef struct DATASTORE_LINE {
		DATASTORE_ELEMENT d[D_MAXCOLS+1];
	} DATASTORE_LINE;

typedef struct DATASTORE {
		DATASTORE_ELEMENT d[D_MAXROWS+1][D_MAXCOLS+1];
	} DATASTORE;

DATASTORE * new_datastore();
DATASTORE_LINE *new_datastore_line();
int  set_datastore_umeta(DATASTORE *p,int r,int c,int m);
int  get_datastore_umeta(DATASTORE *p,int r,int c);
char get_datastore_char(DATASTORE *p,int r,int c);
int  get_datastore_value(DATASTORE *p,int r,int c);
DATASTORE_ELEMENT get_datastore(DATASTORE *p,int r,int c);
int insert_element_bgfg( DATASTORE *,int r,int c,unsigned long v,int bg,int fg);
int update_element_bgfg( DATASTORE *,int r,int c,unsigned long v,int bg,int fg);
int insert_element( DATASTORE *,int r,int c,unsigned long v);
int update_element( DATASTORE *,int r,int c,unsigned long v);
int delete_element( DATASTORE *,int r,int c);
void dump_datastore(DATASTORE *);
void write_datastore(DATASTORE *,FILE *,int r,int c,int nr,int nc);
void view_datastore(DATASTORE *,int r,int c,int nr,int nc);
int datastore_writes();
int get_datastore_fg(DATASTORE *p,int r,int c);
int get_datastore_bg(DATASTORE *p,int r,int c);
int is_dataelement_empty(DATASTORE_ELEMENT);
int set_dataelement_char(DATASTORE_ELEMENT *,char );
#define get_dataelement_char(d)		(d&0x7F)
void datastore_reset();

 /* ========================================================================== *
 *  _    ___ _     ___ _  _ ___                                                *
 * | |  |_ _| |   |_ _| \| | __|                                               *
 * | |__ | || |__ | || .` | _|                                                 *
 * |____|___|____|___|_|\_|___|                                                *
 *                                                                            *
 * ========================================================================== */

#define LINE_MAXCHAR 24
#define LINE_NO_CHANGE    0
#define LINE_CURSOR_MOVED 1
#define LINE_CELL_CHANGED 2
#define LINE_LINE_CHANGED 3
#define LINE_FULL_REDRAW  4

typedef struct LINE_CHAR {
	char s[LINE_MAXCHAR];
	int len;
} LINE_CHAR;

typedef struct LINE_LINE {
	int position;
	int length;
	int mode;
	LINE_CHAR ch[D_MAXCOLS+1];
} LINE_LINE;

LINE_LINE *new_line_line();
int set_line_string(LINE_LINE *,char *);
char *get_line_string(LINE_LINE *);
int line_key(LINE_LINE *,int key);
int line_next_char(LINE_LINE *);
int line_previous_char(LINE_LINE *);
int line_next_word(LINE_LINE *);
int line_previous_word(LINE_LINE *);
int line_end_of_line(LINE_LINE *);
int line_start_of_line(LINE_LINE *);
int line_insert_char(LINE_LINE *,int);
int line_delete_char(LINE_LINE *);
int line_backspace(LINE_LINE *);
int line_toggle_mode(LINE_LINE *);

/* ========================================================================== */
/*  Unicode Utilities (from libu)                                             */
/* ========================================================================== */

unsigned long unicoden(unsigned long);
unsigned long unicodes(char *);
char *unicodex(unsigned long);
char *unicode(char *);
char *unicode_string_display(char *);

 /* ========================================================================== *
 *                                                                            *
 *  K5F2 IMPLEMENTATION                                                       *
 *                                                                            *
 * ========================================================================== */

#ifdef K5F2_IMPLEMENTATION


/* ========================================================================== *
 *  _    ___ ___ _    ___   ___                                               *
 * | |  |_ _| _ ) |  / _ \ / __|                                             *
 * | |__ | || _ \ |_| (_) | (_ |                                             *
 * |____|___|___/____\___/ \___|                                              *
 *                                                                            *
 * ========================================================================== */

enum { UNKNOWN,DEBUG,VERBOSE,NOTICE,ERROR,WARNING,FATAL,SPECIAL };
static char *log_classification[]= {
	"UNKNOWN","DEBUG","VERBOSE","NOTICE","ERROR","WARNING","FATAL","_______" };
static char *process_name="______________________";
static int isdebugon=-1;
static char log_message[1024];
static int isverbose=-1;

void logger( int log_class, char *s, va_list v, char *info )
{
	time_t t;
	char *p;

	t = time(NULL);
	strftime(log_message,sizeof(log_message),"%Y-%m-%d %H:%M:%S",localtime(&t));
	sprintf(&log_message[strlen(log_message)]," %-8.8s",process_name);
	sprintf(&log_message[strlen(log_message)]," %8.8s: ",log_classification[log_class]);
	p=&log_message[strlen(log_message)];
	if ( log_class == VERBOSE ) p=log_message;
	vsprintf(p,s,v);
	if ( info ) {
		strcat(&log_message[strlen(log_message)],", ");
		strcat(&log_message[strlen(log_message)],info);
	}

	strcat(&log_message[strlen(log_message)],"\n");
	fwrite(log_message,strlen(log_message),sizeof(char),stderr);
	fflush(stderr);
}

void error_report( int n, char *s, va_list v)
{
	logger(n,s,v,NULL);
}

void sys_error_report(int n,char *s, va_list v)
{
	logger(n,s,v,strerror(errno));
}

void set_process_name(char *p)
{
	if ( p ) process_name = strdup(p);
}

void set_debug() { isdebugon=1; }
void clr_debug() { isdebugon=0; }
int   is_debug() { return(isdebugon); }
void debug(char *s,...)
{
	va_list v;
	char *pd;
	if ( isdebugon == 0 ) return;
	if ( isdebugon < 0 ) {
		isdebugon=0;
		pd=getenv("DEBUG");
		if ( pd && strcasecmp(pd,"yes")==0 ) isdebugon=1;
	}
	if ( isdebugon == 0 ) return;
	va_start(v,s);
	error_report(DEBUG,s,v);
}

void ldebug(int x,char *s,... )
{
	(void)x;
	va_list v;
	char *pd;
	if ( isdebugon == 0 ) return;
	if ( isdebugon < 0 ) {
		isdebugon=0;
		pd=getenv("DEBUG");
		if ( pd && strcasecmp(pd,"yes")==0 ) isdebugon=1;
	}
	if ( isdebugon == 0 ) return;
	va_start(v,s);
	error_report(DEBUG,s,v);
}

void ddump(char *t,void *v,int n)
{
	char *p,*s;
	int i,m;
	if ( isdebugon == 0 ) return;
	i=0;
	s=(char *)v;
	while ( i < n ) {
		m=16;
		if ( m > n ) m=n;
		p=sdump(s,m);
		debug("%s %s",t,p);
		i+=m;
		s+=m;
	}
}

void set_verbose() { isverbose=1; }
void clr_verbose() { isverbose=0; }
int   is_verbose() { return(isverbose); }
void verbose(char *s,...)
{
	va_list v;
	char *pd;
	if ( isverbose == 0 ) return;
	if ( isverbose < 0 ) {
		isverbose=0;
		pd=getenv("VERBOSE");
		if ( pd && strcasecmp(pd,"yes")==0 ) isverbose=1;
	}
	if ( isverbose == 0 ) return;
	va_start(v,s);
	error_report(VERBOSE,s,v);
}

void vdump(char *t,void *v,int n)
{
	char *p,*s;
	int i,m;
	if ( isverbose == 0 ) return;
	i=0;
	s=(char *)v;
	while ( i < n ) {
		m=16;
		if ( m > n ) m=n;
		p=sdump(s,m);
		verbose("%s %s",t,p);
		i+=m;
		s+=m;
	}
}

void notice(char *s,...)
{
	va_list v;
	va_start(v,s);
	error_report(NOTICE,s,v);
}

void error(char *s,...)
{
	va_list v;
	va_start(v,s);
	error_report(ERROR,s,v);
}

void warning(char *s,...)
{
	va_list v;
	va_start(v,s);
	error_report(WARNING,s,v);
}

void pseudofatal(char *s,...)
{
	va_list v;
	va_start(v,s);
	error_report(FATAL,s,v);
}

void fatal(char *s,...)
{
	va_list v;
	va_start(v,s);
	error_report(FATAL,s,v);
	fflush(NULL);
	exit(1);
}

void sysnotice(char *s,...)
{
	va_list v;
	va_start(v,s);
	sys_error_report(NOTICE,s,v);
}

void syserror(char *s,...)
{
	va_list v;
	va_start(v,s);
	sys_error_report(ERROR,s,v);
}

void syswarning(char *s,...)
{
	va_list v;
	va_start(v,s);
	sys_error_report(WARNING,s,v);
}

void sysfatal(char *s,...)
{
	va_list v;
	va_start(v,s);
	sys_error_report(FATAL,s,v);
	fflush(NULL);
	exit(1);
}

void syspseudofatal(char *s,...)
{
	va_list v;
	va_start(v,s);
	sys_error_report(FATAL,s,v);
}

void logmessage(char *m,char *s,...)
{
	va_list v;
	log_classification[SPECIAL] = m;
	va_start(v,s);
	error_report(SPECIAL,s,v);
}

void returnfar()
{
	/* TODO: longjmp */
}

void syntax(char *s,...)
{
	va_list v;
	va_start(v,s);
	vsprintf(log_message,s,v);
	fprintf(stdout,"%s\n",log_message);
}

void writeln(char *s,...)
{
	va_list v;
	va_start(v,s);
	vsprintf(log_message,s,v);
	fprintf(stdout,"%s\n",log_message);
}

void errorln(char *s,...)
{
	va_list v;
	va_start(v,s);
	vsprintf(log_message,s,v);
	fprintf(stderr,"%s\n",log_message);
}

int loglevel(int x)
{
	(void)x;
	return(0);
}

void logclrlevel(int x)
{
	(void)x;
}

void logsetlevel(int x)
{
	(void)x;
}

/* ========================================================================== *
 *  _    ___ ___  ___ _____ _  _ ___ ___                                      *
 * | |  |_ _| _ )/ _ \_   _| || | __| _ \                                    *
 * | |__ | || _ \ (_) || | | __ | _||   /                                     *
 * |____|___|___/\___/ |_| |_||_|___|_|_\                                     *
 *                                                                            *
 * ========================================================================== */

static unsigned char ebcdic_to_ascii_table[256] = { /* ebcdic */
/*       00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F */
/*0*/ 0x00,0x01,0x02,0x03,0x9C,0x09,0x86,0x7F,0x97,0x8D,0x8E,0x0B,0x0C,0x0D,0x0E,0x0F,
/*1*/ 0x10,0x11,0x12,0x13,0x9D,0x85,0x08,0x87,0x18,0x19,0x92,0x8F,0x1C,0x1D,0x1E,0x1F,
/*2*/ 0x80,0x81,0x82,0x83,0x84,0x0A,0x17,0x1B,0x88,0x89,0x8A,0x8B,0x8C,0x05,0x06,0x07,
/*3*/ 0x90,0x91,0x16,0x93,0x94,0x95,0x96,0x04,0x98,0x99,0x9A,0x9B,0x14,0x15,0x9E,0x1A,
/*4*/ 0x20,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0x20,0xA8,0xD5,0x2E,0x3C,0x28,0x2B,0x7C,
/*5*/ 0x26,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0x21,0x24,0x2A,0x29,0x3B,0x7E,
/*6*/ 0x2D,0x2F,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xCB,0x2C,0x25,0x5F,0x3E,0x3F,
/*7*/ 0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0xC0,0xC1,0xC2,0x60,0x3A,0x23,0x40,0x27,0x3D,0x22,
/*8*/ 0xC3,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,
/*9*/ 0xCA,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,0x5E,0xCC,0xCD,0xCE,0xCF,0xD0,
/*A*/ 0xD1,0xE5,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x20,0xD3,0xD4,0x5B,0xD6,0xD7,
/*B*/ 0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xE0,0xE1,0xE2,0xE3,0xE4,0x5D,0xE6,0xE7,
/*C*/ 0x7B,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x42,0x43,0x44,0x45,0x46,0x47,
/*D*/ 0x7D,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,
/*E*/ 0x5C,0x9F,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0xF4,0x54,0x55,0x56,0x57,0x58,
/*F*/ 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF};

char ebcdic_to_ascii(char c)
{
	return( ebcdic_to_ascii_table[(int)c] );
}

static char xtable[] = "0123456789ABCDEF";

static void dump_memory( char *title, void *x, size_t n, void (*f)(char *,char *,char *), int code, int highlight )
{
	int   i,index;
	unsigned char  k,*p,*l,b[80],t[80],*pt,*pb;

	if ( n > 2048 ) n = 2048;

	p = (unsigned char *)x;

	for ( l = p + n, index = 1; p < l; )
	{
		pb = b;
		pt = t;

		if ( highlight )
		{
			*pt++ = 2;
			*pb++ = 0xf;
		}

		*pt++ = '#';
		*pt++ = ' ';

		for ( i = 0; i < 16 && p < l; i++, p++, index++ )
		{
			k = code?ebcdic_to_ascii(*p):*p;
			*pt++ = (  k < ' ' ||  k > '~' ) ? '.' :  k;

			*pb++ = xtable [ *p >> 4 ];
			*pb++ = xtable [ *p & 15 ];
			*pb++ = ' ';

			if ( i == 7 )
			{
				*pb++ = '-';
				*pb++ = ' ';
			}

			if ( highlight && index >= highlight )
			{
				*pt++ = 3;
				*pb++ = 0x0e;
				highlight = 0;
			}
		}
		while ( i++ < 16 )
		{
			*pb++ = ' ';
			*pb++ = ' ';
			*pb++ = ' ';
			if ( i == 7 )
			{
				*pb++ = ' ';
				*pb++ = ' ';
			}
		}

		*pt = '\0';

		strcpy((char *)pb,(char *)t);

		(*f)( "%-10.10s %s", title, (char *)b );
		title = "\"";
	}
}

static char dump_tmp[512];
static void dump_mprintf( char *f, char *t, char *b )
{
	sprintf(dump_tmp,f,t,b);
	printf("%s\n",dump_tmp);
}
static void dump_eprintf( char *f, char *t, char *b )
{
	sprintf(dump_tmp,f,t,b);
	fprintf(stderr,"%s\n",dump_tmp);
}

void dump( char *title, void *x, size_t n )
{
	dump_memory( title,x,n,dump_mprintf,0,0);
}

void edump( char *title, void *x, size_t n )
{
	dump_memory( title,x,n,dump_eprintf,0,0);
}

static void dump_msprintf( char *f, char *t, char *b )
{
	(void)f; (void)t;
	strcat(dump_tmp,b);
}

char *sdump( void *x, size_t n )
{
	bzero(dump_tmp,sizeof(dump_tmp));
	n = ( n > 64 ) ? 64 : n ;
	dump_memory( "n/a",x,n,dump_msprintf,0,0);
	return(dump_tmp);
}

#define NPOOLMAX 16
static char numpool[NPOOLMAX][32];
static int  npidx=0;

char *number(int n)
{
	char *p=&numpool[npidx++][0];
	if ( npidx >= NPOOLMAX ) npidx=0;
	sprintf(p,"%d",n);
	return(p);
}

char *hnumber(int n)
{
	char *p=&numpool[npidx++][0];
	if ( npidx >= NPOOLMAX ) npidx=0;
	sprintf(p,"%X",n);
	return(p);
}

/* ========================================================================== *
 *  _    ___ ___ ___ ___ ___  _   _ ___ _  _  ___ ___                        *
 * | |  |_ _| _ ) __| __/ _ \| | | | __| \| |/ __| __|                       *
 * | |__ | || _ \__ \ _| (_) | |_| | _|| .` | (__| _|                        *
 * |____|___|___/___/___\__\_\\___/|___|_|\_|\___|___|                        *
 *                                                                            *
 * ========================================================================== */

#define MAX_SEQUENCES 1024
static int number_of_sequences;
static sequence *sequences[MAX_SEQUENCES];

int sequence_count()
{
	return( number_of_sequences );
}

char * sequence_name(int i)
{
	if ( i >= 0 && i < number_of_sequences ) if ( sequences[i] ) return( sequences[i]->name );
	return("");
}

sequence * sequence_get(int i)
{
	if ( i >= 0 && i < number_of_sequences ) return( sequences[i] );
	return(NULL);
}

char * sequence_name_by_value( int v )
{
	for ( int i = 0; i < number_of_sequences; i++ )
		if ( sequences[i] && sequences[i]->value == v )
			return( sequences[i]->name );
	return("none");
}

void sequence_print()
{
	int i=-1;
	while ( sequences[++i] )
		printf("%d %d %s\n",i,sequences[i]->value,sequences[i]->name);
}

void sequence_add( int value, char *name, char *seq, void (*f)(int) )
{
	sequence *ps;
	verbose("%s %s",__FUNCTION__,name);
	if ( number_of_sequences >= MAX_SEQUENCES )
		fatal("Number of Configured Sequences Exceeded");
	ps = sequences[number_of_sequences++]=(sequence *)malloc(sizeof(sequence));
	ps -> value = value;
	ps -> name  = strdup(name);
	ps -> seq   = strdup(seq);
	ps -> function = f;
}

/* ========================================================================== *
 *  _    ___ ___ ___ ___ __  __                                               *
 * | |  |_ _| _ ) __/ __|  \/  |                                             *
 * | |__ | || _ \ _|\__ \ |\/| |                                             *
 * |____|___|___/_| |___/_|  |_|                                              *
 *                                                                            *
 * ========================================================================== */

typedef struct fsm {
	int	u;	/* used */
	int	x;	/* active action */
	int	k;	/* klass */
	int	n;	/* next state */
	int	a;	/* action value */
	} fsm;

typedef struct klass {
	int	u;
	int	k;
	} klass;

#define USED		1
#define UNUSED		0

#define NOTHING		0
#define NUMERIC		1	/* '#' [0-9] */
#define ANY		2	/* Not Implemented */
#define LAST_KLASS	3

#define MAX_KLASS	298
#define MAX_STATE	512

static klass	klasses[MAX_KLASS+1];
static fsm	states[MAX_STATE+1][MAX_KLASS+1];

static void (*fsm_callback_fn)(char *,int);
static int fsm_initialized;

static void fsm_init(void)
{
	if ( fsm_initialized ) return;
	fsm_initialized = 1;
	debug("%s()",__FUNCTION__);
	bzero(klasses,sizeof(klasses));
	bzero(states,sizeof(states));
	klasses[NOTHING].u=USED;
	klasses[NOTHING].k=NOTHING;
	klasses[NUMERIC].u=USED;
	klasses[NUMERIC].k=NUMERIC;
	klasses[ANY].u=USED;
	klasses[ANY].k=ANY;
}

static char *fsm_sub(char *p)
{
	char *s=p;
	while ( *p ) {
		if ( *p < ' ' || *p > '~' ) *p='*';
		p++;
	}
	return(s);
}

static void fsm_do_callback(char *p,int n)
{
	char tmp[256];
	debug("%s [%s] [%d]",__FUNCTION__,fsm_sub(strcpy(tmp,p)),n);
	if ( fsm_callback_fn ) fsm_callback_fn(p,n);
}

void fsm_setcallback( void (*f)(char *,int ) )
{
	fsm_callback_fn=f;
}

void fsm_ccode()
{
	/* Placeholder — not yet implemented */
}

static int get_klass( int k )
{
	int i;

	fsm_init();
	for ( i=LAST_KLASS; klasses[i].u==USED; i++ )
		if ( klasses[i].k==k ) return(i);
	if ( i >= MAX_KLASS ) {
		fprintf(stderr,"Maximum Klasses Exceeded\n");
		exit(1);
	}
	klasses[i].u=USED;
	klasses[i].k=k;
	return(i);
}

static int next_empty_state()
{
	int i=0;
	while ( states[i][0].u==USED ) i++;
	if ( i >= MAX_STATE ) {
		fprintf(stderr,"Maximum States Exceeded\n");
		exit(1);
	}
	states[i][0].u=USED;
	debug("%s returning %d",__FUNCTION__,i);
	return(i);
}

int fsm_add_sequence( char *p, int action )
{
	fsm *pm=NULL;
	int i,s=0,k[2048];

	fsm_init();
	debug("%s %s %d",__FUNCTION__,fsm_sub(strdup(p)),action);

	bzero(k,sizeof(k));
	i=0;
	if ( strlen(p)==0 && action==0 ) {
		k[i++]=get_klass(*p);
	} else
	if ( strlen(p) == 1 ) {
		k[i++]=get_klass(*p);
	} else {
	while ( *p ) {
		switch (*p) {
			case '\\':	p++;
					if ( *p ) k[i]=get_klass(*p++);
					else fprintf(stderr,"Terminating '\\' in pattern ignored\n");
					break;
			case '#':
					k[i]=NUMERIC;
					p++;
					break;
			default:	k[i]=get_klass(*p++);
					break;
		}
		i++;
	}}

	for ( i=0; k[i]; i++ ) {
		debug("%s i=%d k=%d s=%d",__FUNCTION__,i,k[i],s);
		pm=&states[s][k[i]];
		if ( pm->u!=USED ) {
			states[s][0].u=USED;
			pm->u=USED;
			pm->k=k[i];
		}
		if ( k[i+1] && ! pm->n ) pm->n=next_empty_state();
		s=pm->n;
	}
	if ( pm ) {
		pm->a=action;
		pm->x=USED;
	}
	return(0);
}

static char *klass_name( klass *pk, int n )
{
	static char tmp[4];
	if ( pk->k == NOTHING && ! n ) return("N/A");
	if ( pk->k == NUMERIC )	return("NUMERIC");
	if ( pk->k == ANY )	return("ANY");
	sprintf(tmp,"#%2X",pk->k);
	if ( pk->k > ' ' && pk->k <= '~' ) sprintf(tmp,"%c",pk->k);
	return(tmp);
}

void fsm_print()
{
	int i,j;
	fsm_init();
	printf("//     ");
	for ( i=0; klasses[i].u==USED; i++ ) printf(",%-12s",klass_name(&klasses[i],i));
	printf("\n");
	for ( i=0; states[i][0].u==USED; i++ ) {
		printf("// %3.3d ",i);
		for ( j=0; klasses[j].u==USED; j++ ) {
			if ( states[i][j].u==USED ) {
				if ( states[i][j].x && states[i][j].n )
					printf(",%-3s[%2d](%2d) ",klass_name(&klasses[j],j),states[i][j].n,states[i][j].a);
				else
				if ( states[i][j].x )
					printf(",%-3s%4s(%2d) ",klass_name(&klasses[j],j),"",states[i][j].a);
				else
				if ( states[i][j].n )
					printf(",%-3s[%2d]%5s",klass_name(&klasses[j],j),states[i][j].n,"");
				else
					printf(",%-12s",klass_name(&klasses[j],j));
			}
			else printf(",%12s","");
		}
		printf("\n");
	}
}

void fsm_action( int c )
{
	static char sequence[86]={};
	static int n=0;	/* Current Index */
	static int m=0;	/* Last Index with Last Action */
	static int a=0;	/* Last Action */
	static int x=0;	/* Last Action Active */
	static int s=0;	/* Current State */
	fsm *pm=NULL;
	int i,k;
	char y,z;

	fsm_init();
	debug("%s c=%c(%d) sequence=[%s] klass[%d]=%d s=%d",__FUNCTION__,\
		(c<' '||c>'~')?'*':c,c,fsm_sub(strdup(sequence)),c,get_klass(c),s);

	if ( c < 0 ) { /* Reset */
		debug("%s Reset %X %X x=%d",__FUNCTION__,sequence[0],sequence[1],x);
		if ( sequence[0] ) {
			if ( x ) {
				fsm_do_callback(sequence,0);
				y=sequence[m];
				sequence[m]='\0';
				fsm_do_callback(sequence,a);
				sequence[m]=y;
				z=m;
				s=n=m=a=x=0;
				for ( i=z; sequence[i]; i++ ) fsm_action(sequence[i]);
			} else {
				fsm_do_callback(sequence,0);
				sequence[0]='\0';
				s=a=m=n=x=0;
			}
		}
		else {
			sequence[0]='\0';
			s=n=m=a=x=0;
		}
		return;
	}

	if ( c >= '0' && c <= '9' ) pm = &states[s][NUMERIC];
	if ( !pm ) pm=&states[s][ANY];
	if ( pm->u != USED ) {
		k=get_klass(c);
		pm = &states[s][k];
	}

	sequence[n++]=c;
	sequence[n]='\0';

	if ( ! pm->n ) {
		debug("%s next action=NULL pm->x=%d x=%d",__FUNCTION__,pm->x,x);
		if ( pm->x ) {
			fsm_do_callback(sequence,pm->a);
			sequence[0]='\0';
			s=n=m=a=x=0;
		}
		else
		if ( x ) { /* There was a Previous Action */
			y=sequence[m];
			sequence[m]='\0';
			fsm_do_callback(sequence,a);
			sequence[m]=y;
			z=m;
			s=n=m=a=x=0;
			for ( i=z; sequence[i]; i++ ) fsm_action(sequence[i]);
		} else {
			fsm_do_callback(sequence,0);
			sequence[0]='\0';
			s=a=m=n=x=0;
		}
	} else {
		s=pm->n;
		if ( pm->x ) {
			a=pm->a;/* Last Action */
			x=pm->x;/* Last Action is Active */
			m=n;	/* Last Index */
		}
	}
}

/* ========================================================================== *
 *  _    ___ ___ _____ _______   __                                           *
 * | |  |_ _| _ )_   _|_   _\ \ / /                                          *
 * | |__ | || _ \ | |   | |  \ V /                                            *
 * |____|___|___/ |_|   |_|   |_|                                             *
 *                                                                            *
 * ========================================================================== */

static struct termios stio;		/* Saved Copy to Restore */
static struct termios tio;		/* New Settings */
static int sfd;				/* Saved Terminal Descriptor */
struct winsize win;			/* Window Configuration ie 80x24 */
static char *exit_message="\r\n";
static char reset_status='U';
static int terminal_is_a_tty_value=-1;
static int alternate_screen_active=0;

int terminal_rows() { return(win.ws_row); }
int terminal_cols() { return(win.ws_col); }

void terminal_alternate_screen(int enable)
{
	if ( enable ) {
		twrite(1,"\033[?1049h",8);
		alternate_screen_active=1;
	} else {
		twrite(1,"\033[?1049l",8);
		alternate_screen_active=0;
	}
}

int twrite(int a,void *b,int c)
{
	if ( terminal_is_a_tty_value < 0 ) terminal_is_a_tty_value=isatty(1);
	if ( terminal_is_a_tty_value ) return(write(a,b,c));
	return(c);
}

void set_exit_message(char *p)
{
	char b[80];
	strncpy(b,p,72);
	b[72] = '\0';
	strcat(b,"\n");
	exit_message=strdup(b);
}

static void terminal_reset()
{
	int cc,n;
	char c;
	verbose("%s() reset_status='%c'",__FUNCTION__,reset_status);
	if ( reset_status=='C' ) return;
	reset_status='C';
	tcsetattr(sfd,TCSAFLUSH,&stio);
	mouse_events_off();
	visible_cursor();
	if ( alternate_screen_active ) {
		twrite(1,"\033[?1049l",8);
		alternate_screen_active=0;
	}
	if ( strlen(exit_message) ) twrite(1,exit_message,strlen(exit_message));
	usleep(100);
	/* Flush Any Data */
	cc=ioctl(0,FIONREAD,&n);
	if ( cc == 0 && n > 0 ) {
		alarm(1);
		fprintf(stderr,"cc=%u n=%u\n",cc,n);
		for ( int i = 0; i < n; i++ ) if (read(0,&c,1)) {}
	}
}

void terminal_init(int fd)
{
	verbose("%s()",__FUNCTION__);
	if ( tcgetattr( fd, &tio ) )
	{
		if ( errno == ENOTTY ) {
			verbose("%d is not a tty",fd);
			return;
		}
		verbose("%d is a tty",fd);
		return;
	}

	memcpy ( &stio, &tio, sizeof( struct termios ) );

	tio.c_iflag |=  ( IGNBRK | IGNPAR | IXANY );
	tio.c_iflag &= ~( BRKINT | INPCK | PARMRK | ISTRIP | INLCR | IUCLC | IXON | IXOFF );
	tio.c_cflag |=  ( CREAD | CLOCAL );
	tio.c_lflag |=  ( TOSTOP );
	tio.c_lflag &= ~( ISIG | ICANON | ECHO | ECHOE );

	tio.c_cc[VMIN]  = 1;		/* Minimum of a Single Character */
	tio.c_cc[VTIME] = 0;		/* At least 0 Seconds */

	sfd=fd;
	atexit(terminal_reset);
	tcsetattr(fd,TCSAFLUSH,&tio);

	ioctl(fd,TIOCGWINSZ,&win);
}

/*
 * Basic Attributes
 */

void autowrap()		{ twrite(1,"\033[?7h",5); }
void noautowrap()	{ twrite(1,"\033[?7l",5); }
void bold()		{ twrite(1,"\033[1m",3); }
void unbold()		{ twrite(1,"\033[22m",5); }
void cls()		{ twrite(1,"\033[2J\033[3J",8);  }
void clear_line()	{ twrite(1,"\033[2K",4); }
void erase_to_end()	{ twrite(1,"\033[K",3); }
void home()		{ twrite(1,"\033[H",3); }
void reset()		{ twrite(1,"\033[0m",4); }
void newline()		{ twrite(1,"\n",1); }
void reverse()		{ twrite(1,"\033[7m",4); }
void scroll_down()	{ twrite(1,"\033[H\033[L",6); }
void scroll_up()	{ twrite(1,"\n",1); }
void underline()	{ twrite(1,"\033[4m",4); }
void ununderline()	{ twrite(1,"\033[24m",5); }

/*
 * Mouse
 */

void mouse_events_on() {
	twrite(1,"\033[?2004l",8);	/* Turn Off Bracketed Paste Mode */
	twrite(1,"\033[?1000h",8);	/* Turn On Mouse Reporting */
	twrite(1,"\033[?1002h",8);	/* Button Event Tracking */
	twrite(1,"\033[?1003h",8);	/* Any Event Tracking */
	twrite(1,"\033[?1004h",8);	/* Focus Event Reporting */
	twrite(1,"\033[?1006h",8);	/* SGR Ext Mode */
}

void mouse_events_off() {
	twrite(1,"\033[?1006l",8);	/* UnSet SGR Ext Mode */
	twrite(1,"\033[?1004l",8);	/* Focus Event Off */
	twrite(1,"\033[?1003l",8);	/* Any Event Off */
	twrite(1,"\033[?1002l",8);	/* Button Event Off */
	twrite(1,"\033[?1000l",8);	/* Turn Off Mouse Reporting */
	twrite(1,"\033[?2004h",8);	/* Turn On Bracketed Paste Mode */
}

/*
 * Cursor
 */

void restore_cursor()	{ twrite(1,"\033[u\0338",5); }
void save_cursor()	{ twrite(1,"\033[s\0337",5); }
void visible_cursor()	{ twrite(1,"\033[?25h",6); }
void invisible_cursor() { twrite(1,"\033[?25l",6); }

void move_cursor(int r,int c)
{
	char b[64];
	sprintf(b,"\033[%d;%dH",r,c);
	twrite(1,b,strlen(b));
}

/*
 * Colors
 */

static int default_bg,default_fg,fg,bg;

int set_colors_default_bg(int c) { return(default_bg=c); }
int get_colors_default_bg()	 { return(default_bg); }
int set_colors_default_fg(int c) { return(default_fg=c); }
int get_colors_default_fg()	 { return(default_fg); }
int set_colors_bg(int c) { return(bg=c); }
int get_colors_bg()	 { return(bg); }
int set_colors_fg(int c) { return(fg=c); }
int get_colors_fg()	 { return(fg); }

#define NCOLORS 16

static struct {
	char *color;
	int bg;
	int fg;
	int unused_maybe_bold ;
	unsigned long unused_maybe_rgb;
	} ansi_colors[] = {   /*      bg        fg      ?       ? */
	/*  0 */ { "BLACK"          , 40,	30,	0,	0 },
	/*  1 */ { "BLUE"           , 44,	34,	0,	0 },
	/*  2 */ { "GREEN"          , 42,	32,	0,	0 },
	/*  3 */ { "CYAN"           , 46,	36,	0,	0 },
	/*  4 */ { "RED"            , 41,	31,	0,	0 },
	/*  5 */ { "MAGENTA"        , 45,	35,	0,	0 },
	/*  6 */ { "BROWN"          , 43,	33,	0,	0 },
	/*  7 */ { "LIGHTGRAY"      , 47,	37,	0,	0 },
	/*  8 */ { "DARKGRAY"       ,100,	90,	1,	0 },
	/*  9 */ { "LIGHTBLUE"      ,104,	94,	1,	0 },
	/* 10 */ { "LIGHTGREEN"     ,102,	92,	1,	0 },
	/* 11 */ { "LIGHTCYAN"      ,106,	96,	1,	0 },
	/* 12 */ { "LIGHTRED"       ,101,	91,	1,	0 },
	/* 13 */ { "LIGHTMAGENTA"   ,105,	95,	1,	0 },
	/* 14 */ { "YELLOW"         ,103,	93,	1,	0 },
	/* 15 */ { "WHITE"          ,107,	97,	1,	0 }};

int colors_fg(int i)   { return( ansi_colors[i].fg ); }
int colors_bg(int i)   { return( ansi_colors[i].bg ); }
char * colors_name(int i) { return( ansi_colors[i].color ); }

int get_bg_from_fg(int c)
{
	for ( int i=0; i < 8; i++ )
		if ( ansi_colors[i].fg==c )
			return(ansi_colors[i].bg);
	return(0);
}

static int what_color( char *p )
{
	int i;

	if ( ( *p >= 'A' && *p <= 'Z' ) || ( *p >= 'a' && *p <= 'z' ) )
	{
		for ( i = 0; i < NCOLORS; i++ )
		{
			if ( strcasecmp(p,ansi_colors[i].color) == 0 ) return( i );
		}
	}

	return(0);
}

void reset_colors()
{
	char b[32];
	set_colors_bg(get_colors_default_bg());
	set_colors_fg(get_colors_default_fg());
	sprintf(b,"\033[%i;%i;0m",get_colors_bg(),get_colors_fg());
	twrite(1,b,strlen(b));
}

void set_background( char *color )
{
	char b[16];
	set_colors_bg(ansi_colors[ what_color(color) ].bg);
	sprintf(b,"\033[%im",get_colors_bg());
	twrite(1,b,strlen(b));
}

void set_foreground( char *color )
{
	char b[16];
	set_colors_fg(ansi_colors[ what_color(color) ].fg);
	sprintf(b,"\033[%im",get_colors_fg());
	twrite(1,b,strlen(b));
}

/* ========================================================================== *
 *  _    ___ ___ _____   _____ _  _ _____                                     *
 * | |  |_ _| _ ) __\ \ / / __| \| |_   _|                                   *
 * | |__ | || _ \ _| \ V /| _|| .` | | |                                     *
 * |____|___|___/___| \_/ |___|_|\_| |_|                                      *
 *                                                                            *
 * ========================================================================== */

static event pool[16];
static int pool_index=0;

static int tv_sec=1,tv_usec=0;
static fd_set readfds;
static fd_set writefds;
static fd_set exceptfds;
static struct timeval t;

static int iread;
static int events_waiting;

static int event_initialized=0;

void event_signal(int s);

const char *event_type( int t )
{
	verbose("%s(%d)",__FUNCTION__,t);
	if ( t == NO_EVENT	) return("None");
	if ( t == TIME_EVENT	) return("Time");
	if ( t == KEY_EVENT	) return("Key");
	if ( t == ERR_EVENT	) return("Error");
	if ( t == EOF_EVENT	) return("EOF");
	return("Unknown");
	if ( t == TCP_EVENT	) return("TCP");
}

void event_init(int mouse_events)
{
	verbose("%s()",__FUNCTION__);
	// ToDo: isn't this repeated in terminal_init ?
	if ( isatty(0) != 1 )
		verbose("0 is not a tty, %s",strerror(errno));
	else
		verbose("0 is tty");

	terminal_init(0);	// Ignores

	for ( int i=1; i <= 64; i++ ) {
		signal(i,event_signal);
	}

	if ( mouse_events ) event_mouse_on();
}

// ToDo: This is hard-coded just for fd=0
static int read_input(event *pe)
{
	int rc;
	char c;
	for ( iread=0; iread < events_waiting; iread++ ) {
		if ( FD_ISSET(iread,&readfds) ) {
			FD_CLR(iread,&readfds);
			rc=read(0,&c,1);	// ToDo fcntl
			if ( rc==1 ) {
				pe->type=KEY_EVENT;
				pe->parameter.character=c;
				return(1);
			}
			if ( rc== 0 ) {
				pe->type=EOF_EVENT;
				pe->parameter.fd=0;
				return(1);
			} 
			pe->type=ERR_EVENT;
			pe->parameter.error=errno;
			return(1);
		}
	}
	return(0);
}

static int smoke_signals=0;
void event_signal(int s)
{
	smoke_signals=s;
}

void event_timer(int a,int b)
{
	t.tv_sec=tv_sec=a;
	t.tv_usec=tv_usec=b;
}

event *event_wait()
{
	event *pe;

	if ( !event_initialized ) {
		t.tv_sec=tv_sec;
		t.tv_usec=tv_usec;
		event_initialized=1;
	}

	pe=&pool[pool_index];
	pe->index=pool_index++;
	pool_index%=16;
	if ( read_input(pe) ) return(pe);
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);
	FD_SET(0,&readfds);
	events_waiting=select(1,&readfds,&writefds,&exceptfds,&t);
	if ( events_waiting < 0 ) {
		if ( smoke_signals ) {
			pe->type=SIG_EVENT;
			pe->parameter.signal=smoke_signals;
			smoke_signals=0;
			return(pe);
		}
		fprintf(stderr,"Error on select %s\n",strerror(errno));
		exit(1);
	}

	if ( events_waiting == 0 ) {
		pe->type=TIME_EVENT;
		t.tv_sec=tv_sec;
		t.tv_usec=tv_usec;
		return(pe);
	}

    /*
	for ( int i=0; i < events_waiting; i++ ) {
		if ( FD_ISSET(i,&readfds) ) fprintf(stderr,"read i=%d\n",i);
		if ( FD_ISSET(i,&writefds) ) fprintf(stderr,"wrte i=%d\n",i);
		if ( FD_ISSET(i,&exceptfds) ) fprintf(stderr,"eror i=%d\n",i);
	}
    */

	if ( read_input(pe) ) return(pe);
	
	fprintf(stderr,"How did we get Here?");
	fflush(NULL);
	return( NULL );
}

/* libtty wrapper */
void event_mouse_on()
{
	mouse_events_on();
}
void event_mouse_off()
{
	mouse_events_off();
}

/* ========================================================================== *
 *  _    ___ ___ _  __                                                        *
 * | |  |_ _| _ ) |/ /                                                       *
 * | |__ | || _ \ ' <                                                         *
 * |____|___|___/_|\_\                                                        *
 *                                                                            *
 * ========================================================================== */

static void key_nop() { }

#define c(n)	#n
#define k(n,s)	{ n,c(n),s,key_nop },
#define m(n,s)	{ n,s,"X",key_nop  },
#define n(n,s,p){ n,s,p,key_nop },
#define l(n,s)	{ n,s,s,key_nop },

static key_sequence key_sequences[] = {
	n(       0      ,"Null                  (NUL)   @",	"\x00" )
	n(       1      ,"Start Heading         (SOH)   A",	"\x01" )
	n(       2      ,"Start of Text         (STX)   B",	"\x02" )
	n(       3      ,"End of Text           (EOT)   C",	"\x03" )
	n(       4      ,"End Transmit          (EOT)   D",	"\x04" )
	n(       5      ,"Enquiry               (ENQ)   E",	"\x05" )
	n(       6      ,"Acknowledge           (ACK)   F",	"\x06" )
	n(       7      ,"Bell                  (BEL)   G",	"\x07" )
	n(       8      ,"Back Space            (BS)    H",	"\x08" )
	n(       9      ,"Horizontal Tab        (HT)    I",	"\x09" )
	n(      10      ,"Line Feed             (LF)    J",	"\x0A" )
	n(      11      ,"Vertical Tab          (VT)    K",	"\x0B" )
	n(      12      ,"Form Feed             (FF)    L",	"\x0C" )
	n(      13      ,"Carriage Return       (CR)    M",	"\x0D" )
	n(      14      ,"Shift Out             (SO)    N",	"\x0E" )
	n(      15      ,"Shift In              (SI)    O",	"\x0F" )
	n(      16      ,"Device Link Esc       (DLE)   P",	"\x10" )
	n(      17      ,"Device Control 1 XON  (DC1)   Q",	"\x11" )
	n(      18      ,"Device Control 2      (DC2)   R",	"\x12" )
	n(      19      ,"Device Control 3 XOFF (DC3)   S",	"\x13" )
	n(      20      ,"Device Control 4      (DC4)   T",	"\x14" )
	n(      21      ,"Negative Ack          (NAK)   U",	"\x15" )
	n(      22      ,"Synchronous Idle      (SYN)   V",	"\x16" )
	n(      23      ,"End Transmit Block    (ETB    W",	"\x17" )
	n(      24      ,"Cancel                (CAN)   X",	"\x18" )
	n(      25      ,"End Medium            (EM     Y",	"\x19" )
	n(      26      ,"Substitute            (SUB    Z",	"\x1A" )
	n(      27      ,"Escape                (ESC)   [",	"\x1B" )
	n(      28      ,"Cursor Right          (FS)    /",	"\x1C" )
	n(      29      ,"Cursor Left           (GS)    ]",	"\x1D" )
	n(      30      ,"Cursor Up             (RS)    ^",	"\x1E" )
	n(	31      ,"Cursor Down           (US)    -",	"\x1F" )
	l( 32, " " )
	l( 33, "!" )
	l( 34, "\"" )
	l( 35, "#" )
	l( 36, "$" )
	l( 37, "%" )
	l( 38, "&" )
	l( 39, "'" )
	l( 40, "(" )
	l( 41, ")" )
	l( 42, "*" )
	l( 43, "+" )
	l( 44, "," )
	l( 45, "-" )
	l( 46, "." )
	l( 47, "/" )
	l( 48, "0" )
	l( 49, "1" )
	l( 50, "2" )
	l( 51, "3" )
	l( 52, "4" )
	l( 53, "5" )
	l( 54, "6" )
	l( 55, "7" )
	l( 56, "8" )
	l( 57, "9" )
	l( 58, ":" )
	l( 59, ";" )
	l( 60, "<" )
	l( 61, "=" )
	l( 62, ">" )
	l( 63, "?" )
	l( 64, "@" )
	l( 65, "A" ) l( 66, "B" ) l( 67, "C" ) l( 68, "D" ) l( 69, "E" ) l( 70, "F" )
	l( 71, "G" ) l( 72, "H" ) l( 73, "I" ) l( 74, "J" ) l( 75, "K" ) l( 76, "L" )
	l( 77, "M" ) l( 78, "N" ) l( 79, "O" ) l( 80, "P" ) l( 81, "Q" ) l( 82, "R" )
	l( 83, "S" ) l( 84, "T" ) l( 85, "U" ) l( 86, "V" ) l( 87, "W" ) l( 88, "X" )
	l( 89, "Y" ) l( 90, "Z" ) l( 91, "[" )
	l( 92, "\\" )
	l( 93, "]" )
	l( 94, "^" )
	l( 95, "_" )
	l( 96, "`" )
	l( 97, "a" ) l( 98, "b" ) l( 99, "c" ) l( 100, "d" ) l( 101, "e" ) l( 102, "f" )
	l( 103, "g" ) l( 104, "h" ) l( 105, "i" ) l( 106, "j" ) l( 107, "k" ) l( 108, "l" )
	l( 109, "m" ) l( 110, "n" ) l( 111, "o" ) l( 112, "p" ) l( 113, "q" ) l( 114, "r" )
	l( 115, "s" ) l( 116, "t" ) l( 117, "u" ) l( 118, "v" ) l( 119, "w" ) l( 120, "x" )
	l( 121, "y" ) l( 122, "z" ) l( 123, "{" )
	l( 124, "|" )
	l( 125, "}" )
	l( 126, "~" )
	n( 127, "#7F", "\x7F" )
	n( 128, "#80", "\x80" )
	n( 129, "#81", "\x81" )
	n( 130, "#82", "\x82" )
	n( 131, "#83", "\x83" )
	n( 132, "#84", "\x84" )
	n( 133, "#85", "\x85" )
	n( 134, "#86", "\x86" )
	n( 135, "#87", "\x87" )
	n( 136, "#88", "\x88" )
	n( 137, "#89", "\x89" )
	n( 138, "#8A", "\x8A" )
	n( 139, "#8B", "\x8B" )
	n( 140, "#8C", "\x8C" )
	n( 141, "#8D", "\x8D" )
	n( 142, "#8E", "\x8E" )
	n( 143, "#8F", "\x8F" )
	n( 144, "#90", "\x90" )
	n( 145, "#91", "\x91" )
	n( 146, "#92", "\x92" )
	n( 147, "#93", "\x93" )
	n( 148, "#94", "\x94" )
	n( 149, "#95", "\x95" )
	n( 150, "#96", "\x96" )
	n( 151, "#97", "\x97" )
	n( 152, "#98", "\x98" )
	n( 153, "#99", "\x99" )
	n( 154, "#9A", "\x9A" )
	n( 155, "#9B", "\x9B" )
	n( 156, "#9C", "\x9C" )
	n( 157, "#9D", "\x9D" )
	n( 158, "#9E", "\x9E" )
	n( 159, "#9F", "\x9F" )
	n( 160, "#A0", "\xA0" )
	n( 161, "#A1", "\xA1" )
	n( 162, "#A2", "\xA2" )
	n( 163, "#A3", "\xA3" )
	n( 164, "#A4", "\xA4" )
	n( 165, "#A5", "\xA5" )
	n( 166, "#A6", "\xA6" )
	n( 167, "#A7", "\xA7" )
	n( 168, "#A8", "\xA8" )
	n( 169, "#A9", "\xA9" )
	n( 170, "#AA", "\xAA" )
	n( 171, "#AB", "\xAB" )
	n( 172, "#AC", "\xAC" )
	n( 173, "#AD", "\xAD" )
	n( 174, "#AE", "\xAE" )
	n( 175, "#AF", "\xAF" )
	n( 176, "#B0", "\xB0" )
	n( 177, "#B1", "\xB1" )
	n( 178, "#B2", "\xB2" )
	n( 179, "#B3", "\xB3" )
	n( 180, "#B4", "\xB4" )
	n( 181, "#B5", "\xB5" )
	n( 182, "#B6", "\xB6" )
	n( 183, "#B7", "\xB7" )
	n( 184, "#B8", "\xB8" )
	n( 185, "#B9", "\xB9" )
	n( 186, "#BA", "\xBA" )
	n( 187, "#BB", "\xBB" )
	n( 188, "#BC", "\xBC" )
	n( 189, "#BD", "\xBD" )
	n( 190, "#BE", "\xBE" )
	n( 191, "#BF", "\xBF" )
	n( 192, "#C0", "\xC0" )
	n( 193, "#C1", "\xC1" )
	n( 194, "#C2", "\xC2" )
	n( 195, "#C3", "\xC3" )
	n( 196, "#C4", "\xC4" )
	n( 197, "#C5", "\xC5" )
	n( 198, "#C6", "\xC6" )
	n( 199, "#C7", "\xC7" )
	n( 200, "#C8", "\xC8" )
	n( 201, "#C9", "\xC9" )
	n( 202, "#CA", "\xCA" )
	n( 203, "#CB", "\xCB" )
	n( 204, "#CC", "\xCC" )
	n( 205, "#CD", "\xCD" )
	n( 206, "#CE", "\xCE" )
	n( 207, "#CF", "\xCF" )
	n( 208, "#D0", "\xD0" )
	n( 209, "#D1", "\xD1" )
	n( 210, "#D2", "\xD2" )
	n( 211, "#D3", "\xD3" )
	n( 212, "#D4", "\xD4" )
	n( 213, "#D5", "\xD5" )
	n( 214, "#D6", "\xD6" )
	n( 215, "#D7", "\xD7" )
	n( 216, "#D8", "\xD8" )
	n( 217, "#D9", "\xD9" )
	n( 218, "#DA", "\xDA" )
	n( 219, "#DB", "\xDB" )
	n( 220, "#DC", "\xDC" )
	n( 221, "#DD", "\xDD" )
	n( 222, "#DE", "\xDE" )
	n( 223, "#DF", "\xDF" )
	n( 224, "#E0", "\xE0" )
	n( 225, "#E1", "\xE1" )
	n( 226, "#E2", "\xE2" )
	n( 227, "#E3", "\xE3" )
	n( 228, "#E4", "\xE4" )
	n( 229, "#E5", "\xE5" )
	n( 230, "#E6", "\xE6" )
	n( 231, "#E7", "\xE7" )
	n( 232, "#E8", "\xE8" )
	n( 233, "#E9", "\xE9" )
	n( 234, "#EA", "\xEA" )
	n( 235, "#EB", "\xEB" )
	n( 236, "#EC", "\xEC" )
	n( 237, "#ED", "\xED" )
	n( 238, "#EE", "\xEE" )
	n( 239, "#EF", "\xEF" )
	n( 240, "#F0", "\xF0" )
	n( 241, "#F1", "\xF1" )
	n( 242, "#F2", "\xF2" )
	n( 243, "#F3", "\xF3" )
	n( 244, "#F4", "\xF4" )
	n( 245, "#F5", "\xF5" )
	n( 246, "#F6", "\xF6" )
	n( 247, "#F7", "\xF7" )
	n( 248, "#F8", "\xF8" )
	n( 249, "#F9", "\xF9" )
	n( 250, "#FA", "\xFA" )
	n( 251, "#FB", "\xFB" )
	n( 252, "#FC", "\xFC" )
	n( 253, "#FD", "\xFD" )
	n( 254, "#FE", "\xFE" )
	n( 255, "#FF", "\xFF" )
	k(UP_ARROW,		"\033[A")
	k(DOWN_ARROW,		"\033[B")
	k(RIGHT_ARROW,		"\033[C")
	k(LEFT_ARROW,		"\033[D")
	k(UNDEFINED_KEY,	"\033[E")
	k(END_KEY,		"\033[F")
	k(UNDEFINED_KEY,	"\033[G")
	k(HOME_KEY,		"\033[H")
	k(IGNORE_KEY,		"\033[I")
	k(IGNORE_KEY,		"\033[O")
	k(UNDEFINED_KEY,	"\033[P")
	k(SHIFT_TAB,		"\033[Z")
	k(CTRL_UP_ARROW,	"\033[1;5A")
	k(CTRL_DOWN_ARROW,	"\033[1;5B")
	k(CTRL_RIGHT_ARROW,	"\033[1;5C")
	k(CTRL_LEFT_ARROW,	"\033[1;5D")
	k(CTRL_END_KEY,		"\033[1;5F")
	k(CTRL_HOME_KEY,	"\033[1;5H")
	k(ALT_UP_ARROW,		"\033[1;3A")
	k(ALT_DOWN_ARROW,	"\033[1;3B")
	k(ALT_RIGHT_ARROW,	"\033[1;3C")
	k(ALT_LEFT_ARROW,	"\033[1;3D")
	k(ALT_END_KEY,       	"\033[1;3F")
	k(ALT_HOME_KEY,       	"\033[1;3H")
	k(F1,			"\033[001q")
	k(F2,			"\033[002q")
	k(F3,			"\033[003q")
	k(F4,			"\033[004q")
	k(F5,			"\033[005q")
	k(F6,			"\033[006q")
	k(F7,			"\033[007q")
	k(F8,			"\033[008q")
	k(F9,			"\033[009q")
	k(F10,			"\033[010q")
	k(F11,			"\033[011q")
	k(F12,			"\033[012q")
	k(UNDEFINED_KEY,	"\033[013q")
	k(UNDEFINED_KEY,	"\033[014q")
	k(UNDEFINED_KEY,	"\033[015q")
	k(UNDEFINED_KEY,	"\033[016q")
	k(UNDEFINED_KEY,	"\033[017q")
	k(UNDEFINED_KEY,	"\033[018q")
	k(UNDEFINED_KEY,	"\033[019q")
	k(UNDEFINED_KEY,	"\033[020q")
	k(UNDEFINED_KEY,	"\033[021q")
	k(UNDEFINED_KEY,	"\033[022q")
	k(UNDEFINED_KEY,	"\033[023q")
	k(UNDEFINED_KEY,	"\033[024q")
	k(UNDEFINED_KEY,	"\033[025q")
	k(UNDEFINED_KEY,	"\033[026q")
	k(UNDEFINED_KEY,	"\033[027q")
	k(UNDEFINED_KEY,	"\033[028q")
	k(UNDEFINED_KEY,	"\033[029q")
	k(UNDEFINED_KEY,	"\033[030q")
	k(UNDEFINED_KEY,	"\033[031q")
	k(UNDEFINED_KEY,	"\033[032q")
	k(UNDEFINED_KEY,	"\033[033q")
	k(UNDEFINED_KEY,	"\033[034q")
	k(UNDEFINED_KEY,	"\033[035q")
	k(UNDEFINED_KEY,	"\033[036q")
	k(UNDEFINED_KEY,	"\033[037q")
	k(UNDEFINED_KEY,	"\033[038q")
	k(UNDEFINED_KEY,	"\033[039q")
	k(UNDEFINED_KEY,	"\033[040q")
	k(UNDEFINED_KEY,	"\033[041q")
	k(UNDEFINED_KEY,	"\033[042q")
	k(UNDEFINED_KEY,	"\033[043q")
	k(UNDEFINED_KEY,	"\033[044q")
	k(UNDEFINED_KEY,	"\033[045q")
	k(UNDEFINED_KEY,	"\033[046q")
	k(UNDEFINED_KEY,	"\033[047q")
	k(UNDEFINED_KEY,	"\033[048q")
	k(UNDEFINED_KEY,	"\033[049q")
	k(UNDEFINED_KEY,	"\033[050q")
	k(UNDEFINED_KEY,	"\033[051q")
	k(UNDEFINED_KEY,	"\033[052q")
	k(UNDEFINED_KEY,	"\033[053q")
	k(UNDEFINED_KEY,	"\033[054q")
	k(UNDEFINED_KEY,	"\033[055q")
	k(UNDEFINED_KEY,	"\033[056q")
	k(UNDEFINED_KEY,	"\033[058q")
	k(UNDEFINED_KEY,	"\033[059q")
	k(UNDEFINED_KEY,	"\033[060q")
	k(UNDEFINED_KEY,	"\033[061q")
	k(UNDEFINED_KEY,	"\033[062q")
	k(UNDEFINED_KEY,	"\033[063q")
	k(UNDEFINED_KEY,	"\033[064q")
	k(UNDEFINED_KEY,	"\033[065q")
	k(UNDEFINED_KEY,	"\033[066q")
	k(UNDEFINED_KEY,	"\033[067q")
	k(UNDEFINED_KEY,	"\033[071q")
	k(UNDEFINED_KEY,	"\033[073q")
	k(UNDEFINED_KEY,	"\033[074q")
	k(UNDEFINED_KEY,	"\033[075q")
	k(UNDEFINED_KEY,	"\033[071q")
	k(UNDEFINED_KEY,	"\033[073q")
	k(UNDEFINED_KEY,	"\033[074q")
	k(UNDEFINED_KEY,	"\033[075q")
	k(UNDEFINED_KEY,	"\033[075q")
	k(UNDEFINED_KEY,	"\033[076q")
	k(UNDEFINED_KEY,	"\033[077q")
	k(UNDEFINED_KEY,	"\033[078q")
	k(UNDEFINED_KEY,	"\033[079q")
	k(UNDEFINED_KEY,	"\033[080q")
	k(UNDEFINED_KEY,	"\033[081q")
	k(UNDEFINED_KEY,	"\033[082q")
	k(UNDEFINED_KEY,	"\033[083q")
	k(UNDEFINED_KEY,	"\033[087q")
	k(UNDEFINED_KEY,	"\033[088q")
	k(UNDEFINED_KEY,	"\033[089q")
	k(UNDEFINED_KEY,	"\033[090q")
	k(UNDEFINED_KEY,	"\033[091q")
	k(UNDEFINED_KEY,	"\033[092q")
	k(UNDEFINED_KEY,	"\033[093q")
	k(UNDEFINED_KEY,	"\033[094q")
	k(UNDEFINED_KEY,	"\033[095q")
	k(UNDEFINED_KEY,	"\033[100q")
	k(UNDEFINED_KEY,	"\033[101q")
	k(UNDEFINED_KEY,	"\033[102q")
	k(UNDEFINED_KEY,	"\033[103q")
	k(UNDEFINED_KEY,	"\033[104q")
	k(UNDEFINED_KEY,	"\033[105q")
	k(UNDEFINED_KEY,	"\033[106q")
	k(UNDEFINED_KEY,	"\033[107q")
	k(UNDEFINED_KEY,	"\033[114q")
	k(UNDEFINED_KEY,	"\033[121q")
	k(UNDEFINED_KEY,	"\033[122q")
	k(INSERT_KEY,		"\033[139q")
	k(UNDEFINED_KEY,	"\033[140q")
	k(UNDEFINED_KEY,	"\033[141q")
	k(UNDEFINED_KEY,	"\033[142q")
	k(UNDEFINED_KEY,	"\033[143q")
	k(UNDEFINED_KEY,	"\033[144q")
	k(UNDEFINED_KEY,	"\033[145q")
	k(END_KEY,		"\033[146q")
	k(UNDEFINED_KEY,	"\033[147q")
	k(UNDEFINED_KEY,	"\033[148q")
	k(UNDEFINED_KEY,	"\033[149q")
	k(PAGE_UP,		"\033[150q")
	k(UNDEFINED_KEY,	"\033[151q")
	k(UNDEFINED_KEY,	"\033[152q")
	k(UNDEFINED_KEY,	"\033[153q")
	k(PAGE_DOWN,		"\033[154q")
	k(UNDEFINED_KEY,	"\033[155q")
	k(UNDEFINED_KEY,	"\033[156q")
	k(UNDEFINED_KEY,	"\033[157q")
	k(UNDEFINED_KEY,	"\033[159q")
	k(UNDEFINED_KEY,	"\033[160q")
	k(UNDEFINED_KEY,	"\033[162q")
	k(UNDEFINED_KEY,	"\033[163q")
	k(UNDEFINED_KEY,	"\033[165q")
	k(UNDEFINED_KEY,	"\033[166q")
	k(UNDEFINED_KEY,	"\033[168q")
	k(UNDEFINED_KEY,	"\033[169q")
	k(UNDEFINED_KEY,	"\033[170q")
	k(UNDEFINED_KEY,	"\033[172q")
	k(UNDEFINED_KEY,	"\033[174q")
	k(UNDEFINED_KEY,	"\033[176q")
	k(UNDEFINED_KEY,	"\033[178q")
	k(UNDEFINED_KEY,	"\033[179q")
	k(UNDEFINED_KEY,	"\033[180q")
	k(UNDEFINED_KEY,	"\033[182q")
	k(UNDEFINED_KEY,	"\033[184q")
	k(UNDEFINED_KEY,	"\033[186q")
	k(UNDEFINED_KEY,	"\033[187q")
	k(UNDEFINED_KEY,	"\033[188q")
	k(UNDEFINED_KEY,	"\033[190q")
	k(UNDEFINED_KEY,	"\033[192q")
	k(UNDEFINED_KEY,	"\033[194q")
	k(UNDEFINED_KEY,	"\033[196q")
	k(UNDEFINED_KEY,	"\033[197q")
	k(UNDEFINED_KEY,	"\033[198q")
	k(UNDEFINED_KEY,	"\033[199q")
	k(UNDEFINED_KEY,	"\033[200q")
	k(UNDEFINED_KEY,	"\033[201q")
	k(UNDEFINED_KEY,	"\033[209q")
	k(UNDEFINED_KEY,	"\033[210q")
	k(UNDEFINED_KEY,	"\033[211q")
	k(UNDEFINED_KEY,	"\033[212q")
	k(UNDEFINED_KEY,	"\033[213q")
	k(UNDEFINED_KEY,	"\033[214q")
	k(UNDEFINED_KEY,	"\033[215q")
	k(UNDEFINED_KEY,	"\033[216q")
	k(UNDEFINED_KEY,	"\033[217q")
	k(UNDEFINED_KEY,	"\033[218q")
	k(F1,			"\033OP")
	k(F2,			"\033OQ")
	k(F3,			"\033OR")
	k(F4,			"\033OS")
 	k(SHIFT_F1,     "\033[1;2P")
 	k(SHIFT_F2,     "\033[1;2Q")
 	k(SHIFT_F3,     "\033[1;2R")
 	k(SHIFT_F4,     "\033[1;2S")
	k(ALT_F1,		"\033[1;3P")
	k(ALT_F2,		"\033[1;3Q")
	k(ALT_F3,		"\033[1;3R")
	k(ALT_F4,		"\033[1;3S")
	k(CTRL_F1,		"\033[1;5P")
	k(CTRL_F2,		"\033[1;5Q")
	k(CTRL_F3,		"\033[1;5R")
	k(CTRL_F4,		"\033[1;5S")
	k(F1,			"\033[11~")
	k(F2,			"\033[12~")
	k(F3,			"\033[13~")
	k(F4,			"\033[14~")
	k(F5,			"\033[15~")
    k(SHIFT_F5,     "\033[15;2~")
	k(ALT_F5,		"\033[15;3~")
	k(CTRL_F5,		"\033[15;5~")
	k(F6,			"\033[17~")
    k(SHIFT_F6,     "\033[17;2~")
	k(ALT_F6,		"\033[17;3~")
	k(CTRL_F6,      "\033[17;5~")
	k(F7,			"\033[18~")
	k(SHIFT_F7,		"\033[18;2~")
	k(ALT_F7,		"\033[18;3~")
	k(CTRL_F7,      "\033[18;5~")
	k(F8,			"\033[19~")
	k(SHIFT_F8,		"\033[19;2~")
	k(ALT_F8,		"\033[19;3~")
	k(CTRL_F8,      "\033[19;5~")
	k(F9,			"\033[20~")
	k(SHIFT_F9,		"\033[20;2~")
	k(ALT_F9,		"\033[20;3~")
	k(CTRL_F9,      "\033[20;5~")
	k(F10,			"\033[21~")
	k(SHIFT_F10,	"\033[21;2~")
	k(ALT_F10,		"\033[21;3~")
	k(CTRL_F10,     "\033[21;5~")
	k(F11,			"\033[23~")
	k(SHIFT_F11,	"\033[23;2~")
	k(ALT_F11,		"\033[23;3~")
	k(CTRL_F11,     "\033[23;5~")
	k(F12,			"\033[24~")
	k(SHIFT_F12,	"\033[24;2~")
	k(ALT_F12,		"\033[24;3~")
	k(CTRL_F12,     "\033[24;5~")
	k(UNDEFINED_KEY,	"\033[25~")
	k(F14,			    "\033[26~")
	k(HELP_KEY,		    "\033[28~")
	k(DO_KEY,		    "\033[29~")
	k(F17,			    "\033[31~")
	k(F18,			    "\033[32~")
	k(F19,			    "\033[33~")
	k(F20,			    "\033[34~")
	k(FIND_KEY,		    "\033[1~")
	k(INSERT_KEY,		"\033[2~")
	k(REMOVE_KEY,		"\033[3~")
	k(UNDEFINED_KEY,	"\033[4~")
	k(PAGE_UP,		    "\033[5~")
	k(PAGE_DOWN,		"\033[6~")
	k(CTRL_FIND_KEY,	"\033[1;5~")
	k(CTRL_INSERT_KEY,	"\033[2;5~")
	k(CTRL_REMOVE_KEY,	"\033[3;5~")
	k(UNDEFINED_KEY,	"\033[4;5~")
	k(CTRL_PAGE_UP,		"\033[5;5~")
	k(CTRL_PAGE_DOWN,	"\033[6;5~")
	k(ALT_FIND_KEY,		"\033[1;3~")
	k(ALT_INSERT_KEY,	"\033[2;3~")
	k(ALT_REMOVE_KEY,	"\033[3;3~")
	k(UNDEFINED_KEY,	"\033[4;3~")
	k(ALT_PAGE_UP,		"\033[5;3~")
	k(ALT_PAGE_DOWN,	"\033[6;3~")
	k(UNDEFINED_KEY,	"\033[37~")
	k(UNDEFINED_KEY,	"\033[38~")
	k(UNDEFINED_KEY,	"\033[39~")
	k(MOUSE_KEY,	"\033[<#;#;#M")
	k(MOUSE_KEY,	"\033[<#;#;##M")
	k(MOUSE_KEY,	"\033[<#;#;###M")
	k(MOUSE_KEY,	"\033[<#;##;#M")
	k(MOUSE_KEY,	"\033[<#;##;##M")
	k(MOUSE_KEY,	"\033[<#;##;###M")
	k(MOUSE_KEY,	"\033[<#;###;#M")
	k(MOUSE_KEY,	"\033[<#;###;##M")
	k(MOUSE_KEY,	"\033[<#;###;###M")
	k(MOUSE_KEY,	"\033[<##;#;#M")
	k(MOUSE_KEY,	"\033[<##;#;##M")
	k(MOUSE_KEY,	"\033[<##;#;###M")
	k(MOUSE_KEY,	"\033[<##;##;#M")
	k(MOUSE_KEY,	"\033[<##;##;##M")
	k(MOUSE_KEY,	"\033[<##;##;###M")
	k(MOUSE_KEY,	"\033[<##;###;#M")
	k(MOUSE_KEY,	"\033[<##;###;##M")
	k(MOUSE_KEY,	"\033[<##;###;###M")
	k(MOUSE_KEY,	"\033[<#;#;#m")
	k(MOUSE_KEY,	"\033[<#;#;##m")
	k(MOUSE_KEY,	"\033[<#;#;###m")
	k(MOUSE_KEY,	"\033[<#;##;#m")
	k(MOUSE_KEY,	"\033[<#;##;##m")
	k(MOUSE_KEY,	"\033[<#;##;###m")
	k(MOUSE_KEY,	"\033[<#;###;#m")
	k(MOUSE_KEY,	"\033[<#;###;##m")
	k(MOUSE_KEY,	"\033[<#;###;###m")
	k(MOUSE_KEY,	"\033[<##;#;#m")
	k(MOUSE_KEY,	"\033[<##;#;##m")
	k(MOUSE_KEY,	"\033[<##;#;###m")
	k(MOUSE_KEY,	"\033[<##;##;#m")
	k(MOUSE_KEY,	"\033[<##;##;##m")
	k(MOUSE_KEY,	"\033[<##;##;###m")
	k(MOUSE_KEY,	"\033[<##;###;#m")
	k(MOUSE_KEY,	"\033[<##;###;##m")
	k(MOUSE_KEY,	"\033[<##;###;###m")
	k(TTY_KEY,	    "\033[?#;#c")
	k(TTY_KEY,	    "\033[?##;#;#c")
	k(TTY_KEY,	    "\033[?#;#;##;##;##;##;##:##:##c")
	k(TTY_KEY,	    "\033[?##;#;#;#;#;##;##;##;##;##;##;##c")
	k(TTY_KEY,	    "\033[?##;#;#;#;#;##;##;##;##;##;##;##c")
	k(LAST_KEY,	NULL)
};

#undef c
#undef k
#undef m
#undef n
#undef l

static int number_of_key_sequences = 0;
static int key_init_done = 0;

static void key_ensure_init()
{
	if ( key_init_done ) return;
	key_init_done = 1;
	number_of_key_sequences = 0;
	while ( key_sequences[number_of_key_sequences].value != LAST_KEY )
		number_of_key_sequences++;
}

int key_sequence_count()
{
	key_ensure_init();
	return( number_of_key_sequences );
}

char * key_sequence_name(int i)
{
	key_ensure_init();
	if ( i >= 0 && i < number_of_key_sequences )
		return( key_sequences[i].name );
	return("");
}

key_sequence * key_sequence_get(int i)
{
	key_ensure_init();
	if ( i >= 0 && i < number_of_key_sequences ) return( &key_sequences[i] );
	return(NULL);
}

char * key_sequence_name_by_value(int v)
{
	char tmp[64];
	int i=0;
	key_ensure_init();
	if ( v < 0 || v > number_of_key_sequences ) return("none");
	if ( key_sequences[v].value == v ) return( key_sequences[v].name );
	for ( i = 0; i < number_of_key_sequences; i++ )
		if ( key_sequences[i].value == v ) return( key_sequences[i].name );
	sprintf(tmp,"none %d/%d value=%d",v,number_of_key_sequences,key_sequences[v].value);
	return(strdup(tmp));
	return("none");
}

void key_sequence_print()
{
	int i=-1;
	key_ensure_init();
	while ( key_sequences[++i].name )
		printf("%s %d %d %s\n",__FUNCTION__,i,key_sequences[i].value,key_sequences[i].name);
}

/* ========================================================================== *
 *  _    ___ _____   __                                                       *
 * | |  |_ _| _ ) \ / /                                                      *
 * | |__ | || _ \\ V /                                                        *
 * |____|___|___/ \_/                                                         *
 *                                                                            *
 * ========================================================================== */

static void vt_nop() { }

#define c(n)	#n
#define v(n,s)	{ n,c(n),s,vt_nop },
#define m(n,s)	{ n,s,"X",vt_nop  },
#define n(n,s,p){ n,s,p,vt_nop },
#define l(n,s)	{ n,s,s,vt_nop },

static vt_sequence vt_sequences[] = {

////////////////////////////////// Same as libk 
/*
ASCII HEXADECIMAL
=================
            
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
 --------------------------------------------------------------------
 00 |NUL|SOH|STX|ETX|EOT|ENQ|ACK|BEL| BS|TAB| NL| VT| FF| CR| SO| SI|
 10 |DLE|DC1|DC2|DC3|DC4|NAK|SYN|ETB|CAN| EM|SUB|ESC| FS| GS| RS| US|
 20 | SP| ! | " | # | $ | % | & | ' | ( | ) | * | + | , | - | . | / |
 30 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | : | ; | < | = | > | ? |  
 40 | @ | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O |
 50 | P | Q | R | S | T | U | V | W | X | Y | Z | [ | \ | ] | ^ | _ |
 60 | ` | a | b | c | d | e | f | g | h | i | j | k | l | m | n | o |
 70 | p | q | r | s | t | u | v | w | x | y | z | { | | | } | ~ |DEL|
*/
        n(       0      ,"Null                  (NUL)   @",	"\x00" )
        n(       1      ,"Start Heading         (SOH)   A",	"\x01" )
        n(       2      ,"Start of Text         (STX)   B",	"\x02" )
        n(       3      ,"End of Text           (EOT)   C",	"\x03" )
        n(       4      ,"End Transmit          (EOT)   D",	"\x04" )
        n(       5      ,"Enquiry               (ENQ)   E",	"\x05" )
        n(       6      ,"Acknowledge           (ACK)   F",	"\x06" )
        n(       7      ,"Bell                  (BEL)   G",	"\x07" )
        n(       8      ,"Back Space            (BS)    H",	"\x08" )
        n(       9      ,"Horizontal Tab        (HT)    I",	"\x09" )
        n(      10      ,"Line Feed             (LF)    J",	"\x0A" )
        n(      11      ,"Vertical Tab          (VT)    K",	"\x0B" )
        n(      12      ,"Form Feed             (FF)    L",	"\x0C" )
        n(      13      ,"Carriage Return       (CR)    M",	"\x0D" )
        n(      14      ,"Shift Out             (SO)    N",	"\x0E" )
        n(      15      ,"Shift In              (SI)    O",	"\x0F" )
        n(      16      ,"Device Link Esc       (DLE)   P",	"\x10" )
        n(      17      ,"Device Control 1 XON  (DC1)   Q",	"\x11" )
        n(      18      ,"Device Control 2      (DC2)   R",	"\x12" )
        n(      19      ,"Device Control 3 XOFF (DC3)   S",	"\x13" )
        n(      20      ,"Device Control 4      (DC4)   T",	"\x14" )
        n(      21      ,"Negative Ack          (NAK)   U",	"\x15" )
        n(      22      ,"Synchronous Idle      (SYN)   V",	"\x16" )
        n(      23      ,"End Transmit Block    (ETB    W",	"\x17" )
        n(      24      ,"Cancel                (CAN)   X",	"\x18" )
        n(      25      ,"End Medium            (EM     Y",	"\x19" )
        n(      26      ,"Substitute            (SUB    Z",	"\x1A" )
        n(      27      ,"Escape                (ESC)   [",	"\x1B" )
        n(      28      ,"Cursor Right          (FS)    /",	"\x1C" )
        n(      29      ,"Cursor Left           (GS)    ]",	"\x1D" )
        n(      30      ,"Cursor Up             (RS)    ^",	"\x1E" )
	n(	31      ,"Cursor Down           (US)    -",	"\x1F" )

/*
ASCII DECIMAL
=============

            | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
         --------------------------------------------
         00 |NUL|SOH|STX|ETX|EOT|ENQ|ACK|BEL| BS|TAB|
         10 | NL| VT| FF| CR| SO| SI|DLE|DC1|DC2|DC3|
         20 |DC4|NAK|SYN|ETB|CAN| EM|SUB|ESC| FS| GS|
         30 | RS| US| SP| ! | " | # | $ | % | & | ' |
         40 | ( | ) | * | + | , | - | . | / | 0 | 1 |
         50 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | : | ; |
         60 | < | = | > | ? | @ | A | B | C | D | E |
         70 | F | G | H | I | J | K | L | M | N | O |
         80 | P | Q | R | S | T | U | V | W | X | Y |
         90 | Z | [ | \ | ] | ^ | _ | ` | a | b | c |
        100 | d | e | f | g | h | i | j | k | l | m |
        110 | n | o | p | q | r | s | t | u | v | w |
        120 | x | y | z | { | | | } | ~ |DEL|
*/
	l( 32, " " )
	l( 33, "!" )
	l( 34, "\"" )
	l( 35, "#" )
	l( 36, "$" )
	l( 37, "%" )
	l( 38, "&" )
	l( 39, "'" )
	l( 40, "(" )
	l( 41, ")" )
	l( 42, "*" )
	l( 43, "+" )
	l( 44, "," )
	l( 45, "-" )
	l( 46, "." )
	l( 47, "/" )
	l( 48, "0" )
	l( 49, "1" )
	l( 50, "2" )
	l( 51, "3" )
	l( 52, "4" )
	l( 53, "5" )
	l( 54, "6" )
	l( 55, "7" )
	l( 56, "8" )
	l( 57, "9" )
	l( 58, ":" )
	l( 59, ";" )
	l( 60, "<" )
	l( 61, "=" )
	l( 62, ">" )
	l( 63, "?" )
	l( 64, "@" )
	l( 65, "A" ) l( 66, "B" ) l( 67, "C" ) l( 68, "D" ) l( 69, "E" ) l( 70, "F" )
	l( 71, "G" ) l( 72, "H" ) l( 73, "I" ) l( 74, "J" ) l( 75, "K" ) l( 76, "L" )
	l( 77, "M" ) l( 78, "N" ) l( 79, "O" ) l( 80, "P" ) l( 81, "Q" ) l( 82, "R" )
	l( 83, "S" ) l( 84, "T" ) l( 85, "U" ) l( 86, "V" ) l( 87, "W" ) l( 88, "X" )
	l( 89, "Y" ) l( 90, "Z" ) l( 91, "[" )
	l( 92, "\\" )
	l( 93, "]" )
	l( 94, "^" )
	l( 95, "_" )
	l( 96, "`" )
	l( 97, "a" ) l( 98, "b" ) l( 99, "c" ) l( 100, "d" ) l( 101, "e" ) l( 102, "f" )
	l( 103, "g" ) l( 104, "h" ) l( 105, "i" ) l( 106, "j" ) l( 107, "k" ) l( 108, "l" )
	l( 109, "m" ) l( 110, "n" ) l( 111, "o" ) l( 112, "p" ) l( 113, "q" ) l( 114, "r" )
	l( 115, "s" ) l( 116, "t" ) l( 117, "u" ) l( 118, "v" ) l( 119, "w" ) l( 120, "x" )
	l( 121, "y" ) l( 122, "z" ) l( 123, "{" )
	l( 124, "|" )
	l( 125, "}" )
	l( 126, "~" )

	n( 127, "#7F", "\x7F" )
	n( 128, "#80", "\x80" )
	n( 129, "#81", "\x81" )
	n( 130, "#82", "\x82" )
	n( 131, "#83", "\x83" )
	n( 132, "#84", "\x84" )
	n( 133, "#85", "\x85" )
	n( 134, "#86", "\x86" )
	n( 135, "#87", "\x87" )
	n( 136, "#88", "\x88" )
	n( 137, "#89", "\x89" )
	n( 138, "#8A", "\x8A" )
	n( 139, "#8B", "\x8B" )
	n( 140, "#8C", "\x8C" )
	n( 141, "#8D", "\x8D" )
	n( 142, "#8E", "\x8E" )
	n( 143, "#8F", "\x8F" )
	n( 144, "#90", "\x90" )
	n( 145, "#91", "\x91" )
	n( 146, "#92", "\x92" )
	n( 147, "#93", "\x93" )
	n( 148, "#94", "\x94" )
	n( 149, "#95", "\x95" )
	n( 150, "#96", "\x96" )
	n( 151, "#97", "\x97" )
	n( 152, "#98", "\x98" )
	n( 153, "#99", "\x99" )
	n( 154, "#9A", "\x9A" )
	n( 155, "#9B", "\x9B" )
	n( 156, "#9C", "\x9C" )
	n( 157, "#9D", "\x9D" )
	n( 158, "#9E", "\x9E" )
	n( 159, "#9F", "\x9F" )
	n( 160, "#A0", "\xA0" )
	n( 161, "#A1", "\xA1" )
	n( 162, "#A2", "\xA2" )
	n( 163, "#A3", "\xA3" )
	n( 164, "#A4", "\xA4" )
	n( 165, "#A5", "\xA5" )
	n( 166, "#A6", "\xA6" )
	n( 167, "#A7", "\xA7" )
	n( 168, "#A8", "\xA8" )
	n( 169, "#A9", "\xA9" )
	n( 170, "#AA", "\xAA" )
	n( 171, "#AB", "\xAB" )
	n( 172, "#AC", "\xAC" )
	n( 173, "#AD", "\xAD" )
	n( 174, "#AE", "\xAE" )
	n( 175, "#AF", "\xAF" )
	n( 176, "#B0", "\xB0" )
	n( 177, "#B1", "\xB1" )
	n( 178, "#B2", "\xB2" )
	n( 179, "#B3", "\xB3" )
	n( 180, "#B4", "\xB4" )
	n( 181, "#B5", "\xB5" )
	n( 182, "#B6", "\xB6" )
	n( 183, "#B7", "\xB7" )
	n( 184, "#B8", "\xB8" )
	n( 185, "#B9", "\xB9" )
	n( 186, "#BA", "\xBA" )
	n( 187, "#BB", "\xBB" )
	n( 188, "#BC", "\xBC" )
	n( 189, "#BD", "\xBD" )
	n( 190, "#BE", "\xBE" )
	n( 191, "#BF", "\xBF" )
	n( 192, "#C0", "\xC0" )
	n( 193, "#C1", "\xC1" )
	n( 194, "#C2", "\xC2" )
	n( 195, "#C3", "\xC3" )
	n( 196, "#C4", "\xC4" )
	n( 197, "#C5", "\xC5" )
	n( 198, "#C6", "\xC6" )
	n( 199, "#C7", "\xC7" )
	n( 200, "#C8", "\xC8" )
	n( 201, "#C9", "\xC9" )
	n( 202, "#CA", "\xCA" )
	n( 203, "#CB", "\xCB" )
	n( 204, "#CC", "\xCC" )
	n( 205, "#CD", "\xCD" )
	n( 206, "#CE", "\xCE" )
	n( 207, "#CF", "\xCF" )
	n( 208, "#D0", "\xD0" )
	n( 209, "#D1", "\xD1" )
	n( 210, "#D2", "\xD2" )
	n( 211, "#D3", "\xD3" )
	n( 212, "#D4", "\xD4" )
	n( 213, "#D5", "\xD5" )
	n( 214, "#D6", "\xD6" )
	n( 215, "#D7", "\xD7" )
	n( 216, "#D8", "\xD8" )
	n( 217, "#D9", "\xD9" )
	n( 218, "#DA", "\xDA" )
	n( 219, "#DB", "\xDB" )
	n( 220, "#DC", "\xDC" )
	n( 221, "#DD", "\xDD" )
	n( 222, "#DE", "\xDE" )
	n( 223, "#DF", "\xDF" )
	n( 224, "#E0", "\xE0" )
	n( 225, "#E1", "\xE1" )
	n( 226, "#E2", "\xE2" )
	n( 227, "#E3", "\xE3" )
	n( 228, "#E4", "\xE4" )
	n( 229, "#E5", "\xE5" )
	n( 230, "#E6", "\xE6" )
	n( 231, "#E7", "\xE7" )
	n( 232, "#E8", "\xE8" )
	n( 233, "#E9", "\xE9" )
	n( 234, "#EA", "\xEA" )
	n( 235, "#EB", "\xEB" )
	n( 236, "#EC", "\xEC" )
	n( 237, "#ED", "\xED" )
	n( 238, "#EE", "\xEE" )
	n( 239, "#EF", "\xEF" )
	n( 240, "#F0", "\xF0" )
	n( 241, "#F1", "\xF1" )
	n( 242, "#F2", "\xF2" )
	n( 243, "#F3", "\xF3" )
	n( 244, "#F4", "\xF4" )
	n( 245, "#F5", "\xF5" )
	n( 246, "#F6", "\xF6" )
	n( 247, "#F7", "\xF7" )
	n( 248, "#F8", "\xF8" )
	n( 249, "#F9", "\xF9" )
	n( 250, "#FA", "\xFA" )
	n( 251, "#FB", "\xFB" )
	n( 252, "#FC", "\xFC" )
	n( 253, "#FD", "\xFD" )
	n( 254, "#FE", "\xFE" )
	n( 255, "#FF", "\xFF" )

	v(VT_UP,	"\033[#A")
	v(VT_UP,	"\033[##A")
	v(VT_DOWN,	"\033[#B")
	v(VT_DOWN,	"\033[##B")
	v(VT_RIGHT,	"\033[#C")
	v(VT_RIGHT,	"\033[##C")
	v(VT_LEFT,	"\033[#D")
	v(VT_LEFT,	"\033[##D")
	v(VT_HOME,	"\033[H")
	v(VT_ERASE,	"\033[#J")
	v(VT_ERASE,	"\033[J")
	v(VT_ERASE2SOL,	"\033[#J")
	v(VT_ERASE,	"\033[K")	// Fix
	v(VT_ERASE,	"\033]R")	// Fix
	v(VT_RESET,	"\033[m")
	v(VT_CURSAVE,   "\033[s")
	v(VT_CURRESTORE,"\033[u")
/*
	v(VT_RESET,	"\033[0m")
	v(VT_BOLD,	"\033[1m")
	v(VT_FAINT,	"\033[2m")
	v(VT_ITALIC,	"\033[3m")
	v(VT_UNDERLINE,	"\033[4m")
	v(VT_BLINKING,	"\033[5m")
	v(VT_ATTR,	"\033[6m")
	v(VT_INVERSE,	"\033[7m")
	v(VT_HIDDEN,	"\033[8m")
	v(VT_STRIKE,	"\033[9m")
*/

	v(VT_ATTR,	"\033[#m")
	v(VT_ATTR,	"\033[#;m")
	v(VT_ATTR,	"\033[#;#m")
	v(VT_ATTR,	"\033[#;##m")

	v(VT_ATTR,	"\033[##m")
	v(VT_ATTR,	"\033[##;m")
	v(VT_ATTR,	"\033[##;#m")
	v(VT_ATTR,	"\033[##;##m")
	v(VT_ATTR,	"\033[#;##;##m")
	v(VT_ATTR,	"\033[##;##;##m")

	v(VT_ATTR,	"\033[#C")
	v(VT_ATTR,	"\033[##C")

	v(VT_ATTR,	"\033[#H")
	v(VT_ATTR,	"\033[#;H")
	v(VT_ATTR,	"\033[#;#H")
	v(VT_ATTR,	"\033[#;##H")
	v(VT_ATTR,	"\033[##;#H")
	v(VT_ATTR,	"\033[##;##H")

	v(VT_ATTR,	"\033[#I")
	v(VT_ATTR,	"\033[#;I")
	v(VT_ATTR,	"\033[#;#I")
	v(VT_ATTR,	"\033[#;##I")
	v(VT_ATTR,	"\033[##;#I")
	v(VT_ATTR,	"\033[##;##I")

	v(VT_ATTR,	"\033[#;#;#m")
	v(VT_ATTR,	"\033[#;#;##m")
	v(VT_ATTR,	"\033[#;##;#m")
	v(VT_ATTR,	"\033[#;##;##m")

	v(VT_ATTR,	"\033[#;#;#;#m")
	v(VT_ATTR,	"\033[#;#;#;##m")
	v(VT_ATTR,	"\033[#;#;##;#m")
	v(VT_ATTR,	"\033[#;#;##;##m")

	v(VT_ATTR,	"\033[#;##;#;#m")
	v(VT_ATTR,	"\033[#;##;#;##m")
	v(VT_ATTR,	"\033[#;##;##;#m")
	v(VT_ATTR,	"\033[#;##;##;##m")

	v(VT_ATTR,	"\033[##;#;##m")

	v(VT_ATTR,	"\033[##;##;#;#m")
	v(VT_ATTR,	"\033[##;##;#;##m")
	v(VT_ATTR,	"\033[##;##;##;#m")
	v(VT_ATTR,	"\033[##;##;##;##m")

	v(LAST_VT,	NULL )
/*
*/

};

#undef c
#undef v
#undef m
#undef n
#undef l

static int number_of_vt_sequences = 0;
static int vt_init_done = 0;

static void vt_ensure_init()
{
	if ( vt_init_done ) return;
	vt_init_done = 1;
	number_of_vt_sequences = 0;
	while ( vt_sequences[number_of_vt_sequences].value != LAST_VT )
		number_of_vt_sequences++;
}

int vt_sequence_count()
{
	vt_ensure_init();
	return( number_of_vt_sequences );
}

char * vt_sequence_name(int i)
{
	vt_ensure_init();
	if ( i >= 0 && i < number_of_vt_sequences )
		return( vt_sequences[i].name );
	return("");
}

vt_sequence * vt_sequence_get(int i)
{
	vt_ensure_init();
	if ( i >= 0 && i < number_of_vt_sequences ) return( &vt_sequences[i] );
	return(NULL);
}

char * vt_sequence_name_by_value(int v)
{
	char tmp[64];
	int i=0;
	vt_ensure_init();
	if ( v < 0 || v > number_of_vt_sequences ) return("none");
	if ( vt_sequences[v].value == v ) return( vt_sequences[v].name );
	for ( i = 0; i < number_of_vt_sequences; i++ ) 
		if ( vt_sequences[i].value == v ) return( vt_sequences[i].name );
	sprintf(tmp,"none %d/%d value=%d",v,number_of_vt_sequences,vt_sequences[v].value);
	return(strdup(tmp));
	return("none");
}

void vt_sequence_print()
{
	int i=-1;
	vt_ensure_init();
	while ( vt_sequences[++i].name ) 
		printf("%s %d %d %s\n",__FUNCTION__,i,vt_sequences[i].value,vt_sequences[i].name);
}

/* ========================================================================== *
 *  _    ___ ___ __  __ ___  ___                                              *
 * | |  |_ _| _ )  \/  / __|/ __|                                             *
 * | |__ | || _ \ |\/| \__ \ (_ |                                              *
 * |____|___|___/_|  |_|___/\___|                                              *
 *                                                                            *
 * ========================================================================== */

/* --- mouse.c (inlined) --- */

// Lookup table
static const char *MouseEventNames[] = {
    [0x00] = "MOUSE_LEFT_BUTTON_PRESSED",
    [0x01] = "MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x02] = "MOUSE_RIGHT_BUTTON_PRESSED",
    [0x03] = "MOUSE_NONE_BUTTON_PRESSED",
    [0x04] = "SHIFTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x05] = "SHIFTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x06] = "SHIFTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x07] = "SHIFTKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x08] = "ALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x09] = "ALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x0A] = "ALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x0B] = "ALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x0C] = "SHIFTALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x0D] = "SHIFTALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x0E] = "SHIFTALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x0F] = "SHIFTALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x10] = "CTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x11] = "CTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x12] = "CTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x13] = "CTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x14] = "SHIFTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x15] = "SHIFTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x16] = "SHIFTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x17] = "SHIFTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x18] = "ALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x19] = "ALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x1A] = "ALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x1B] = "ALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x1C] = "SHIFTALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x1D] = "SHIFTALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x1E] = "SHIFTALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x1F] = "SHIFTALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x20] = "MOTM_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x21] = "MOTM_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x22] = "MOTM_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x23] = "MOUSE_ON_THE_MOVE", /*MOTM_AND_MOUSE_NONE_BUTTON_PRESSED",*/
    [0x24] = "MOTM_AND_SHIFTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x25] = "MOTM_AND_SHIFTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x26] = "MOTM_AND_SHIFTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x27] = "MOTM_AND_SHIFTKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x28] = "MOTM_AND_ALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x29] = "MOTM_AND_ALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x2A] = "MOTM_AND_ALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x2B] = "MOTM_AND_ALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x2C] = "MOTM_AND_SHIFTALTKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x2D] = "MOTM_AND_SHIFTALTKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x2E] = "MOTM_AND_SHIFTALTKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x2F] = "MOTM_AND_SHIFTALTKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x30] = "MOTM_AND_CTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x31] = "MOTM_AND_CTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x32] = "MOTM_AND_CTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x33] = "MOTM_AND_CTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x34] = "MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x35] = "MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x36] = "MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x37] = "MOTM_AND_SHIFTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x38] = "MOTM_AND_ALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x39] = "MOTM_AND_ALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x3A] = "MOTM_AND_ALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x3B] = "MOTM_AND_ALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x3C] = "MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_LEFT_BUTTON_PRESSED",
    [0x3D] = "MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_MIDDLE_BUTTON_PRESSED",
    [0x3E] = "MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_RIGHT_BUTTON_PRESSED",
    [0x3F] = "MOTM_AND_SHIFTALTCTRLKEY_AND_MOUSE_NONE_BUTTON_PRESSED",
    [0x40] = "MOUSE_SCROLL_UP",
    [0x41] = "MOUSE_SCROLL_DOWN"
};

static int mouse_decoder(int n)
{
    return( MOUSE_LEFT_BUTTON_PRESSED + ( n & 0x7F ) );
}

const char *mouse_event_name(int n)
{
    if ( n > BEFORE_MOUSE_EVENTS && n < LAST_MOUSE_EVENT )
        return( MouseEventNames[n-MOUSE_LEFT_BUTTON_PRESSED] );
	
    return("NOT A MOUSE EVENT");
}

/* --- ansi.c (inlined) --- */

/*
           Klass      
         123456789 123456789 123456789 123456789 123456789 123456789
________|___ESC___|____[____|_#30-#3F_|_#20-#2F_|_#40-#7E_|____c____|____*____|
state 0 |    A1   |    A0   |    A0   |    A0   |    A0   |    A0   |    A0   |
state 1 |    A2   |    A3   |    A4   |    A4   |    A4   |    A4   |    A4   |
state 2 |    A2   |    A4   |    A5   |    A6   |    A4   |    A7   |    A4   |
state 3 |    A2   |    A4   |    A4   |    A6   |    A4   |    A7   |    A4   |

           Actions A0 - PassThru                                    return(0)
           Actions A1 - Queue ESC, State = 1                        return(1);
           Actions A2 - Purge Queue, Queue ESC, State = 1           return(3);
           Actions A3 - Queue [, State = 2                          return(1);
           Actions A4 - Purge Queue, State = 0                      return(2);
           Actions A5 - Queue c                                     return(1);
           Actions A6 - Queue c, State = 3                          return(1);
           Actions A7 - Discard Queue, which contains Terminal Info return(2);
*/
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
static char afsm[4][7] = {
    { A1,A0,A0,A0,A0,A0,A0 },
    { A2,A3,A4,A4,A4,A4,A4 },
    { A2,A4,A5,A6,A4,A7,A4 },
    { A2,A4,A4,A6,A4,A7,A4 }};
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7

static char aqb[128];
static int aqi=0;
static void aq(char c) {
    if ( aqi >= 0 && aqi < 127 ) 
           aqb[aqi++]=c;
    else
        fprintf(stderr,"Memory Overrun in aq()\n");
}
static void ap(char **p)
{
    aqb[aqi]='\0';
    aqi=0;
    *p = aqb;
}
static void ad(char c)
{
    aqb[aqi++]=c;
    //fprintf(stderr,"Terminal Sequence [%s]\n",sdump(aqb,aqi));
    aqi=0;
}

static int ansi(char c,char **p)
{
    static int state=0;
    int klass;

    *p = NULL;

    klass=6;
    if ( c == '\033' ) klass=0; else
    if ( c == '[' ) klass=1; else
    if ( c == 'c' ) klass=5; else
    if ( c >= 0x20 && c <= 0x2F ) klass=2; else
    if ( c >= 0x30 && c <= 0x3F ) klass=3; else
    if ( c >= 0x40 && c <= 0x7E ) klass=4; 

    //fprintf(stderr,"#%X state=%u klass=%u action=%u\n",c,state,klass,afsm[state][klass]);

    switch ( afsm[state][klass] ) {
        case 0:               state=0; return(0);  break;  // continue with current char(uc)
        case 1:        aq(c); state=1; return(1);  break;  // continue no action
        case 2: ap(p); aq(c); state=1; return(3);  break;  // purge the queue, but not current character
        case 3:        aq(c); state=2; return(1);  break;  // continue no action
        case 4: ap(p);        state=0; return(2);  break;  // purge the queue, and continue with uc
        case 5:        aq(c);          return(1);  break;  // continue no action
        case 6:        aq(c); state=3; return(1);  break;  // continue no action
        case 7: ad(c);        state=0; return(1);  break;  // continue no action
    }
    fprintf(stderr,"Error in ansi()\n");
    state=0;
    aqi=0;
    return(0);
}

/* --- libmsg.c (inlined) --- */

static message msg_pool[16];
static int message_index=0;
static int  message_counter;
static int  purge_countdown;
static message *pmessage=NULL;

static void set_event_name(message *pm,char *n)
{
	assert(pm);
	bzero(pm->event_name,sizeof(pm->event_name));
	strncpy(pm->event_name,n,sizeof(pm->event_name)-1);
}

////////////////////////////////////////////////////////////////

static void mm(int n)
{
	fprintf(stderr,"mm %d\n",n);
}

static void message_init_sequences()
{
	int i;
	key_sequence *pk;
	vt_sequence *pv;
	sequence *ps;

	verbose("%s()",__FUNCTION__);

	i=0;
	while ( (pk=key_sequence_get(i++) ) )
		sequence_add(pk->value,pk->name,pk->seq,mm);

	while ( (pv=vt_sequence_get(i++) ) )
		sequence_add(pv->value,pv->name,pv->seq,mm);

	i=0;
	while ( (ps=sequence_get(i)) ) {
		verbose("Sequence %d %d %s",i,ps->value,ps->name);
		//if ( strlen(ps->seq) > 1 ) pattern_add(ps->seq,i);
		if ( strcmp(ps->seq,"#")==0 ) fsm_add_sequence("\\#",i);
		else fsm_add_sequence(ps->seq,i);
		i++;
	}

	//fsm_print(); 
}
////////////////////////////////////////////////////////////////

static void message_reset()
{
	purge_countdown=0;
}

static void message_callback( char *p, int n )
{
	sequence *ps;
	int a,b,c,r;
	char e;
	//fprintf(stderr,"%s [%s] %d\n",__FUNCTION__,sdump(p,strlen(p)+1),n);
	//if ( counter++ > 100 ) exit(0);
	ps=sequence_get(n);
	if ( ! ps ) {
		fprintf(stderr,"Unknown Sequence");
		return;
	}
	//fprintf(stderr,"%s %d %d %s\n",__FUNCTION__,n,ps->value,ps->name);
	pmessage=&msg_pool[message_index];
	pmessage->index=message_index++;
	pmessage->counter=message_counter++;
	message_index%=16;
	if ( ps->value==MOUSE_KEY ) {
		b=r=c=0;
		sscanf(p,"%c[<%d;%d;%dM",&e,&b,&c,&r);
		pmessage->type=MOUSE_MESSAGE;
		pmessage->parameter.mouse.character = mouse_decoder(b);
		pmessage->parameter.mouse.button = b;
		pmessage->parameter.mouse.row = r;
		pmessage->parameter.mouse.column = c;
		set_event_name(pmessage,"MOUSE");
	}
	else
	if ( ps->value==TTY_KEY ) {
		sscanf(p,"%c[?%d;%d;%dc",&e,&a,&b,&c);
		pmessage->type=TTY_MESSAGE;
		pmessage->parameter.tty.a=a;
		pmessage->parameter.tty.b=b;
		pmessage->parameter.tty.c=c;
		set_event_name(pmessage,"TTY");
	}
	else {
		pmessage->type=KEY_MESSAGE;
		pmessage->parameter.character = ps->value;
		set_event_name(pmessage,"KEY");
	}
}

static int msg_init_done = 0;

static void msg_ensure_init()
{
	if ( msg_init_done ) return;
	msg_init_done = 1;
	message_reset();
	message_counter=0;
}

void message_init()
{
	verbose("%s()",__FUNCTION__);
	msg_ensure_init();
	message_init_sequences();
	if ( is_verbose() ) sequence_print();
	//pattern_print();
	event_init(1);
	fsm_setcallback(message_callback);
}

static void message_buffer_purge()
{
	verbose("%s",__FUNCTION__);
	purge_countdown=0;
	fsm_action(-1);
}

message * message_get()
{
    char *p;
    int cc;
	event *pe;

	pmessage=NULL;

	// ToDo: Complete Purge if Rquired
	while ( (pe = event_wait()) ) {
		switch (pe->type) {
			case NO_EVENT:
				break;
			case TIME_EVENT:
				if ( purge_countdown ) {
					if ( --purge_countdown < 1 ) {
						purge_countdown=0;
						message_buffer_purge();
					}
				}
				pmessage=&msg_pool[message_index];
				pmessage->index=message_index++;
				pmessage->counter=message_counter++;
				message_index%=16;
				pmessage->type=TIME_MESSAGE;
				set_event_name(pmessage,"TIMER");
				break;
			case KEY_EVENT:
				verbose("%s %X",__FUNCTION__);
                if ( 1 == 1 ) {
                    // ANSI Interceptor, currently only for the terminal
                    // response \033[...c but should be expanded
                    // since the fsm is a bit strict on the patterns
                    // cc=0 nothing, cc=1 continuation cc=2 complete, purge(empty for terminal seq)
                    cc = ansi(pe->parameter.character,&p);
                    if ( cc ) {
                        if ( cc == 1 ) break;
                        if ( p ) while ( *p ) fsm_action(*p++);
                        if ( cc == 3 ) break;
                    }
                }
				fsm_action(pe->parameter.character);
				purge_countdown=2;
				break;
			case SIG_EVENT:
				pmessage=&msg_pool[message_index];
				pmessage->index=message_index++;
				pmessage->counter=message_counter++;
				message_index%=16;
				pmessage->type=SIG_MESSAGE;
				pmessage->parameter.signal=pe->parameter.signal;
				set_event_name(pmessage,"SIGNAL");
				break;
			case EOF_EVENT:
				pmessage=&msg_pool[message_index];
				pmessage->index=message_index++;
				pmessage->counter=message_counter++;
				message_index%=16;
				pmessage->type=EOF_MESSAGE;
				pmessage->parameter.signal=pe->parameter.signal;
				set_event_name(pmessage,"EOF");
				break;
			default:
				fprintf(stderr,"Unknown Event %d\n",pe->type);
				exit(1);
				break;
		}
		if ( pmessage ) return(pmessage);
	}
	error("Missing EOF Event");
	return(NULL);
}

/* libmsg wraps libevent wraps libtty */
void message_mouse_on()
{
	event_mouse_on();
}

void message_mouse_off()
{
	event_mouse_off();
}

// Provide a Common Message Display
void message_display(message *pm,char *note)
{
		int c;
		char *p;
		if ( ! note ) note="|||";
		switch (pm->type) {
			case TIME_MESSAGE:
				fprintf(stderr,"%6.6s\n",pm->event_name);
				break;
			case MOUSE_MESSAGE:
				fprintf(stderr,"%6.6s %4.4s #%2.2s %3.3s %3.3s %-44.44s %s %X\n",\
					pm->event_name,\
					number(pm->parameter.mouse.character),
					number(pm->parameter.mouse.button),
					number(pm->parameter.mouse.row),
					number(pm->parameter.mouse.column),
					mouse_event_name(pm->parameter.mouse.character),
					note,pm->parameter.mouse.button);
				break;
			case TTY_MESSAGE:
				fprintf(stderr,"%6.6s %d %d %d %s\n",\
					pm->event_name,\
					pm->parameter.tty.a,\
					pm->parameter.tty.b,\
					pm->parameter.tty.c,note);
				break;
			case KEY_MESSAGE:
				c=pm->parameter.character;
				p=key_sequence_name_by_value(c);
				fprintf(stderr,"%6.6s %4.4s             %-44.44s %s\n",\
					pm->event_name,\
					number(pm->parameter.character),
					p?p:"Unknown",
					note);
				break;
			case SIG_MESSAGE:
				fprintf(stderr,"%6.6s %4.4s\n",pm->event_name,
					number(pm->parameter.signal));
				break;
			case EOF_MESSAGE:
				fprintf(stderr,"%6.6s %4.4s\n",pm->event_name,
					number(pm->parameter.fd));
				break;
			default:
				fprintf(stderr,"Unknown Message\n");
				break;
		}
}

/* ========================================================================== *
 *  _    ___ ___ _    _    ___ ___ _____                                      *
 * | |  |_ _| _ ) |  | |  |_ _/ __|_   _|                                    *
 * | |__ | || _ \ |__| |__ | |\__ \ | |                                      *
 * |____|___|___/____|____|___|___/ |_|                                       *
 *                                                                            *
 * ========================================================================== */

static void *lmalloc( int x )
{
	void *v;
	v = malloc(x);
	if ( ! v ) fatal("No Memory");
	bzero(v,x);
	return(v);
}

static void lfree( void *v )
{
	if ( v ) free(v);
}

LLIST *llnext( LLIST *h )
{
	return( ( h ) ? ((LLIST *)h) -> next     : NULL );
}

LLIST *llprevious ( LLIST *h )
{
	return( ( h ) ? ((LLIST *)h) -> previous : NULL );
}

LLIST * llinsert( LLIST **s, LLIST *h )
{
	h = (LLIST *)memcpy( lmalloc( sizeof(LLIST) ),h,sizeof(LLIST) );
	h -> next = h->previous = NULL;
	if ( *s ) {
		h -> previous = (*s)->previous;
		if ( (*s)->previous ) (*s)->previous->next = h;
		(*s)->previous = h;
		h -> next = *s;
	}
	else {
		*s = h;
	}

	return( h );
}

LLIST * llappend( LLIST **s, LLIST *h )
{
	h = (LLIST *)memcpy( lmalloc( sizeof(LLIST) ),h,sizeof(LLIST) );
	h -> next = h->previous = NULL;

	if ( *s ) {
		h -> next = (*s) -> next;
		if ( (*s)->next ) (*s)->next->previous = h;
		(*s)->next = h;
		h -> previous = *s;
	}
	else {
		*s = h;
	}

	return( h );
}

LLIST * llend( LLIST **s, LLIST *h )
{
	LLIST **p;
	p=s;
	if ( *p ) 
		while ( (*p)->next ) p=&((*p)->next);
	return( llappend(p,h) );
}

LLIST * llremove( LLIST **s, LLIST *h )
{
	if ( ! h ) fatal( "Invalid Pointer passed to %s",__FUNCTION__ );

	if ( h -> next ) h -> next -> previous = h -> previous;
	if ( h -> previous ) h -> previous -> next = h -> next;
	if ( *s == h ) *s = NULL;
	lfree( h );
	return(*s);
}

LLIST * lllast( LLIST *h )
{
	if ( ! h ) return(NULL);
	while ( h->next ) h = h->next;
	return(h);
}

LLIST * llfirst( LLIST *h )
{
	if ( ! h ) return(NULL);
	while ( h->previous ) h = h->previous;
	return(h);
}

/* ========================================================================== *
 *  _    ___ ___ ___                                                          *
 * | |  |_ _| _ ) _ \                                                        *
 * | |__ | || _ \  _/                                                        *
 * |____|___|___/_|                                                           *
 *                                                                            *
 * ========================================================================== */

typedef struct pattern {
	char	*s;
	int	v;
	} pattern;

static pattern *patterns[1024]={};	// ToDo: Fix 1024 Hard-Coded Limit
static int pattern_count=0;
static int pattern_sorted=0;

static int pattern_compare( const void *a, const void *b )
{
	pattern *p1,*p2;
	p1=*(pattern **)a;
	p2=*(pattern **)b;
	return( strlen(p2->s) - strlen(p1->s) );
}

static void pattern_sort()
{
	if ( pattern_sorted==0 )
		qsort(patterns,pattern_count,sizeof(pattern **),pattern_compare);
	pattern_sorted=1;
}

static int pattern_strcmp(char *a,char *b)
{
	int i=-1;
	while ( *a ) {
		if ( *a == *b || *b == '.' ) {
			i=0;
			a++;
			b++;
		}
		else {
			break;
		}
	}
	if (  *a &&  *b ) return(-1);
	if (  *a && !*b ) return(-1);
	if ( !*a &&  *b ) return(i);
	if ( !*a && !*b ) return(1);
	return(1);
}

int pattern_find( char *p )
{
	int i,cc,rc=-1;
	if ( !p ) return(-1);
	pattern_sort();
	for ( i=0; patterns[i]; i++ )  {
		if ( (cc=pattern_strcmp(p,patterns[i]->s)) > 0 )
			return(patterns[i]->v);
		if ( cc == 0 ) rc=0;
	}
	return(rc);
}

int pattern_add(char *p,int v)
{
	int i;
	i=pattern_count++;
	patterns[i]=(pattern *)malloc(sizeof(pattern));
	patterns[i]->s=strdup(p);
	patterns[i]->v=v;
	pattern_sorted=0;
	return(0);
}

void pattern_print()
{
	int i;
	pattern_sort();
	for ( i=0; patterns[i]; i++ )
		printf("%d %d %s\n",i,patterns[i]->v,patterns[i]->s);
}

/* ========================================================================== *
 *  _    ___ ___ ___ ___ ___ ___ _____ _   _                                  *
 * | |  |_ _| _ )|   \_ _/ __|_ _|_   _/_\ | |                               *
 * | |__ | || _ \| |) | | (_ || |  | |/ _ \| |__                              *
 * |____|___|___/|___/___\___|___| |_/_/ \_\____|                              *
 *                                                                            *
 * ========================================================================== */

/* ---- digital_fixup ---- */

word * digital_fixup( byte *s, int length )
{
	static word *pattern = NULL;
	word *wp;
	byte *pe = s + length;

	debug( "%s %i", __FUNCTION__, length );

	if ( pattern ) free(pattern);
	wp = pattern = (word *)malloc( (strlen((char *)s)+3) << 1 );

	while ( s < pe )
	{
		*wp = *s;

		if ( *s == '?' )  *wp = DIGITAL_ANY;
		else
		if ( *s == '*' )  *wp = DIGITAL_MANY;
		else
		if ( *s == '\\' ) *wp = *++s;

		s++;
		wp++;
	}

	*wp = -1;

	return(pattern);
}

/* ---- print_digital_character ---- */

void print_digital_character( word w )
{
	byte *p;
	byte b[64];

	p = b;

	if ( w == 0 ) return;

	if ( w >= ' ' && w <= '~' ) sprintf((char *)b,"%c",w);
	else
	if ( w < 255 ) sprintf((char *)b,"[%02X]",w);
	else
	if ( w == DIGITAL_MANY ) p = (byte *)"[*]";
	else
	if ( w == DIGITAL_ANY  ) p = (byte *)"[?]";
	else
	if ( w == (word)-1 ) p = (byte *)"[END]";
	else
		fatal("Invalid Digital Tree Character");

	while ( *p ) putchar(*p++);
}

/* ---- print_digital_tree_path ---- */

void print_digital_tree_path( DNODE *p )
{
	if ( ! p ) return;
	print_digital_tree_path( p -> parent );
	putchar(p->c);
}

/* ---- digital_add ---- */

static void digital_nop( void *t, void *x )
{
	DNODE *pn = (DNODE *)x;

	if ( pn -> parent == NULL ) return;

	digital_nop( (DNODE *)t, pn -> parent );

	print_digital_character(pn->c);

	if ( pn == (DNODE *)t ) newline();
}

static DNODE * digital_create( DROOT *pr, word w )
{
	DNODE *pc,*pn;
	size_t z;
	int    i;

	pc = pr -> current;

	assert(pc);

	pc -> n++;

	z = sizeof(DNODE) + ( pc -> n * sizeof(DNODE *) );
	pn = (DNODE *)calloc( 1, z );
	memcpy( pn, pc, z - sizeof(DNODE *) );
	free( pc );
	pn -> index[ w ] = pn -> n;
	pn -> reference[ pn -> n ] = (DNODE *)calloc( 1, sizeof(DNODE) );
	pn -> reference[ pn -> n ] -> parent = pn;
	pn -> reference[ pn -> n ] -> c      = w;

	if ( pn -> parent )
	     pn -> parent -> reference[ pn -> parent -> index[ pn -> c ] ] = pn;
	else
	     pr->root = pn;

	for ( i = 1; i < DIGITAL_MAX; i++ )
	{
		if ( pn -> index[i] )
			pn -> reference[ pn -> index[ i ] ] -> parent = pn;
	}

	debug( "%s",__FUNCTION__);

	return( pn );
}

static void digital_add_recursive( DROOT *pr, word *wp )
{
	if ( *wp == (word)-1 ) return;

	debug( "%s [%X]",__FUNCTION__,*wp);

	if ( ! ( pr->current -> index[ *wp ] ) ) pr->current = digital_create( pr, *wp );

	pr->current = pr->current -> reference [ pr->current -> index [ *wp ] ];

	digital_add_recursive( pr, ++wp );
}

int digital_add_len( DTREE *pt, byte *s, int length, void (*f)( void *,void *), void *parameter )
{
	DROOT *pr;
	DNODE *pc;
	word *wp;

	if ( ! pt ) fatal("Invalid Reference to Digital Tree");

	if ( ! * pt ) *(DROOT **)pt = (DROOT *)calloc( 1, sizeof(DROOT) );

	pr = *((DROOT **)pt);

	debug_dump( "ADD",s,length);
	wp = digital_fixup(s,length);
	debug_dump( "FIXED",wp,length*2);

	if ( !wp ) return(1);
	length <<= 1;

	if ( ! pr->root ) pr->root = (DNODE *)calloc(1, sizeof(DNODE));

	pr->current = pr->root;

	digital_add_recursive( pr, wp );

	pc = pr->current;
	assert(pc);
	if ( pc->function ) return(-1);
	pc -> function = (f)?f:digital_nop;
	pc -> parameter = (f)?parameter:pc;

	debug( "%s EXIT",__FUNCTION__);

	return(0);
}

int digital_add( DTREE *pt, byte *s, void (*f)( void *,void *), void *parameter )
{
	debug(  "%s [%s]",__FUNCTION__,s);
	return (digital_add_len(pt,s,strlen((char *)s),f,parameter));
}

/* ---- digital_lookup ---- */

DNODE * digital_lookup( DROOT *pr, DNODE *pn, byte w )
{
	debug( "%s %i %i",__FUNCTION__,w,pr->deleting);

	assert(pr);
	assert(pn);

	if ( ! ( pn -> index[(int)w] ) )
	{
		if ( pn -> c == DIGITAL_MANY ) return(pn);

		if ( pn -> index[ DIGITAL_ANY ]  ) return(pn -> reference[ pn -> index[ DIGITAL_ANY ] ] );
		if ( pn -> index[ DIGITAL_MANY ] ) return(pn -> reference[ pn -> index[ DIGITAL_MANY ] ] );

		debug( "%s NOT Found",__FUNCTION__);
		return( NOT_FOUND );
	}

	pn = pn -> reference[ pn -> index[(int)w] ];

	if ( pn -> n == 0 )
	{
		debug( "%s Found c=%d deleting=%i",__FUNCTION__,pn->c,pr->deleting);
		if ( ! pr->deleting )
		{
			debug( "%s Calling Function, %p",__FUNCTION__,pn->parameter);
			pr->current = pn;
			(*(pn -> function))(pn,pn->parameter);
		}
		return(NULL);
	}

	debug( "%s Continue c=%d (%i)",__FUNCTION__,pn->c,pn->n);

	return(pn);
}

/* ---- digital_find ---- */

int digital_find( DTREE *pt, byte *s )
{
	DNODE *pn;
	DROOT *pr;
	word *wp;

	if ( ! pt ) return(-1);
	if ( ! * pt ) return(-1);

	pr = *((DROOT **)pt);

	if ( ! pr->root ) return(-1);

	pn = pr->root;

	wp = digital_fixup(s,strlen((char *)s));

	while ( *wp != (word)-1 )
	{
		pn = digital_lookup( pr, pn, *wp++ );

		debug("%s pn=#%p",__FUNCTION__,pn);

		if ( pn == NOT_FOUND ) return(-1);
		if ( pn == NULL ) {
			return(0);
		}
	}

	debug("%s pn=#%p function=#%p",__FUNCTION__,pn,pn->function);

	if ( pn -> function && *wp == (word)-1 )
	{
		(*(pn->function))(pn,pn -> parameter);
		return(0);
	}

	return( -1 );
}

/* ---- digital_delete ---- */

static int digital_delete_node( DROOT *pr, DNODE *pn, word *wp )
{
	int n;

	debug( "%s [%X]",__FUNCTION__, *wp );

	if ( pn == NOT_FOUND ) longjmp( pr->jump, -1 );

	if ( pn && *wp != (word)-1 )
	{
		if ( ! digital_delete_node( pr, digital_lookup( pr, pn, *wp ), wp + 1 ) )
		{
			pn -> index[ *wp ] = 0;
		}
	}
	else
	if (  pn && *wp != (word)-1  )
	{
		if (!(pn -> function))
			longjmp(pr->jump, -1);
		pn->function = NULL;
	}
	else
	if ( !pn &&  *wp != (word)-1 )
		longjmp( pr->jump, -1 );
	else
	{
		return(0);
		pn -> function = NULL;
		assert ( pn -> n != 0 );
	}

	n = pn -> n;

	if ( n == 0 && !(pn -> function))
	{
		if ( pn == pr->root ) pr->root = NULL;
		free(pn);
	}

	return( (pn -> function) ? 1 : n );
}

int digital_delete_len( DTREE *pt, byte *p, int length )
{
	DROOT *pr;
	word *wp;

	if ( ! pt ) return(-1);
	if ( ! * pt ) return(-1);

	pr = *((DROOT **)pt);

	if ( ! pr->root ) return(-1);

	if ( setjmp( pr->jump ) )
	{
		pr->deleting = 0;
		return(-1);
	}

	debug_dump( "DEL",p,length);
	wp = digital_fixup(p,length);
	debug_dump( "FIX",wp,length);
	if ( !wp ) return(1);

	length <<= 1;

	pr->deleting = 1;

	digital_delete_node( pr, pr->root, wp );
	pr->deleting = 0;
	pr->current = pr->root;
	pr->search = NULL;
	return(0);
}

int digital_delete ( DTREE *pt, byte *p )
{
	return( digital_delete_len ( pt, p, strlen((char *)p) ) );
}

/* ---- digital_print ---- */

static int digital_print_level=0, digital_print_found=0;

static void digital_ptree( DNODE *pn )
{
	int i,j;

	debug("%s",__FUNCTION__);

	if ( !pn ) return;

	if ( pn -> function )
	{
		newline();
		digital_print_found = 0;
	}

	++digital_print_level;

	for ( i = 1; i < DIGITAL_MAX; i++ )
	{
		if ( pn -> index[i] )
		{
			if ( ! digital_print_found )
			{
				for ( j = 0; j < digital_print_level; j++ ) printf(" ");
				digital_print_found = 1;
			}

			print_digital_character(i);

			digital_ptree( pn->reference[ pn -> index[i] ]);
		}
	}

	--digital_print_level;
}

void digital_print( DTREE *pt )
{
	DROOT *pr;

	debug("%s",__FUNCTION__);

	if ( ! pt ) return;
	if ( ! * pt ) return;

	pr = *((DROOT **)pt);

	if ( ! pr->root ) return;

	digital_print_level = -1;
	digital_print_found =  0;
	if ( pr->root )
		writeln("<<%i Nodes>>",pr->root->n);
	else
		writeln("Empty");

	digital_ptree( pr->root );
}

/* ---- digital_purge ---- */

static void purge_digital_tree( DNODE *pn )
{
	int i;

	if ( ! pn ) return;

	for ( i = 1; i < DIGITAL_MAX; i++ )
	{
		if ( pn -> index[i] )
			purge_digital_tree( pn -> reference[ pn -> index[i] ] );
	}

	free( pn );
}

void digital_purge( DTREE *pt )
{
	DROOT *pr;

	if ( ! pt ) return;
	if ( ! * pt ) return;

	pr = *((DROOT **)pt);

	if ( ! pr->root ) return;

	purge_digital_tree( pr->root );
	pr->root = pr->current = pr->search = NULL;
	free(pr);
	*pt = NULL;
}

/* ---- digital_possibilities ---- */

static void print_child_digital_tree_paths( DNODE *pn )
{
	int n;

	if ( ! pn ) return;

	print_digital_character(pn->c);

	debug( "pn -> n %i", pn->n );

	if ( pn -> n )
		print_child_digital_tree_paths( pn -> reference[1] );
	else
		newline();

	for ( n = 2; n <= pn -> n; n++ )
	{
		print_digital_tree_path( pn );
		print_child_digital_tree_paths( pn -> reference[n] );
	}
}

void digital_possibilities( DTREE *pt )
{
	DNODE *pn;
	DROOT *pr;

	debug("%s",__FUNCTION__);

	if ( ! pt ) return;
	if ( ! * pt ) return;

	pr = *((DROOT **)pt);

	if ( ! pr->root ) return;

	pn = pr->search ? pr->search : pr->root;
	if ( !pn ) return;

	print_digital_tree_path( pn -> parent );
	print_child_digital_tree_paths( pn );
}

/* ---- digital_finish ---- */

byte * digital_finish( DTREE *pt, byte *p )
{
	DROOT *pr;
	DNODE *pl;
	word *wp;
	int i,length;
	static byte b[BUFSIZE];

	if ( ! pt ) fatal("Invalid Reference to Digital Tree");

	if ( ! * pt ) *(DROOT **)pt = (DROOT *)calloc( 1, sizeof(DROOT) );

	pr = *((DROOT **)pt);

	length = strlen((char *)p);
	wp = digital_fixup(p,length);
	if ( !wp ) return((byte *)"");
	length <<= 1;

	pl = pr->root;

	while ( *p )
	{
		pl = digital_lookup( pr, pl, *p );
		if ( ! pl  ) return((byte *)"");
		if ( pl == NOT_FOUND ) return((byte *)"");
		p++;
	}

	i = 0;
	bzero(b,sizeof(b));
	if ( pl && pl -> n == 1 ) pl = pl->reference[1];
	while ( pl && pl->n == 1 )
	{
		b[i++] = pl->c;
		pl = pl->reference[1];
	}
	if ( pl ) b[i++] = pl->c;
	return(b);
}

/* ---- search (streaming multi-pattern) ---- */

typedef struct DSEARCH {
	struct DNODE    *node;
	struct DSEARCH  *prev;
	struct DSEARCH  *next;
	byte c;
} DSEARCH;

typedef struct DSEARCHES {
	struct DROOT   *tree;
	struct DSEARCH *search;
} DSEARCHES;

#define MAX_DSEARCHES 4

static DSEARCHES  digital_searches[MAX_DSEARCHES];
static DSEARCHES *digital_pl;

static DSEARCH * digital_delete_search( DSEARCH *ps )
{
	DSEARCH *ss = ps -> next;

	debug("%s",__FUNCTION__);

	assert(digital_pl);

	if ( ss )
		ss -> prev = ps -> prev;

	if ( ps -> prev )
		ps -> prev -> next = ss;
	else
		digital_pl -> search = ss;

	free(ps);

	return(ss);
}

static void digital_delete_search_list( DSEARCH *ps )
{
	if ( ! ps )  return;

	debug("%s",__FUNCTION__);

	digital_delete_search_list( ps -> next );
	free( ps );
	digital_pl->search = NULL;
}

static DSEARCH * digital_insert_search( DROOT *pr, DNODE *pn )
{
	DSEARCH *ps;

	debug("%s",__FUNCTION__);

	assert( pn );
	assert( pr );

	ps = (DSEARCH *)calloc( 1, sizeof(DSEARCH) );
	ps -> node = pn;
	ps -> next = digital_pl->search;
	if ( digital_pl->search ) digital_pl->search->prev = ps;
	digital_pl->search = ps;
	return( ps );
}

static void digital_pstree( DNODE *pn )
{
	if ( ! pn ) return;

	digital_pstree(pn->parent);
	if ( pn -> parent ) printf("{#%X,%d}",pn->c,pn->c);
}

void print_search_tree()
{
	int  i = 0;
	DSEARCH *ps;

	debug("%s",__FUNCTION__);

	if ( ! digital_pl )
	{
		writeln("No Searches");
		return;
	}

	ps = digital_pl->search;

	if ( ! ps )
	{
		writeln("No Searches");
		return;
	}

	while ( ps )
	{
		printf("Search %3i. ->",++i);
		digital_pstree( ps -> node );
		printf("\n");
		ps = ps -> next;
	}
}

int  check_search_list( DTREE *pt, word w )
{
	DSEARCH *ps;
	DROOT *pr;
	DNODE *pn;
	int    i;
	int    rc;
	byte   c;

	c = (byte)w;

	if ( ! pt ) return(DS_NOT_FOUND);
	if ( ! * pt ) return(DS_NOT_FOUND);

	pr = *((DROOT **)pt);
	if ( ! pr->root ) return(DS_NOT_FOUND);

	for ( digital_pl = NULL, i = 0; i < MAX_DSEARCHES; i++ )
	{
		if ( digital_searches[i].tree == pr )
		{
			digital_pl = &digital_searches[i];
			break;
		}
	}

	if ( ! digital_pl )
	{
		for ( i = 0; i < MAX_DSEARCHES; i++ )
		{
			if ( digital_searches[i].tree == NULL )
			{
				digital_pl = &digital_searches[i];
				digital_pl -> tree = pr;
				break;
			}
		}
	}

	if ( ! digital_pl ) fatal("No Trees");

	if ( w == (word)-1 )
	{
		digital_delete_search_list(digital_pl->search);
		return(DS_NOT_FOUND);
	}

	rc = DS_NOT_FOUND;
	ps = digital_pl->search;
	while ( ps )
	{
		pn = digital_lookup( pr, ps -> node, c );

		debug("%s digital_lookup returns %p",__FUNCTION__,pn);

		if ( pn == NOT_FOUND )
		{
			ps = digital_delete_search(ps);
		}
		else
		if ( pn )
		{
			ps -> node = pn;
			ps = ps -> next;
			rc = DS_CONTINUE;
		}
		else
		{
			digital_delete_search_list( digital_pl->search );
			return(DS_FOUND);
		}
	}

	assert(pr->root);

	pn = digital_lookup( pr, pr->root, c );

	debug("%s digital_lookup, returns %p",__FUNCTION__,pn);

	if ( pn == NOT_FOUND || ! pn ) return(rc);

	ps = digital_insert_search( pr, pn );
	ps -> c = c;

	return(DS_START);
}

void delete_searches( DTREE *pt )
{
	check_search_list(pt,-1);
}

/* ========================================================================== *
 *  _    ___ ___  ___                                                         *
 * | |  |_ _| _ )/ _ \                                                       *
 * | |__ | || _ \ (_) |                                                      *
 * |____|___|___/\__\_\                                                      *
 *                                                                            *
 * ========================================================================== */

static void *qmalloc( int x )
{
	void *v;
	v = malloc(x);
	if ( ! v ) fatal("No Memory");
	bzero(v,x);
	return(v);
}

static void qfree( void *v )
{
	if ( v ) free(v);
}

int chkqueue( QUEUE *x )
{
	if ( !   x  ) return(0);
	if ( ! * x  ) return(0);

	return( (*(QH **)x)->n );
}

static void create_queue( QUEUE *x )
{
	// Create A Queue Header, and Copy Signature
	// -----------------------------------------
	if ( !((*(QH **)x) = (QH *)qmalloc( sizeof( QH ))) ) exit(1); // <-- Ouch
	memcpy( (*(QH **)x) -> sig, QSIG, 16 );
}

static void verify_queue_sig( QUEUE *x )
{
	int rc;

	rc = memcmp( (*(QH **)x) -> sig, QSIG, 16 );
	if ( rc ) fatal("Queue Reference appears to be invalid [%s]",(*(QH **)x) -> sig );
}

void * queue( QUEUE *x, void *item )
{
	Q *q;

	if ( ! x ) fatal("Invalid Reference to Queue");
	if ( ! * x ) create_queue(x);

	verify_queue_sig(x);

	if ( !(q = (Q *)qmalloc( sizeof(Q) )) ) exit(1); // <-- Ouch
	bzero(q,sizeof(Q));
	q -> item = item;

	// Empty Queue (first = last)
	if ( ! ( (*(QH **)x) -> first ) ) (*(QH **)x) -> first = q;

	q -> previous = NULL;
	q -> next     = (*(QH **)x) -> last;

	if ( q -> next ) q -> next -> previous = q;

	(*(QH **)x) -> last  = q;
	(*(QH **)x) -> n++;

	return( item );
}

void * dequeue( QUEUE *x )
{
	Q	*q;
	void	*item;

	if ( !   x ) return(NULL);
	if ( ! * x ) return(NULL);

	verify_queue_sig(x);

	q = (*(QH **)x) -> first;

	item = q -> item;

	if ( q -> previous ) // More than single item in Queue
	{
		(*(QH **)x) -> first = q -> previous;
		q -> previous -> next = NULL;
	}
	else                  // Last Item in Queue
	{
		qfree( *(QH **)x );
		(*(QH **)x) = NULL;
	}
        
	if ( * x ) (*(QH **)x) -> n--;

	qfree(q);
	return(item);
}

void * stack( QUEUE *x, void *item )
{
	Q *q;

	if ( ! x ) fatal("Invalid Reference to Queue");
	if ( ! * x ) create_queue(x);

	verify_queue_sig(x);

	if ( !(q = (Q *)qmalloc( sizeof(Q) )) ) exit(1); // <-- Ouch
	bzero(q,sizeof(Q));
	q -> item = item;

	// Empty Queue (first = last)
	if ( ! ( (*(QH **)x) -> last ) ) (*(QH **)x) -> last = q;

	q -> previous = (*(QH **)x) -> first;
	q -> next     = NULL;

	if ( q -> previous ) q -> previous -> next = q;

	(*(QH **)x) -> first  = q;
	(*(QH **)x) -> n++;

	return( item );
}

void * unstack( QUEUE *x )
{
	return ( dequeue(x) );
}

void purge_queue( QUEUE *x )
{
	if ( !   x  ) return;
	if ( ! * x  ) return;

	while ( dequeue(x) );

	qfree( *(QH **)x );
	(*(QH **)x) = NULL;
}

static char *invalid_ref="Queue Referece is Invalid";
void test_queue( QUEUE *x )
{
	Q *q;

	if ( ! x ) fatal(invalid_ref);
	if ( ! * x ) fatal(invalid_ref);

	verify_queue_sig(x);

	q = (*(QH **)x) -> first;
	if ( ! q ) 
	{
		printf("Empty Queue\n");
		return;
	}

	while ( q )
	{
		printf("%s\n",(char*)(q->item));
		q = q->previous;
	}
}

/* ========================================================================== *
 *   _    ___ ___   _                                                         *
 *  | |  |_ _| _ ) /_\                                                        *
 *  | |__ | || _ \/ _ \                                                       *
 *  |____|___|___/_/ \_\                                                      *
 *                                                                            *
 * ========================================================================== */

static int (*app_list[MAX_APPS])( message *);
static int app_status=0;

void app_init()
{
	message_init();
	for ( int i=0; i < MAX_APPS; i++ ) app_list[i]=NULL;
}

int app_register( int (*f)( message *) )
{
	for ( int i=0; i < MAX_APPS; i++ ) {
		if ( app_list[i] == NULL ) {
			app_list[i]=f;
			return(0);
		}
	}
	return(1);
}

int app_timer(int s,int ms)
{
	event_timer(s,ms);
	return(0);
}

static void app_broadcast(message *pm,char *text)
{
	(void)text;
	for ( int i=0; i < MAX_APPS; i++ ) {
		if ( app_list[i] != NULL ) {
			// ToDo: Do Not Exit like this, send Broadcast
			if ( app_list[i](pm) ) exit(0);
		}
	}
}

static int appomatic( message *pm )
{
	switch ( pm->type ) {
		case APP_NO_MESSAGE:    app_broadcast(pm,"NONE");    break;
		case APP_TIME_MESSAGE:  app_broadcast(pm,"TIME");    break;
		case APP_KEY_MESSAGE:   app_broadcast(pm,"MESSAGE"); break;
		case APP_SIG_MESSAGE:   app_broadcast(pm,"SIGNAL");  break;
		case APP_ERR_MESSAGE:   error("err message");        break;
		case APP_EOF_MESSAGE:   error("eof message");        break;
		case APP_MOUSE_MESSAGE: app_broadcast(pm,"MOUSE");   break;
		case APP_TTY_MESSAGE:   app_broadcast(pm,"TTY");     break;
		case APP_MESSAGE:       app_broadcast(pm,"APP");     break;
		default:                fatal("bogus message");      break;
	}                               // ToDo: Do Better...
	return(0);
}

message *app_wait_any()
{
	message *pm;
	while ( (pm=message_get()) ) {
		switch ( pm->type ) {
			case APP_KEY_MESSAGE:
			case APP_MOUSE_MESSAGE:
				return(pm);
				break;
		}
	}
	return(pm);
}

int app_wait()
{
	message *pm;
	while ( (pm=message_get()) ) {
		verbose("%s Event",__FUNCTION__);
		//message_display(pm,"from app_wait");
		appomatic(pm);
		if ( app_status < 0 ) break;
	}
	return(app_status);
}

int app_message( char *text )
{
	message m;
	bzero(&m,sizeof(m));
	m.type=APP_HOWDY;
	strcpy(m.event_name,"APPMSG");
	strncpy(m.parameter.app.greetings,text,7);
	appomatic(&m);
	return(0);
}

int app_exit()
{
	app_message("EXIT");
	app_status=-1;
	return(0);
}

/* ========================================================================== *
 *   _    ___ ___ ___                                                         *
 *  | |  |_ _| _ )   \                                                        *
 *  | |__ | || _ \ |) |                                                       *
 *  |____|___|___/___/                                                        *
 *                                                                            *
 * ========================================================================== */

static int ds_write_count=0;

static DATASTORE therecanbeonlyone;

DATASTORE * new_datastore()
{
	DATASTORE *p;
	//p=(DATASTORE *)malloc(sizeof(DATASTORE));
	p=&therecanbeonlyone;
	bzero(p,sizeof(DATASTORE));
	for ( int r = 0; r <= D_MAXROWS; r++ ) {
		for ( int c = 0; c <= D_MAXCOLS; c++ ) {
			p->d[r][c]=D_NOTHING;
		}
	}
	return(p);
}

DATASTORE_LINE *new_datastore_line()
{
	DATASTORE_LINE *p;
	p=(DATASTORE_LINE *)malloc(sizeof(DATASTORE_LINE));
	bzero(p,sizeof(DATASTORE_LINE));
	for ( int c = 0; c <= D_MAXCOLS; c++ ) {
		p->d[c]=D_NOTHING;
	}
	return(p);
}

int is_dataelement_empty( DATASTORE_ELEMENT d )
{
	if ( d == 0LL ) return(1);
	return(0);
}

int set_dataelement_char( DATASTORE_ELEMENT *p, char k )
{
/// D_CHAR   0x00000000FFFFFFFF
	*p &=0xFFFFFFFF00000000; // Not D_CHAR
	*p |= k;
	return(0);
}

int datastore_writes()
{
	return( ds_write_count );
}

// Called by update_element...
static int ds_reset_written=0;
void datastore_reset() // Called by Doodler when in doodler mode
{
	ds_write_count += write(1,"\033[0m",4);
	ds_reset_written=1;
}

static void ds_update_view(DATASTORE *p,int r,int c)
{
	char w[64],b[8],*s;
	unsigned long k,k1,k2,k3,k4;
	int bg,fg;
	move_cursor(r,c);
	k=p->d[r][c]&D_CHAR;
	k1=(k >> 24) & 0xff;
	k2=(k >> 16) & 0xff;
	k3=(k >>  8) & 0xff;
	k4=(k & 0xff);
	s=b;
	if ( k1 ) *s++=k1;
	if ( k2 ) *s++=k2;
	if ( k3 ) *s++=k3;
	*s++=k4;
	*s='\0';
	k=p->d[r][c];
	bg = d_bg(k);
	fg = d_fg(k);
// ToDo: use functions in libvt or libtty for the escape sequences.
	if ( bg || fg ) {
		if ( bg && fg ) sprintf(w,"\033[%d;%dm",bg,fg); else
		if ( bg       ) sprintf(w,"\033[%dm",bg); else
		if ( fg       ) sprintf(w,"\033[%dm",fg);
		ds_write_count += write(1,w,strlen(w));
		ds_reset_written=0;
	}
	else { // This is to reduce the number of resets being written.
		if ( ds_reset_written == 0 ) datastore_reset();
	}

	ds_write_count += write(1,b,strlen(b));

	// ToDo: Concatentate the Above Strings Before Calling Write (at least)
}

int insert_element_bgfg( DATASTORE *p,int r,int c,unsigned long v,int bg,int fg )
{
	unsigned long long f,b,x,y;
	// ToDo: Trust but Verify
	if ( v == '\n' ) {
		p->d[r][0]|=D_LINE;
		return(1);
	}
	x=(unsigned long long)v;
	f=(unsigned long long)fg;
	b=(unsigned long long)bg;
	y = ( ( x & D_CHAR ) | ( ( f << 40 ) & D_FG ) | ( ( b << 48 ) & D_BG ) );
	if ( p->d[r][c] == y ) return(0);
	p->d[r][c]=y;
	return(1);
}

int update_element_bgfg( DATASTORE *p,int r,int c,unsigned long v,int bg,int fg )
{
	if ( insert_element_bgfg(p,r,c,v,bg,fg) ) {
		ds_update_view(p,r,c);
		return(1);
	}
	return(0);
}

int insert_element( DATASTORE *p,int r,int c, unsigned long v )
{
	return( insert_element_bgfg(p,r,c,v,0,0) );
}

int update_element( DATASTORE *p,int r,int c, unsigned long v )
{
	if ( insert_element_bgfg(p,r,c,v,0,0) ) {
		ds_update_view(p,r,c);
		return(1);
	}
	return(0);
}

int delete_element( DATASTORE *p,int r,int c )
{
	p->d[r][c]=D_NOTHING;
	return(1);
}

void dump_datastore(DATASTORE *p)
{
	int r,c;
	//fprintf(stderr,"%s %p\n",__FUNCTION__,d);
	for ( r = 0; r <= D_MAXROWS; r++ ) {
		printf("%3.3d",r);
		for ( c = 0; c < D_MAXCOLS; c++ ) {
			printf(" %4.4llX",p->d[r][c]);
		}
		printf(" %4.4llX\n",p->d[r][c]);
	}
}

char get_datastore_char(DATASTORE *p,int r,int c)
{
	char k;
	if ( r < 1 || r >= D_MAXROWS ) return(0);
	if ( c < 1 || c >= D_MAXCOLS ) return(0);
	k=(char)( p->d[r][c] & 0x7F );
	return( k );
}

static void ds_fill( DATASTORE *p,int r, int c )
{
	for ( int i=1; i < c; i++ ) if ( !p->d[r][i] ) p->d[r][i]=' ';
}

static void ds_empty( DATASTORE *p,int r )
{
	for ( int i=1; i <= r; i++ ) p->d[i][0]|=D_LINE;
}

void write_datastore(DATASTORE *p,FILE *fp,int sr,int sc,int nr,int nc)
{
	int r,c;
	char b[8],*s;
	unsigned long k,k1,k2,k3,k4;
	int bg=0,fg=0,last_row=0,last_col;

	verbose("%s %p",__FUNCTION__,p);

	// Fill in Empty Columns as Necessary
	verbose("%s fill",__FUNCTION__);
	for ( r = 1; r <= D_MAXROWS; r++ ) {
		last_col=0;
		for ( c = 1; c <= D_MAXCOLS; c++ ) {
			if ( p->d[r][c] ) {
				ds_empty(p,r);
				ds_fill(p,r,c);
				last_row=r;
				if ( c > last_col ) last_col=c;
			}
		}
		p->d[r][0] &= ~R_COLUMNS; // <----- did we loose d_line
		p->d[r][0] |= last_col & R_COLUMNS;
	}

	set_colors_bg(0);
	set_colors_fg(0);

	// Walk Each Row and Column.
	// If it is a Rewrite, Don't Position.
	verbose("%s walk last_row=%d",__FUNCTION__,last_row);
	nr = ( nr == 0 ) ? last_row  : ( sr + nr );
	nc = ( nc == 0 ) ? D_MAXCOLS : ( sc + nc );
	verbose("%s nr=%d",__FUNCTION__,nr);
	for ( r = sr; r <= nr; r++ ) {
		verbose("writing row %d/%d",r,nr);
		last_col = p->d[r][0] & R_COLUMNS;
		for ( c = sc; c <= nc && c <= last_col; c++ ) {
			if ( p->d[r][c] ) {
				k=p->d[r][c]&D_CHAR;
				k1=(k >> 24) & 0xff;
				k2=(k >> 16) & 0xff;
				k3=(k >>  8) & 0xff;
				k4=(k & 0xff);
				s=b;
				if ( k1 ) *s++=k1;
				if ( k2 ) *s++=k2;
				if ( k3 ) *s++=k3;
				*s++=k4;
				*s='\0';

				k=p->d[r][c];
				bg = d_bg(k);
				fg = d_fg(k);

// ToDo: use functions in libvt or libtty for the escape sequences.
				if ( bg && fg ) {
					if ( bg != get_colors_bg() && fg != get_colors_fg() ) {
						fprintf(fp,"\033[%d;%dm",bg,fg);
						set_colors_bg(bg);
						set_colors_fg(fg);
					} else
					if ( bg != get_colors_bg() ) {
						fprintf(fp,"\033[%dm",bg);
						set_colors_bg(bg);
					} else
					if ( fg != get_colors_fg() ) {
						fprintf(fp,"\033[%dm",fg);
						set_colors_fg(fg);
					}
				} else
				if ( bg ) {
					if ( bg != get_colors_bg() ) {
						fprintf(fp,"\033[%dm",bg);
						set_colors_bg(bg);
					}
				} else
				if ( fg ) {
					if ( fg != get_colors_fg() ) {
						fprintf(fp,"\033[%dm",fg);
						set_colors_fg(fg);
					}
				}
				else { /* ! bg && ! fg */
					if ( get_colors_bg() || get_colors_fg() ) {
						fprintf(fp,"\033[0m");
						set_colors_fg(0);
						set_colors_bg(0);
					}
				}

				// Only Write if it is NBSP (emojis)
				if ( k != U_NBSP ) fprintf(fp,"%s",b);
			} // if ( p ..
		} // for ( c ...
		//printf("...d[r][0]=%X",d[r][0]);
		// ToDo: Is this the same as last_row ?
		//if ( ! ( p->d[r][0] & D_LINE ) ) break;
		if ( r == last_row ) {
			if ( get_colors_bg() || get_colors_fg() ) {
				fprintf(fp,"\033[0m");
			}
		}
		fprintf(fp,"\n");
	} // for ( r ...
	set_colors_fg(0);
	set_colors_bg(0);
	fflush(fp);
}

void view_datastore(DATASTORE *p,int r,int c,int nr,int nc)
{
	verbose("%s %p",__FUNCTION__,p);
	write_datastore(p,stdout,r,c,nr,nc);
}

int get_datastore_fg(DATASTORE *p,int r,int c)
{
	return( d_fg( p->d[r][c] ) );
}

int get_datastore_bg(DATASTORE *p,int r,int c)
{
	return( d_bg( p->d[r][c] ) );
}

int set_datastore_umeta(DATASTORE *p,int r,int c,int m)
{
	unsigned long k;
	k=(unsigned long)(m&0xF);
	p->d[r][c] |= ( k << 36 ); // ToDo, this is NOT Correct;
	return( (int)k );
}

int get_datastore_umeta(DATASTORE *p,int r,int c)
{
	unsigned long k;
	k = p->d[r][c] >> 36;
	k &= 0xF;
	return( (int)k );
}

DATASTORE_ELEMENT get_datastore(DATASTORE *p,int r,int c)
{
	unsigned long k;
	k = p->d[r][c];
	return(k);
}

int get_datastore_value(DATASTORE *p,int r,int c)
{
	return( p->d[r][c] & D_CHAR );
}

/* ========================================================================== *
 *  _    ___ _     ___ _  _ ___                                                *
 * | |  |_ _| |   |_ _| \| | __|                                               *
 * | |__ | || |__ | || .` | _|                                                 *
 * |____|___|____|___|_|\_|___|                                                *
 *                                                                            *
 * ========================================================================== */

static char lines[16][D_MAXCOLS+1];
static int pool_index;

LINE_LINE *new_line_line()
{
	LINE_LINE *p;
	p = (LINE_LINE *)malloc(sizeof(LINE_LINE));
	if (p) {
		bzero(p,sizeof(LINE_LINE));
		p->position=0;
		p->length=0;
		p->mode=0;
	}
	return(p);
}

int set_line_string(LINE_LINE *pll,char *s)
{
	int i=0;
	if (!pll || !s) return(-1);
	while (i < D_MAXCOLS) {
		pll->ch[i].s[0] = *s;
		pll->ch[i].len = (*s ? 1 : 0);
		if (!*s) {
			pll->length = i;
			return(0);
		}
		s++;
		i++;
	}
	pll->length = D_MAXCOLS;
	return(-1);
}

char *get_line_string(LINE_LINE *pll)
{
	int i=0;
	char *p,*s;
	if (!pll) return(NULL);
	p=s=&lines[pool_index][0];
	pool_index = (pool_index + 1) % 16;
	while (i < D_MAXCOLS) {
		*s = pll->ch[i].s[0];
		if (!*s) return(p);
		s++;
		i++;
	}
	return(p);
}

int line_key(LINE_LINE *pll, int key)
{
	if (!pll) return(LINE_NO_CHANGE);
	if (key >= 32 && key < 127) {
		return line_insert_char(pll, key);
	}
	switch(key) {
		case RIGHT_ARROW: return line_next_char(pll);
		case LEFT_ARROW: return line_previous_char(pll);
		case END_KEY: return line_end_of_line(pll);
		case HOME_KEY: return line_start_of_line(pll);
		case INSERT_KEY: return line_toggle_mode(pll);
		case 127:
		case DEL: return line_backspace(pll);
	}
	return(LINE_NO_CHANGE);
}

int line_next_char(LINE_LINE *pll)
{
	if (pll && pll->position < pll->length) pll->position++;
	return LINE_CURSOR_MOVED;
}

int line_previous_char(LINE_LINE *pll)
{
	if (pll && pll->position > 0) pll->position--;
	return LINE_CURSOR_MOVED;
}

int line_next_word(LINE_LINE *pll) { (void)pll; return LINE_CURSOR_MOVED; }
int line_previous_word(LINE_LINE *pll) { (void)pll; return LINE_CURSOR_MOVED; }
int line_end_of_line(LINE_LINE *pll) { if (pll) pll->position = pll->length; return LINE_CURSOR_MOVED; }
int line_start_of_line(LINE_LINE *pll) { if (pll) pll->position = 0; return LINE_CURSOR_MOVED; }

int line_insert_char(LINE_LINE *pll, int k)
{
	if (!pll || pll->position >= D_MAXCOLS) return LINE_NO_CHANGE;
	pll->ch[pll->position].s[0] = k;
	pll->ch[pll->position].len = 1;
	if (pll->position >= pll->length) pll->length = pll->position+1;
	pll->position++;
	return LINE_LINE_CHANGED;
}

int line_delete_char(LINE_LINE *pll) { (void)pll; return LINE_LINE_CHANGED; }
int line_backspace(LINE_LINE *pll)
{
	if (!pll || pll->position <= 0) return LINE_NO_CHANGE;
	pll->position--;
	return LINE_LINE_CHANGED;
}
int line_toggle_mode(LINE_LINE *pll)
{
	if (pll) pll->mode = 1 - pll->mode;
	return LINE_NO_CHANGE;
}

/* ========================================================================== */
/*  Unicode Utilities (from libu)                                             */
/* ========================================================================== */

static unsigned long enumber(char *u)
{
	unsigned long x;
	if ( *u == 'U' || *u == 'u' ) u++;
	if ( *u == '+' ) u++;
	x=strtol(u,NULL,16);
	return(x);
}

unsigned long unicoden(unsigned long x)
{
	unsigned long u1,u2,u3,u4;
	if ( x < 0x80 ) {
		x &= 0x7F;
	} else
	if ( x < 0x800 ) {
		u1= 0xC0   | (x >> 6 );
		u2=   0x80 | (x & 0x3F );
		x = ( u1 << 8 ) | u2;
	} else
	if ( x < 0x10000) {
		u1= 0xE0     | ( x >> 12 );
		u2=   0x80   |(( x >>  6 ) & 0x3F );
		u3=     0x80 | ( x & 0x3F);
		x =( u1 << 16 ) | ( u2 << 8 ) | u3;
	} else
	if ( x < 0x100000 ) {
		u1= 0xF0       | ( x >> 18 );
		u2=   0x80     |(( x >> 12 ) & 0x3F );
		u3=     0x80   |(( x >>  6 ) & 0x3F );
		u4=       0x80 | ( x & 0x3F );
		x =( u1 << 24 ) | ( u2 << 16 ) | ( u3 << 8 ) | u4;
	}
	return(x);
}

unsigned long unicodes( char *p )
{
	return( unicoden( enumber(p) ) );
}

#define UPOOL 16
static char upool[UPOOL][64];
static int upool_index=0;
static char unicode_b[128];

char *unicodex( unsigned long u)
{
	char *p,*pemoji;
	u = unicoden(u);
	pemoji = upool[upool_index++];
	if ( upool_index >= UPOOL ) upool_index=0;
	pemoji[0]=(u>>24)&0xff;
	pemoji[1]=(u>>16)&0xff;
	pemoji[2]=(u>>8)&0xff;
	pemoji[3]=u&0xff;
	pemoji[4]='\0';
	p=pemoji;
	if ( pemoji[0]==0 ) { p=&pemoji[1]; }
	if ( pemoji[1]==0 ) { p=&pemoji[2]; }
	if ( pemoji[2]==0 ) { p=&pemoji[3]; }
	if ( pemoji[3]==0 ) { p=&pemoji[4]; }
	return(p);
}

char *unicode( char *pu )
{
	return( unicodex( enumber(pu) ) );
}

char *unicode_string_display( char *pu )
{
	char *pemoji;
	char xemoji0[12],xemoji1[12],xemoji2[12],xemoji3[12];
	char oemoji0[12],oemoji1[12],oemoji2[12],oemoji3[12];
	pemoji = unicode(pu);
	sprintf(xemoji0,"%x",pemoji[0]);
	sprintf(xemoji1,"%x",pemoji[1]);
	sprintf(xemoji2,"%x",pemoji[2]);
	sprintf(xemoji3,"%x",pemoji[3]);
	if ( pemoji[0] == 0 ) strcpy(xemoji0," ");
	if ( pemoji[1] == 0 ) strcpy(xemoji1," ");
	if ( pemoji[2] == 0 ) strcpy(xemoji2," ");
	if ( pemoji[3] == 0 ) strcpy(xemoji3," ");
	sprintf(oemoji0,"\\0%o",pemoji[0]);
	sprintf(oemoji1,"\\0%o",pemoji[1]);
	sprintf(oemoji2,"\\0%o",pemoji[2]);
	sprintf(oemoji3,"\\0%o",pemoji[3]);
	if ( pemoji[0] == 0 ) strcpy(oemoji0," ");
	if ( pemoji[1] == 0 ) strcpy(oemoji1," ");
	if ( pemoji[2] == 0 ) strcpy(oemoji2," ");
	if ( pemoji[3] == 0 ) strcpy(oemoji3," ");
	sprintf(unicode_b,"%2.2s %2.2s %2.2s %2.2s ( %5.5s %5.5s %5.5s %5.5s )",
	 xemoji0,xemoji1,xemoji2,xemoji3,oemoji0,oemoji1,oemoji2,oemoji3);
	return(unicode_b);
}

#endif /* K5F2_IMPLEMENTATION */

#endif /* K5F2_H */
