//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/Fibre/ReservationTimer.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "ReservationTimer_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(ReservationTimer)

ReservationTimer::ReservationTimer(const char *name, short kind) : ::TransmittedMessage_Base(name,kind)
{
    this->setByteLength(150);
    this->setIsControl(true);

    this->numseq = 0;
    this->burstifierId = 0;
    this->spectrumCenter = 0;
    this->spectrumLowerBound = 0;
    this->spectrumUpperBound = 0;
    this->msgSize = 0;
    this->msgOffset = 0;
    this->msgDuration = 0;
    this->timerStart = 0;
    this->timerEnd = 0;
    this->channelIndex = 0;
    this->senderId = 0;
}

ReservationTimer::ReservationTimer(const ReservationTimer& other) : ::TransmittedMessage_Base(other)
{
    copy(other);
}

ReservationTimer::~ReservationTimer()
{
}

ReservationTimer& ReservationTimer::operator=(const ReservationTimer& other)
{
    if (this==&other) return *this;
    ::TransmittedMessage_Base::operator=(other);
    copy(other);
    return *this;
}

void ReservationTimer::copy(const ReservationTimer& other)
{
    this->numseq = other.numseq;
    this->burstifierId = other.burstifierId;
    this->spectrumCenter = other.spectrumCenter;
    this->spectrumLowerBound = other.spectrumLowerBound;
    this->spectrumUpperBound = other.spectrumUpperBound;
    this->msgSize = other.msgSize;
    this->msgOffset = other.msgOffset;
    this->msgDuration = other.msgDuration;
    this->timerStart = other.timerStart;
    this->timerEnd = other.timerEnd;
    this->channelIndex = other.channelIndex;
    this->senderId = other.senderId;
}

void ReservationTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::TransmittedMessage_Base::parsimPack(b);
    doParsimPacking(b,this->numseq);
    doParsimPacking(b,this->burstifierId);
    doParsimPacking(b,this->spectrumCenter);
    doParsimPacking(b,this->spectrumLowerBound);
    doParsimPacking(b,this->spectrumUpperBound);
    doParsimPacking(b,this->msgSize);
    doParsimPacking(b,this->msgOffset);
    doParsimPacking(b,this->msgDuration);
    doParsimPacking(b,this->timerStart);
    doParsimPacking(b,this->timerEnd);
    doParsimPacking(b,this->channelIndex);
    doParsimPacking(b,this->senderId);
}

void ReservationTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::TransmittedMessage_Base::parsimUnpack(b);
    doParsimUnpacking(b,this->numseq);
    doParsimUnpacking(b,this->burstifierId);
    doParsimUnpacking(b,this->spectrumCenter);
    doParsimUnpacking(b,this->spectrumLowerBound);
    doParsimUnpacking(b,this->spectrumUpperBound);
    doParsimUnpacking(b,this->msgSize);
    doParsimUnpacking(b,this->msgOffset);
    doParsimUnpacking(b,this->msgDuration);
    doParsimUnpacking(b,this->timerStart);
    doParsimUnpacking(b,this->timerEnd);
    doParsimUnpacking(b,this->channelIndex);
    doParsimUnpacking(b,this->senderId);
}

int ReservationTimer::getNumseq() const
{
    return this->numseq;
}

void ReservationTimer::setNumseq(int numseq)
{
    this->numseq = numseq;
}

int ReservationTimer::getBurstifierId() const
{
    return this->burstifierId;
}

void ReservationTimer::setBurstifierId(int burstifierId)
{
    this->burstifierId = burstifierId;
}

double ReservationTimer::getSpectrumCenter() const
{
    return this->spectrumCenter;
}

void ReservationTimer::setSpectrumCenter(double spectrumCenter)
{
    this->spectrumCenter = spectrumCenter;
}

double ReservationTimer::getSpectrumLowerBound() const
{
    return this->spectrumLowerBound;
}

void ReservationTimer::setSpectrumLowerBound(double spectrumLowerBound)
{
    this->spectrumLowerBound = spectrumLowerBound;
}

double ReservationTimer::getSpectrumUpperBound() const
{
    return this->spectrumUpperBound;
}

void ReservationTimer::setSpectrumUpperBound(double spectrumUpperBound)
{
    this->spectrumUpperBound = spectrumUpperBound;
}

double ReservationTimer::getMsgSize() const
{
    return this->msgSize;
}

void ReservationTimer::setMsgSize(double msgSize)
{
    this->msgSize = msgSize;
}

::omnetpp::simtime_t ReservationTimer::getMsgOffset() const
{
    return this->msgOffset;
}

void ReservationTimer::setMsgOffset(::omnetpp::simtime_t msgOffset)
{
    this->msgOffset = msgOffset;
}

::omnetpp::simtime_t ReservationTimer::getMsgDuration() const
{
    return this->msgDuration;
}

