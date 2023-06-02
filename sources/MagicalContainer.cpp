#include "MagicalContainer.hpp"
#include <algorithm>
#include <cmath>

using namespace std;

MagicalContainer::MagicalContainer()
{
    elements =  vector<int>();
    prime_elements = vector<int*>();
}

MagicalContainer::~MagicalContainer()
{
    // Clear the elements vector
    elements.clear();

    // Delete the prime elements (pointers) individually
    for (int* prime : prime_elements)
    {
        delete prime;
    }

    // Clear the prime elements vector
    prime_elements.clear();
}

MagicalContainer::MagicalContainer(const MagicalContainer& other)
{
    elements = other.elements;
    prime_elements = other.prime_elements;
}
MagicalContainer& MagicalContainer::operator=(MagicalContainer&& other) noexcept
{
    if (this != &other)
    {
        elements = std::move(other.elements);
        prime_elements = std::move(other.prime_elements);
    }
    return *this;
}

void MagicalContainer::addElement(int element)
{
    if (isPrime(element))
    {
        for (size_t i = 0; i < prime_elements.size(); i++)
        {
            if (element < *prime_elements.at(i))
            {
                int* elem = new int(element);
                prime_elements.insert(prime_elements.begin() + int(i), elem);
                break;
            }
        }
    }

    for (size_t i = 0; i < elements.size(); i++)
    {
        if (element < elements.at(i))
        {
            elements.insert(elements.begin() + int(i), element);
            return;
        }
    }

    elements.emplace_back(element);

    if (isPrime(element))
    {
        int* elem = new int(element);
        prime_elements.emplace_back(elem);
    }
}


void MagicalContainer::removeElement(int element)
{
    auto to_remove = find(elements.begin(), elements.end(), element);
    if (to_remove != elements.end())
    {
        elements.erase(to_remove);

        // Find and remove the element from prime_elements
        auto prime_iter = find_if(prime_elements.begin(), prime_elements.end(),
                                  [element](int* ptr) { return *ptr == element; });
        if (prime_iter != prime_elements.end())
        {
            delete *prime_iter;
            prime_elements.erase(prime_iter);
        }
    }
    else
    {
        throw std::runtime_error("Element not found in the container");
    }
}

int MagicalContainer::size()
{
    return elements.size();
}

MagicalContainer& MagicalContainer::operator=(const MagicalContainer& other){
    if (this != &other) {
        elements = other.elements;
        prime_elements = other.prime_elements;
    }
    return *this;
}

//--------------------AscendingIterator-------------------------------------//

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
    : container(&container), currentIndex(0) {
    
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), currentIndex(other.currentIndex) {
    
}

MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator&& other) noexcept
    : container(other.container), currentIndex(other.currentIndex) {
    other.container = nullptr;
    other.currentIndex = 0;
}

