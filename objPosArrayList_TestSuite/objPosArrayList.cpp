#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity){
        return;
    }

    for(int i = listSize; i > 0; i--)//shift all elements 1 to the right
    {
        aList[i] = aList[i - 1];
    }
    
    aList[0] = thisPos;//make new head at the beginning
    listSize++;//increase list size because we have a new element
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity) 
    {
        return;
    }

    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0) 
    {
        return;
    }

    for(int i = 0; i < listSize; i++)
    {
        aList[i] = aList[i + 1];
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        return;
    }
        listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{

    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}