#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>

//TODO I JUST REMADE 2 NEW STRUCTS TO SPLIT UP HEADER AND BODY ATTRIBUTES
// I DIDN'T CASCADE TEH CHANGES TO EVERYTHING ELSE SO YEAH I NEED TO REALLY FIX THAT
// NOTHING WILL COME CLOSE TO WORKING UNTIL I SORT THAT OUT

/*
 * refine with better borders
 *  0123456789
    +--------------+
    |  header      |
    +--------------+
    |              |
    |              |
    |              |
    |              |
    +--------------+

    COLOR_BLACK   0
    COLOR_RED     1
    COLOR_GREEN   2
    COLOR_YELLOW  3
    COLOR_BLUE    4
    COLOR_MAGENTA 5
    COLOR_CYAN    6
    COLOR_WHITE   7
*/

typedef enum e_align {
    LEFT,
    CENTER,
    RIGHT
} text_align;

typdef struct s_header_attr {
    //general background color
    int background_color; //spaces that fill gaps between meaningful data

    //all things border
    int border_color;
    bool border_bold;
    bool border_blinking;

    //all things text
    text_align align;
    int text_color;
    bool text_blinking;
    bool text_bold;
    bool text_italic;

} header_attr;

typedef struct s_body_attr {
    //general background color
    int background_color;
    bool background_blinking;

    //all things border
    int border_color;
    bool border_blinking;
    bool border_bold;

    //all things text
    text_align align;
    int text_color;
    bool text_blinking;
    bool text_bold;
    bool text_italic;
    bool text_scrolling;


} body_attr;

//contains attributes for both header and body
typedef struct s_tbox_attr {
    header_attr head_attr;
    body_attr bod_attr
} textbox_attributes;

typedef struct s_tbox {
    int id;
    int x_coordinate;          //0 = x, 1 = y
    int y_coordinate;          //0 = x, 1 = y
    int body_height;     //0 = w, 1 = h
    int width;
    int header_height;
    bool header;                //there is a header for the box, maybe if header_text is null then there is no text?
    char *body_text;            //holds ALL body text
    char *header_text;          //holds ALL header text
    textbox_attributes *attr;
} textbox;

void set_attributes_header_border_style(textbox *tbox, bool blinking, bool bold, text_align align)
{
    //default values
    tbox->attr->header_border_bold = false;
    tbox->attr->header_border_blinking = false;

    //overriden values
    tbox->attr->header_border_bold = bold;
    tbox->attr->header_border_blinking = blinking;
}

void set_attributes_header_text_style(textbox *tbox, bool blinking, bool bold, bool italic, text_align align)
{
    //default values
    tbox->attr->header_text_bold = false;
    tbox->attr->header_text_blinking = false;
    tbox->attr->header_text_italic = false;
    tbox->attr->header_text_align = LEFT;

    //overriden values
    tbox->attr->header_text_bold = bold;
    tbox->attr->header_text_blinking = blinking;
    tbox->attr->header_text_italic = italic;
    tbox->attr->header_text_align = align;
}

void set_attributes_body_style(textbox *tbox, bool blinking, bool bold, text_align align)
{
    //default values
    tbox->attr->body_bold = false;
    tbox->attr->body_blinking = false;
    tbox->attr->body_align = LEFT;

    //overriden values
    tbox->attr->body_bold = bold;
    tbox->attr->body_blinking = blinking;
    tbox->attr->body_align = align;
}

void set_attributes_header_colors(textbox *tbox, int t_color, int bg_color, int bord_color)
{

    //default values
    tbox->attr->header_border_color = COLOR_WHITE;
    tbox->attr->header_text_color = COLOR_WHITE;
    tbox->attr->header_background_color = COLOR_BLACK;

    //overriden values
    tbox->attr->header_border_color = bord_color;
    tbox->attr->header_text_color = t_color;
    tbox->attr->header_background_color = bg_color;
}

void set_attributes_body_colors(textbox *tbox, int t_color, int bg_color, int bord_color)
{
    //default values
    tbox->attr->body_border_color = COLOR_WHITE;
    tbox->attr->body_text_color = COLOR_WHITE;
    tbox->attr->body_background_color = COLOR_BLACK;

    //overrident values
    tbox->attr->body_border_color = bord_color;
    tbox->attr->body_text_color = t_color;
    tbox->attr->body_background_color = bg_color;

}

int main(int argc, char *argv[])
{


}

//redraws the box?
int update(void)
{

}

void init_textbox(textbox *tbox, int xcoord, int ycoord, int b_width, int b_height, int h_height)
{
    //default values
    tbox->x_coordinate = 0;
    tbox->y_coordinate = 0;
    tbox->body_height = 3;
    tbox->width = 3;
    tbox->header_height = 0;

    //overriden values
    tbox->x_coordinate = xcoord;
    tbox->y_coordinate = ycoord;
    tbox->body_height = b_height;
    tbox->width = b_width;
    if(tbox->header == true)
    {
        tbox->header_height = h_height;
    }
}

void draw_box(textbox *tbox)
{

}

void draw_header_border(textbox *tbox)
{
    //set attributes for border!
    if(tbox->attr->header_border_blinking == true)
        attron(A_BLINK);
    if(tbox->attr->header_border_bold == true)
        attron(A_BOLD);

    //activate magical colors
    start_color();
    init_pair(1, tbox->attr->header_border_color, tbox->attr->header_background_color);
    attron(COLOR_PAIR(1));
    //corner pieces
    //upper left corner
    mvaddch(tbox->y_coordinate, tbox->x_coordinate, ACS_ULCORNER);
    //upper right corner
    mvaddch(tbox->y_coordinate, tbox->x_coordinate + tbox->width, ACS_URCORNER);
    //lower left corner
    mvaddch(tbox->y_coordinate + tbox->header_height, tbox->x_coordinate, ACS_URCORNER);
    //lower right corner
    mvaddch(tbox->y_coordinate + tbox->header_height, tbox->x_coordinate + tbox->width, ACS_URCORNER);

    //connecting lines
    //top line
    mvhline(tbox->y_coordinate, tbox->x_coordinate + 1, ACS_HLINE, tbox->width-2);
    //bottom line
    mvhline(tbox->y_coordinate + tbox->header_height, tbox->x_coordinate + 1, ACS_HLINE, tbox->width-2);
    //left vertical line
    mvvline(tbox->y_coordinate+1, tbox->x_coordinate, ACS_VLINE, tbox->header_height-2);
    //right vertical line
    mvvline(tbox->y_coordinate+1, tbox->x_coordinate + tbox->width, ACS_VLINE, tbox->header_height-2);

    if(tbox->attr->header_border_blinking == true)
        attroff(A_BLINK);
    if(tbox->attr->header_border_bold == true)
        attroff(A_BOLD);

    attroff(COLOR_PAIR(1));
}

int destroy_textbox(textbox *box)
{
    free(box); //should free all memory associated with struct
}