void ReservationTimer::setMsgDuration(::omnetpp::simtime_t msgDuration)
{
    this->msgDuration = msgDuration;
}

::omnetpp::simtime_t ReservationTimer::getTimerStart() const
{
    return this->timerStart;
}

void ReservationTimer::setTimerStart(::omnetpp::simtime_t timerStart)
{
    this->timerStart = timerStart;
}

::omnetpp::simtime_t ReservationTimer::getTimerEnd() const
{
    return this->timerEnd;
}

void ReservationTimer::setTimerEnd(::omnetpp::simtime_t timerEnd)
{
    this->timerEnd = timerEnd;
}

int ReservationTimer::getChannelIndex() const
{
    return this->channelIndex;
}

void ReservationTimer::setChannelIndex(int channelIndex)
{
    this->channelIndex = channelIndex;
}

int ReservationTimer::getSenderId() const
{
    return this->senderId;
}

void ReservationTimer::setSenderId(int senderId)
{
    this->senderId = senderId;
}

class ReservationTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ReservationTimerDescriptor();
    virtual ~ReservationTimerDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ReservationTimerDescriptor)

ReservationTimerDescriptor::ReservationTimerDescriptor() : omnetpp::cClassDescriptor("ReservationTimer", "TransmittedMessage_Base")
{
    propertynames = nullptr;
}

ReservationTimerDescriptor::~ReservationTimerDescriptor()
{
    delete[] propertynames;
}

bool ReservationTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ReservationTimer *>(obj)!=nullptr;
}

const char **ReservationTimerDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ReservationTimerDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ReservationTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount() : 12;
}

unsigned int ReservationTimerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<12) ? fieldTypeFlags[field] : 0;
}

const char *ReservationTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "numseq",
        "burstifierId",
        "spectrumCenter",
        "spectrumLowerBound",
        "spectrumUpperBound",
        "msgSize",
        "msgOffset",
        "msgDuration",
        "timerStart",
        "timerEnd",
        "channelIndex",
        "senderId",
    };
    return (field>=0 && field<12) ? fieldNames[field] : nullptr;
}

int ReservationTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numseq")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstifierId")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "spectrumCenter")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "spectrumLowerBound")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "spectrumUpperBound")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgSize")==0) return base+5;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgOffset")==0) return base+6;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgDuration")==0) return base+7;
    if (fieldName[0]=='t' && strcmp(fieldName, "timerStart")==0) return base+8;
    if (fieldName[0]=='t' && strcmp(fieldName, "timerEnd")==0) return base+9;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelIndex")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderId")==0) return base+11;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ReservationTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "double",
        "double",
        "double",
        "double",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "int",
        "int",
    };
    return (field>=0 && field<12) ? fieldTypeStrings[field] : nullptr;
}

const char **ReservationTimerDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ReservationTimerDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ReservationTimerDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ReservationTimer *pp = (ReservationTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ReservationTimerDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ReservationTimer *pp = (ReservationTimer *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ReservationTimerDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ReservationTimer *pp = (ReservationTimer *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNumseq());
        case 1: return long2string(pp->getBurstifierId());
        case 2: return double2string(pp->getSpectrumCenter());
        case 3: return double2string(pp->getSpectrumLowerBound());
        case 4: return double2string(pp->getSpectrumUpperBound());
        case 5: return double2string(pp->getMsgSize());
        case 6: return simtime2string(pp->getMsgOffset());
        case 7: return simtime2string(pp->getMsgDuration());
        case 8: return simtime2string(pp->getTimerStart());
        case 9: return simtime2string(pp->getTimerEnd());
        case 10: return long2string(pp->getChannelIndex());
        case 11: return long2string(pp->getSenderId());
        default: return "";
    }
}

bool ReservationTimerDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ReservationTimer *pp = (ReservationTimer *)object; (void)pp;
    switch (field) {
        case 0: pp->setNumseq(string2long(value)); return true;
        case 1: pp->setBurstifierId(string2long(value)); return true;
        case 2: pp->setSpectrumCenter(string2double(value)); return true;
        case 3: pp->setSpectrumLowerBound(string2double(value)); return true;
        case 4: pp->setSpectrumUpperBound(string2double(value)); return true;
        case 5: pp->setMsgSize(string2double(value)); return true;
        case 6: pp->setMsgOffset(string2simtime(value)); return true;
        case 7: pp->setMsgDuration(string2simtime(value)); return true;
        case 8: pp->setTimerStart(string2simtime(value)); return true;
        case 9: pp->setTimerEnd(string2simtime(value)); return true;
        case 10: pp->setChannelIndex(string2long(value)); return true;
        case 11: pp->setSenderId(string2long(value)); return true;
        default: return false;
    }
}

const char *ReservationTimerDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ReservationTimerDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ReservationTimer *pp = (ReservationTimer *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


