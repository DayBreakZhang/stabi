### Introduction ###
Any interface/object designer in C++ needs to consider a number of seemingly obvious, but often overlooked aspect of the language.  Minimally, any contribution to stabi needs to consider [Object Ownership](#Ownership.md), [Allocation/Deallocation](#Allocation/Deallocation.md), [Primitive types](#Primitives.md), [Errors/Exceptions](#Errors/Exceptions.md), [Comparisons](#Comparisons.md), [Concurrency](#Concurrency.md), [Constness](#Constness.md), [Performance](#Performance.md).

### Ownership ###
When objects are handed out of a method, the ownership is ambiguous by the syntax alone.  People generally follow coding standards, best practices or documentation to determine object ownership.  stabi handles ownership via self documentation in code.  If an object is handed out and if it contains the destructible interface, then ownership is granted.

### Allocation/Deallocation ###
In theory, the person allocating should be the person deallocating.  This is often overlooked in C++ since most people assumes all objects come from the same heap.  Some common abuses are:
  * The abused factory pattern not being coupled with a destruction method
  * Smart pointers assuming the global free operator can be called

To handle this exact problem, and to allow for user configured allocation schemes, you'll see fun code like this in our implementation:

`m_pMapImpl = AllocatorType::rebind<mapImplType>::other().allocate(1);`

stabi interface objects are always destroyed via the destructible interface.  This analogous to overloading delete operator on an object, but in a manner that's well defined in a binary format.  For this reason, a virtual destructor on the public interface is not necessary.

### Primitives ###
Primitives are safe for c++ abi because they are fixed size, non-throwing, almost standard (msvc9 doesn't support types like int16\_t in stdint.h) types.  We encourage the users to use primitive, POD, and pointer types for all template parameters.

The downside to primitive types is that they are not Objects.  An immediate consequence is that they do not have associated traits and attributes for us to use in the template container implementation.

Some consideration was done for providing primitive object types (much like Java), but quickly dismissed for the following reasons:
1. Added complexity takes away from flexibility.
2. Adding a V-table would deviate too far from the primitive types.
3. It is really outside the scope of stabi.

### Errors/Exceptions ###
The use of exceptions is one of the most hotly debated subjects in programming.  Unfortunately, exceptions are done very poorly in C++ (I'm going to avoid going on a 2 page rant here).  Regardless of how you feel about exceptions, you don't want to be throwing across module boundaries.  Thus, all stabi interfaces have a throw nothing specifier.  As such, anyone implementing the stabi interfaces must take care to not throw.  Needless to say, throwing anything will result in undefined behavior.  On the other hand if one were to use the provided adapters and follow abi rules for templated types, then there is nothing to worry about.

This leaves us with the option of returning error codes to indicate an error.  Unfortunately, every project and every platform has their own set of error codes.  Due to the lack of standardization on a comprehensive set of error codes, we will simply return bool type for simplicity.  (The user is welcome, to adapt the stabi interfaces to return the type of their choice)

Further, this results in pointer return types to allow for allow for error communication: for example, one would see:

`const returnType * f() const;`

as opposed to

`const returnType & f() const;`

### Comparisons ###
**_<this section is currently under consideration>_**

### Concurrency ###
All stabi interfaces are to be used under the assumption that the objects are not synchronized unless otherwise specified on the instance comments.  stabi is meant to be generic, thus, we cannot anticipate the user's threading model.  Any attempt to blindly handle synchronization will only result in poor performance.  If the user wishes to add synchronization, simply provide a synchronized wrapper on-top of the provided implementations.  (I suppose we can make synchronization a trait if someone wants to make a compelling argument)

### Constness ###
Constness is another very ambiguous, and poorly enforced concept in C++.
Regardless, I've found Java's final to be more restrictive and much more useful for efficient multi-threaded programming.  Thus, all stabi interface const methods shall adopt this restriction and all such methods can be called across multiple threads safely without the need for synchronization.  This conveniently makes all const objects safe to use across multiple threads efficiently.

Note to Caller:
If you mix and match const and non-const methods, then it is no longer thread safe.

Note to Implementer:
Be very cautious of using mutable when implementing stabi interfaces.

Note to both:
Be very careful not to break the final-const contract when using `const_cast<T>(o)`

### Performance ###
stabi is designed with performance in mind.  If your compiler inlines well enough, and you don't mind the extra v-table look up, then you can even use stabi within a module boundary efficiently.   While we would like to provide our own container implementation to allow for additional memory/speed control, we simply don't have the time, so the stl adapters will have to do for now.