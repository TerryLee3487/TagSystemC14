#include "tag.h"
using namespace std;

// deafult constructor, initialize all attribute
Tag::Tag(const string &type) : 
    type{type},
    id{""},
    value{""},
    parent{nullptr},
    children{nullptr},
    childrenLength{0},
    childrenCapacity{0} {}


// Copy constructor
Tag::Tag(const Tag &other) :
    // copy over all the basic values
    type{other.type},
    id{other.id},
    value{other.value},
    childrenLength{other.childrenLength},
    childrenCapacity{other.childrenCapacity} {
    
    // check if the parent was nullptr if not copy it over
    if(other.parent == nullptr) {
        parent = nullptr;
    } else {
        parent = other.parent;
    } 

    // check if children was nullptr, if not do a deep copy and assign the new array to children
    if (other.children == nullptr) {
        children = nullptr;
    } else {
        Tag ** tmp = new Tag * [other.childrenCapacity];
        for (int i = 0; i < other.childrenLength; i++) {
            // deep copy each element from the other.chidren to tmp array
            tmp[i] = new Tag {*other.children[i]};
        }
        // assign ymp to be the new children
        children = tmp;
    }
}


// move constructor
Tag::Tag(Tag &&other) : 
    // copy over the basic fields
    type{other.type},
    id{other.id},
    value{other.value},
    childrenLength{other.childrenLength},
    childrenCapacity{other.childrenCapacity} {
    
    // check if your parent was nullptr
    if (other.parent == nullptr) {
        parent = nullptr;
    } else {
        parent = other.parent;
    }

    // check if the children was nullptr
    if (other.children == nullptr) {
        children = nullptr;
    } else {
        Tag ** tmp = new Tag * [other.childrenCapacity];
        for (int i = 0; i < other.childrenLength; i++) {
            // deep copy each element over to tmp
            tmp[i] = new Tag {*other.children[i]};
            // set each child's parent to be this tag
            tmp[i]->setParent(this);
        }
        // assign tmp to be the new children array
        children = tmp;
    }

    // clear out other
    other.parent = nullptr;
    other.children = nullptr;
    other.childrenCapacity = 0;
    other.childrenLength = 0;
    other.type = "";
    other.id = "";
    other.value = "";
}

// copy assignment operator
Tag & Tag::operator=(const Tag &other) {
    // check for self assignment
    if (this == &other) {
        return *this;
    }

    // copy over the basic fields
    type = other.type;
    id = other.id;
    value = other.value;
    childrenLength = other.childrenLength;
    childrenCapacity = other.childrenCapacity;

    // check for other.parent nullptr
    if (other.parent == nullptr) {
        parent = nullptr;
    } else {
        parent = other.parent;
    }
    
    // initialized a tmp array to store children from other
    Tag ** tmp = new Tag * [other.childrenCapacity];
    for (int i = 0; i < other.childrenLength; i++) {
        // deep copy every element in other.children
        tmp[i] = new Tag {*other.children[i]};
        // set each child's parent to be the current tag
        tmp[i]->setParent(this);
    }
    // assign tmp to be the new children
    children = tmp;
    return *this;
}

// Move assignment operator 
Tag & Tag::operator=(Tag &&other) {
    // swap every field from other to current tag
    swap(type, other.type);
    swap(id, other.id);
    swap(value, other.value);
    swap(parent, other.parent);
    swap(children, other.children);
    swap(childrenLength, other.childrenLength);
    swap(childrenCapacity, other.childrenCapacity);
    for (int i = 0; i < childrenLength; i++) {
        // set each child's new parent to be the current tag
        children[i]->setParent(this);
    }
    return *this;
}

// Destructor
Tag::~Tag() {
    // dereference each child 
    if (childrenCapacity != 0) {
        for (int i = 0; i < childrenLength; i++) {
            delete children[i];
        }
        // deref the children array
        delete [] children;
    }
}

// get the tag of a tag
const string & Tag::getType() const {
    return type;
}

// get the id of a tag
const string & Tag::getId() const {
    return id;
}

// set new id for a tag
void Tag::setId(const string &_id) {
    this->id = _id;
}

// get the value of a tag
const string & Tag::getValue() const {
    return value;
}

// set new value of a tag
void Tag::setValue(const string &_value) {
    this->value = _value;
}

// get the parent of the current tag
Tag * Tag::getParent() const {
    return parent;
}

// set the new parent to the current tag
void Tag::setParent(Tag *_parent) {
    this->parent = _parent;
}


