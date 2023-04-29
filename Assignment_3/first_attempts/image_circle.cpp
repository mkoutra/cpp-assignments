// Print images in circular order. Their number is not known in advance.

#include "Simple_window.h"
#include "Graph.h" 
#include "std_lib_facilities.h"

#include <cmath>

using namespace Graph_lib;
/*
 * Returns an image object whose center is placed on Point p.
 * imx and imy are the size of the image in pixels
 * i_name is the name of the image.
*/
Image* image_center(Point p, string i_name, int imx, int imy) {
    return new Image(Point(p.x - imx/2, p.y - imy/2), i_name);
}

/*
 * Returns a point of a circle with center c, radius r located 
 * at theta degrees relative to x axis.
*/
Point circle_point(Point c, int r, int theta) {
    float x_coord = r*cos(theta*M_PI/180) + c.x;
    float y_coord = r*sin(theta*M_PI/180) + c.y;

    return Point((int) x_coord, (int) y_coord);
}

/* 
 * Puts images in a circular order inside the window win.
 * num: number of images to put in circle (num >= 1).
 * radius: circle radius in pixels
 * i_name: image name
 * imx: x-size of image in pixels
 * imy y-size of image in pixels 
*/
void circular_order(const int num, const int radius, Simple_window &win, \
    const string i_name, const int imx, const int imy) 
{
    Point win_center = Point(win.x_max() / 2, win.y_max() / 2);

    float angle_step = 360./num;
    vector<float> angles;
    vector<Point> circle_points;
    
    // fill angles
    for(int i = 0; i < num; ++i) {
        angles.push_back(i*angle_step);
    }
    
    // fill points
    for (int i = 0; i < num; ++i) {
        circle_points.push_back(circle_point(win_center, radius, angles[i]));
    }

    // attach objects to window
    for (int i = 0; i < num; ++i) {
        Image* ii = image_center(circle_points[i], "image.jpg", imx, imy);
        win.attach(*ii);
    }
}

int main (void) { 
    int winx = 600, winy = 400; // Window size 600*400.
    int imx = 50, imy = 50; // Image size 50*50.
    Point tl(100, 100); // top-left corner of our window.
    Point win_cen(winx/2, winy/2); // win_cen of window
    
    Simple_window win(tl, winx, winy,"Images in circle");

    // // Circle stuff
    // int angles[4] = {0, 90, 180, 270};
    // int cir_radius = 150; // 150 pixels
    // vector<Point> all_points;

    // for (int i=0; i<4; ++i) {
    //     all_points.push_back(circle_point(win_cen, cir_radius, angles[i]));
    // }
    
    // // for (int i=0; i<4; ++i) {
    // //     all_images.push_back(image_center(all_points[i], "image.jpg", imx, imy));
    // // }

    // for (int i = 0; i < 4; ++i) {
    //     // Image* ii = new Image(Point(all_points[i].x - imx/2, all_points[i].y - imy/2), \
    //     // "image.jpg");
    //     Image* ii = image_center(all_points[i], "image.jpg", imx, imy);
    //     win.attach(*ii);
    // }
    
    // Image* ii0 = image_center(all_points[0], "image.jpg", imx, imy);
    // Image* ii1 = image_center(all_points[1], "image.jpg", imx, imy);
    // Image* ii2 = image_center(all_points[2], "image.jpg", imx, imy);
    // Image* ii3 = image_center(all_points[3], "image.jpg", imx, imy);
    // win.attach(*ii0);win.attach(*ii1);win.attach(*ii2);win.attach(*ii3);
    // win.detach(*ii2);
    
    int num = 5;
    //Vector_ref<Image> imgs;
    vector<Image*> imgs;
    
    for (int i = 0; i < num; ++i) {
        double angle = i * (360. / num);
        Point p = circle_point(Point(300,200), 150, angle);
        imgs.push_back(image_center(p, "image.jpg", imx, imy));
    }

    for (int i = 0; i < imgs.size(); ++i) win.attach(*imgs[i]);
    win.detach(*imgs[2]);
    //circular_order(14, 150, win, "image.jpg", 50, 50);
    win.wait_for_button();

    return 0;
} 

