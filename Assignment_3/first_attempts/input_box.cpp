// Print images in circular order. Their number is not known in advance.

#include "Simple_window.h"
#include "Graph.h" 
#include "std_lib_facilities.h"
#include <iostream>
#include <cmath>

using namespace Graph_lib;

class Box_with_button : public Widget {
    public:
        Box_with_button(Point p, int ww, int hh, \
            const string &but_s, const string &box_s);
    
        Button submit_button;
        In_box submit_box;

        // Callback for submit box
        static void cb_submit(Address, Address); 
        void submit(void);
        
        void attach(Graph_lib::Window& win);
};

Box_with_button::Box_with_button(Point p, int w, int h, \
    const string &but_s, const string &box_s)
    :Widget(p, w, h, "box with button", 0),
    submit_box(p, w, h, box_s),
    submit_button(Point(p.x + w + 5, p.y), w, h, but_s, cb_submit)
    {}

void Box_with_button::cb_submit(Address w, Address pw) {
    reference_to<Box_with_button>(pw).submit();
}

void Box_with_button::submit(void) {
    int num;
    num = submit_box.get_int();
    cout << num << '\n';
}

void Box_with_button::attach(Graph_lib::Window& win) {
    win.attach(submit_button);
    win.attach(submit_box);
    own = &win;
};

void test_func() {
    printf("Test!\n");
}

void cb_test(void*, void* pw) {
    test_func();
} 

int main (void) { 
    int winx = 600, winy = 400; // Window size 600*400.
    int imx = 50, imy = 50; // Image size 50*50.
    Point tl(100, 100); // top-left corner of our window.
    Point win_cen(winx/2, winy/2); // win_cen of window
    
    Simple_window win(tl, winx, winy, "Images in circle");
    // In_box test_input(win_cen, 70, 20, "test");
    // Button test_button(Point(winx / 2 + 75, winy / 2), 50, 20, "test", cb_test);
    
    // win.attach(test_button);
    // win.attach(test_input);
    // win.wait_for_button();
    // int test_int = test_input.get_int();
    // std::cout << "Test int = " << test_int;

    Box_with_button test(Point(200,200), 70, 20, "Submit", "Box string");
    win.attach(test);

    win.wait_for_button();

    return 0;
} 