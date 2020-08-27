#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
#include <exception>
#include <stdexcept>


#ifndef CPP_EX3_HASHMAP_HPP
#define CPP_EX3_HASHMAP_HPP

const int DEFAULT_CAPACITY = 1;

const int INITIAL_CAPACITY = 16;

const double DEFAULT_HIGHER_CAPACITY = 0.75;

const double DEFAULT_LOWER_CAPACITY = 0.25;

const int QUADRATIC_FACTOR = 2;

const int EMPTY_SET = 0;

const bool TO_ADD = true;

const bool TO_DELETE = false;

static const int DEFAULT_SIZE = 0;

static const char *const INVALID_MSG = "Invalid input\n";

static const char *const USAGE_MSG = "Usage: SpamDetector <database path> <message path> <threshold>\n";

static const int NO_ELEMENTS = 0;

static const int ONE_PAIR_SIZE = 1;

static const bool CHECK_KEY_ONLY = true;

static const bool CHECK_KEY_AND_VALUE = false;

static const char *const FACTOR_RANGE_ERR = "Lower Load Factor or Upper Load Factor out of range";

static const char *const CAPACITY_VEC_ERR = "Capacities of the vectors must br equal";

static const char *const NOT_CONTAIN_ERR = "Table dose not contain the key";




template<class KeyT, class ValueT>
/**
 *A hash map container made up of (key,value) pairs, which can be
 * retrieved based on a key.
 * @tparam KeyT - represents a key for the map
 * @tparam ValueT - represents a value for the map
 */
class HashMap
{
    using bucket = std::vector<std::pair<KeyT, ValueT>>;
    using tuple = std::pair<KeyT, ValueT>;

    /**
     * iterator to the map
     */
    class Iterator
    {
    public:
        /**
         *Default Constructor
         */
        Iterator() = default;

        /**
         * Constructor
         * @param hashMap - the table
         * @param pair - (key,value)
         * @param pairNum - pair index in current bucket
         * @param buckNum - current bucket number
         */
        Iterator(const HashMap<KeyT, ValueT> *hashMap, tuple *pair, unsigned int pairNum, int buckNum)
        {
            _hashMap = hashMap;
            _pair = pair;
            _pairNum = pairNum;
            _numOfBucket = buckNum;
        }

        /**
         * Operator * overload
         * @return const reference to current pair
         */
        const tuple & operator*() const
        {
            return *_pair;
        }

        /**
         *Prefix operator overload
         */
        Iterator & operator++();

        /**
         *Postfix operator overload
         */
        Iterator operator++(int)
        {
            Iterator r(*this);
            ++*this;
            return r;
        }

        /**
         *Operator -> overload
         */
        const tuple *operator->()
        { return &(*_pair); }

        /**
         *Operator != overload
         */
        bool operator!=(const Iterator & other) const;

        /**
         *Operator == overload
         */
        bool operator==(const Iterator & other) const;


    private:

        tuple *_pair;

        const HashMap<KeyT, ValueT> *_hashMap;

        unsigned int _pairNum;

        int _numOfBucket;

        /**
         * Set the index of the next bucket
         */
        void _setNextBucket();

        /**
         * Set the index of the next bucket
         */
        void _setNextPair();


    };

private:

    int _currentCapacity;

    int _size;

    double _lowerLoadFactor;

    double _upperLoadFactor;

    bucket *_hashSet;


    /**
   * Clamps hashing indices to fit within the current table capacity
   *
   * @param index - the index before clamping
   * @return An index properly clamped
   */
    int _clamp(int index) const;

    /**
     * This method is given a capacity that fits to the new size of the Hash table
     * and creates new hash set with that capacity and re-adding the data according to the new parameters.
     * @param newCapacity - new capacity of the hash set
     */
    void _reHash(int newCapacity);

    /**
     * This method adds data to the new HashSet after Re-Hashing
     * @param oldTable -pointer to the old hash set before re-hashing
     * @param oldCapacity- The capacity of the old table
     */
    void _addItemsToNewTable(const bucket *oldTable, const int oldCapacity);

    /**
     * This method is given a key and value and getting the pair : (key,value)
     * from the hash set (assuming the key has exactly one appearance in the hash set )
     * @param key - key to get
     * @return the pair (key,value)
     */
    std::pair<KeyT, ValueT> & _getTuple(const KeyT & key) const;

