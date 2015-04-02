### Abstract ###
stabi is an acronym for Standard`[`ish`]` Template Application Binary Interface ([ABI](http://en.wikipedia.org/wiki/Application_binary_interface)).
stabi provides a set of platform agnostic templated interfaces which are inspired by Java collections and written in C++.  While the interfaces are relatively simple to use, they are a little harder to implement.  For that reason, we also provide a set of adapters from STL to the templated collection interface.  We encourage loose coupling, so you can use as much or as little as you like.

### Rationale ###
Traditionally binary modules have exported functionality via C style function pointers.  In order to expose a more "object oriented" interface across module boundaries, one would have to follow the factory/ABI paradigm in C++. The use of a pure C++ interface with only primitive types is relatively straight forward.  However, the next logical step of transferring a collection is not. There has been very little progress in this area in both the standards and open source community.

### History ###
People have attempted to solve the problem in all sorts of manners, some are discussed below:

  1. Raw C array + size: not object oriented, and limited to contiguous collections.  Additionally, ownership of the data is ambiguous.
  1. STL containers: This just doesn't work.
  1. UDT hidden behind an opaque Handle:  This works well, but is not object oriented enough from the client's perspective.
  1. COM like interfaces: Mixing in QI and Reference counting only makes things more complicated.  The rule set is too large, and too often misused.  A quick survey of some experienced developers show there is no agreement on how an out parameter is suppose to be handled.  (release or no release before assignment).
  1. Type specific collections: This is repetitive and it's exactly what we are trying to solve.

### Who this is for ###
  * C++ component writers
  * Anyone who needs container interface definitions
  * Intermediate C++ developers.  While the provided code looks relatively simple, it is built on top of many restrictions to keep the user from hurting themselves.  I am not a language expert, but I have seen too many pitfalls in C++.

### Who this is not for ###
  * Anyone who does not need to deliver components with binary separation.  If you always update the entire software together, then don't go asking for trouble by providing an abi.  While you are welcome to use the code for internal interfaces and stl adapters, you should also consider your project's overall exception strategy and your compiler's ability to inline code (MSVC is very good at it).
  * Anyone who can control the library version of the entire project.  If you control the build environment (compiler, tool-chain, library...) then there is no reason why you cannot expose complex container types.  In fact, the use of ABI is completely unnecessary.
  * Language lawyers and cute generic code writers.

### More Info ###
  1. [Design](Design.md)
  1. [FAQ](FAQ.md)