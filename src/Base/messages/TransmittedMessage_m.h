//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/TransmittedMessage.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __TRANSMITTEDMESSAGE_M_H
#define __TRANSMITTEDMESSAGE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
    #include "TransmissionEntry_m.h"
     typedef TransmissionEntry *tEntryPtr; 
// }}

/**
 * Class generated from <tt>src/Base/messages/TransmittedMessage.msg:21</tt> by nedtool.
 * <pre>
 * packet TransmittedMessage
 * {
 *     \@customize(true);
 *     double sourcePower \@unit(db);
 *     bool hasPassedFirstStation = false;
 *     bool isControl;
 *     bool isReadable;
 *     tEntryPtr transmissionEntry;
 *     simtime_t sourceSendTIme;
 * }
 * </pre>
 *
 * TransmittedMessage_Base is only useful if it gets subclassed, and TransmittedMessage is derived from it.
 * The minimum code to be written for TransmittedMessage is the following:
 *
 * <pre>
 * class TransmittedMessage : public TransmittedMessage_Base
 * {
 *   private:
 *     void copy(const TransmittedMessage& other) { ... }

 *   public:
 *     TransmittedMessage(const char *name=nullptr, short kind=0) : TransmittedMessage_Base(name,kind) {}
 *     TransmittedMessage(const TransmittedMessage& other) : TransmittedMessage_Base(other) {copy(other);}
 *     TransmittedMessage& operator=(const TransmittedMessage& other) {if (this==&other) return *this; TransmittedMessage_Base::operator=(other); copy(other); return *this;}
 *     virtual TransmittedMessage *dup() const override {return new TransmittedMessage(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from TransmittedMessage_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(TransmittedMessage)
 * </pre>
 */
class TransmittedMessage_Base : public ::omnetpp::cPacket
{
  protected:
    double sourcePower;
    bool hasPassedFirstStation;
    bool isControl;
    bool isReadable;
    tEntryPtr transmissionEntry;
    ::omnetpp::simtime_t sourceSendTIme;

  private:
    void copy(const TransmittedMessage_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TransmittedMessage_Base&);
    // make constructors protected to avoid instantiation
    TransmittedMessage_Base(const char *name=nullptr, short kind=0);
    TransmittedMessage_Base(const TransmittedMessage_Base& other);
    // make assignment operator protected to force the user override it
    TransmittedMessage_Base& operator=(const TransmittedMessage_Base& other);

  public:
    virtual ~TransmittedMessage_Base();
    virtual TransmittedMessage_Base *dup() const override {throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class TransmittedMessage");}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getSourcePower() const;
    virtual void setSourcePower(double sourcePower);
    virtual bool getHasPassedFirstStation() const;
    virtual void setHasPassedFirstStation(bool hasPassedFirstStation);
    virtual bool getIsControl() const;
    virtual void setIsControl(bool isControl);
    virtual bool getIsReadable() const;
    virtual void setIsReadable(bool isReadable);
    virtual tEntryPtr& getTransmissionEntry();
    virtual const tEntryPtr& getTransmissionEntry() const {return const_cast<TransmittedMessage_Base*>(this)->getTransmissionEntry();}
    virtual void setTransmissionEntry(const tEntryPtr& transmissionEntry);
    virtual ::omnetpp::simtime_t getSourceSendTIme() const;
    virtual void setSourceSendTIme(::omnetpp::simtime_t sourceSendTIme);
};


#endif // ifndef __TRANSMITTEDMESSAGE_M_H

