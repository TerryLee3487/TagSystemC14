# TagSystemC14
A markup language is a system for annotating documents. In markup languages such as HTML
and XML, annotations consist of tags, identified by the starting and end characters < >. Tags can further contain attributes
or children tags/text and are closed by </ >. For example, in the following excerpt, document, body, and text are tags.

<document>
  <body>
    <text id=’t1’ value=’CS246’>
    </text>
  </body>
  </document>
  
This is a class to manage tags in a document. Our markup language is loosely inspired by HTML
and XML, but it is quite simplified. Our tags can be of any type (such as document, body, or text) and can optionally
contain the attributes id and value (and no other). Additionally, they can contain any number of children tags. There is
always a top-level document tag. The example document above is a valid document in our markup language and also an
example of the formatting that should be used by the program when printing the tags.


print      |    Prints the current tag to the standard output.  
add        |    type Creates a new tag of the type specified by the argument, adds it as a child of the current tag, and  
makes      |    it the new current tag. Note that type cannot be "document".  
delete     |    Deletes the current tag, removes it from its parent, and makes its parent the new current tag.  
parent     |    Sets the parent of the current tag as the new current tag.  
up         |    Sets the topmost tag (<document>) as the current tag.  
id val     |    Sets the id attribute of the current tag to val. Note that val cannot contain whitespaces.  
value      |    val Sets the value attribute of the current tag to val. Note that val cannot contain whitespaces.  
find       |    type Finds the first tag that is a child of the current tag and has the specified type. If such a tag if found,  
                it is set as the current tag. Otherwise, nothing happens.  
findId id  |    Finds the first tag that is a child of the current tag and has the specified id. If such a tag if found,  
                it is set as the current tag. Otherwise, nothing happens.  
list       |    Lists all the children of the current tag.  
cut        |    Removes the current tag from its parent and moves it to the program’s internal clipboard. Sets its  
                parent tag as the current tag.  
copy       |    Copies the current tag to the program’s internal clipboard.  
paste      |    Adds a new child to the current tag, whose contents are a copy of the tag currently in the clipboard.  
quit       |    Quits the program.  
