#include <atomic>
#include <vector>

// A class to wrap around a general type, intended to provide
// a way to have a lock free array of the type.
// Essentially taken from: http://stackoverflow.com/questions/16919858/thread-safe-lock-free-array
// Needless to say, this implementation requires c++11

template <typename T>
class lockfree_t
{
    public:
        lockfree_t() : atomic(T()){}
        explicit lockfree_t(T const& v) : atomic(v){}
        explicit lockfree_t(std::atomic<T> const& a) : atomic(a.load()){}
        lockfree_t(lockfree const& other) : atomic(other.atomic.load()){}
        
        lockfree_t& operator=(lockfree const& other)
        {
            atomic.store(other.atomic.load());
            return *this;
        }
        
        // These are functions I needed to be able to use the lockfree_t in a
        // lock-free array class. Particularly the CAE function. They simply fall through 
        // to the underlying atomic type.
        
        T load(){return atomic.load();}
        
        void store(T val){atomic.store();}
        
        bool compare_exchange_weak(T& exp, T val)
        {
            return atomic.compare_exchange_weak(exp, val);
        }
        
    private:
        std::atomic<T> atomic;// This being public is maybe not a great idea...
};

// Atomic array class. Simply a layer on top of a normal STL vector
// which allows for the underlying data to be accessed atomically

template <typename T>
class atomic_array
{
    public:
        atomic_array()
        {
            data = new std::vector<lockfree_t<T> >;
        }
        
        atomic_array(int N)
        {
            data = new std::vector<lockfree_t<T> > (N);
        }
        
        lockfree_t<T>& at(int N){return data->at(N);}
        
        lockfree_t<T>& operator[](size_t n){return data->at(n);}
        
    private:
    
        std::vector<lockfree_t<T> >* data;
};