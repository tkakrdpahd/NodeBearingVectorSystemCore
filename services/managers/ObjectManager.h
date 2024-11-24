/**
 * ObjectManager.h
 * Formerly attributeManager.h
 * Linked File: ObjectManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Manage Vector and Segment Attributes
 * Provides CRUD operations for Vector Attributes
 */

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "SegmentManager.h"

class ObjectManager
{
private:
    /* 
     ObjectManager는 NodeVector, BearingVector, SegmentManager를 unique_ptr로 선언하는 선언지점임.
     NodeVector는 3개의 float 데이터를 가지는 배열임.
     BearingVector는 2개의 vector3, 한개의 int 자료를 가지는 4차원 배열임.
     SegmentManager는 NodeVector, BearingVector를 포인터로 참조, 세그먼트 & 버퍼인덱스를 unique_ptr로 선언하는 5차원 포인터 배열임.
     IndexBuffer는 NodeVector, BearingVector, Segments 인덱스를 4차원 포인터 배열로 관리하는 객체임.
     */
public:
    ObjectManager(/* args */);
    ~ObjectManager();
};

#endif // OBJECTMANAGER_H