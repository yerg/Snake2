#ifndef GUIELEMENTS_H
#define GUIELEMENTS_H

#include "IndependentInclude.h"
#include "Image.h"
class Button {
	Point point;
	Image* image;
public:
	Button(Image * i, Point p) : image(i), point(p){}
	Point SetPosition(Point p){point=p;}
	Point GetPosition(){return point;}
	Point GetSize(){return Point(image->GetWidth(),image->GetHeight());}
	Image* GetImage(){return image;}
};

#endif