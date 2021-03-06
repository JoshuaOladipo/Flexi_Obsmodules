//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/K_ShortestPathTableEntry.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __K_SHORTESTPATHTABLEENTRY_M_H
#define __K_SHORTESTPATHTABLEENTRY_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>src/Base/K_ShortestPathTableEntry.msg:16</tt> by nedtool.
 * <pre>
 * //
 * // This program is free software: you can redistribute it and/or modify
 * // it under the terms of the GNU Lesser General Public License as published by
 * // the Free Software Foundation, either version 3 of the License, or
 * // (at your option) any later version.
 * // 
 * // This program is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * // GNU Lesser General Public License for more details.
 * // 
 * // You should have received a copy of the GNU Lesser General Public License
 * // along with this program.  If not, see http://www.gnu.org/licenses/.
 * //
 * class K_ShortestPathTableEntry
 * {
 *     int srcAddress;
 *     int destAddress;
 *     double cost;
 *     double path[];
 * }
 * </pre>
 */
class K_ShortestPathTableEntry : public ::omnetpp::cObject
{
  protected:
    int srcAddress;
    int destAddress;
    double cost;
    double *path; // array ptr
    unsigned int path_arraysize;

  private:
    void copy(const K_ShortestPathTableEntry& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const K_ShortestPathTableEntry&);

  public:
    K_ShortestPathTableEntry();
    K_ShortestPathTableEntry(const K_ShortestPathTableEntry& other);
    virtual ~K_ShortestPathTableEntry();
    K_ShortestPathTableEntry& operator=(const K_ShortestPathTableEntry& other);
    virtual K_ShortestPathTableEntry *dup() const override {return new K_ShortestPathTableEntry(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSrcAddress() const;
    virtual void setSrcAddress(int srcAddress);
    virtual int getDestAddress() const;
    virtual void setDestAddress(int destAddress);
    virtual double getCost() const;
    virtual void setCost(double cost);
    virtual void setPathArraySize(unsigned int size);
    virtual unsigned int getPathArraySize() const;
    virtual double getPath(unsigned int k) const;
    virtual void setPath(unsigned int k, double path);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const K_ShortestPathTableEntry& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, K_ShortestPathTableEntry& obj) {obj.parsimUnpack(b);}


#endif // ifndef __K_SHORTESTPATHTABLEENTRY_M_H