    /**
   * This method checks if the current load factor is out of it's boundaries the check is done according
   * to the action that is currently occurring
   *
   * @param addFlag - a flag that indicates if the current action is either add or delete
   * @return true if the current loadFactor is out of it's boundaries.
   */
    bool _checkCapacity(bool addFlag) const;

    /**

     * @param pair  - pair of (KeyT,ValueT)
     * @param keyOnly - flag whether to check if only the key contained in one of the buckets
     * or the and it's value
     * @return key only is true: true if the key contains in it's bucket and false otherwise
     *          if pair : true if the pair contained in it's bucket and false otherwise
     */
    bool _isInBucket(const std::pair<KeyT, ValueT> & pair, bool keyOnly) const;


public:

    typedef Iterator const_iterator;


    /**
     * Default Constructor
     */
    HashMap();

    /**
     * Constructs a new hash map with default capacity and the given factors
     *
     * @param upperLoadFactor -the upper load factor before rehashing
     * @param lowerLoadFactor - the lower load factor before rehashing
     */
    HashMap(double upperFactor, double lowerFactor);

    /**
     *Constructor : given two vectors of the same size - called n
     * and creates hash map such that for all 0<= i < n keys[i] |-> values[i]
     * @param keys - vector of KeyT
     * @param values - vector of ValueT
     */
    HashMap(std::vector<KeyT> keys, std::vector<ValueT> values);

    /**
     * Copy Constructor
     */
    HashMap(const HashMap & other);

    /**
     * Move Constructor
     */
    HashMap(HashMap && other) noexcept: HashMap()
    { swap(other); }

    /**
   * Destructor
   */
    ~HashMap();

    /**
  * operator = overload
  */
    HashMap<KeyT, ValueT> & operator=(HashMap other);

    HashMap & operator=(HashMap && other) noexcept;

    /**
    * operator == overload
    */
    bool operator==(const HashMap & other) const;

    /**
     * operator != overload
     */
    bool operator!=(const HashMap & other) const;

    /**
     * const Operator [] overload
     */
    const ValueT & operator[](const KeyT & key) const;

    /**
     *Operator [] overload
     */
    ValueT & operator[](const KeyT & key);

    /**
     * This exchanges the elements between two maps
    */
    void swap(HashMap & other) noexcept;

    /**
     * This method is given a value and a key and tries to add the assignment(key|->value) it to the
     * hast set
     * @return true if the assignment(key|->value) has been added and false otherwise
     */
    bool insert(const KeyT & key, const ValueT & val);

    /**
     * @return True if the given key contained in the map and false otherwise
     */
    bool containsKey(const KeyT & key) const;

    /**
     * This method is given a key and tries to erase the the pair which contains it
     * @param key - KeyT
     * @return true if the pair has been removed and false otherwise
     */
    bool erase(const KeyT & key);

    /**
     * This methods clears the hash set from elements
     */
    void clear();

    /**
     *  This method is given a key and returns it's bucket index in the set and -1 if it has not been found
     * @param key - key value
     * @return returns it's bucket index in the set and -1 if it has not been found
     */
    int getKeyIndex(const KeyT & key) const;

    /**
    *@return The current capacity (number of cells) of the table.
    */
    int capacity() const;

    /**
     * @param key - key which contained in a pair within the hash set
     * @return The size of the key's bucket size
     */
    int bucketSize(const KeyT & key);

    /**
     * This method is given key which contained in a pair within the hash set and returns
     * the it's value ( key |-> value)
     * @param key - key which contained in a pair within the hash set
     * @return the value (key |-> value), if the hash set contains the key
     */
    ValueT & at(const KeyT & key) const;

    /**
     * @return true if the table is empty and false otherwise
     */
    bool empty() const;

    /**
     * @return The load factor value
     */
    double getLoadFactor() const;

    /**
     * @return the size of the collection(the numbers of values)
     */
    int size() const;

    /**
     * @return a read iterator that points to the first pair in the
     */
    const Iterator begin() const;

    /**
     * @return a read iterator that points to the last pair in the
     */
    const Iterator end() const;

    /**
     * @return a read iterator that points to the first pair in the
     */
    const Iterator cbegin() const
    {
        return begin();
    }

    /**
     * @return a read iterator that points to the last pair in the
     */
    const Iterator cend() const
    {
        return end();
    }
};

//=================HashMap implementation==================//



