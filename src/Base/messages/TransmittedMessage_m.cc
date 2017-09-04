//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/TransmittedMessage.msg.
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
#include "TransmittedMessage_m.h"

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

TransmittedMessage_Base::TransmittedMessage_Base(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->sourcePower = 0;
    this->hasPassedFirstStation = false;
    this->isControl = false;
    this->isReadable = false;
    this->sourceSendTIme = 0;
}

TransmittedMessage_Base::TransmittedMessage_Base(const TransmittedMessage_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

TransmittedMessage_Base::~TransmittedMessage_Base()
{
}

TransmittedMessage_Base& TransmittedMessage_Base::operator=(const TransmittedMessage_Base& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void TransmittedMessage_Base::copy(const TransmittedMessage_Base& other)
{
    this->sourcePower = other.sourcePower;
    this->hasPassedFirstStation = other.hasPassedFirstStation;
    this->isControl = other.isControl;
    this->isReadable = other.isReadable;
    this->transmissionEntry = other.transmissionEntry;
    this->sourceSendTIme = other.sourceSendTIme;
}

void TransmittedMessage_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sourcePower);
    doParsimPacking(b,this->hasPassedFirstStation);
    doParsimPacking(b,this->isControl);
    doParsimPacking(b,this->isReadable);
    doParsimPacking(b,this->transmissionEntry);
    doParsimPacking(b,this->sourceSendTIme);
}

void TransmittedMessage_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sourcePower);
    doParsimUnpacking(b,this->hasPassedFirstStation);
    doParsimUnpacking(b,this->isControl);
    doParsimUnpacking(b,this->isReadable);
    doParsimUnpacking(b,this->transmissionEntry);
    doParsimUnpacking(b,this->sourceSendTIme);
}

double TransmittedMessage_Base::getSourcePower() const
{
    return this->sourcePower;
}

void TransmittedMessage_Base::setSourcePower(double sourcePower)
{
    this->sourcePower = sourcePower;
}

bool TransmittedMessage_Base::getHasPassedFirstStation() const
{
    return this->hasPassedFirstStation;
}

void TransmittedMessage_Base::setHasPassedFirstStation(bool hasPassedFirstStation)
{
    this->hasPassedFirstStation = hasPassedFirstStation;
}

bool TransmittedMessage_Base::getIsControl() const
{
    return this->isControl;
}

void TransmittedMessage_Base::setIsControl(bool isControl)
{
    this->isControl = isControl;
}

bool TransmittedMessage_Base::getIsReadable() const
{
    return this->isReadable;
}

void TransmittedMessage_Base::setIsReadable(bool isReadable)
{
    this->isReadable = isReadable;
}

tEntryPtr& TransmittedMessage_Base::getTransmissionEntry()
{
    return this->transmissionEntry;
}

void TransmittedMessage_Base::setTransmissionEntry(const tEntryPtr& transmissionEntry)
{
    this->transmissionEntry = transmissionEntry;
}

::omnetpp::simtime_t TransmittedMessage_Base::getSourceSendTIme() const
{
    return this->sourceSendTIme;
}

void TransmittedMessage_Base::setSourceSendTIme(::omnetpp::simtime_t sourceSendTIme)
{
    this->sourceSendTIme = sourceSendTIme;
}

class TransmittedMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TransmittedMessageDescriptor();
    virtual ~TransmittedMessageDescriptor();

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

Register_ClassDescriptor(TransmittedMessageDescriptor)

TransmittedMessageDescriptor::TransmittedMessageDescriptor() : omnetpp::cClassDescriptor("TransmittedMessage", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

TransmittedMessageDescriptor::~TransmittedMessageDescriptor()
{
    delete[] propertynames;
}

bool TransmittedMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TransmittedMessage_Base *>(obj)!=nullptr;
}

const char **TransmittedMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TransmittedMessageDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TransmittedMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int TransmittedMessageDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *TransmittedMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourcePower",
        "hasPassedFirstStation",
        "isControl",
        "isReadable",
        "transmissionEntry",
        "sourceSendTIme",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int TransmittedMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePower")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hasPassedFirstStation")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "isControl")==0) return base+2;
    if (fieldName[0]=='i' && strcmp(fieldName, "isReadable")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmissionEntry")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceSendTIme")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TransmittedMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "bool",
        "bool",
        "bool",
        "tEntryPtr",
        "simtime_t",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **TransmittedMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TransmittedMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"unit")) return "db";
            return nullptr;
        default: return nullptr;
    }
}

int TransmittedMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TransmittedMessage_Base *pp = (TransmittedMessage_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TransmittedMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TransmittedMessage_Base *pp = (TransmittedMessage_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TransmittedMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TransmittedMessage_Base *pp = (TransmittedMessage_Base *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getSourcePower());
        case 1: return bool2string(pp->getHasPassedFirstStation());
        case 2: return bool2string(pp->getIsControl());
        case 3: return bool2string(pp->getIsReadable());
        case 4: {std::stringstream out; out << pp->getTransmissionEntry(); return out.str();}
        case 5: return simtime2string(pp->getSourceSendTIme());
        default: return "";
    }
}

bool TransmittedMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TransmittedMessage_Base *pp = (TransmittedMessage_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setSourcePower(string2double(value)); return true;
        case 1: pp->setHasPassedFirstStation(string2bool(value)); return true;
        case 2: pp->setIsControl(string2bool(value)); return true;
        case 3: pp->setIsReadable(string2bool(value)); return true;
        case 5: pp->setSourceSendTIme(string2simtime(value)); return true;
        default: return false;
    }
}

const char *TransmittedMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 4: return omnetpp::opp_typename(typeid(tEntryPtr));
        default: return nullptr;
    };
}

void *TransmittedMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TransmittedMessage_Base *pp = (TransmittedMessage_Base *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getTransmissionEntry()); break;
        default: return nullptr;
    }
}


