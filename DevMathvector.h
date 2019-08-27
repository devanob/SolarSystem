#ifndef DevMathVECTOR_H
#define DevMathVECTOR_H
#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <mutex>

namespace DevMath {
class generic_error : public std::exception{
public:
    generic_error(){
        this->error_mssg =(char*)"Error:Unknown";
    }
    generic_error(const char* mssg){
        this->error_mssg = (char*)mssg;

    }
    char* error_mssg;
    unsigned int error_code;
    virtual const char* what() const throw(){
       return (const char*) this->error_mssg;
    }
};
class EmptyVectorOperation : public generic_error{
    public:
        EmptyVectorOperation():generic_error((char*)"Exception Error: Operation On Empty Vector"){

        }


}; // throws an exception when operations are done on an empty vector
class VectorOperationUnevenLength : public generic_error {
    public:
        VectorOperationUnevenLength():generic_error((char*)"Exception Error: Even Vector Pair Operation"){

        }


};
class IndexOutOfBound : generic_error {
    public:
        IndexOutOfBound():generic_error((char*)"Exception Error:Index Out Of Bound"){

        }
};
template <class type>
class vector {


public:
    // mutex function
    std::mutex& getMutexLock(); //gets the internel mutex
    void lock_vector_mut() ; // lock the internel mutex
    void unlock_vector_mut();
    bool try_lock_mut ();
    //unlock the internel mutex
    vector(const vector& vector_); // contructors
    vector(vector&& vector_); // move contructor
    template <class seperate_type>
    vector(const DevMath::vector<seperate_type>& vector_);
    template <class seperate_type>
    vector(DevMath::vector<seperate_type>&& vector_);

    vector();
    vector(const unsigned int& intial_size);
    //-------------------------------------------------
    template <class seperate_type>
    inline DevMath::vector<type>& operator=(const DevMath::vector<seperate_type>& vector_);
    inline DevMath::vector<type>& operator=(const DevMath::vector<type>& vector_); // copy operator and move operator
    template <class seperate_type>
    inline DevMath::vector<type>& operator=(DevMath::vector<seperate_type>&& vector_);
    inline DevMath::vector<type>& operator=(DevMath::vector<type>&& vector_);

    template <class c_type>
    inline void assign(const vector<c_type>& vector_);

    template <class c_type>
    inline void assign(vector<c_type>&&);
    //---------------------------------------------------
    inline type& operator[](const unsigned int& index); // push pack values//resize
    inline const type& operator[](const unsigned int& index) const;

    inline void push_back(const type& var);
    inline void resize(const unsigned int& size);
    inline void clear();
    inline const type* data_ptr() const;
    inline const std::vector<type>& data_vector() const;

    //-------------------------------------------------------------------------
    //
    template <class c_type>
    bool operator==(const vector<c_type>& vector_) const;

    template <class c_type>
    bool operator!=(const vector<c_type>& vector_) const;

    template <class vector_type>
    type operator*(const vector<vector_type>& vector_);

    vector<type> operator/(const type& divider) const; // vector arthimetic

    DevMath::vector<type>& operator/=(const type& divider);

    vector<type> operator*(const type& divider) const;

    DevMath::vector<type>& operator*=(const type& divider);

    template <class vector_type>
    vector<type> operator+(const DevMath::vector<vector_type>& vector_) const;

    template <class vector_type>
    vector<type>& operator+(DevMath::vector<vector_type>&& vector_) const;

    template <class vector_type>
    DevMath::vector<type>& operator+=(const DevMath::vector<vector_type>& vector_);

    template <class vector_type>
    DevMath::vector<type>& operator+=(DevMath::vector<vector_type>&& vector_);

    unsigned int size() const;
    //-------------------------------------------------------------------GENERAL-
    template <class vector_type>
    type dot(const vector<vector_type>& vector_);
    type normVec(unsigned int& norm_count);
    type length_n();
    type* ptr_vec();

private:
    std::mutex vector_lock;
    std::vector<type> data;
};
template <class type>
void swap(DevMath::vector<type>& vector1, DevMath::vector<type>& vector2);

template <class type_matrix>
vector<type_matrix> operator*(const type_matrix& numoper, const DevMath::vector<type_matrix>& vec1);
}
template <class type>
DevMath::vector<type>::vector()
{
}

template <class type>
DevMath::vector<type>::vector(const vector& vector_)
{
    this->data = vector_.data;
}

template <class type>
template <class seperate_type>
DevMath::vector<type>::vector(const DevMath::vector<seperate_type>& vector_)
{
    try {
        assign(vector_);
    }
    catch (std::exception& except) {
        throw std::runtime_error("Error Assigning Vector Defualt Contructor");
    }
}

template <class type>
template <class seperate_type>
DevMath::vector<type>::vector(DevMath::vector<seperate_type>&& vector_)
{
    try {
        assign(std::move(vector_));
    }
    catch (std::exception& except) {
        throw std::runtime_error("Error In Vector Assignment in Vector Defualt Contructor-Move");
    }
}

