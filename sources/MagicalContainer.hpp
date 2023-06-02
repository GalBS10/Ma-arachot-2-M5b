#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace ariel{};

class MagicalContainer
{
private:

public:
    std::vector<int> elements;        // Container to store all elements
    std::vector<int*> prime_elements;  // Container to store prime elements onlu pointers so it does not count as multiple lists.

    MagicalContainer();                              // Default constructor
    ~MagicalContainer();                             // Destructor
    MagicalContainer(const MagicalContainer& other);  // Copy constructor
    MagicalContainer(MagicalContainer&& other) noexcept;  // Move constructor

    bool isPrime(int number);  // Function to check if a number is prime
    void addElement(int element);   // Function to add an element to the container
    void removeElement(int element);  // Function to remove an element from the container
    int size();  // Function to return the size of the container
    MagicalContainer& operator=(const MagicalContainer& other);  // Copy assignment operator
    MagicalContainer& operator=(MagicalContainer&& other) noexcept;  // Move assignment operator

    class AscendingIterator
    {
    private:
        MagicalContainer* container;  // Pointer to the MagicalContainer object
        size_t currentIndex;  // Current index of the iterator

    public:
        AscendingIterator(MagicalContainer& container);  // Constructor
        AscendingIterator(const AscendingIterator& other);  // Copy constructor
        AscendingIterator(AscendingIterator&& other) noexcept;  // Move constructor
        ~AscendingIterator();  // Destructor
        AscendingIterator& operator=(const AscendingIterator& other);  // Copy assignment operator
        AscendingIterator& operator=(AscendingIterator&& other) noexcept;  // Move assignment operator

        bool operator==(const AscendingIterator& other) const;  // Equality operator
        bool operator!=(const AscendingIterator& other) const;  // Inequality operator
        bool operator<(const AscendingIterator& other) const;  // Less than operator
        bool operator>(const AscendingIterator& other) const;  // Greater than operator

        int operator*() const;  // Dereference operator

        AscendingIterator& operator++();  // Pre-increment operator
        AscendingIterator begin() const;  // Begin iterator
        AscendingIterator end() const;  // End iterator
    };

    class SideCrossIterator
    {
    private:
        MagicalContainer* container;  // Pointer to the MagicalContainer object
        size_t currentIndexLeft;  // Current left index of the iterator
        size_t currentIndexRight;  // Current right index of the iterator
        bool flag;  // Flag to indicate the iterator direction

    public:
        SideCrossIterator(MagicalContainer& container);  // Constructor
        SideCrossIterator(const SideCrossIterator& other);  // Copy constructor
        SideCrossIterator(SideCrossIterator&& other) noexcept;  // Move constructor
        ~SideCrossIterator();  // Destructor
        SideCrossIterator& operator=(const SideCrossIterator& other);  // Copy assignment operator
        SideCrossIterator& operator=(SideCrossIterator&& other) noexcept;  // Move assignment operator

        bool operator==(const SideCrossIterator& other) const;  // Equality operator
        bool operator!=(const SideCrossIterator& other) const;  // Inequality operator
        bool operator<(const SideCrossIterator& other) const;  // Less than operator
        bool operator>(const SideCrossIterator& other) const;  // Greater than operator

        int operator*() const;  // Dereference operator

        SideCrossIterator& operator++();  // Pre-increment operator
        SideCrossIterator begin() const;  // Begin iterator
        SideCrossIterator end() const;  // End iterator
    };

    class PrimeIterator
    {
    private:
        MagicalContainer* container;  // Pointer to the MagicalContainer object
        size_t currentIndex;  // Current index of the iterator

    public:
        PrimeIterator(MagicalContainer& container);  // Constructor
        PrimeIterator(const PrimeIterator& other);  // Copy constructor
        PrimeIterator(PrimeIterator&& other) noexcept;  // Move constructor
        ~PrimeIterator();  // Destructor
        PrimeIterator& operator=(const PrimeIterator& other);  // Copy assignment operator
        PrimeIterator& operator=(PrimeIterator&& other) noexcept;  // Move assignment operator

        bool operator==(const PrimeIterator& other) const;  // Equality operator
        bool operator!=(const PrimeIterator& other) const;  // Inequality operator
        bool operator<(const PrimeIterator& other) const;  // Less than operator
        bool operator>(const PrimeIterator& other) const;  // Greater than operator

        int operator*() const;  // Dereference operator

        PrimeIterator& operator++();  // Pre-increment operator
        PrimeIterator begin() const;  // Begin iterator
        PrimeIterator end() const;  // End iterator
    };
};
