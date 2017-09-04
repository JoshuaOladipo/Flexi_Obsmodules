//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/Fibre/TransmissionEntry.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __TRANSMISSIONENTRY_M_H
#define __TRANSMISSIONENTRY_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
enum class Mux{Left, Right};
// }}

/**
 * Class generated from <tt>src/Base/Fibre/TransmissionEntry.msg:24</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * message TransmissionEntry
 * {
 *     double spectrumCenter;
 *     double spectrumLowerBound;
 *     double spectrumUpperBound;
 *     simtime_t startTime;
 *     simtime_t endTime;
 *     double power;
 *     double bitrate;
 *     Mux sender;
 *     bool readyForDeletion = false;
 * }
 * </pre>
 */
class TransmissionEntry : public ::omnetpp::cMessage
{
  protected:
    double spectrumCenter;
    double spectrumLowerBound;
    double spectrumUpperBound;
    ::omnetpp::simtime_t startTime;
    ::omnetpp::simtime_t endTime;
    double power;
    double bitrate;
    Mux sender;
    bool readyForDeletion;

  private:
    void copy(const TransmissionEntry& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TransmissionEntry&);

  public:
    TransmissionEntry(const char *name=nullptr, short kind=0);
    TransmissionEntry(const TransmissionEntry& other);
    virtual ~TransmissionEntry();
    TransmissionEntry& operator=(const TransmissionEntry& other);
    virtual TransmissionEntry *dup() const override {return new TransmissionEntry(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getSpectrumCenter() const;
    virtual void setSpectrumCenter(double spectrumCenter);
    virtual double getSpectrumLowerBound() const;
    virtual void setSpectrumLowerBound(double spectrumLowerBound);
    virtual double getSpectrumUpperBound() const;
    virtual void setSpectrumUpperBound(double spectrumUpperBound);
    virtual ::omnetpp::simtime_t getStartTime() const;
    virtual void setStartTime(::omnetpp::simtime_t startTime);
    virtual ::omnetpp::simtime_t getEndTime() const;
    virtual void setEndTime(::omnetpp::simtime_t endTime);
    virtual double getPower() const;
    virtual void setPower(double power);
    virtual double getBitrate() const;
    virtual void setBitrate(double bitrate);
    virtual Mux& getSender();
    virtual const Mux& getSender() const {return const_cast<TransmissionEntry*>(this)->getSender();}
    virtual void setSender(const Mux& sender);
    virtual bool getReadyForDeletion() const;
    virtual void setReadyForDeletion(bool readyForDeletion);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TransmissionEntry& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TransmissionEntry& obj) {obj.parsimUnpack(b);}


#endif // ifndef __TRANSMISSIONENTRY_M_H