template <class type>
DevMath::vector<type>::vector(vector&& vector_)
{
    data = std::move(vector_.data);
}

template <class type>
DevMath::vector<type>& DevMath::vector<type>::operator=(const DevMath::vector<type>& vector_)
{
    data = vector_.data;
    return *this;
}
template <class type>
template <class seperate_type>
DevMath::vector<type>& DevMath::vector<type>::operator=(const DevMath::vector<seperate_type>& vector_)
{
    try {
        assign(vector_);
    }
    catch (std::exception& except) {
        throw std::runtime_error("Error In Vector Assignment in Vector Operator= ");
    }

    return *this;
}
template <class type>
DevMath::vector<type>& DevMath::vector<type>::operator=(DevMath::vector<type>&& vector_)
{
    try {
        assign(std::move(vector_));
    }
    catch (std::exception& except) {
        throw std::runtime_error("Error In Vector Assignment in Vector Operator=move ");
    }

    return *this;
}

template <class type>
template <class seperate_type>
DevMath::vector<type>& DevMath::vector<type>::operator=(DevMath::vector<seperate_type>&& vector_)
{
    try {
        assign(std::move(vector_));
    }
    catch (std::exception& except) {
        throw std::runtime_error("Error In Vector Assignment in Vector Operator=move ");
    }

    return *this;
}

template <class type>
type& DevMath::vector<type>::operator[](const unsigned int& index)
{

    if (data.size() == 0 || index >= data.size() || index < 0) {
        throw IndexOutOfBound();
    }


    return data[index];
}
template <class type>
const type& DevMath::vector<type>::operator[](const unsigned int& index) const
{
    if (data.size() == 0 || index >= data.size() || index < 0)
        IndexOutOfBound();
    return data[index];
}

template <class type>
void DevMath::vector<type>::push_back(const type& var)
{
    data.push_back(var);
}

template <class type>
DevMath::vector<type>::vector(const unsigned int& intial_size)
{
    data.resize(intial_size);
}

template <class type>
DevMath::vector<type> DevMath::vector<type>::operator/(const type& divider) const
{
    if (data.size() == 0)
        throw EmptyVectorOperation();
    else {
        const unsigned int& size_vector = data.size();
        DevMath::vector<type> temp = *this;
        for (unsigned int i = 0; i < size_vector; i++) {
            temp.data[i] /= divider;
        }
        return std::move(temp);
    }
}
template <class type>
DevMath::vector<type>& DevMath::vector<type>::operator/=(const type& divider)
{
    if (data.size() == 0)
        throw EmptyVectorOperation();

    else {
        const unsigned int& size_vector = data.size();
        for (unsigned int i = 0; i < size_vector; i++) {
            data[i] /= divider;
        }
    }
    return *this;
}

template <class type>
DevMath::vector<type>& DevMath::vector<type>::operator*=(const type& divider)
{
    if (data.size() == 0)
        throw EmptyVectorOperation();

    else {
        const unsigned int& size_vector = data.size();
        for (unsigned int i = 0; i < size_vector; i++) {
            data[i] *= divider;
        }
    }
    return *this;
}

template <class type>
DevMath::vector<type> DevMath::vector<type>::operator*(const type& divider) const
{
    if (data.size() == 0)
        throw EmptyVectorOperation();
    else {
        const unsigned int& size_vector = data.size();
        DevMath::vector<type> temp = *this;

        for (unsigned int i = 0; i < size_vector; i++) {
            temp.data[i] *= divider;
        }
        return std::move(temp);
    }
}

template <class type>
template <class vector_type>
DevMath::vector<type> DevMath::vector<type>::operator+(const DevMath::vector<vector_type>& vector_) const
{
    if (vector_.data.size() != data.size()) {
        throw VectorOperationUnevenLength();
    }
    else {
        const unsigned int& data_size = vector_.data.size();
        DevMath::vector<type> temp(data_size);
        for (unsigned int i = 0; i < data_size; i++) {
            temp.data[i] = vector_.data[i] + data[i];
        };
        return std::move(temp);
    }
}

template <class type>
template <class vector_type>
DevMath::vector<type>& DevMath::vector<type>::operator+(DevMath::vector<vector_type>&& vector_) const
{
    if (vector_.data.size() != data.size()) {
        throw VectorOperationUnevenLength();
    }
    else {
        const unsigned int& data_size = vector_.data.size();
        for (unsigned int i = 0; i < data_size; i++) {
            vector_.data[i] += data[i];
        };
        return vector_;
    }
}

template <class type>
template <class vector_type>
DevMath::vector<type>& DevMath::vector<type>::operator+=(const vector<vector_type>& vector_)
{
    if (vector_.data.size() != data.size()) {
        throw VectorOperationUnevenLength();
    }
    else {
        const unsigned int& data_size = vector_.data.size();
        for (unsigned int i = 0; i < data_size; i++) {
            data[i] += vector_.data[i];
        };
    }
    return *this;
}

