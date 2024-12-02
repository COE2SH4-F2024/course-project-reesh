#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
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
    
    aList[0] = thisPos;//put new head at the beginning
    listSize++;//increase list size, added a new element
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity) 
    {
        return;
    }

    //insert tail at last index position and increase the size
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0) 
    {
        return;
    }

    for(int i = 0; i < listSize; i++)//shift all elements to the left
    {
        aList[i] = aList[i + 1];
    }
    listSize--;//decrease list size, removed an element
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        return;
    }
    //gets rid of last element
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