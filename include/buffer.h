/**
 * @file buffer.h
 * @brief Definition of the BufferView class.
 * @author mueller@fnal.gov
 * @author jwolcott@fnal.gov
*/
#ifndef BUFFER_H
#define BUFFER_H

#include "H5Cpp.h"

namespace dlp
{
    /**
     * @brief A class representing a view of a buffer in the HDF5 file.
     * 
     * This class consolidates the reading of variable-length arrays from the
     * HDF5 file. It provides a simple interface for accessing the data in the
     * buffer.
    */
    template <typename T>
    class BufferView
    {
        public:
        /**
         * @brief A default constructor for the BufferView class.
        */
        BufferView();

        /**
         * @brief A constructor for the BufferView class.
         * @param handle The handle to the buffer in the HDF5 file.
        */
        explicit BufferView(const hvl_t* handle);

        /**
         * @brief A class implementing a forward iterator for the BufferView class.
         * 
         * This class implements a template specialization of the forward iterator
         * for the BufferView class. It provides the necessary functionality to
         * iterate over the variable-length buffer in the HDF5 file.
        */
        class forward_iterator
        {
            public:
            /**
             * @brief Type definitions for the forward_iterator class.
             * 
             * These type definitions are required for the forward_iterator class
             * to be used as an iterator.
            */
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = const T*;
            using reference = const T&;
            using iterator_category = std::forward_iterator_tag;

            /**
             * @brief Constructor for the forward_iterator class.
             * @param buffer The BufferView object to iterate over.
             * @param idx The index to start at.
            */
            forward_iterator(const BufferView<T>* buffer, long idx = 0);

            /**
             * @brief Prefix increment operator.
             * @return A reference to the incremented iterator.
            */
            forward_iterator& operator++();

            /**
             * @brief Postfix increment operator.
             * @return A copy of the iterator before incrementing.
            */
            forward_iterator operator++(int);

            /**
             * @brief Equality operator.
             * @param other The iterator to compare to.
             * @return True if the iterators are equal, false otherwise.
            */
            bool operator==(forward_iterator other) const;

            /**
             * @brief Inequality operator.
             * @param other The iterator to compare to.
             * @return True if the iterators are not equal, false otherwise.
            */
            bool operator!=(forward_iterator other) const;

            /**
             * @brief Dereference operator.
             * @return A reference to the current element.
            */
            const T& operator*() const;

            private:
            const BufferView<T>* fBuffer;
            std::size_t fIdx;
        };

        /**
         * @brief Get an iterator to the first object/entry in the buffer.
         * @return An iterator to the first object/entry in the buffer.
        */
        forward_iterator begin() const;

        /**
         * @brief Get an iterator to one past the last object/entry in the buffer.
         * @return An iterator to one past the last object/entry in the buffer.
        */
        forward_iterator end() const;

        /**
         * @brief Get the object/entry at the specified index.
         * @param i The index of the object/entry to retrieve.
         * @return A reference to the object/entry at the specified index.
        */
        const T& operator[](std::size_t i) const;

        /**
         * @brief Reset the buffer to a new handle.
         * @param handle The new handle to use.
        */
        void reset(const hvl_t* handle);

        /**
         * @brief Get the size of the buffer.
         * @return The size of the buffer.
        */
        std::size_t size() const;

        private:
        const hvl_t* fHandle;
    };
}
#endif // BUFFER_H
