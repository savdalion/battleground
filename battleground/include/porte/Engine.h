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


// #! Структуры OpenCL и C++ должны быть одинакового размера.
//    Особое внимание стоит обратить на структуры, которые содержат
//    вложенные структуры и атрибут "упаковать".
#pragma pack( 1 )


/**
* # Структуры организованы т. о., чтобы не дублировать их при включении
*   в код OpenCL. Поэтому даём неск. определений.
*/
#ifndef __constant
#define __constant const
#endif

#ifndef __global
#define __global /*nothing*/
#endif

// Выравнивание для VC++ не требуется
#define __attribute__(x) /*nothing*/


#include "../world/@/_.hcl"


namespace battleground {


/**
* Движок для моделирования поля битвы.
*
* # Движок параметризируется файлом '_.h'.
*/
class Engine {
public:
    Engine();


    virtual ~Engine();




    /**
    * Методы для воплощения элементов и их наборов.
    * Генерируются при формировании мира из графов.
    */
    #include "../world/@/method-incarnate-element.inl"
    #include "../world/@/method-incarnate-set.inl"




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
    */
    void pulse( int n );




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
    void emitEvent( int n );




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




    /**
    * Резервируем место для элементов в куче.
    * Инициализируем структуры элементов нулями.
    */
    template< class T, size_t N >
    static inline std::unique_ptr< T >  createContent() {
        std::unique_ptr< T >  content( new T[ N ] );
        std::memset( content.get(),  0,  sizeof( T ) * N );
        return std::move( content );
    }




private:
    /**
    * Сколько пульсов прожила система.
    *
    * Если шаг времени (mTimestep) не меняется движком, время жизни =
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
    #include "../world/@/enum-buffer-cl.inl"

};


} // battleground






#include "Engine.inl"
