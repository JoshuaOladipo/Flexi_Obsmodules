//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/Flexi_OBS_BurstRouterInfo.msg.
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
#include "Flexi_OBS_BurstRouterInfo_m.h"

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

Register_Class(Flexi_OBS_BurstRouterInfo)

Flexi_OBS_BurstRouterInfo::Flexi_OBS_BurstRouterInfo() : ::omnetpp::cObject()
{
    this->burstId = -1;
    this->burstifierId = -1;
    this->numSeq = -1;
    this->assignedSpectrumCenter = -1;
    this->aSsignedSpectrumLowerBound = -1;
    this->assignedSpectrumUpperBund = -1;
    this->label = -1;
    this->ACO_RouteId = -1;
}

Flexi_OBS_BurstRouterInfo::Flexi_OBS_BurstRouterInfo(const Flexi_OBS_BurstRouterInfo& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Flexi_OBS_BurstRouterInfo::~Flexi_OBS_BurstRouterInfo()
{
}

Flexi_OBS_BurstRouterInfo& Flexi_OBS_BurstRouterInfo::operator=(const Flexi_OBS_BurstRouterInfo& other)
{
    if (this==&other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Flexi_OBS_BurstRouterInfo::copy(const Flexi_OBS_BurstRouterInfo& other)
{
    this->burstId = other.burstId;
    this->burstifierId = other.burstifierId;
    this->numSeq = other.numSeq;
    this->assignedSpectrumCenter = other.assignedSpectrumCenter;
    this->aSsignedSpectrumLowerBound = other.aSsignedSpectrumLowerBound;
    this->assignedSpectrumUpperBund = other.assignedSpectrumUpperBund;
    this->label = other.label;
    this->ACO_RouteId = other.ACO_RouteId;
}

void Flexi_OBS_BurstRouterInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->burstId);
    doParsimPacking(b,this->burstifierId);
    doParsimPacking(b,this->numSeq);
    doParsimPacking(b,this->assignedSpectrumCenter);
    doParsimPacking(b,this->aSsignedSpectrumLowerBound);
    doParsimPacking(b,this->assignedSpectrumUpperBund);
    doParsimPacking(b,this->label);
    doParsimPacking(b,this->ACO_RouteId);
}

void Flexi_OBS_BurstRouterInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->burstId);
    doParsimUnpacking(b,this->burstifierId);
    doParsimUnpacking(b,this->numSeq);
    doParsimUnpacking(b,this->assignedSpectrumCenter);
    doParsimUnpacking(b,this->aSsignedSpectrumLowerBound);
    doParsimUnpacking(b,this->assignedSpectrumUpperBund);
    doParsimUnpacking(b,this->label);
    doParsimUnpacking(b,this->ACO_RouteId);
}

int Flexi_OBS_BurstRouterInfo::getBurstId() const
{
    return this->burstId;
}

void Flexi_OBS_BurstRouterInfo::setBurstId(int burstId)
{
    this->burstId = burstId;
}

int Flexi_OBS_BurstRouterInfo::getBurstifierId() const
{
    return this->burstifierId;
}

void Flexi_OBS_BurstRouterInfo::setBurstifierId(int burstifierId)
{
    this->burstifierId = burstifierId;
}

int Flexi_OBS_BurstRouterInfo::getNumSeq() const
{
    return this->numSeq;
}

void Flexi_OBS_BurstRouterInfo::setNumSeq(int numSeq)
{
    this->numSeq = numSeq;
}

double Flexi_OBS_BurstRouterInfo::getAssignedSpectrumCenter() const
{
    return this->assignedSpectrumCenter;
}

void Flexi_OBS_BurstRouterInfo::setAssignedSpectrumCenter(double assignedSpectrumCenter)
{
    this->assignedSpectrumCenter = assignedSpectrumCenter;
}

double Flexi_OBS_BurstRouterInfo::getASsignedSpectrumLowerBound() const
{
    return this->aSsignedSpectrumLowerBound;
}

void Flexi_OBS_BurstRouterInfo::setASsignedSpectrumLowerBound(double aSsignedSpectrumLowerBound)
{
    this->aSsignedSpectrumLowerBound = aSsignedSpectrumLowerBound;
}

double Flexi_OBS_BurstRouterInfo::getAssignedSpectrumUpperBund() const
{
    return this->assignedSpectrumUpperBund;
}

