namespace battleground {


inline Engine::Engine(
) :
    mLive(),
    mLastUID( 0 ),
    errorCL( CL_SUCCESS )
{
    // �������������� �������� � ������� ������ ��� ������ � OpenCL
    prepareCL();

    // ���������� ���������� ��� ������ ������� � OpenCL
    #include "../world/@/init-buffer-cl.inl"

    // # ���� OpenCL ������ �� ����������.
}




inline Engine::~Engine() {
}




inline void Engine::pulse( int n ) {

    assert( (n > 0)
        && "����� �������� ������ � ����������� ���-��� �������." );

    // ������������ ����������� �� ���� ������� �������
    // # ��� �������� ��������� �������� �� ������ �����.
    // # ������ ������� ���������� ���� ����� �������. ������, �������
    //   ����������� � ����������� ������� - ��. ����. � ������ '*.gv'.
    // # ����������� ��������� ������� �������� ����� ���������.
    // # ������� ����� �������� ��� ��� �������, ��� � ��. ��������. �������,
    //   ����� "����������" ������� ������ ������� ������������� ��. ��������
    //   �� ������� �������, ������� ����� ������� ������� �� ��� �������.
    // # ����� �������� ������������ ������������ ������� (��������,
    //   ������������), ���������:
    //   �������. ����� ������� �������������� *������* ������ �� ��������
    //   ���������. ��������� ��������� ������������� ����� ������� � �������
    //   �� �� ������ ���������� (����) �������. �������� ������: ������
    //   �������� ������ ����� �������, ��������� ���������.

    // ��������� 'n' ������
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

    // @todo fine clEnqueueMigrateMemObjects() ��� ������������ ��������.


    // �������� 'n' �������
    for (int p = 0; p < n; ++p) {

        // # ����� ������� ������� ������ � � ����� ���� �������� -
        //   ����������� (��������������). ��. �������� ����.

        const cl_long pulselive = mLive.pulselive();


        // ���������� ������ ���� ��������� � ���������� ��� ���������������
        // ��� ���������


        // �������������� �������� � �������� �������
        /* - ? �������� �� ������...
        #include "../battleground/clamp-coord/@/begin.inl"
        #include "../warrior/training/single-sword/turn/@/begin.inl"
        queueCL.finish();
        */

        // @todo ...


        // # � ���� ����� ������� ������� ���������.

        // ��� ���������� ������
        mLive.inc( TIMESTEP );

    } // for (int p = 0 ...



    // ������ ���������
    #include "../world/@/read-buffer-cl.inl"
}




inline void Engine::prepareCL() {

    std::vector< cl::Platform >  mPlatformCL;
    cl::Platform::get( &mPlatformCL );
    if ( mPlatformCL.empty() ) {
        throw porte::Exception( "�� ������� �� ������ ���������� � ���������� OpenCL." );
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
    std::cout << "\n������� ���������� OpenCL:\n";
    porte::printCLInfo( mPlatformCL.front()() );
#endif
}




inline void Engine::prepareEmitEvent( const std::string& element ) {
    // # �������� � ������� ������ ���������������� � ������������.

    // @todo ...

    assert( false && "�� �����������." );
}




inline void Engine::compileCLKernel(
    const std::vector< std::string >&  kernelKeys,
    const std::vector< std::string >&  includeHCL,
    const std::string& options
) {
    // # �������� � ������� ������ ���������������� � ������������.

#ifdef _DEBUG
        std::cout << std::endl << std::endl;
#endif

    std::ostringstream commonOptions;
    commonOptions
        // ����� �������� ��� float
        << std::fixed
        // #! ������� ����� ������������� ��������: ���� ������
        //   � helper.hcl, ������� ���������� ��.
        << " " << options
        << commonConstantCLKernel()
        << commonOptionCLKernel()
        << "";

    // ����� ����� ��� ����������� ���� ���������
    std::string kernelLibraryCode = "";

    // ���������� ����� ���������� � ���������
    // (������������ ����� ������ ������)
    // #! ����� ������� �����������.
    std::vector< std::string > hcl = boost::assign::list_of
        ( CL_WORLD_PATH_BATTLEGROUND + "/pragma.hcl" )
        ( CL_WORLD_PATH_BATTLEGROUND + "/restruct.hcl" )
        ( CL_WORLD_PATH_BATTLEGROUND + "/_.hcl" )
    ;
    hcl.insert( hcl.end(), includeHCL.cbegin(), includeHCL.cend() );
    for (auto itr = hcl.cbegin(); itr != hcl.cend(); ++itr) {
        const std::string& pathAndName = *itr;
#ifdef _DEBUG
        const std::string shortName =
            itr->substr( pathAndName.find_last_of( '/' ) + 1 );
        std::cout << "�������� \"" << shortName << "\" ..";
#endif
        const std::ifstream  file( pathAndName.c_str() );
        assert( file.is_open()
            && "���� �� ������." );
        std::stringstream buffer;
        buffer << file.rdbuf();
        kernelLibraryCode +=
            (std::string)"\n\n\n\n\n" +
            "// #include " + pathAndName + "\n" +
            buffer.str();
#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif
    } // for (auto itr = hcl.cbegin(); ...


    // �������� ��������� ���� � ���� ���� � �����������
    for (auto itr = std::begin( kernelKeys ); itr != std::end( kernelKeys ); ++itr) {
        //   # ��������� �� "/" �������� �������� ������ ����.
        const std::string kernelKey = *itr;
        const std::string kernelName =
            itr->substr( itr->find_last_of( '/' ) + 1 );

        // Program Setup
        const std::string fileKernel = kernelKey + ".cl";
        const std::string pathAndName =
            CL_WORLD_PATH_BATTLEGROUND + "/" + fileKernel;
#ifdef _DEBUG
        std::cout << "\"" << fileKernel << "\" ..";
#endif
        const std::ifstream  file( pathAndName.c_str() );
        assert( file.is_open()
            && "���� ���� �� ������." );
        std::stringstream buffer;
        buffer << file.rdbuf();
        const std::string kernelSC = buffer.str();
#ifdef _DEBUG
    std::cout << " ��" << std::endl;
#endif

        // create the program
        const std::string kernelSourceCode =
            kernelLibraryCode + "\n\n\n\n\n" +
            "// @include kernel " + pathAndName + "\n" +
            kernelSC;

#ifdef _DEBUG
        // ��������� ������ ��� ���� � ����
        const std::string fn =
            boost::replace_all_copy( kernelKey, "/", "_" ) + ".debug.cl";
        std::ofstream  out( fn.c_str() );
        out << kernelSourceCode;
        out.close();
#endif

        // @todo optimize ���� ����� ��������� ��� ����������������.
        const cl::Program::Sources  source( 1,  std::make_pair(
            kernelSourceCode.c_str(),  kernelSourceCode.length()
        ) );

        // ����������� ������ ���� � ����������� ��������� ��� ����������
#ifdef _DEBUG
        std::cout << "����� OpenCL ��� ���� \"" << kernelKey << "\"" <<
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
        && "���� OpenCL �� �������." );

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
        // ����� ��������
        << std::fixed

        // ��������� � ������ ��������� �� �++ ������ ������ ��� OpenCL.
        << " -D PORTULAN_AS_OPEN_CL_STRUCT"

        << " -D __DEBUG"
        //<< " -D GPU_OPENCL"

        // ������� �������� �� ������
        #include "../world/@/constant-cl.inl"

        // #! ���� ��� ���������� �� ������������ double, ����� ����������
        //    ������������ �������� ��� float. ����� �� �������� OpenCL 1.2
        //    �� Intel - ������ ����������.
        << std::scientific

        // �������� ��������� �������� � ����. ������
        << " -D PRECISION=" << typelib::PRECISION << "f"

        // @todo ���������� � �������������� ���������.

        << "";

    return options.str();
}




inline std::string Engine::commonOptionCLKernel() {

    std::ostringstream options;
    options
        // ����� �������� ��� float
        //<< std::fixed

        // �������������� � ����� ������� ��������
        << " -Werror"
#if 0
        // ��������� �����������
        // #i ~10% ������� ������ � ���������� ����� ����.
        // @todo optimize ������ ����������� OpenCL.
        //       http://khronos.org/registry/cl/sdk/1.0/docs/man/xhtml/clBuildProgram.html
        << " -cl-fast-relaxed-math"
        << " -cl-mad-enable"
#endif
#if 0
        // ������������ �������
        // #i �������� ������ ��� ������������ ����: ����� ���
        //    20-������� ����������.
        << " -cl-opt-disable"
#endif
        << "";

    return options.str();
}


} // battleground
