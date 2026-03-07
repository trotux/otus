
class IDelegateVoid
{
public:
    virtual ~IDelegateVoid() {}
    virtual void Invoke() = 0;
    virtual bool Compare(IDelegateVoid* pDelegate) = 0;
};

class CStaticDelegateVoid : public IDelegateVoid
{
public:
    typedef void (*PFunc)();
    CStaticDelegateVoid(PFunc pFunc) { m_pFunc = pFunc; }
    virtual void Invoke() { m_pFunc(); }
    virtual bool Compare(IDelegateVoid* pDelegate);

private:
    PFunc m_pFunc;
};

bool CStaticDelegateVoid::Compare(IDelegateVoid* pDelegate)
{
    CStaticDelegateVoid* pStaticDel = dynamic_cast<CStaticDelegateVoid*>(pDelegate);

    if (pStaticDel == nullptr || pStaticDel->m_pFunc != m_pFunc)
        return false;

    return true;
}

template<class TObj>
class CMethodDelegateVoid : public IDelegateVoid
{
public:
    typedef void (TObj::*PMethod)();
    CMethodDelegateVoid(TObj* pObj, PMethod pMethod)
    {
        m_pObj = pObj;
        m_pMethod = pMethod;
    }
    virtual void Invoke() { (m_pObj->*m_pMethod)(); }
    bool Compare(IDelegateVoid* pDelegate) override
    {
        CMethodDelegateVoid<TObj>* pMethodDel = dynamic_cast<CMethodDelegateVoid<TObj>*>(pDelegate);

        if (pMethodDel == nullptr || pMethodDel->m_pObj != m_pObj || pMethodDel->m_pMethod != m_pMethod)
            return false;

        return true;
    }

private:
    TObj* m_pObj;
    PMethod m_pMethod;
};

IDelegateVoid* NewDelegate(void (*pFunc)())
{
  return new CStaticDelegateVoid(pFunc);
}

template <class TObj>
IDelegateVoid* NewDelegate(TObj* pObj, void (TObj::*pMethod)())
{
  return new CMethodDelegateVoid<TObj> (pObj, pMethod);
}

