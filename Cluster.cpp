//
// Created by Quang Dang on 2/17/16.
//

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

#include "Cluster.h"

namespace Clustering {

    Cluster::Cluster() {
        __size = 0;
        __points = nullptr;
        head = nullptr;
    }

    void Cluster::__del() {

    }

    void Cluster::__cpy(LNodePtr pts) {

    }

    // The big three: cpy ctor, overloaded operator=, dtor
    bool Cluster::__in(const Point &p) const {
        return false;
    }

    Cluster::Cluster(const Cluster &__cl) {
        LNodePtr __n;
        LNodePtr __c;
        LNodePtr __l;
        if (__cl.head != nullptr) {
            head = new LNode;
            this->__size = __cl.__size;
            __c = __cl.head;
            head->point = __c->point;
            __l = head;
            __c = __c->next;
            for (int i = 1; i < __cl.__size; i++) {
                __n = new LNode(__c->point, nullptr);
                __l->next = __n;
                __l = __l->next;
                __c = __c->next;
            }
            __l->next = nullptr;
        } else {
            head = nullptr;
            __size = 0;
        }
    }

    Cluster &Cluster::operator=(const Cluster &__cl) {
        if (this == &__cl || *this == __cl) {       // assignment to itself
        } else if(__cl.head == nullptr) {       //assignment to an empty cluster
            this->clearList();
        } else {
            this->clearList();
            LNodePtr __new, __c, __f = __cl.head;
            __new = new LNode(__f->point, nullptr);
            head = __new;
            __c = head;
            __f = __f->next;
            for (int i = 1; i < __cl.__size; i++) {
                __new = new LNode(__f->point, nullptr);
                __c->next = __new;
                __c = __c->next;
                __f = __f->next;
            }
            __size = __cl.__size;
        }
        return *this;
    }

    bool operator==(const Cluster &leftSide, const Cluster &rightSide) {
        if (leftSide.__size < rightSide.__size || leftSide.__size > rightSide.__size) {
            return false;
        }
        LNodePtr nodeCheckSetOne = leftSide.head;
        LNodePtr nodeCheckSetTwo = rightSide.head;
        for (int i = 0; i < leftSide.__size; i++) {
            if (nodeCheckSetOne->point != nodeCheckSetTwo->point) {
                return false;
            }
            nodeCheckSetOne = nodeCheckSetOne->next;
            nodeCheckSetTwo = nodeCheckSetTwo->next;
        }
        return true;
    }

    Cluster::~Cluster() {
        clearList();
    }

    // Getters/setters
    int Cluster::getSize() const {
        return __size;
    }

    // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const Point &__pt) {
        LNodePtr __new = new LNode(__pt, nullptr);
        if (head != nullptr) {
            LNodePtr __c = head;
            LNodePtr __p = head;
            while (__c != nullptr) {
                if (__new->point <= __c->point) {
                    if (__c == head) {
                        head = __new;
                        __new->next = __c;
                        break;
                    } else {
                        __p->next = __new;
                        __new->next = __c;
                        break;
                    }
                } else {
                    if (__c->next != nullptr) {
                        __p = __c;
                        __c = __c->next;
                    } else {
                        __c->next = __new;
                        break;
                    }
                }
            }

        } else {
            head = __new;
        }
        __size++;
    }

    std::ostream &operator<<(std::ostream &os, const Cluster &__cl) {
        if(__cl.__size == 0) {
            return os;
        }
        LNodePtr __s = __cl.head;
        for (int i = 0; i < __cl.__size - 1; i++) {
            os << __s->point << " " << std::endl;
            __s = __s->next;
        }
        os << __s->point << " " << std::endl;
        return os;
    }

    std::istream &operator>>(std::istream &istream, Cluster &cluster) {
        // check if the stream is failing
        assert(!istream.fail());

        std::string value;              // Used to store the getline below- no use except for counting
        std::string line;
        std::string token;
        std::stringstream streamToPoint;
        while (std::getline(istream, line)) {
            int size;
            // Set the string we are going to parse
            streamToPoint.str(line);
            while(std::getline(streamToPoint, token, ',')) {
                size++;
            }
            // Create our new point
            Point newPoint(size);

            // clear the buffer and re assign the same string want to pass to new point
            // for it to parse
            streamToPoint.clear();
            streamToPoint.str(line);

            // Stream input to the new point
            streamToPoint >> newPoint;

            // Add the new point
            cluster += newPoint;
        }
        return istream;
    }

    const Point &Cluster::remove(const Point &__pt) {
        if (head != nullptr) {
            LNodePtr __p = head, __c = head, __n = __c->next;
            while (__c != nullptr) {
                if (__pt == __c->point) {
                    if (__c == head) {
                        head = __n;
                    }
                    delete __c;
                    __size--;
                    if (__p == nullptr) {
                        head = __n;
                        __c = __n;
                    } else {
                        __c = __n;
                        __p->next = __c;
                        if (__n != nullptr) {
                            __n = __n->next;
                        }
                    }
                } else {
                    __p = __c;
                    __c = __n;
                    if (__n != nullptr) {
                        __n = __n->next;
                    }
                }
            }
        }
        return __pt;
    }

    bool Cluster::contains(const Point &point) {
        LNodePtr check = head;

        while (check != nullptr) {
            if (check->point == point) {
                return true;
            }  else {
                check = check->next;
            }
        }
        return false;
    }

    bool operator!=(const Cluster &c1, const Cluster &c2) {
        return !(c1 == c2);
    }

    void Cluster::clearList() {
        // Check to see if the list is empty.
        if (head != nullptr) {
            if (__size > 1) {
                // If it isn't, create a loopNode that will use to obtain 1 node ahead of
                // the head node (or first node).
                LNodePtr __l = head->next;

                // loop size - 1, on to loop through 1 less than the total size.
                for (int i = 0; i < __size - 1; i++) {
                    // delete the node.
                    delete head;

                    if (__l != nullptr) {
                        if (__l->next != nullptr) {  // Only gets in here if loopNode points to another node (not nullptr).
                            head = __l;
                            __l = __l->next;
                        }
                        else { // gets executed when at the end of the list.
                            // Where loopNode is pointing to the last node in the list and head is pointing to the
                            // second to last node.
                            head = __l;
                            delete head;
                        }
                    }

                }
            } else {
                delete head;
            }
            head = nullptr;
            __size = 0;
        }
    }

    // Members: Subscript
    const Point &Cluster::operator[](unsigned int index) const {
        LNodePtr __c = head;
        for (int i = 0; i < index; i++) {
            __c = __c->next;
        }
        return __c->point;
    }

    Cluster &Cluster::operator+=(const Point &point) {
        add(point);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
        LNodePtr loopNodeFirst, loopNodeSecond;
        loopNodeSecond = head;
        for (int i = 0; i < __size; i++) {
            if (loopNodeSecond->point == rhs) {
                if (loopNodeSecond == head) {
                    loopNodeFirst = loopNodeSecond;
                    loopNodeSecond = loopNodeSecond->next;
                    head = loopNodeSecond;
                    delete loopNodeFirst;
                } else {
                    loopNodeFirst->next = loopNodeSecond->next;
                    delete loopNodeSecond;
                    loopNodeSecond = loopNodeFirst->next;
                }
                i--;
                __size--;
            } else {
                loopNodeFirst = loopNodeSecond;
                loopNodeSecond = loopNodeSecond->next;
            }
        }
        return *this;
    }

    Cluster &Cluster::operator+=(const Cluster &rightSide) {
        if (this == &rightSide) {
            return *this;
        }
        *this = (*this + rightSide);
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rightSide) {
        if (this == &rightSide) {
            return *this;
        }
        *this = (*this - rightSide);
        return *this;
    }

    const Cluster operator+(const Cluster &c, const Point &point) {
        Cluster newCluster(c);

        newCluster.add(point);
        return newCluster;
    }

    const Cluster operator-(const Cluster &c, const Point &point) {
        Cluster newCluster(c);

        newCluster.remove(point);
        return newCluster;
    }

    const Cluster operator+(const Cluster &__ls, const Cluster &__rs) {
        if (__ls == __rs) {
            return __ls;
        }
        Cluster __nc = __ls;

        LNodePtr __x = __rs.head;
        LNodePtr __ncp = __nc.head;
        bool __a = true;
        for (int i = 0; i < __rs.__size; i++) {
            for (int j = 0; j < __nc.__size; j++) {
                if (&__x->point == &__ncp->point) {
                    __a = false;
                    break;
                } else {
                    __ncp = __ncp->next;
                }
            }
            if (__a) {
                __nc.add(__x->point);
            }
            __x = __x->next;
            __ncp  = __nc.head;
            __a = true;
        }
        return __nc;
    }

    const Cluster operator-(const Cluster &__ls, const Cluster &__rs) {

        Cluster __nc(__ls);
        if (__ls == __rs) {
            __nc.clearList();
            return __nc;
        }

        LNodePtr __nst = __rs.head;
        LNodePtr __nl;
        __nl = __nc.head;

        for (int i = 0; i < __rs.__size; i++) {

            for (int j = 0; j < __nc.__size; j++) {

                if (__nst->point == __nl->point) {
                    __nc.remove(__nst->point);
                    break;
                }
                __nl = __nl->next;
            }
            __nst = __nst->next;
            __nl = __nc.head;
        }
        return __nc;
    }
}
