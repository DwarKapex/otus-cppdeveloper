add_compile_options(
        -Wcast-align
        -Wcast-qual
        -Wdeprecated
        -Wdisabled-optimization
        # -Wglobal-constructors
        -Wimplicit-fallthrough
        -Winit-self
        -Wmissing-include-dirs
        -Wnon-virtual-dtor
        -Wnull-dereference
        # -Wold-style-cast
        -Woverloaded-virtual
        -Wpessimizing-move
        -Wpointer-arith
        -Wredundant-decls
        -Wredundant-move
        -Wsign-promo
        -Wuninitialized
        -Wunreachable-code
)

# clang recomendations
if (${CMAKE_CXX_COMPILER} MATCHES ".*clang.*")
        add_compile_options(
            -Wbool-conversion
            -Wcomma
            -Wdeprecated-implementations
            -Wduplicate-method-match
            -Wempty-body
            -Wenum-conversion
            -Wextra-semi
            -Winfinite-recursion
            -Wmacro-redefined
            -Wmove
            -Wnon-literal-null-conversion
            -Wrange-loop-analysis
            -Wstrict-prototypes
            -Wundef
            -Wunreachable-code
        #     -Wweak-vtables
        )
endif()
