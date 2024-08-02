/**
 * @file buffer.cc
 * @brief Implementation of the BufferView class.
 * @author mueller@fnal.gov
 * @author jwolcott@fnal.gov
*/
#include "H5Cpp.h"
#include "buffer.h"

namespace dlp
{
    /**
     * @brief A default constructor for the BufferView class.
    */
    template <typename T>
    BufferView<T>::BufferView()
        : fHandle(nullptr)
    {}

    /**
     * @brief A constructor for the BufferView class.
     * @param handle The handle to the buffer in the HDF5 file.
    */
    template <typename T>
    BufferView<T>::BufferView(const hvl_t* handle)
        : fHandle(handle)
    {}

    /**
     * @brief Get an iterator to the first object/entry in the buffer.
     * @return An iterator to the first object/entry in the buffer.
    */
    template <typename T>
    BufferView<T>::forward_iterator BufferView<T>::begin() const
    {
        return forward_iterator(this, 0);
    }

    /**
     * @brief Get an iterator to one past the last object/entry in the buffer.
     * @return An iterator to one past the last object/entry in the buffer.
    */
    template <typename T>
    BufferView<T>::forward_iterator BufferView<T>::end() const
    {
        return forward_iterator(this, size());
    }

    /**
     * @brief Get the object/entry at the specified index.
     * @param i The index of the object/entry to retrieve.
     * @return A reference to the object/entry at the specified index.
    */
    template <typename T>
    const T& BufferView<T>::operator[](std::size_t i) const
    {
        return static_cast<const T*>(fHandle->p)[i];
    }

    /**
     * @brief Reset the buffer to a new handle.
     * @param handle The new handle to use.
    */
    template <typename T>
    void BufferView<T>::reset(const hvl_t* handle)
    {
        fHandle = handle;
    }

    /**
     * @brief Get the size of the buffer.
     * @return The size of the buffer.
    */
    template <typename T>
    std::size_t BufferView<T>::size() const
    {
        return fHandle->len;
    }

    /**
     * @brief Constructor for the forward_iterator class.
     * @param buffer The BufferView object to iterate over.
     * @param idx The index to start at.
    */
    template <typename T>
    BufferView<T>::forward_iterator::forward_iterator(const BufferView<T>* buffer, long idx)
        : fBuffer(buffer), fIdx(idx)
    {}

    /**
     * @brief Prefix increment operator.
     * @return A reference to the incremented iterator.
    */
    template <typename T>
    BufferView<T>::forward_iterator& BufferView<T>::forward_iterator::operator++()
    {
        fIdx++;
        return *this;
    }

    /**
     * @brief Postfix increment operator.
     * @return A copy of the iterator before incrementing.
    */
    template <typename T>
    BufferView<T>::forward_iterator BufferView<T>::forward_iterator::operator++(int)
    {
        forward_iterator tmp(*this);
        operator++();
        return tmp;
    }

    /**
     * @brief Equality operator.
     * @param other The iterator to compare to.
     * @return True if the iterators are equal, false otherwise.
    */
    template <typename T>
    bool BufferView<T>::forward_iterator::operator==(forward_iterator other) const
    {
        return fIdx == other.fIdx;
    }

    /**
     * @brief Inequality operator.
     * @param other The iterator to compare to.
     * @return True if the iterators are not equal, false otherwise.
    */
    template <typename T>
    bool BufferView<T>::forward_iterator::operator!=(forward_iterator other) const
    {
        return fIdx != other.fIdx;
    }

    /**
     * @brief Dereference operator.
     * @return A reference to the current element.
    */
    template <typename T>
    const T& BufferView<T>::forward_iterator::operator*() const
    {
        return static_cast<const T*>(fBuffer->fHandle->p)[fIdx];
    }
}
/**
 * Explicit instantiation of the BufferView template class for the types
 * that we expect to use.
*/
template class dlp::BufferView<int32_t>;
template class dlp::BufferView<int64_t>;
template class dlp::BufferView<float>;