// Prints this tag to out in the following format:
    // <type id="id" value="value">
    //   ...children
    // </type>
    // Note that the indentLevel starts at 0 for the first tag,
    // so, the first tag is printed without any trailing spaces.
    // For each children level, increase the indentLevel by 1.
    // For each indentLevel, add two spaces to the beginning of the line
    // If the id or value attributes are empty (""), do not print them.
    // If this tag does not have children, don't print anything for the ...children line.
void Tag::print(ostream &out, int indentLevel) const {
    // indentation
    for (int i = 0; i < indentLevel; i++) {
        cout << " ";
    }
    // print out the type first
    out << "<" << type;
    // check the existence of id, if yes, print out id
    if (id != "") {
        out << " id=" << "'" << id << "'";
    }
    // check the existence of value if yes print out value
    if (value != "") {
        out << " value=" << "'" << value << "'";
    } 

    out << ">" << endl;

    // call print on each child and their children recursively to print out everything 
    for (int i = 0; i < childrenLength; i++) {
        children[i]->print(out, indentLevel+2);
    }

    // print the indentation for the ending brackets 
    for (int i = 0; i < indentLevel; i++) {
        cout << " ";
    }
    // print out the ending bracket
    out << "</" << type << ">" << endl;
}

void Tag::addChild(Tag *other) {
    // increment the children length
    childrenLength += 1;
    // if the children array is empty, allocate size one memeory to the heap
    if (childrenCapacity == 0) {
        childrenCapacity = 1;
        children = new Tag * [1];
    }

    // if the length exceeds the new capacity
    if (childrenLength > childrenCapacity) {
        // double the capacity
        childrenCapacity = childrenCapacity * 2;
        // initilize tmp to store children from other
        Tag **tmp = new Tag * [childrenCapacity];
        for (int i = 0; i < childrenLength-1; i++) {
            // create a tmp child to store the corresponding child from other
            Tag * tmpChild = new Tag {*children[i]};
            // dereference each child 
            delete children[i];
            // assign tmpChild to tmp[i]
            tmp[i] = tmpChild;
        }
        // derefe the old children array
        delete [] children;
        // assign tmp as the new children array
        children = tmp;
    }
    // add other to the last place of the children array
    children[childrenLength-1] = other;
}

void Tag::removeChild(Tag *other) {
    // use q to check if other was found in the children array
    int q = -1;
    for (int i = 0; i < childrenLength; i++) {
        if (children[i] == other) {
            // if other is found in children, make index i the new q
            q = i;
            break;
        }
    }

    // if other was found
    if (q != -1) {
        // check if "other" found in children
        if (q < childrenLength) {
            for (int j = q; j < childrenLength; j++) {
                // shift all elements after "other" to 1 position forward
                children[j] = children[j++];
            }
            // decrease the length by 1 if a child was removed
            childrenLength--;   
        }
    }
}

Tag * Tag::findChild(string &type) {
    // use j to keep track of if a child with type was found
    int j = -1;
    for (int i = 0; i < childrenLength; i++) {
       if (children[i]->type == type) {
           // if a child with "type" was found, make index i the new j
            j = i;
            break;
       }
   }
   // if a child with "type" was found, return the pointer of that child tag
   if (j != -1) {
       return children[j];
   } else {
    // if that specific child was not found, return nullptr
    return nullptr; 
   }
}

Tag * Tag::findChildId(string &id) {
    // use j to keep track of if a child with type was found
    int j = -1;
    for (int i = 0; i < childrenLength; i++) {
       if (children[i]->id == id) {
           // if a child with "id" was found, make index i the new j
            j = i;
            break;
       }
   }
   // if a child with "type" was found, return the pointer of that child tag
   if (j != -1) {
        return children[j];
   } else {
       // if that specific child was not found, return nullptr
        return nullptr; 
   }
}

// Returns an iterator to the start of the children array.
TagIterator Tag::begin() const {
    return TagIterator(children);
}

// Returns an iterator past the end of the children array.
TagIterator Tag::end() const {
    return TagIterator(children+childrenLength);
}

// constructor for TagIterator
TagIterator::TagIterator(Tag **t) {
    this->t = t;
}

// Returns the tag that this iterator is currently pointing to
Tag * TagIterator::operator*() const {
    return *t;
}

// increment t and advance the iterator
TagIterator TagIterator::operator++() {
    t++;
    return *this;
}

// Compares this iterator with other; returns true if they point to the same array position.
bool TagIterator::operator==(const TagIterator &other) const {
    if (t == other.t) {
        return true;
    } else {
        return false;
    }
}

// Compares this iterator with other; returns true if they do not point to the same array position.
bool TagIterator::operator!=(const TagIterator &other) const {
    if (t == other.t) {
        return false;
    } else {
        return true;
    }
}

// print out the content of tag
ostream &operator<<(ostream &out, const Tag &tag) {
    tag.print(out, 0);
    return out;
}
