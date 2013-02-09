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
* Движок для моделирования поля битвы.
*
* # Движок параметризируется файлом '_.h'.
*/
class Engine :
    public std::enable_shared_from_this< Engine >
{
public:
    Engine( std::shared_ptr< Portulan > );


    virtual ~Engine();




    inline std::shared_ptr< const Portulan >  portulan() const {
        ASSERT( !mPortulan.expired() );
        return mPortulan.lock();
    }


    inline std::shared_ptr< Portulan >  portulan() {
        ASSERT( !mPortulan.expired() );
        return mPortulan.lock();
    }




    /**
    * Методы для воплощения элементов и их наборов.
    * Генерируются при формировании мира из графов.
    */
    #include "../world/@/porte/method-incarnate-kind.inl"
    #include "../world/@/porte/method-incarnate-set.inl"




    /**
    * @return След. свободный UID для элемента.
    *
    * #! Каждый вызов - другой UID.
    */
    inline uid_t nextUID() {
        ++mLastUID;
        return mLastUID;
    }

    
    
    
    inline porte::Pulse live() const {
        return mLive;
    }




    /**
    * Изменение карты движком.
    *
    * @param timestep Сколько времени должно пройти в мире.
    */
    void pulse( real_t timestep );




    /**
    * Очередь команд OpenCL.
    */
    inline cl::CommandQueue const& queueCL() const {
        return mQueueCL;
    }


    inline cl::CommandQueue& queueCL() {
        return mQueueCL;
    }




    /**
    * Контекст OpenCL.
    */
    inline cl::Context const& contextCL() const {
        return mContextCL;
    }


    inline cl::Context& contextCL() {
        return mContextCL;
    }




private:
    void emitEvent( real_t timestep );




    void prepareCL();




    void prepareEmitEvent( const std::string& element );




    void compileCLKernel(
        const std::vector< std::string >&  kernelKeys,
        const std::vector< std::string >&  includeHCL = std::vector< std::string >(),
        const std::string& options = ""
    );




    /**
    * Выполняет ядро OpenCL по имени 'key'.
    *
    * @param waitEvents  Ядро подождёт завершения этих событий.
    * @param event  Если указан, инициируется событием (для синхронизации
    *        потоков).
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
    * Портулан для движка.
    */
    std::weak_ptr< Portulan >  mPortulan;


    /**
    * Сколько пульсов прожила система.
    *
    * Если шаг времени не меняется движком, время жизни =
    * = шаг * количество прожитых пульсов.
    */
    porte::Pulse mLive;


    /**
    * Последний выданный воплощённому элементу UID.
    */
    uid_t mLastUID;


    /**
    * Для работы с OpenCL.
    */
    boost::unordered_map< std::string, cl::Kernel >  mKernelCL;
    cl::Context mContextCL;
    std::vector< cl::Device >  mDeviceCL;
    cl::CommandQueue mQueueCL;
    cl_int errorCL;


    // # Общедоступны, чтобы сейчас? не заморачиваться с методами. @todo?
public:
    // подключаем переменные для обмена с OpenCL
    #include "../world/@/porte/enum-buffer-cl.inl"

};


} // battleground






#include "Engine.inl"
