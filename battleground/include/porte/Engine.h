#pragma once

#include "../../configure.h"
#include <CL/cl.hpp>
#include <porte/include/porte/CL.h>
#include <porte/include/porte/Pulse.h>
#include <porte/include/porte/Exception.h>
#include <typelib/typelib.h>
#include <ostream>
#include <set>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/assign.hpp>
#include "../portulan/Portulan.h"


namespace battleground {


/**
* ������ ��� ������������� ���� �����.
*
* # ������ ����������������� ������ '_.h'.
*/
class Engine :
    public std::enable_shared_from_this< Engine >
{
public:
    Engine( std::shared_ptr< Portulan > );


    virtual ~Engine();




    inline std::shared_ptr< const Portulan >  portulan() const {
        assert( !mPortulan.expired() );
        return mPortulan.lock();
    }


    inline std::shared_ptr< Portulan >  portulan() {
        assert( !mPortulan.expired() );
        return mPortulan.lock();
    }




    /**
    * ������ ��� ���������� ��������� � �� �������.
    * ������������ ��� ������������ ���� �� ������.
    */
    #include "../world/@/porte/method-incarnate-element.inl"
    #include "../world/@/porte/method-incarnate-set.inl"




    /**
    * @return ����. ��������� UID ��� ��������.
    *
    * #! ������ ����� - ������ UID.
    */
    inline uid_t nextUID() {
        ++mLastUID;
        return mLastUID;
    }

    
    
    
    inline porte::Pulse live() const {
        return mLive;
    }




    /**
    * ��������� ����� �������.
    */
    void pulse( int n );




    /**
    * ������� ������ OpenCL.
    */
    inline cl::CommandQueue const& queueCL() const {
        return mQueueCL;
    }


    inline cl::CommandQueue& queueCL() {
        return mQueueCL;
    }




    /**
    * �������� OpenCL.
    */
    inline cl::Context const& contextCL() const {
        return mContextCL;
    }


    inline cl::Context& contextCL() {
        return mContextCL;
    }




private:
    void emitEvent( int n );




    void prepareCL();




    void prepareEmitEvent( const std::string& element );




    void compileCLKernel(
        const std::vector< std::string >&  kernelKeys,
        const std::vector< std::string >&  includeHCL = std::vector< std::string >(),
        const std::string& options = ""
    );




    /**
    * ��������� ���� OpenCL �� ����� 'key'.
    *
    * @param waitEvents  ���� ������� ���������� ���� �������.
    * @param event  ���� ������, ������������ �������� (��� �������������
    *        �������).
    */
    typedef VECTOR_CLASS< cl::Event >  vectorEventCL_t;


    template< size_t GLOBAL_SIZE >
    void enqueueEventKernelCL(
        const std::string&  key,
        cl::Event*          event = nullptr
    );


    template< size_t GLOBAL_SIZE >
    void enqueueEventKernelCL(
        const std::string&      key,
        const vectorEventCL_t&  waitEvents,
        cl::Event*              event = nullptr
    );




    static std::string commonConstantCLKernel();
    static std::string commonOptionCLKernel();




private:
    /**
    * �������� ��� ������.
    */
    std::weak_ptr< Portulan >  mPortulan;


    /**
    * ������� ������� ������� �������.
    *
    * ���� ��� ������� (mTimestep) �� �������� �������, ����� ����� =
    * = ��� * ���������� �������� �������.
    */
    porte::Pulse mLive;


    /**
    * ��������� �������� ������������ �������� UID.
    */
    uid_t mLastUID;


    /**
    * ��� ������ � OpenCL.
    */
    boost::unordered_map< std::string, cl::Kernel >  mKernelCL;
    cl::Context mContextCL;
    std::vector< cl::Device >  mDeviceCL;
    cl::CommandQueue mQueueCL;
    cl_int errorCL;


    // # ������������, ����� ������? �� �������������� � ��������. @todo?
public:
    // ���������� ���������� ��� ������ � OpenCL
    #include "../world/@/porte/enum-buffer-cl.inl"

};


} // battleground






#include "Engine.inl"
