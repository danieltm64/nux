// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "Nux",
    products: [
        .library(
            name: "Nux",
            targets: ["Nux"]
        )
    ],
    targets: [
        .systemLibrary(
            name: "CNux",
            path: "Sources/CNux",
            pkgConfig: nil,
            providers: []
        ),
        .target(
            name: "Nux",
            dependencies: [
                "CNux"
            ],
            path: "Sources/Nux",
            cSettings: [
                .headerSearchPath("../../vendor/include"),
                .define("NUXC_STRING_TYPE_STD_U8STRING"),
                .define("NUXC_SWIFT")
            ],
            linkerSettings: [
                .unsafeFlags(["-Lvendor", "-lnux8c"])
            ]
        )
    ]
)
