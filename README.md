AlgorithmPrep
=============

Preparing for data structure and algorithm study based on my ancient notes. The code is not meant to be producion quality, but rather a refresher for the data-structure and algorithms I had studied around 2008. 

The notes are in drawing and pseudo-code format, so it's gonna be fun to code them in C++. Besides, I am also using this as an opportunity to learn C++11. This means that as time progresses, I will start using more advanced  C++11 features. I am not indulging in a very comprehensive study of C++11 yet, so you might not see me using additions related to multithreading and locks. But at the very least, I plan to use auto, nullptr, &&, move semantics, perfect forwarding and lambdas wherever applicable.  

In general, the format I'm going for is:  
Files created:  
study_subject.h             # Minimal implementation that works for the most common cases(like assuming   
                            # ascending sort order instead of providing a more general implementation  
                            # that allows the caller to supply a functor for the ordering)  
  
test_study_subject.cpp      # Basic tests for the study subject. I don't think I have enough time to  
                            # write comprehensive tests right now. But I plan to make another pass through  
                            # the entire code base some day to improve it, tests included.  
  
In case there isn't a need to break the code into .h and .cpp on the basis mentioned above,  
I simply go for study_subject.cpp which incorporates both the study subject and test code  
in a single file.  
  
This is the commandline I use most ferquently for compiling(There are no exceptions today):  
g++ -std=c++11 test_study_subject.cpp  
  
Execution is just as simple:  
./a.out  
  
Makefiles: This code base, at least currently, is not meant to generate a single target. Almost every .cpp has its own main(). As such the minimal command line mentioned above is not only sufficient, but also the sensible choice. With an automated build, all we will achieve is a bunch of independent executables(one per .cpp). This might be useful to automate regression testing at some point. But as of today, each .cpp stands on its own. It is also merely a test-suite targetting a single study subject. So, I don't envisage changes in one header file propogating to break more than one(or maybe 3 when we get to graphs) .cpp file(s). Dropping both makefiles and regression arrangements until such a time as when I decide to break the file structure rule mentioned above.


Notes on what I plan to explicitly avoid from all my code:  
1) Exceptions: I will neither handle them nor throw them. This will obviously mould the  
   function signatures I use. Some options that come to mind:   
   i)  Make the caller pass references so that certain types of error checks are forced at the caller level.  
   ii) Return error codes from methods and use in-out parameters to return results if the results do not   
       have a meaningful failure value (for example: bool stringToInt(const string &s, int &rval) )  
   I will learn a few more tricks and interesting scenarios along the way. Will try to document them in this README as well.  
2) Naked Pointers: Since we have simple STL options to rid our code of the unnecessary complexity of dealing  
   with naked pointers, I will try to stay clear of these. I didnt try this right from the start,  
   but starting with the binary tree code, I plan to follow this through.  
3) Explicit new and delete: Use alternatives wherever possible. STL containers can save copies of the   
   objects and discard them when we discard the STL container. unique_ptr and shared_ptr will help keep   
   the STL containers and custom objects alive for the right duration. These two might help me avoid   
   exceptions (in cases where resources need to be released safely) and naked pointers as well.   
   To avoid explicit new statements, I'll need to go for factory methods within my classes. For   
   library classes, I will not have a choice but to use new.   
4) Template Meta Programming: Just because it's tempting to study it, but I don't have enough time to   
   focus on it right now. I'd rather spend the time on newer algorithms and Swift programming.   


