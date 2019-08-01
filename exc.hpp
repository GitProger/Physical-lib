#ifndef __EXC_HPP_INC
#define __EXC_HPP_INC

class ZeroDivisionException;
class NullPointerException;
class ObjectIsNotAPointerException;
template <typename, bool> class SmartPtrToObj;
/** System classes
 * @ZeroDivisionException
 * @NullPointerException
 * @SmartPtrToObj
 */
class bs_exception {
    protected:
       const char *txt;
    public:
       bs_exception(const char *_t = nullptr) : txt(_t) {}
       virtual ~bs_exception() {}
       virtual const char *what() const = 0;
};
class ZeroDivisionException : public bs_exception {
    public:
        ZeroDivisionException(const char *_p) : bs_exception(_p) {}
        ~ZeroDivisionException() {}
        const char *what() const override final { return this->txt; }
};
class NullPointerException : public bs_exception {
    public:
        NullPointerException(const char *_p) : bs_exception(_p) {}
        ~NullPointerException() {}
        const char *what() const override final { return this->txt; }
};        
class ObjectIsNotAPointerException : public bs_exception {
    public:
        ObjectIsNotAPointerException(const char *_p) : bs_exception(_p) {}
        ~ObjectIsNotAPointerException() {}
        const char *what() const override final { return this->txt; }
};        

constexpr bool NO_ARRAY = false;
constexpr bool IS_ARRAY = true;

template <class T = int, bool isArr = false> class SmartPtrToObj {
    private:
        T *object;
        void operator = (SmartPtrToObj<T>) {}
    public:
        SmartPtrToObj() : object(new T) {}    
        SmartPtrToObj(T *ptr) : object(ptr) {}
        SmartPtrToObj(T ptr) : object(ptr) {} // if array
        ~SmartPtrToObj() {
            if (isArr)
                delete[] object;
            else
                delete object; // call here a destuctor of the 'object'
        }
        T operator * () {
            return *this->object;
        }
        T *operator -> () {
            return this->object;
        }
        T operator [] (size_t ind) {
            if (!isArr)
                throw ObjectIsNotAPointerException("type of instanse of "
                       "'SmartPtrToObj' is not a pointer");
            return object[ind];
        } 
};
/** Sample:
 *     SmartPtrToObj<object, IS_ARRAY> arrPtr = new object[arraySize];
 *     SmartPtrToObj<object, NO_ARRAY> objPtr = new object;
 */
#endif
