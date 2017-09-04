//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/K_ShortestPathTableEntry.msg.
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
#include "K_ShortestPathTableEntry_m.h"

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

Register_Class(K_ShortestPathTableEntry)

K_ShortestPathTableEntry::K_ShortestPathTableEntry() : ::omnetpp::cObject()
{
    this->srcAddress = 0;
    this->destAddress = 0;
    this->cost = 0;
    path_arraysize = 0;
    this->path = 0;
}

K_ShortestPathTableEntry::K_ShortestPathTableEntry(const K_ShortestPathTableEntry& other) : ::omnetpp::cObject(other)
{
    path_arraysize = 0;
    this->path = 0;
    copy(other);
}

K_ShortestPathTableEntry::~K_ShortestPathTableEntry()
{
    delete [] this->path;
}

K_ShortestPathTableEntry& K_ShortestPathTableEntry::operator=(const K_ShortestPathTableEntry& other)
{
    if (this==&other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void K_ShortestPathTableEntry::copy(const K_ShortestPathTableEntry& other)
{
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
    this->cost = other.cost;
    delete [] this->path;
    this->path = (other.path_arraysize==0) ? nullptr : new double[other.path_arraysize];
    path_arraysize = other.path_arraysize;
    for (unsigned int i=0; i<path_arraysize; i++)
        this->path[i] = other.path[i];
}

void K_ShortestPathTableEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
    doParsimPacking(b,this->cost);
    b->pack(path_arraysize);
    doParsimArrayPacking(b,this->path,path_arraysize);
}

void K_ShortestPathTableEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
    doParsimUnpacking(b,this->cost);
    delete [] this->path;
    b->unpack(path_arraysize);
    if (path_arraysize==0) {
        this->path = 0;
    } else {
        this->path = new double[path_arraysize];
        doParsimArrayUnpacking(b,this->path,path_arraysize);
    }
}

int K_ShortestPathTableEntry::getSrcAddress() const
{
    return this->srcAddress;
}

void K_ShortestPathTableEntry::setSrcAddress(int srcAddress)
{
    this->srcAddress = srcAddress;
}

int K_ShortestPathTableEntry::getDestAddress() const
{
    return this->destAddress;
}

void K_ShortestPathTableEntry::setDestAddress(int destAddress)
{
    this->destAddress = destAddress;
}

double K_ShortestPathTableEntry::getCost() const
{
    return this->cost;
}

void K_ShortestPathTableEntry::setCost(double cost)
{
    this->cost = cost;
}

void K_ShortestPathTableEntry::setPathArraySize(unsigned int size)
{
    double *path2 = (size==0) ? nullptr : new double[size];
    unsigned int sz = path_arraysize < size ? path_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        path2[i] = this->path[i];
    for (unsigned int i=sz; i<size; i++)
        path2[i] = 0;
    path_arraysize = size;
    delete [] this->path;
    this->path = path2;
}

unsigned int K_ShortestPathTableEntry::getPathArraySize() const
{
    return path_arraysize;
}

double K_ShortestPathTableEntry::getPath(unsigned int k) const
{
    if (k>=path_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", path_arraysize, k);
    return this->path[k];
}

void K_ShortestPathTableEntry::setPath(unsigned int k, double path)
{
    if (k>=path_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", path_arraysize, k);
    this->path[k] = path;
}

class K_ShortestPathTableEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    K_ShortestPathTableEntryDescriptor();
    virtual ~K_ShortestPathTableEntryDescriptor();

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

Register_ClassDescriptor(K_ShortestPathTableEntryDescriptor)

K_ShortestPathTableEntryDescriptor::K_ShortestPathTableEntryDescriptor() : omnetpp::cClassDescriptor("K_ShortestPathTableEntry", "omnetpp::cObject")
{
    propertynames = nullptr;
}

K_ShortestPathTableEntryDescriptor::~K_ShortestPathTableEntryDescriptor()
{
    delete[] propertynames;
}

bool K_ShortestPathTableEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<K_ShortestPathTableEntry *>(obj)!=nullptr;
}

const char **K_ShortestPathTableEntryDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *K_ShortestPathTableEntryDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int K_ShortestPathTableEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int K_ShortestPathTableEntryDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *K_ShortestPathTableEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
        "destAddress",
        "cost",
        "path",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int K_ShortestPathTableEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddress")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddress")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "cost")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "path")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *K_ShortestPathTableEntryDescriptor::getFieldTypeString(int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **K_ShortestPathTableEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *K_ShortestPathTableEntryDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int K_ShortestPathTableEntryDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    K_ShortestPathTableEntry *pp = (K_ShortestPathTableEntry *)object; (void)pp;
    switch (field) {
        case 3: return pp->getPathArraySize();
        default: return 0;
    }
}

const char *K_ShortestPathTableEntryDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    K_ShortestPathTableEntry *pp = (K_ShortestPathTableEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string K_ShortestPathTableEntryDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    K_ShortestPathTableEntry *pp = (K_ShortestPathTableEntry *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrcAddress());
        case 1: return long2string(pp->getDestAddress());
        case 2: return double2string(pp->getCost());
        case 3: return double2string(pp->getPath(i));
        default: return "";
    }
}

bool K_ShortestPathTableEntryDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    K_ShortestPathTableEntry *pp = (K_ShortestPathTableEntry *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcAddress(string2long(value)); return true;
        case 1: pp->setDestAddress(string2long(value)); return true;
        case 2: pp->setCost(string2double(value)); return true;
        case 3: pp->setPath(i,string2double(value)); return true;
        default: return false;
    }
}

const char *K_ShortestPathTableEntryDescriptor::getFieldStructName(int field) const
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

void *K_ShortestPathTableEntryDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    K_ShortestPathTableEntry *pp = (K_ShortestPathTableEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


