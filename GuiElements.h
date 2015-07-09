#ifndef GUIELEMENTS_H
#define GUIELEMENTS_H

#include "Independent.h"
#include "Image.h"
class Button {
	Point point;
	Image* image;
public:
	Button(Image * i, Point p) : image(i), point(p){}
	void SetPosition(Point p){point=p;}
	Point GetPosition(){return point;}
	Point GetSize(){return Point(image->GetWidth(),image->GetHeight());}
	bool CheckHit(Point &hit){return ( (point.x<=hit.x)&&(point.y<=hit.y)&&(image->GetWidth()+point.x>=hit.x)&&(image->GetHeight()+point.y>=hit.y) );}
	Image* GetImage(){return image;}
	void SetImage(Image* i){image=i;}
};

#endif