#include <iostream>
#include <string>
#include "controller.h"
#include "tag.h"
using namespace std;

int main() {
    Controller ctr;
    string cmd;
    string option;
    cout << "[Command?]" << endl;
    while (cin >> cmd) {
        if (cmd == "print") { // tests Tag::print
            ctr.print();
        } else if (cmd == "add") { // tests Tag::addChild
            cin >> option;
            ctr.addChild(option);
        } else if (cmd == "delete") { // tests Tag::removeChild
            ctr.deleteCur();
        } else if (cmd == "parent") { // tests Tag::getParent
            ctr.parent();
        } else if (cmd == "up") { // goes back to the Document level
            ctr.up();
        } else if (cmd == "id") { // tests Tag::setId
            cin >> option;
            ctr.setId(option);
        } else if (cmd == "value") { // tests Tag::setValue
            cin >> option;
            ctr.setValue(option);
        } else if (cmd == "find") { // tests Tag::findChild
            cin >> option;
            ctr.findChild(option);
        } else if (cmd == "findId") { // tests Tag::findChildId
            cin >> option;
            ctr.findChildId(option);
        } else if (cmd == "list") { // tests TagIterator
            ctr.list();
        } else if (cmd == "cut") { // moves current tag to internal clipboard
            ctr.cut();
        } else if (cmd == "copy") { // copies current tag to internal clipboard
            ctr.copy();
        } else if (cmd == "paste") { // adds tag from internal clipboard as a new child
            ctr.paste();
        } else if (cmd == "quit") {
            break;
        } else {
            cerr << "Invalid command." << endl;
        }
        cout << "[Command?]" << endl;
    }    
}
