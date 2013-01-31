namespace battleground {


inline Engine::Engine(
) :
    mLive(),
    errorCL( CL_SUCCESS )
{
    // Подготавливаем контекст и очередь команд для работы с OpenCL
    prepareCL();

    // Инициируем переменные для обмена данными с OpenCL
    #include "../world/@/init-buffer-cl.h"

    // # Ядра OpenCL соберём по требованию.
}




inline Engine::~Engine() {
}




inline void Engine::pulse( int n ) {

    assert( (n > 0)
        && "Умеем работать только с натуральным кол-вом пульсов." );

    // рассчитываем воздействия на тела звёздной системы
    // # Все элементы портулана работают по единой схеме.
    // # Каждый элемент генерирует свой набор событий. Причём, события
    //   генерируюся в непрерывном времени - см. комм. в графах '*.gv'.
    // # Испускаемые элементом события хранятся самим элементом.
    // # Событие может изменить как сам элемент, так и др. элементы. Поэтому,
    //   после "испускания" события каждый элемент просматривает др. элементы
    //   на наличие событий, которые могут оказать влияние на сам элемент.
    // # Чтобы избежать дублирования симметричных событий (например,
    //   столкновений), принимаем:
    //   Симметр. общее событие регистрируется *только* первым по алфавиту
    //   элементом. остальные участники просматривают такие события и создают
    //   на их основе конкретные (свои) события. Побочный эффект: меньше
    //   загрузка памяти общих событий, ускорение обработки.

    // выполняем 'n' циклов
    try {
        emitEvent( n );
    } catch ( cl::Error& ex ) {
        const std::string s =
            static_cast< std::string >( ex.what() ) +
            " (" + boost::lexical_cast< std::string >( ex.err() ) + ")";
        std::cerr << s << std::endl;
        throw porte::Exception( s );
    }
}




inline void Engine::emitEvent( int n ) {

    // @todo fine clEnqueueMigrateMemObjects() для актуализации структур.


    // выполним 'n' пульсов
    for (int p = 0; p < n; ++p) {

        // # Перед началом каждого пульса и в конце него элементы -
        //   упорядочены (оптимизированы). См. старания ниже.

        const cl_long pulselive = mLive.pulselive();


        // просмотрим память всех элементов и отработаем все запланированные
        // ими стратегии


        // подготавливаем элементы к созданию событий
        /* - ? поменьше бы файлов...
        #include "../battleground/clamp-coord/@/begin.inl"
        #include "../warrior/training/single-sword/turn/@/begin.inl"
        queueCL.finish();
        */

        // @todo ...


        // # В этом месте очередь событий завершена.

        // мир становится старше
        mLive.inc( TIMESTEP );

    } // for (int p = 0 ...



    // читаем результат
    #include "../world/@/read-buffer-cl.inl"
}




inline void Engine::prepareCL() {

    std::vector< cl::Platform >  mPlatformCL;
    cl::Platform::get( &mPlatformCL );
    if ( mPlatformCL.empty() ) {
        throw porte::Exception( "Не найдено ни одного устройства с поддержкой OpenCL." );
    }

    cl_context_properties properties[] = {
        CL_CONTEXT_PLATFORM,
        ( cl_context_properties )( mPlatformCL.front() )(),
        0
    };
    mContextCL = cl::Context( CL_DEVICE_TYPE_CPU, properties );
    mDeviceCL = mContextCL.getInfo< CL_CONTEXT_DEVICES >();
    mQueueCL = cl::CommandQueue( mContextCL, mDeviceCL[ 0 ],  0,  &errorCL );

#ifdef _DEBUG
    std::cout << "\nВыбрано устройство OpenCL:\n";
    porte::printCLInfo( mPlatformCL.front()() );
#endif
}




inline void Engine::prepareEmitEvent( const std::string& element ) {
    // # Контекст и очередь команд инициализированы в конструкторе.

    // @todo ...

    assert( false && "Не реализовано." );
}




inline void Engine::compileCLKernel(
    const std::vector< std::string >&  kernelKeys,
    const std::vector< std::string >&  includeHCL,
    const std::string& options
) {
    // # Контекст и очередь команд инициализированы в конструкторе.

#ifdef _DEBUG
        std::cout << std::endl << std::endl;
#endif

    std::ostringstream commonOptions;
    commonOptions
        // лечим точность для float
        << std::fixed
        // #! Рабочие сетки декларируются отдельно: есть методы
        //   в helper.hcl, которые используют их.
        << " " << options
        << commonConstantCLKernel()
        << commonOptionCLKernel()
        << "";

    // здесь будет код необходимых ядру библиотек
    std::string kernelLibraryCode = "";

    // подключаем общие библиотеки и структуры
    // (используются всеми ядрами движка)
    // #! Важен порядок подключения.
    std::vector< std::string > hcl = boost::assign::list_of
        ( PATH_CL_BATTLEGROUND + "/pragma.hcl" )
        ( PATH_CL_BATTLEGROUND + "/restruct.hcl" )
        ( PATH_CL_BATTLEGROUND + "/_.hcl" )
    ;
    hcl.insert( hcl.end(), includeHCL.cbegin(), includeHCL.cend() );
    for (auto itr = hcl.cbegin(); itr != hcl.cend(); ++itr) {
        const std::string& pathAndName = *itr;
#ifdef _DEBUG
        const std::string shortName =
            itr->substr( pathAndName.find_last_of( '/' ) + 1 );
        std::cout << "Собираем \"" << shortName << "\" ..";
#endif
        const std::ifstream  file( pathAndName.c_str() );
        assert( file.is_open()
            && "Файл не найден." );
        std::stringstream buffer;
        buffer << file.rdbuf();
        kernelLibraryCode +=
            (std::string)"\n\n\n\n\n" +
            "// #include " + pathAndName + "\n" +
            buffer.str();
#ifdef _DEBUG
    std::cout << " ОК" << std::endl;
#endif
    } // for (auto itr = hcl.cbegin(); ...


    // собираем исходники ядер в один файл и компилируем
    for (auto itr = std::begin( kernelKeys ); itr != std::end( kernelKeys ); ++itr) {
        //   # Последнее за "/" название является именем ядра.
        const std::string kernelKey = *itr;
        const std::string kernelName =
            itr->substr( itr->find_last_of( '/' ) + 1 );

        // Program Setup
        const std::string fileKernel = kernelKey + ".cl";
        const std::string pathAndName =
            PATH_CL_BATTLEGROUND + "/" + fileKernel;
#ifdef _DEBUG
        std::cout << "\"" << fileKernel << "\" ..";
#endif
        const std::ifstream  file( pathAndName.c_str() );
        assert( file.is_open()
            && "Файл ядра не найден." );
        std::stringstream buffer;
        buffer << file.rdbuf();
        const std::string kernelSC = buffer.str();
#ifdef _DEBUG
    std::cout << " ОК" << std::endl;
#endif

        // create the program
        const std::string kernelSourceCode =
            kernelLibraryCode + "\n\n\n\n\n" +
            "// @include kernel " + pathAndName + "\n" +
            kernelSC;

#ifdef _DEBUG
        // сохраняем полный код ядра в файл
        const std::string fn =
            boost::replace_all_copy( kernelKey, "/", "_" ) + ".debug.cl";
        std::ofstream  out( fn.c_str() );
        out << kernelSourceCode;
        out.close();
#endif

        // @todo optimize Ядра можно загружать уже скомпилированные.
        const cl::Program::Sources  source( 1,  std::make_pair(
            kernelSourceCode.c_str(),  kernelSourceCode.length()
        ) );

        // компилируем каждое ядро в определённом контексте для устройства
#ifdef _DEBUG
        std::cout << "Опции OpenCL для ядра \"" << kernelKey << "\"" <<
            std::endl << commonOptions.str() <<
        std::endl;
#endif

        const cl::Program  program( mContextCL, source );
        try {
            program.build( mDeviceCL,  commonOptions.str().c_str() );

        } catch ( const cl::Error& ex ) {
            std::cerr << "(!) Error: " << ex.what() <<
                "(" << ex.err() << ")" <<
            std:: endl;
            if (ex.err() == CL_BUILD_PROGRAM_FAILURE) {
                std::cerr <<
                    program.getBuildInfo< CL_PROGRAM_BUILD_LOG >( mDeviceCL.front() ) <<
                std::endl;
            }
            throw ex;
        }

        const cl::Kernel  kernel( program,  kernelName.c_str(),  &errorCL );
        mKernelCL[ kernelKey ] = kernel;

    } // for (auto itr

}




template< size_t GLOBAL_SIZE >
inline void Engine::enqueueEventKernelCL(
    const std::string&  key,
    cl::Event*          event
) {
    static const auto EMPTY_WAIT = vectorEventCL_t();
    enqueueEventKernelCL< GLOBAL_SIZE >(
        key,  EMPTY_WAIT,  event
    );
}




template< size_t GLOBAL_SIZE >
inline void Engine::enqueueEventKernelCL(
    const std::string&      key,
    const vectorEventCL_t&  waitEvents,
    cl::Event*              event
) {
    assert( (mKernelCL.find( key ) != mKernelCL.cend())
        && "Ядро OpenCL не найдено." );

    mQueueCL.enqueueNDRangeKernel(
        mKernelCL[ key ],
        cl::NullRange,
        cl::NDRange( GLOBAL_SIZE ),
        cl::NullRange,
        waitEvents.empty() ? nullptr : &waitEvents,
        event
    ); 
}




inline std::string Engine::commonConstantCLKernel() {

    std::ostringstream options;
    options
        // лечим точность
        << std::fixed

        // структуры и методы портулана на С++ станут годным для OpenCL.
        << " -D PORTULAN_AS_OPEN_CL_STRUCT"

        << " -D __DEBUG"
        //<< " -D GPU_OPENCL"

        << " -D WARRIOR_COUNT=" << WARRIOR_COUNT
        << " -D BATTLEFIELD_COUNT=" << BATTLEGROUND_COUNT

        // #! Если для вычислений не используется double, важно передавать
        //    вещественные значения как float. Иначе на драйвере OpenCL 1.2
        //    от Intel - ошибка компиляции.
        << std::scientific

        // точность сравнения значений с плав. точкой
        << " -D PRECISION=" << typelib::PRECISION << "f"

        // @todo Физические и геометрические константы.

        << "";

    return options.str();
}




inline std::string Engine::commonOptionCLKernel() {

    std::ostringstream options;
    options
        // лечим точность для float
        //<< std::fixed

        // предупреждения в ядрах считаем ошибками
        << " -Werror"
#if 0
        // серьёзная оптимизация
        // #i ~10% прирост только с включением опций ниже.
        // @todo optimize Тонкая оптимизация OpenCL.
        //       http://khronos.org/registry/cl/sdk/1.0/docs/man/xhtml/clBuildProgram.html
        << " -cl-fast-relaxed-math"
        << " -cl-mad-enable"
#endif
#if 0
        // внимательная отладка
        // #i Включать только при вылавливании блох: более чем
        //    20-кратное замедление.
        << " -cl-opt-disable"
#endif
        << "";

    return options.str();
}


} // battleground