template <class type>
template <class vector_type>
DevMath::vector<type>& DevMath::vector<type>::operator+=(vector<vector_type>&& vector_)
{
    if (vector_.data.size() != data.size()) {
        throw VectorOperationUnevenLength();
    }
    else {
        unsigned int data_size = vector_.data.size();
        for (unsigned int i = 0; i < data_size; i++) {
            data[i] += vector_.data[i];
        };
    }
    return *this;
}
template <class type>
void DevMath::vector<type>::resize(const unsigned int& size)
{
    data.resize(size);
}

template <class type>
void DevMath::swap(DevMath::vector<type>& vector1, DevMath::vector<type>& vector2)
{
    DevMath::vector<type> temp(std::move(vector1));
    vector1 = std::move(vector2);
    vector2 = std::move(temp);
}

template <class type>
std::mutex& DevMath::vector<type>::getMutexLock()
{
    return vector_lock;
}
template <class type>
unsigned int DevMath::vector<type>::size() const
{
    return this->data.size();
}

template<class type>
type DevMath::vector<type>::normVec(unsigned int &norm_count)
{
    type norm_count_dim = type(0);
}

template<class type>
type DevMath::vector<type>::length_n()
{
    type sqrted_val;
    for (unsigned int i = 0; i < this->data.size(); i++){
        sqrted_val+= std::pow(data[i],2);
    }
    return std::sqrt(sqrted_val);

}

template<class type>
type *DevMath::vector<type>::ptr_vec()
{
    return data.data();

}
template <class type>
template <class vector_type>
type DevMath::vector<type>::dot(const vector<vector_type>& vector_)
{
    type dot_product = 0;
    if (vector_.size() != this->size())
        throw VectorOperationUnevenLength();
    for (unsigned int i = 0; i < vector_.size(); i++) {
        dot_product += vector_[i] * data[i];
    }
    return std::move(dot_product);
}

template <class type>
template <class vector_type>

type DevMath::vector<type>::operator*(const vector<vector_type>& vector_)
{
    type dot_product = 0;
    if (vector_.size() != this->size())
        throw VectorOperationUnevenLength();
    for (unsigned int i = 0; i < vector_.size(); i++) {
        dot_product += vector_[i] * data[i];
    }
    return std::move(dot_product);
}
template <class type>
template <class c_type>
void DevMath::vector<type>::assign(const vector<c_type>& vector_)
{

    if (vector_.size() == 0) {
        this->data.clear();
    }
    else {
        try {
            this->data.clear();
            this->data.assign(vector_.data_vector().begin(), vector_.data_vector().end());
        }
        catch (std::exception& expt) {
            throw std::runtime_error("Unable To Do Such Assignment On DevMathvector<type,c_type>");
        }
    }
}
template <class type>
template <class c_type>
void DevMath::vector<type>::assign(vector<c_type>&& vector_)
{
    if (vector_.size() == 0) {
        this->data.clear();
    }
    else {
        try {
            this->data = std::move(vector_.data_vector());
        }
        catch (const std::exception& expt) {
            try {
                this->data.assign(vector_.data_vector().begin(), vector_.data_vector().end());
                vector_.clear();
            }
            catch (std::exception& expt) {
                throw std::runtime_error("Unable To Do Such Assignment On DevMathvector<type,c_type>");
            }
        }
        vector_.clear();
    }
}
template <class type>
void DevMath::vector<type>::clear()
{
    data.clear();
}
template <class type>
template <class c_type>
bool DevMath::vector<type>::operator==(const vector<c_type>& vector_) const
{
    if (vector_.size() != data.size())
        return false;
    else {
        unsigned int dat_size = vector_.size();
        for (unsigned int i = 0; i < dat_size; i++) {
            if (data[i] != vector_[i])
                return false;
        }
    }
    return true;
}

template <class type>
template <class c_type>
bool DevMath::vector<type>::operator!=(const vector<c_type>& vector_) const
{
    if (vector_.size() != data.size())
        return true;
    else {
        unsigned int dat_size = vector_.size();
        for (unsigned int i = 0; i < dat_size; i++) {
            if (data[i] != vector_[i])
                return true;
        }
    }
    return false;
}
template <class type_matrix>
DevMath::vector<type_matrix> operator*(const type_matrix& numoper, const DevMath::vector<type_matrix>& vec1)
{
    return std::move(vec1 * numoper);
}

template <class type>
const type* DevMath::vector<type>::data_ptr() const
{
    return this->data.data();
}
template <class type>
const std::vector<type>& DevMath::vector<type>::data_vector() const
{
    return this->data;
}
template<class type>
void DevMath::vector<type>::lock_vector_mut() {
    this->vector_lock.lock();
}
template<class type>
void DevMath::vector<type>::unlock_vector_mut() {
    this->vector_lock.unlock();
}
template<class type>
bool DevMath::vector<type>::try_lock_mut() {
    return this->vector_lock.try_lock();
}

#endif // DevMathVECTOR_H
