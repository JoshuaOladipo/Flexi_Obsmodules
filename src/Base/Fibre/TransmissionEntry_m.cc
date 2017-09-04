//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/Fibre/TransmissionEntry.msg.
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
#include "TransmissionEntry_m.h"

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

Register_Class(TransmissionEntry)

TransmissionEntry::TransmissionEntry(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->spectrumCenter = 0;
    this->spectrumLowerBound = 0;
    this->spectrumUpperBound = 0;
    this->startTime = 0;
    this->endTime = 0;
    this->power = 0;
    this->bitrate = 0;
    this->readyForDeletion = false;
}

TransmissionEntry::TransmissionEntry(const TransmissionEntry& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TransmissionEntry::~TransmissionEntry()
{
}

TransmissionEntry& TransmissionEntry::operator=(const TransmissionEntry& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TransmissionEntry::copy(const TransmissionEntry& other)
{
    this->spectrumCenter = other.spectrumCenter;
    this->spectrumLowerBound = other.spectrumLowerBound;
    this->spectrumUpperBound = other.spectrumUpperBound;
    this->startTime = other.startTime;
    this->endTime = other.endTime;
    this->power = other.power;
    this->bitrate = other.bitrate;
    this->sender = other.sender;
    this->readyForDeletion = other.readyForDeletion;
}

void TransmissionEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->spectrumCenter);
    doParsimPacking(b,this->spectrumLowerBound);
    doParsimPacking(b,this->spectrumUpperBound);
    doParsimPacking(b,this->startTime);
    doParsimPacking(b,this->endTime);
    doParsimPacking(b,this->power);
    doParsimPacking(b,this->bitrate);
    doParsimPacking(b,this->sender);
    doParsimPacking(b,this->readyForDeletion);
}

void TransmissionEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->spectrumCenter);
    doParsimUnpacking(b,this->spectrumLowerBound);
    doParsimUnpacking(b,this->spectrumUpperBound);
    doParsimUnpacking(b,this->startTime);
    doParsimUnpacking(b,this->endTime);
    doParsimUnpacking(b,this->power);
    doParsimUnpacking(b,this->bitrate);
    doParsimUnpacking(b,this->sender);
    doParsimUnpacking(b,this->readyForDeletion);
}

double TransmissionEntry::getSpectrumCenter() const
{
    return this->spectrumCenter;
}

void TransmissionEntry::setSpectrumCenter(double spectrumCenter)
{
    this->spectrumCenter = spectrumCenter;
}

double TransmissionEntry::getSpectrumLowerBound() const
{
    return this->spectrumLowerBound;
}

void TransmissionEntry::setSpectrumLowerBound(double spectrumLowerBound)
{
    this->spectrumLowerBound = spectrumLowerBound;
}

double TransmissionEntry::getSpectrumUpperBound() const
{
    return this->spectrumUpperBound;
}

void TransmissionEntry::setSpectrumUpperBound(double spectrumUpperBound)
{
    this->spectrumUpperBound = spectrumUpperBound;
}

::omnetpp::simtime_t TransmissionEntry::getStartTime() const
{
    return this->startTime;
}

void TransmissionEntry::setStartTime(::omnetpp::simtime_t startTime)
{
    this->startTime = startTime;
}

::omnetpp::simtime_t TransmissionEntry::getEndTime() const
{
    return this->endTime;
}

void TransmissionEntry::setEndTime(::omnetpp::simtime_t endTime)
{
    this->endTime = endTime;
}

double TransmissionEntry::getPower() const
{
    return this->power;
}

void TransmissionEntry::setPower(double power)
{
    this->power = power;
}

double TransmissionEntry::getBitrate() const
{
    return this->bitrate;
}

void TransmissionEntry::setBitrate(double bitrate)
{
    this->bitrate = bitrate;
}

Mux& TransmissionEntry::getSender()
{
    return this->sender;
}

void TransmissionEntry::setSender(const Mux& sender)
{
    this->sender = sender;
}

bool TransmissionEntry::getReadyForDeletion() const
{
    return this->readyForDeletion;
}

void TransmissionEntry::setReadyForDeletion(bool readyForDeletion)
{
    this->readyForDeletion = readyForDeletion;
}

class TransmissionEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TransmissionEntryDescriptor();
    virtual ~TransmissionEntryDescriptor();

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

Register_ClassDescriptor(TransmissionEntryDescriptor)

TransmissionEntryDescriptor::TransmissionEntryDescriptor() : omnetpp::cClassDescriptor("TransmissionEntry", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

TransmissionEntryDescriptor::~TransmissionEntryDescriptor()
{
    delete[] propertynames;
}

bool TransmissionEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TransmissionEntry *>(obj)!=nullptr;
}

const char **TransmissionEntryDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TransmissionEntryDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TransmissionEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int TransmissionEntryDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *TransmissionEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "spectrumCenter",
        "spectrumLowerBound",
        "spectrumUpperBound",
        "startTime",
        "endTime",
        "power",
        "bitrate",
        "sender",
        "readyForDeletion",
    };
    return (field>=0 && field<9) ? fieldNames[field] : nullptr;
}

int TransmissionEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "spectrumCenter")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "spectrumLowerBound")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "spectrumUpperBound")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "startTime")==0) return base+3;
    if (fieldName[0]=='e' && strcmp(fieldName, "endTime")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "power")==0) return base+5;
    if (fieldName[0]=='b' && strcmp(fieldName, "bitrate")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "sender")==0) return base+7;
    if (fieldName[0]=='r' && strcmp(fieldName, "readyForDeletion")==0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TransmissionEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "double",
        "simtime_t",
        "simtime_t",
        "double",
        "double",
        "Mux",
        "bool",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : nullptr;
}

const char **TransmissionEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *TransmissionEntryDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int TransmissionEntryDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TransmissionEntry *pp = (TransmissionEntry *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TransmissionEntryDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TransmissionEntry *pp = (TransmissionEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TransmissionEntryDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TransmissionEntry *pp = (TransmissionEntry *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getSpectrumCenter());
        case 1: return double2string(pp->getSpectrumLowerBound());
        case 2: return double2string(pp->getSpectrumUpperBound());
        case 3: return simtime2string(pp->getStartTime());
        case 4: return simtime2string(pp->getEndTime());
        case 5: return double2string(pp->getPower());
        case 6: return double2string(pp->getBitrate());
        case 7: {std::stringstream out; out << pp->getSender(); return out.str();}
        case 8: return bool2string(pp->getReadyForDeletion());
        default: return "";
    }
}

bool TransmissionEntryDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TransmissionEntry *pp = (TransmissionEntry *)object; (void)pp;
    switch (field) {
        case 0: pp->setSpectrumCenter(string2double(value)); return true;
        case 1: pp->setSpectrumLowerBound(string2double(value)); return true;
        case 2: pp->setSpectrumUpperBound(string2double(value)); return true;
        case 3: pp->setStartTime(string2simtime(value)); return true;
        case 4: pp->setEndTime(string2simtime(value)); return true;
        case 5: pp->setPower(string2double(value)); return true;
        case 6: pp->setBitrate(string2double(value)); return true;
        case 8: pp->setReadyForDeletion(string2bool(value)); return true;
        default: return false;
    }
}

const char *TransmissionEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 7: return omnetpp::opp_typename(typeid(Mux));
        default: return nullptr;
    };
}

void *TransmissionEntryDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TransmissionEntry *pp = (TransmissionEntry *)object; (void)pp;
    switch (field) {
        case 7: return (void *)(&pp->getSender()); break;
        default: return nullptr;
    }
}


