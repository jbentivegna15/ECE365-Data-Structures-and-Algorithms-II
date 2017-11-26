/*
Joseph Bentivegna
Professor Sable
DSA2 Project 2
This project involved the creation of a priority queue
using a binary heap implementation.  The items in the binary heap
contain a unique string id, an integer key, and optionally
any pointer. The user can specify a heap capacity and functionality
is built for insersion, deletion, delete-min, and set-key.
*/

#include "heap.h"

heap::heap(int capacity) {

  // construct the mapping hashtable to hold the id's
  mapping = new hashTable(capacity*2);
  data.resize(capacity+1);
  // set capacity equal to the user specified capacity and size equal to zero
  this->capacity = capacity;
  size = 0;
}

int heap::insert(const std::string &id, int key, void * pv) {

  // check if the heap is not full
  if (size < capacity) {
    // check the heap contains the id already (via the hashtable)
    if (!(mapping->contains(id))) {
      size += 1;
      // insert the new item into the heap and hashtable
      data[size].id = id;
      data[size].key = key;
      data[size].pData = pv;
      mapping->insert(id, &data[size]);
      percolateUp(size);
    } else {
      return 2;
    }
  } else {
    return 1;
  }
  return 0;
}

int heap::setKey(const std::string &id, int key){

  // check if the heap contains the id already (via the hashtable)
  if (mapping->contains(id)) {
    // create a reference to the specified node
    node * pn = static_cast<node*> (mapping->getPointer(id));

    // keep the old key value and update it with the new
    int old = pn->key;
    pn->key = key;

    // call getPos to get the location of the node in the heap
    int loc = getPos(pn);
    if (key < old) {
      percolateUp(loc);
    } else if (key > old){
      percolateDown(loc);
    }
    return 0;
  } else {
    return 1;
  }
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {

  // check to make sure the heap isn't empty
  if (size != 0) {
    // update values if specified
    if (pId != nullptr) {
      *pId = data[1].id;
    }
    if (pKey != nullptr) {
      *pKey = data[1].key;
    }
    if(ppData != nullptr) {
      *(static_cast<void**> (ppData)) = data[1].pData;
    }

    // remove the node from the hashtable and heap
    mapping->remove(data[1].id);
    data[1] = data[size];
    size -= 1;
    percolateDown(1);

    return 0;
  } else {
    return 1;
  }
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {

  // check if the heap contains the id already (via the hashtable)
  if (mapping->contains(id)) {
    // create a reference to the specified node
    node * pn = static_cast<node*> (mapping->getPointer(id));

    // update values if specified
    if (pKey != nullptr) {
      *pKey = pn->key;
    }
    if (ppData != nullptr) {
      *(static_cast<void**> (ppData)) = pn->pData;
    }

    // remove the node from the hashtable and heap
    mapping->remove(id);
    int old = pn->key;
    *pn = data[size];
    int newk = pn->key;
    size -= 1;

    // using the old location and the getPos location, sort elements accordingly
    int loc = getPos(pn);
    if (newk < old) {
      percolateUp(loc);
    } else if (old < newk){
      percolateDown(loc);
    }
    return 0;
  } else {
    return 1;
  }
}

void heap::percolateUp(int posCur) {
  // make a temp node of the data we want to move
  node temp = data[posCur];

  // loop through the binary heap and swap items accordingly
  while (posCur > 1 && temp.key < data[posCur/2].key) {
    data[posCur] = data[posCur/2];
    // don't forget to remap the hashtable!
    mapping->setPointer(data[posCur].id, &data[posCur]);
    posCur /= 2;
  }

  // set the final location to the node we wanted to move
  data[posCur] = temp;
  mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur) {
  //make a temp node of the data we want to move
  node temp = data[posCur];
  int target;
  int left, right;

  // loop trough the binary heap and swap items accordingly
  while (2*posCur <= size) {
    int left = 2*posCur;
    int right = left + 1;

    // figure out where the target position should be
    if (left < size && data[right].key < data[left].key) {
      target = right;
    } else {
      target = left;
    }

    if (data[target].key < temp.key) {
      data[posCur] = data[target];
      mapping->setPointer(data[posCur].id, &data[posCur]);
    } else {
      break;
    }
    posCur = target;
  }

  // set the final loation to the node we wanted to move
  data[posCur] = temp;
  mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn) {

  int pos = pn - &data[0];
  return pos;
}