void Flexi_OBS_BurstRouterInfo::setAssignedSpectrumUpperBund(double assignedSpectrumUpperBund)
{
    this->assignedSpectrumUpperBund = assignedSpectrumUpperBund;
}

int Flexi_OBS_BurstRouterInfo::getLabel() const
{
    return this->label;
}

void Flexi_OBS_BurstRouterInfo::setLabel(int label)
{
    this->label = label;
}

int Flexi_OBS_BurstRouterInfo::getACO_RouteId() const
{
    return this->ACO_RouteId;
}

void Flexi_OBS_BurstRouterInfo::setACO_RouteId(int ACO_RouteId)
{
    this->ACO_RouteId = ACO_RouteId;
}

class Flexi_OBS_BurstRouterInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    Flexi_OBS_BurstRouterInfoDescriptor();
    virtual ~Flexi_OBS_BurstRouterInfoDescriptor();

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

Register_ClassDescriptor(Flexi_OBS_BurstRouterInfoDescriptor)

Flexi_OBS_BurstRouterInfoDescriptor::Flexi_OBS_BurstRouterInfoDescriptor() : omnetpp::cClassDescriptor("Flexi_OBS_BurstRouterInfo", "omnetpp::cObject")
{
    propertynames = nullptr;
}

Flexi_OBS_BurstRouterInfoDescriptor::~Flexi_OBS_BurstRouterInfoDescriptor()
{
    delete[] propertynames;
}

bool Flexi_OBS_BurstRouterInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Flexi_OBS_BurstRouterInfo *>(obj)!=nullptr;
}

const char **Flexi_OBS_BurstRouterInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Flexi_OBS_BurstRouterInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Flexi_OBS_BurstRouterInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int Flexi_OBS_BurstRouterInfoDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *Flexi_OBS_BurstRouterInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "burstId",
        "burstifierId",
        "numSeq",
        "assignedSpectrumCenter",
        "aSsignedSpectrumLowerBound",
        "assignedSpectrumUpperBund",
        "label",
        "ACO_RouteId",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int Flexi_OBS_BurstRouterInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstId")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstifierId")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "numSeq")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumCenter")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "aSsignedSpectrumLowerBound")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumUpperBund")==0) return base+5;
    if (fieldName[0]=='l' && strcmp(fieldName, "label")==0) return base+6;
    if (fieldName[0]=='A' && strcmp(fieldName, "ACO_RouteId")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Flexi_OBS_BurstRouterInfoDescriptor::getFieldTypeString(int field) const
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
        "int",
        "double",
        "double",
        "double",
        "int",
        "int",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **Flexi_OBS_BurstRouterInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *Flexi_OBS_BurstRouterInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Flexi_OBS_BurstRouterInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstRouterInfo *pp = (Flexi_OBS_BurstRouterInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Flexi_OBS_BurstRouterInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstRouterInfo *pp = (Flexi_OBS_BurstRouterInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Flexi_OBS_BurstRouterInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstRouterInfo *pp = (Flexi_OBS_BurstRouterInfo *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getBurstId());
        case 1: return long2string(pp->getBurstifierId());
        case 2: return long2string(pp->getNumSeq());
        case 3: return double2string(pp->getAssignedSpectrumCenter());
        case 4: return double2string(pp->getASsignedSpectrumLowerBound());
        case 5: return double2string(pp->getAssignedSpectrumUpperBund());
        case 6: return long2string(pp->getLabel());
        case 7: return long2string(pp->getACO_RouteId());
        default: return "";
    }
}

bool Flexi_OBS_BurstRouterInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstRouterInfo *pp = (Flexi_OBS_BurstRouterInfo *)object; (void)pp;
    switch (field) {
        case 0: pp->setBurstId(string2long(value)); return true;
        case 1: pp->setBurstifierId(string2long(value)); return true;
        case 2: pp->setNumSeq(string2long(value)); return true;
        case 3: pp->setAssignedSpectrumCenter(string2double(value)); return true;
        case 4: pp->setASsignedSpectrumLowerBound(string2double(value)); return true;
        case 5: pp->setAssignedSpectrumUpperBund(string2double(value)); return true;
        case 6: pp->setLabel(string2long(value)); return true;
        case 7: pp->setACO_RouteId(string2long(value)); return true;
        default: return false;
    }
}

const char *Flexi_OBS_BurstRouterInfoDescriptor::getFieldStructName(int field) const
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

void *Flexi_OBS_BurstRouterInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstRouterInfo *pp = (Flexi_OBS_BurstRouterInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


