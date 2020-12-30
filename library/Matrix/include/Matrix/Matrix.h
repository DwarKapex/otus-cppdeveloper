/**
 * \brief main library header for Matrix
 *  TODO: Multidimentional sparced infinite matrix with default given value
 *  \code
 *  Matrix<int, -2, 5> m; // create 5D matrix of int with default value -2;
 *  \endcode
 * Idea:
 *  1. Use <map> to represent cell with value. It takes
 *  2. Overload operator[] by using matrixes with lower dimention so that it can be used in this manner
 *  \code
 *   Matrix <int,-1, 3> m;
 *   m [1][2][3][4] = 5;
 *   std::cout << m[1][2][3][4] << std::endl; // print "5";
 *   std::cout << m[1][2][3][3] << std::endl; // print "-1";
 *  \endcode
 */
#pragma once

#include <map>
#include <vector>

namespace Matrix {

//----------------------------------
#pragma mark Matrix declaration
//----------------------------------
template<typename ValueType, ValueType DefaultValue, size_t MainDimension = 2>
class Matrix
{
        using KeyType = std::vector<size_t>;
        using DataType = std::map<KeyType, ValueType>;
        using MatrixType = Matrix<ValueType, DefaultValue, MainDimension>;

    public:

        /**
         * \brief Use pattern Proxy to get access to element
         * 
         * \tparam ProxyDimention 
         */
        template<size_t ProxyDimention>
        class Proxy {
            public:
                Proxy(MatrixType* matrix, KeyType key)
                        : matrix_(matrix),
                            const_matrix_(nullptr),
                            key_(key) {}
            
                Proxy(const MatrixType* matrix, KeyType key)
                        : matrix_(nullptr),
                            const_matrix_(matrix),
                            key_(key) {}

                auto operator[](const size_t idx) {
                    key_[MainDimension - ProxyDimention] = idx;
                    if (matrix_)
                        return Proxy<ProxyDimention - 1>{matrix_, key_};
                    else
                        return Proxy<ProxyDimention - 1>{const_matrix_, key_};
                }
            
            private:
                MatrixType* matrix_;
                const MatrixType* const_matrix_;
                KeyType key_;
        };

         /// \brief Zero-dimention proxy to contain actual value of the element
        template<>
        class Proxy<0> {
            public:
                Proxy(MatrixType* matrix, KeyType key)
                        : matrix_(matrix),
                          const_matrix_(nullptr),
                          key_(key) {}

                Proxy(const MatrixType* matrix, KeyType key)
                        : matrix_(nullptr),
                          const_matrix_(matrix),
                          key_(key) {}


                operator ValueType() const {
                    if (matrix_)
                        return matrix_->get_value(key_);
                    else
                        return const_matrix_->get_value(key_);
                }
            
                auto operator=(const ValueType& value) {
                    return matrix_->set_value(key_, value);
                }

            private:
                MatrixType* matrix_;
                const MatrixType* const_matrix_;
                KeyType key_;
        };

        Matrix() = default;
        virtual ~Matrix() = default;
    
        // copy
        Matrix(const Matrix&) = default;
        Matrix& operator=(const Matrix&) = default;
        
        //move
        Matrix(Matrix&&) = default;
        Matrix& operator=(Matrix&&) = default;
        
        auto operator[](const size_t idx) {
            KeyType key(MainDimension, 0);
            key[0] = idx;
            return Proxy<MainDimension - 1>{this, key};
        };
    
        auto operator[](const size_t idx) const {
            KeyType key(MainDimension, 0);
            key[0] = idx;
            return Proxy<MainDimension - 1>{this, key};
        };


        size_t size() const {
            return data_.size();
        }

        auto begin() const {
            return data_.begin();
        }

        auto end() const {
            return data_.end();
        }

    private:
        DataType data_;
        
        auto get_value(const KeyType& key) const -> const ValueType{
            auto it = data_.find(key);
            if (it == data_.end()) {
                return DefaultValue;
            }
            else {
                return it->second;
            }
        }
        auto set_value(const KeyType& key, const ValueType& value) -> ValueType {
            if (value == DefaultValue){
                data_.erase(key);
            }
            else
                data_[key] = value;
            return value;
        }

};

} // namespace Matrix