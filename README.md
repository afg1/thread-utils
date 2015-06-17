# thread-utils
Some handy bits of code I wrote while mucking about with multithreaded codes. These things may or may not be useful.

==Atomic Array ==
Atomic arrays are useful when you have may threads all writing to a simgle data structure (eg many threads depositing dose in a volume). This class defines a lockfree_t<typename T> type which allows you to wrap anything in an atomic wrapper. Importantly, several constructors are overloaded so that it can be used in STL containers. For details see here: http://stackoverflow.com/questions/16919858/thread-safe-lock-free-array

The atomic_array<> class is then defined using the lockfree_t type, and provides a simple wrapper around the STL vector class. I intend to include other functions from the class, but at the moment I only need the ability to access and modify elements.