//Constructors and Destructor:

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap()
{
    _currentCapacity = INITIAL_CAPACITY;
    _lowerLoadFactor = DEFAULT_LOWER_CAPACITY;
    _upperLoadFactor = DEFAULT_HIGHER_CAPACITY;
    _size = NO_ELEMENTS;
    _hashSet = new bucket[_currentCapacity];
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(double lowerFactor, double upperFactor):HashMap()
{

    if (lowerFactor > upperFactor or lowerFactor <= 0 or upperFactor >= 1)
    {
        throw (std::invalid_argument(FACTOR_RANGE_ERR));
    }
    _lowerLoadFactor = lowerFactor;
    _upperLoadFactor = upperFactor;

}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(std::vector<KeyT> keys, std::vector<ValueT> values):HashMap()
{

    if (keys.size() != values.size())
    {
        throw std::invalid_argument(CAPACITY_VEC_ERR);
    }

    for (int i = 0; i < keys.size(); i++)
    {
        (*this)[keys[i]] = values[i];
    }

}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap & other)
{

    _currentCapacity = other._currentCapacity;
    _upperLoadFactor = other._upperLoadFactor;
    _lowerLoadFactor = other._lowerLoadFactor;
    _size = NO_ELEMENTS;
    _hashSet = new bucket[_currentCapacity];

    try
    {
        for (auto pair: other)
        {
            insert(pair.first, pair.second);
        }
    }
    catch (...)
    {
        delete[] _hashSet;
        throw;
    }
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::~HashMap()
{
    delete[] _hashSet;
}



//Operators Overload:

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> & HashMap<KeyT, ValueT>::operator=(HashMap other)
{
    swap(other);
    return *this;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator==(const HashMap & other) const
{
    if (_currentCapacity != other.capacity() or _size != other._size)
    {
        return false;
    }
    for (auto pair:other)
    {
        if (!_isInBucket(pair, CHECK_KEY_AND_VALUE))
        {
            return false;
        }
    }
    return true;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator!=(const HashMap & other) const
{
    return !(*this == other);
}

template<class KeyT, class ValueT>
const ValueT & HashMap<KeyT, ValueT>::operator[](const KeyT & key) const
{
    return at(key);
}

template<class KeyT, class ValueT>
ValueT & HashMap<KeyT, ValueT>::operator[](const KeyT & key)
{
    if (!containsKey(key))
    {
        insert(key, ValueT());
    }
    return at(key);
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> & HashMap<KeyT, ValueT>::operator=(HashMap && other) noexcept
{
    swap(other);
    *this;
}


//Other Public Methods:

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::getKeyIndex(const KeyT & key) const
{
    return _clamp(std::hash<KeyT>{}(key));
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::containsKey(const KeyT & key) const
{
    return _isInBucket(std::make_pair(key, ValueT()), CHECK_KEY_ONLY);
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::insert(const KeyT & key, const ValueT & val)
{
    if (containsKey(key))
    {
        return false;
    }

    _hashSet[getKeyIndex(key)].push_back(tuple(key, val));
    _size++;

    if (_checkCapacity(TO_ADD))
    {
        _reHash(capacity() * QUADRATIC_FACTOR);
    }
    return true;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::capacity() const
{
    return _currentCapacity;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucketSize(const KeyT & key)
{

    if (!containsKey(key))
    {
        throw (std::invalid_argument(NOT_CONTAIN_ERR));
    }
    return static_cast<int>(_hashSet[getKeyIndex(key)].size());
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::erase(const KeyT & key)
{
    if (!containsKey(key))
    {
        return false;
    }
    int currIndex = getKeyIndex(key);
    auto it = std::find(_hashSet[currIndex].begin(), _hashSet[currIndex].end(), _getTuple(key));

    _hashSet[currIndex].erase(it, it + 1);
    _size--;

    if (_checkCapacity(TO_DELETE))
    {
        _reHash(capacity() / QUADRATIC_FACTOR);
    }
    return true;
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::clear()
{
    for (int i = 0; i < _currentCapacity; i++)
    {
        _hashSet[i].clear();
    }
    _size = DEFAULT_SIZE;
}

template<class KeyT, class ValueT>
ValueT & HashMap<KeyT, ValueT>::at(const KeyT & key) const
{
    return _getTuple(key).second;
}

template<class KeyT, class ValueT>
const typename HashMap<KeyT, ValueT>::Iterator HashMap<KeyT, ValueT>::begin() const
{
    int numOfBucket = 0;

    while (numOfBucket < capacity() and _hashSet[numOfBucket].empty())
    {
        ++numOfBucket;

        if (numOfBucket >= capacity())
        {
            return end();
        }
    }
    return HashMap::Iterator(this, _hashSet[numOfBucket].data(), ONE_PAIR_SIZE, numOfBucket);
}

template<class KeyT, class ValueT>
const typename HashMap<KeyT, ValueT>::Iterator HashMap<KeyT, ValueT>::end() const
{
    bucket *last = _hashSet + (capacity() - 1);

    int lastSize = static_cast<int>(last->size());

    return HashMap::Iterator(this, last->data(), static_cast<unsigned int>(capacity()), lastSize);

}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::empty() const
{
    return size() == 0;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::size() const
{
    return _size;
}

template<class KeyT, class ValueT>
double HashMap<KeyT, ValueT>::getLoadFactor() const
{
    return ((double) (_size) / double(capacity()));
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::swap(HashMap & other) noexcept
{
    std::swap(_hashSet, other._hashSet);
    std::swap(_currentCapacity, other._currentCapacity);
    std::swap(_lowerLoadFactor, other._lowerLoadFactor);
    std::swap(_upperLoadFactor, other._upperLoadFactor);
    std::swap(_size, other._size);
}


//Private Methods:

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::_addItemsToNewTable(const bucket *oldTable, const int oldCapacity)
{

    for (int i = 0; i < oldCapacity; i++)
    {
        for (auto pair :oldTable[i])
        {
            insert(pair.first, pair.second);
        }
    }
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::_isInBucket(const std::pair<KeyT, ValueT> & pair, bool keyOnly) const
{
    int bucketIndex = getKeyIndex(pair.first);
    for (auto currPair:_hashSet[bucketIndex])
    {
        if (currPair.first == pair.first)
        {
            return keyOnly ? true : currPair.second == pair.second;
        }
    }
    return false;
}

template<class KeyT, class ValueT>
std::pair<KeyT, ValueT> & HashMap<KeyT, ValueT>::_getTuple(const KeyT & key) const
{
    int currIndex = getKeyIndex(key);

    for (int i = 0; i < _hashSet[currIndex].size(); i++)
    {
        if (_hashSet[currIndex][i].first == key)
        {
            return _hashSet[currIndex][i];
        }
    }
    throw (std::invalid_argument(NOT_CONTAIN_ERR));
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::_reHash(int newCapacity)
{

    if (newCapacity == EMPTY_SET)
    {
        newCapacity = DEFAULT_CAPACITY;
    }
    int oldCapacity = capacity();
    bucket *temp = _hashSet;
    _hashSet = new bucket[newCapacity];
    _currentCapacity = newCapacity;
    _size = DEFAULT_SIZE;
    try
    {
        _addItemsToNewTable(temp, oldCapacity);
    }
    catch (...)
    {
        delete[] temp;
        throw;
    }
    delete[] temp;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::_checkCapacity(bool addFlag) const
{
    double loadFactor = ((double) (_size) / double(capacity()));
    if (addFlag)
    {
        return loadFactor > _upperLoadFactor;
    }
    return loadFactor < _lowerLoadFactor;
}

template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::_clamp(int index) const
{
    return index & (capacity() - 1);
}

//Iterator Methods:

template<class KeyT, class ValueT>
typename HashMap<KeyT, ValueT>::Iterator & HashMap<KeyT, ValueT>::Iterator::operator++()
{
    _setNextPair();
    _setNextBucket();
    if (_numOfBucket >= _hashMap->capacity())
    {
        _pair = nullptr;
    }
    else
    {
        _pair = &_hashMap->_hashSet[_numOfBucket][_pairNum];
        _pairNum++;
    }
    return *this;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Iterator::operator!=(const HashMap<KeyT, ValueT>::Iterator & other) const
{
    if (_numOfBucket == other._numOfBucket)
    {
        return _pairNum != other._pairNum;
    }
    return _pair != NULL;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Iterator::operator==(const HashMap::Iterator & other) const
{
    return !(*this != other);
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::Iterator::_setNextBucket()
{

    while (_numOfBucket < _hashMap->capacity() and _hashMap->_hashSet[_numOfBucket].empty())
    {
        _numOfBucket++;
    }
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::Iterator::_setNextPair()
{
    if (_pairNum == _hashMap->_hashSet[_numOfBucket].size())
    {
        _numOfBucket++;
        _pairNum = 0;
    }
}

#endif

