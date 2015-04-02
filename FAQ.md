**Q:** How do you pronounce stabi?
**A:** sta-bē

**Q:** What's with the weird hxx file?
**A:** If you've ever tried to read template code in C++ (like stl, or parts of boost), you would probably have been very confused at some point in time.  One of the reasons for this is because C++ requires you to place the implementation of the templated function/class in the header.  In order to address this legibility problem, we decided to make template files read like non-template files.  We achieve this by placing the class/function definitions in the .h files (much like non-template files), and the implementation in the .hxx files (much like the .cpp or .c files).  To satisfy the "templates must be in headers" requirement, we simply include the .hxx files at the bottom of the .h file.  With this little trick we achieved 2 things:
  1. he client of the code can easily open up the .h file to learn about the interface without being concerned with the implementation.
  1. he client can simply include the .h file and be non-the-wiser

**Q:** Why do you always use 2 stage initialization?
**A:** I just don't see any other way of constructing an object when you are trying to write exception aware code.  Throwing out of constructors is very often overlooked, especially when it's the constructor of a member element (so much for hiding the implementation from the user of the class...)

**Q:** If you only want primitive types, pointer types, and POD types to be used as template parameters, then what are you catching for in put/remove?
**A:** While I do recommend only ABI safe types be used for ABI purposes, I try to make the implementation classes a bit more generic.  Specifically, I try to make them function with stl (due to its prevalence and it being standard), so that they can be use in non-abi manners.  For example, you can safely use:
`util::stabi::adapter::STLMap2StabiMapAdapter<std::string, std::string> stabiMap;`