#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <string>
#include "tag.h"

class Controller {
    Tag *doc;
    Tag *cur;
    Tag *clip;
    void printCurrent();
    bool canMove();
  public:
    Controller();
    ~Controller();
    void print();                         // tests Tag::print
    void addChild(std::string option);    // tests Tag::addChild
    void deleteCur();                     // tests Tag::removeChild
    void parent();                        // tests Tag::getParent
    void up();                            // goes back to the Document level
    void setId(std::string option);       // tests Tag::setId
    void setValue(std::string option);    // tests Tag::setValue
    void findChild(std::string option);   // tests Tag::findChild
    void findChildId(std::string option); // tests Tag::findChildId
    void list();                          // tests TagIterator
    void cut();                           // moves current tag to internal clipboard (tests move operations)
    void copy();                          // copies current tag to internal clipboard (tests copy operations)
    void paste();                         // adds tag from internal clipboard as a new child
};

#endif
