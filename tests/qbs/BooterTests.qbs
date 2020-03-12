import qbs

CppApplication {
    name: "BooterTests"
    consoleApplication: true

    Group {
        name: "Booter"
        prefix: "../../src/"
        files: [
            "Booter.h",
            "BooterBootable.h",
            "BooterChain.cpp",
            "BooterChain.h",
            "BooterLevel.h",
            "BooterNode.cpp",
            "BooterNode.h",
            "BooterProvider.cpp",
            "BooterProvider.h",
            "BooterStaticBootable.h",
        ]
    }

    Group {
        name: "Tests"
        prefix: "../"
        files: [
            "tests.Booter.cpp",
        ]
        cpp.includePaths:       ["../../src", "../../3rd_party/googletest/googletest/include"]
    }

    Group {
        name: "Google Test Framework"
        prefix: "../../3rd_party/googletest/googletest/"
        files: [
            "src/gtest.cc",
            "src/gtest-death-test.cc",
            "src/gtest-filepath.cc",
            "src/gtest-port.cc",
            "src/gtest-printers.cc",
            "src/gtest-test-part.cc",
            "src/gtest-typed-test.cc",
        ]
        cpp.includePaths: [
            "../../3rd_party/googletest/googletest/include",
            "../../3rd_party/googletest/googletest",
        ]
        cpp.warningLevel: "none"
    }

    files: [
        "main.cpp",
    ]

    cpp.optimization:       "none"
    cpp.debugInformation:   true
    // cpp.warningLevel:       "all"
    cpp.cxxLanguageVersion: "c++14"
    cpp.includePaths:       ["../../src", "../../3rd_party/googletest/googletest/include"]
    cpp.dynamicLibraries:   [ "pthread" ]


    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
