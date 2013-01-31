#pragma once

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
#include "../world/@/_.hcl"


namespace battleground {


/**
* ������ ��� ������������� ���� �����.
*
* # ������ ����������������� ������ '_.h'.
*/
class Engine {
public:
    Engine();


    virtual ~Engine();




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




    /**
    * ����������� ����� ��� ��������� � ����.
    * �������������� ��������� ��������� ������.
    */
    template< class T, size_t N >
    static inline std::unique_ptr< T >  createContent() {
        std::unique_ptr< T >  content( new T[ N ] );
        std::memset( content.get(),  0,  sizeof( T ) * N );
        return std::move( content );
    }




private:
    /**
    * ������� ������� ������� �������.
    *
    * ���� ��� ������� (mTimestep) �� �������� �������, ����� ����� =
    * = ��� * ���������� �������� �������.
    */
    porte::Pulse mLive;

    boost::unordered_map< std::string, cl::Kernel >  mKernelCL;

    cl::Context mContextCL;
    std::vector< cl::Device >  mDeviceCL;
    cl::CommandQueue mQueueCL;

    cl_int errorCL;

    // ���������� ���������� ��� ������ � OpenCL
    #include "../world/@/enum-buffer-cl.inl"

};


} // battleground






#include "Engine.inl"
