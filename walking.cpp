#include "stdafx.h"
#include "distantion.h"
#
void go_to() {
	if (calculateDistantion(normal.getX(), normal.getY(), p.getX(), p.getY()) > calculateDistantion(normal.getX(), normal.getY(), p1.getX(), p1.getY())) {
		gototarget(normal.Xdir, normal.Ydir, p1.getX(), p1.getY(), normal.getX(), normal.getY());
	}
	else
	{
		gototarget(normal.Xdir, normal.Ydir, p.getX(), p.getY(), normal.getX(), normal.getY());;
	}
}