MagicalContainer::AscendingIterator::~AscendingIterator() {
    
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(AscendingIterator&& other) noexcept {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
        other.container = nullptr;
        other.currentIndex = 0;
    }
    return *this;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (this != &other) {
        if(container != other.container){
            throw runtime_error ("the containers are differents");
        }
        currentIndex = other.currentIndex;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {

    if(container != other.container){
            return false; 
        }
    return this->currentIndex == other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    return this->currentIndex < other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    return this->currentIndex > other.currentIndex;
}

int MagicalContainer::AscendingIterator::operator*() const {
    return this->container->elements.at(currentIndex);
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if(*this == this->end()){
        throw runtime_error ("beyond limits");
    }
    this->currentIndex = this->currentIndex+1;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    AscendingIterator iterator(*container);
    iterator.currentIndex = 0;
    return iterator;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    AscendingIterator iterator(*container);
    iterator.currentIndex = size_t(container->size());
    return iterator;
}

//--------------------SideCrossIterator-------------------------------------//

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
    : container(&container), currentIndexLeft(0),currentIndexRight(size_t(container.size()-1)), flag(true) {
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : container(other.container), currentIndexLeft(other.currentIndexLeft), currentIndexRight(other.currentIndexRight) {
}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {
}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& other) noexcept
    : container(other.container), currentIndexLeft(other.currentIndexLeft), currentIndexRight(other.currentIndexRight), flag(other.flag) {
    other.container = nullptr;
    other.currentIndexLeft = 0;
    other.currentIndexRight = 0;
    other.flag = true;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (this != &other) {
        if(container != other.container){
            throw runtime_error ("the containers are differents");
        }
        currentIndexLeft = other.currentIndexLeft;
        currentIndexRight = other.currentIndexRight;
        flag = other.flag;
    }
    return *this;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(SideCrossIterator&& other) noexcept {
    if (this != &other) {
        container = other.container;
        currentIndexLeft = other.currentIndexLeft;
        currentIndexRight = other.currentIndexRight;
        flag = other.flag;
        other.container = nullptr;
        other.currentIndexLeft = 0;
        other.currentIndexRight = 0;
        other.flag = true;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    if(container != other.container){
            return false; 
    }
    return this->currentIndexLeft == other.currentIndexLeft && this->currentIndexRight == other.currentIndexRight;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    return !(*this > other) && (*this != other); // only lower than without <=.
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    if(currentIndexLeft > other.currentIndexLeft){
        return true;
    }
    if(currentIndexLeft < other.currentIndexLeft){
        return false;
    }
    if(currentIndexRight < other.currentIndexRight){
        return true;
    }
    return false;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    if(flag){
        return this->container->elements.at(currentIndexLeft);
    }
    return this->container->elements.at(currentIndexRight);
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if(*this == this->end()){
        throw runtime_error ("beyond limits");
    }
    if(flag){
        this->currentIndexLeft++;
    }
    else{
        this->currentIndexRight--;
    }
    flag = !flag;
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    SideCrossIterator iterator(*container);
    iterator.currentIndexLeft = 0;
    iterator.currentIndexRight = size_t(container->size()-1);
    return iterator;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    SideCrossIterator iterator(*container);
    if(container->size()%2 != 0){
        iterator.currentIndexLeft = size_t((container->size()/2)+1);
        iterator.currentIndexRight = iterator.currentIndexLeft-1;
    }
    else{
        iterator.currentIndexLeft = size_t((container->size()/2));
        iterator.currentIndexRight = iterator.currentIndexLeft-1;
    }
    return iterator;
}

//--------------------PrimeIterator-------------------------------------//

bool MagicalContainer::isPrime(int number) // this function taken from stack overflow
{
    if(number<2 || (!(number&1) && number!=2))
        return false;
    for(int i=3; i*i<=number; i+=2){
        if(!(number%i))
            return false;
    }
    return true;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
    : container(&container), currentIndex(0){

}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : container(other.container), currentIndex(other.currentIndex){

}

MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator&& other) noexcept
    : container(other.container), currentIndex(other.currentIndex) {
    other.container = nullptr;
    other.currentIndex = 0;
}

MagicalContainer::PrimeIterator::~PrimeIterator() {
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (this != &other) {
        if(container != other.container){
            throw runtime_error ("the containers are differents");
        }
        currentIndex = other.currentIndex;
    }
    return *this;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(PrimeIterator&& other) noexcept {
    if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
        other.container = nullptr;
        other.currentIndex = 0;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    if(container != other.container){
        return false; 
    }
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    return currentIndex < other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
    return currentIndex > other.currentIndex;
}

int MagicalContainer::PrimeIterator::operator*() const {
    return *container->prime_elements.at(currentIndex);
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if(*this == this->end()){
        throw runtime_error ("beyond limits");
    }
    currentIndex++;
    return *this;
}


MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{
    MagicalContainer::PrimeIterator it(*container);
    it.currentIndex = 0;
    return it;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    MagicalContainer::PrimeIterator it(*container);
    it.currentIndex = container->prime_elements.size();
    return it;
}


